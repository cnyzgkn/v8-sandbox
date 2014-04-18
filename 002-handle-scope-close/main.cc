#include <iostream>
#include <v8.h>

using namespace v8;

Handle<Array> getItems(int x, int y, int z) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope handle_scope;

  Handle<Array> items = Array::New(3);

  // did we encounter an error? -> bail
  if (items.IsEmpty()){
    std::cerr << "failed to create proper array" << std::endl;
    return Handle<Array>();
  }

  items->Set(0, Integer::New(x));
  items->Set(1, Integer::New(y));
  items->Set(2, Integer::New(z));

  // Close method copies the value of its argument into the enclosing scope,
  // deletes all its local handles and then gives back the new handle copy
  return handle_scope.Close(items);
}


int main(int argc, const char *argv[]) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope handle_scope;
  Handle<Context> context = Context::New();
  Context::Scope context_scope(context);

  Handle<Array> items = getItems(3, 4, 2);

  return 0;
}
