#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "Cv.h"

using namespace v8;

Cv cv;

Handle<Value> debug(const Arguments& args) {
	HandleScope scope;

	cv.debug();
	return scope.Close(String::NewSymbol("0"));
}

Handle<Value> locatePoint(const Arguments& args) {
	HandleScope scope;
	Cordinate point = cv.locatePoint();
	Local<Object> obj = Object::New();
	obj->Set(String::NewSymbol("x"), Number::New( point.x ));
	obj->Set(String::NewSymbol("y"), Number::New( point.y ));
	obj->Set(String::NewSymbol("z"), Number::New( 0 ));

	Local<Function> cb = Local<Function>::Cast(args[0]);
	const unsigned argc = 1;
	stringstream ss; //create a stringstream
	ss << point.x; //add number to the stream

	Local<Value> argv[argc] = { Local<Value>::New(String::New( "asdf" )) };
	cb->Call(Context::GetCurrent()->Global(), argc, argv);

	return scope.Close(obj);
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
