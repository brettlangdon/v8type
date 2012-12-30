#include <node.h>
#include <v8.h>

using namespace v8;

#define ARRAY String::NewSymbol("array")
#define BOOLEAN String::NewSymbol("boolean")
#define DATE String::NewSymbol("date")
#define FUNCTION String::NewSymbol("function")
#define NUMBER String::NewSymbol("number")
#define REGEXP String::NewSymbol("regexp")
#define STRING String::NewSymbol("string")
#define OBJECT String::NewSymbol("object")
#define UNDEFINED String::NewSymbol("undefined")
#define NULL_TYPE String::NewSymbol("null")

Handle<Value> v8type_of(const Arguments& args){
  HandleScope scope;

  if(args.Length() < 1){
    ThrowException(Exception::TypeError(String::New("v8type.of function requires at least 1 argument")));
    return scope.Close(Undefined());
  }

  if(args[0]->IsArray()){
    return scope.Close(ARRAY);

  } else if(args[0]->IsBoolean()){
    return scope.Close(BOOLEAN);

  } else if(args[0]->IsDate()){
    return scope.Close(DATE);

  } else if(args[0]->IsFunction()){
    return scope.Close(FUNCTION);

  } else if(args[0]->IsNumber()){
    return scope.Close(NUMBER);

  } else if(args[0]->IsString()){
    return scope.Close(STRING);

  } else if(args[0]->IsRegExp()){
    return scope.Close(REGEXP);

  } else if(args[0]->IsUndefined()){
    return scope.Close(UNDEFINED);

  } else if(args[0]->IsNull()){
    return scope.Close(NULL_TYPE);

  } else if(args[0]->IsObject()){
    return scope.Close(OBJECT);
  }

  return scope.Close(Undefined());
}

Handle<Value> v8type_is(const Arguments& args){
  HandleScope scope;

  if(args.Length() < 2){
    ThrowException(Exception::TypeError(String::New("v8type.is function requires at least 2 arguments")));
    return scope.Close(Undefined());
  }

  if(!args[1]->IsString()){
    ThrowException(Exception::TypeError(String::New("v8type.is second argument must be a string")));
    return scope.Close(Undefined());
  }

  Handle<Context> context = Context::New();
  Context::Scope context_scope(context);

  Handle<Value> arguments[] = { args[0] };
  Handle<Value> type = FunctionTemplate::New(v8type_of)->GetFunction()->Call(context->Global(), 1, arguments);


  return scope.Close(Boolean::New(args[1] == type));
}

void init_constants(Handle<Object> target){
  target->Set(String::NewSymbol("ARRAY"), ARRAY);
  target->Set(String::NewSymbol("BOOLEAN"), BOOLEAN);
  target->Set(String::NewSymbol("DATE"), DATE);
  target->Set(String::NewSymbol("FUNCTION"), FUNCTION);
  target->Set(String::NewSymbol("NUMBER"), NUMBER);
  target->Set(String::NewSymbol("REGEXP"), REGEXP);
  target->Set(String::NewSymbol("STRING"), STRING);
  target->Set(String::NewSymbol("OBJECT"), OBJECT);
  target->Set(String::NewSymbol("UNDEFINED"), UNDEFINED);
  target->Set(String::NewSymbol("NULL"), NULL_TYPE);
}

void init_v8type_of(Handle<Object> target){
  target->Set(String::NewSymbol("of"), FunctionTemplate::New(v8type_of)->GetFunction());
}

void init_v8type_is(Handle<Object> target){
  target->Set(String::NewSymbol("is"), FunctionTemplate::New(v8type_is)->GetFunction());
}

void init(Handle<Object> target){
  init_constants(target);
  init_v8type_of(target);
  init_v8type_is(target);
}

NODE_MODULE(v8type, init);
