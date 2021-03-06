#include <v8.h>

using namespace v8;

int main(int argc, const char *argv[]) {
  Isolate* isolate = Isolate::GetCurrent();

  HandleScope handle_scope(isolate);
  Handle<Context> context = Context::New(isolate);
  Context::Scope context_scope(context);

  Handle<String> source = String::NewFromUtf8(isolate, "'Hello, World! ' + (2000 + 14)");
  Handle<Script> script = Script::Compile(source);
  Handle<Value> result  = script->Run();

  String::Utf8Value utf8(result);
  printf("%s\n", *utf8);
  return 0;
}
