#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "Cv.h"

using namespace v8;

Cv cv;

Handle<v8::Value> do_string_convert_to_v8(const std::string& value) {
	return v8::String::New(value.c_str(), value.size());
}

void printUndef() {
	std::cout << "undefined" << std::endl;
}

void call(Cordinate point) {
	/*Local<Function> cb = Local<Function>::Cast(argues[0]);
	const unsigned argc = 1;
	Local<Value> argv[argc] = { Local<Value>::New(String::New("hello world")) };
	cb->Call(Context::GetCurrent()->Global(), argc, argv);*/
	std::cout << point.toString() << std::endl;
}

Handle<Value> debug(const Arguments& args) {
	HandleScope scope;

	cv.debug();
	return scope.Close(String::NewSymbol("0"));
}

Handle<Value> locatePoint(const Arguments& args) {
	HandleScope scope;
	cv.locatePoint(&call, &printUndef);

	/*
	Cordinate point = cv.locatePoint(&print);
	Local<Object> obj = Object::New();
	obj->Set(String::NewSymbol("x"), Number::New( point.x ));
	obj->Set(String::NewSymbol("y"), Number::New( point.y ));
	obj->Set(String::NewSymbol("z"), Number::New( 0 ));
	 */


	return scope.Close(Undefined());
}

Handle<Value> RunCallback(const Arguments& args) {
	HandleScope scope;

	Local<Function> cb = Local<Function>::Cast(args[0]);
	const unsigned argc = 1;
	Local<Value> argv[argc] = { Local<Value>::New(String::New("hello world")) };
	cb->Call(Context::GetCurrent()->Global(), argc, argv);

	return scope.Close(Undefined());
}

void init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("debug"),
			FunctionTemplate::New(debug)->GetFunction());
	exports->Set(String::NewSymbol("locatePoint"),
			FunctionTemplate::New(locatePoint)->GetFunction());
}


NODE_MODULE(track, init)
