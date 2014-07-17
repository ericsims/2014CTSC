#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <pthread.h>
#include "Cv.h"
#include "Callback.h"

using namespace v8;

Cv cv;
static Callback parent;

Handle<v8::Value> stdStringTov8(const std::string& value) {
	return v8::String::New(value.c_str(), value.size());
}

void printUndef() {
	parent.call("undef\0");
	std::cout << "undefined" << std::endl;
}

void dataCallback(Cordinate point) {
	//parent.call("point: " + point.toString());
	std::cout << point.toString() << std::endl;
}

Handle<Value> debug(const Arguments& args) {
	HandleScope scope;
	cv.debug();
	return scope.Close(String::NewSymbol("0"));
}

Handle<Value> locatePoint(const Arguments& args) {
	HandleScope scope;

	// TODO: http://oguzbastemur.blogspot.com/2013/12/multithread-nodejs.html

	parent.init(*args[0], *args[1]);
	cv.locatePoint(&dataCallback, &printUndef);

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
