#include <iostream>
#include <v8.h>

using namespace std;
using namespace v8;

void Print(const v8::FunctionCallbackInfo<Value>& argv) {

  cout << "printing ";

  for (int i = 0; i < argv.Length(); i++) {
    String::Utf8Value arg(argv[i]);
    cout << *arg << " ";
  }

  cout << endl;
}

void Add(const v8::FunctionCallbackInfo<Value>& argv) {
  cout << "adding ";
  int sum = 0;
  for (int i = 0; i < argv.Length(); i++) {
    if (argv[i]->IsInt32()) {
      String::Utf8Value arg(argv[i]);
      cout << *arg << " ";
      sum += argv[i]->Int32Value();
    } else {
      String::Utf8Value arg(argv[i]);
      cout << endl << "WARN: can only add integers, therefore ignoring " << *arg;
    }
  }

  cout << "sum: " <<  sum << endl;
  argv.GetReturnValue().Set(Number::New(argv.GetIsolate(), sum));
}

Handle<String> GetScript(Isolate* isolate) {
  string src =
    "'use strict';"
    ""
    "print('Hello', 'World');"
    ""
    "var sum1 = add(1, 2, 3, 4, 4.5, 'four', 5)"
    "  , sum2 = add(11, 22, 33);"
    "add(sum1, sum2);";

  const char *js = src.c_str();
  return String::NewFromUtf8(isolate, js);
}

void AddFunction(Isolate* isolate, Handle<Object> global, const char* name, FunctionCallback callback) {
  global->Set(String::NewFromUtf8(isolate, name), FunctionTemplate::New(isolate, callback)->GetFunction());
}

int main(int argc, const char *argv[]) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope handle_scope(isolate);
  Handle<Context> context = Context::New(isolate);
  Context::Scope context_scope(context);

  // add functions to global context
  Handle<Object> global = context->Global();
  AddFunction(isolate, global, "print", Print);
  AddFunction(isolate, global, "add", Add);

  // compile and run js
  Handle<String> source = GetScript(isolate);
  Handle<Value> result = Script::Compile(source)->Run();

  cout << "Running script returned: " << *String::Utf8Value(result);

  return 0;
}
