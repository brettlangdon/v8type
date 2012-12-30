#include <node.h>
#include <v8.h>

using namespace v8;

#define ARRAY String::NewSymbol("array")
#define BOOLEAN String::NewSymbol("boolean")
#define BOOLEAN_OBJECT String::NewSymbol("boolean_object")
#define DATE String::NewSymbol("date")
#define FUNCTION String::NewSymbol("function")
#define NUMBER String::NewSymbol("number")
#define NUMBER_OBJECT String::NewSymbol("number_object")
#define REGEXP String::NewSymbol("regexp")
#define STRING String::NewSymbol("string")
#define STRING_OBJECT String::NewSymbol("string_object")
#define OBJECT String::NewSymbol("object")
#define UNDEFINED String::NewSymbol("undefined")
#define NULL_TYPE String::NewSymbol("null")
#define PRIMITIVE String::NewSymbol("primitive")

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

  } else if(args[0]->IsBooleanObject()){
    return scope.Close(BOOLEAN_OBJECT);

  } else if(args[0]->IsDate()){
    return scope.Close(DATE);

  } else if(args[0]->IsFunction()){
    return scope.Close(FUNCTION);

  } else if(args[0]->IsNumber()){
    return scope.Close(NUMBER);

  } else if(args[0]->IsNumberObject()){
    return scope.Close(NUMBER_OBJECT);

  } else if(args[0]->IsString()){
    return scope.Close(STRING);

  } else if(args[0]->IsStringObject()){
    return scope.Close(STRING_OBJECT);

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

Handle<Value> v8type_instance(const Arguments& args){
  HandleScope scope;

  if(args.Length() < 2){
    ThrowException(Exception::TypeError(String::New("v8type.instance function requires at least 2 arguments")));
    return scope.Close(Undefined());
  }

  if(!args[1]->IsString()){
    ThrowException(Exception::TypeError(String::New("v8type.instance second argument must be a string")));
    return scope.Close(Undefined());
  }

  Handle<Context> context = Context::New();
  Context::Scope context_scope(context);

  Handle<Value> arguments[] = { args[0] };
  Handle<Value> type = FunctionTemplate::New(v8type_of)->GetFunction()->Call(context->Global(), 1, arguments);

  if(args[1] == type){
    return scope.Close(Boolean::New(true));
  }

  if(args[1]->ToString() == OBJECT){
    if(type == ARRAY or type == FUNCTION or type == DATE or type == REGEXP or type == STRING_OBJECT
       or type == BOOLEAN_OBJECT or type == NUMBER_OBJECT){
      return scope.Close(Boolean::New(true));
    }
  } else if(args[1]->ToString() == PRIMITIVE){
    if(type == NUMBER or type == BOOLEAN or type == STRING){
      return scope.Close(Boolean::New(true));
    }
  } else if(args[1]->ToString() == NUMBER and type == NUMBER_OBJECT){
    return scope.Close(Boolean::New(true));
  } else if(args[1]->ToString() == STRING and type == STRING_OBJECT){
    return scope.Close(Boolean::New(true));
  } else if(args[1]->ToString() == BOOLEAN and type == BOOLEAN_OBJECT){
    return scope.Close(Boolean::New(true));
  }

  return scope.Close(Boolean::New(false));
}

void init_constants(Handle<Object> target){
  target->Set(String::NewSymbol("ARRAY"), ARRAY);
  target->Set(String::NewSymbol("BOOLEAN"), BOOLEAN);
  target->Set(String::NewSymbol("BOOLEAN_OBJECT"), BOOLEAN_OBJECT);
  target->Set(String::NewSymbol("DATE"), DATE);
  target->Set(String::NewSymbol("FUNCTION"), FUNCTION);
  target->Set(String::NewSymbol("NUMBER"), NUMBER);
  target->Set(String::NewSymbol("NUMBER_OBJECT"), NUMBER_OBJECT);
  target->Set(String::NewSymbol("REGEXP"), REGEXP);
  target->Set(String::NewSymbol("STRING"), STRING);
  target->Set(String::NewSymbol("STRING_OBJECT"), STRING_OBJECT);
  target->Set(String::NewSymbol("OBJECT"), OBJECT);
  target->Set(String::NewSymbol("UNDEFINED"), UNDEFINED);
  target->Set(String::NewSymbol("NULL"), NULL_TYPE);
  target->Set(String::NewSymbol("PRIMITIVE"), PRIMITIVE);
}

void init_v8type_of(Handle<Object> target){
  target->Set(String::NewSymbol("of"), FunctionTemplate::New(v8type_of)->GetFunction());
}

void init_v8type_is(Handle<Object> target){
  target->Set(String::NewSymbol("is"), FunctionTemplate::New(v8type_is)->GetFunction());
}

void init_v8type_instance(Handle<Object> target){
  target->Set(String::NewSymbol("instance"), FunctionTemplate::New(v8type_instance)->GetFunction());
}

void init(Handle<Object> target){
  init_constants(target);
  init_v8type_of(target);
  init_v8type_is(target);
  init_v8type_instance(target);
}

NODE_MODULE(v8type, init);
