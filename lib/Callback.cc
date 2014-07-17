#include "Callback.h"

void Callback::init(Local<Value> newArg0, Local<Value> newArg1) {
	arg0 = newArg0;
	arg1 = newArg1;
	cb = Local<Function>::Cast(arg0);
}

void Callback::call(std::string str) {
	const unsigned argc = 1;
	Local<Value> argv[argc] = { Local<Value>::New(v8::String::New(str.c_str(), str.size())) };
	cb->Call(Context::GetCurrent()->Global(), argc, argv);
}
