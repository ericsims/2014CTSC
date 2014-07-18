#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <pthread.h>
#include <unistd.h>
#include "Cv.h"
#include "Callback.h"

using namespace v8;

Cv cv;
static Callback parent;
Cordinate currentPoint(0,0);
int aVar = 0;
pthread_t threads[1];

Handle<v8::Value> stdStringTov8(const std::string& value) {
	return v8::String::New(value.c_str(), value.size());
}

void error(std::string err) {
	//parent.call("error");
	std::cout << "\033[1;31m" << "Error: " << err << "\033[0m\n" << err << std::endl;
}

void *print1(void *t) {
	cv.locatePoint(currentPoint, &error);
}

Handle<Value> debug(const Arguments& args) {
	HandleScope scope;
	cv.debug();
	return scope.Close(String::NewSymbol("0"));
}

Handle<Value> locatePoint(const Arguments& args) {
	HandleScope scope;
	parent.init(*args[0], *args[1]);
	pthread_create(&threads[0], NULL, print1, (void *)0 );
	return scope.Close(Undefined());
}

Handle<Value> getDataPoint(const Arguments& args) {
	HandleScope scope;

	Local<Object> obj = Object::New();
	obj->Set(String::NewSymbol("x"), Number::New( currentPoint.getX() ));
	obj->Set(String::NewSymbol("y"), Number::New( currentPoint.getY() ));
	return scope.Close(obj);
}

void init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("debug"),
			FunctionTemplate::New(debug)->GetFunction());
	exports->Set(String::NewSymbol("locatePoint"),
			FunctionTemplate::New(locatePoint)->GetFunction());
	exports->Set(String::NewSymbol("getDataPoint"),
			FunctionTemplate::New(getDataPoint)->GetFunction());
}

NODE_MODULE(track, init)
