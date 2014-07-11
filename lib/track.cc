#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include "Cv.h"

using namespace v8;

Cv cv;

Handle<Value> getRandomCoords3D(const Arguments& args) {
	HandleScope scope;

	Local<Object> obj = Object::New();
	obj->Set(String::NewSymbol("x"), Number::New( 1 + rand() ));
	obj->Set(String::NewSymbol("y"), Number::New( 1 + rand()));
	obj->Set(String::NewSymbol("z"), Number::New( 1 + rand()));
	return scope.Close(obj);
}

Handle<Value> debug(const Arguments& args) {
	HandleScope scope;

	cv.debug();
	return scope.Close(String::NewSymbol("0"));
}

Handle<Value> locatePoint(const Arguments& args) {
	HandleScope scope;
	bool state = false;
	Cordinate point = cv.locatePoint(&state);
	Local<Object> obj = Object::New();
	obj->Set(String::NewSymbol("x"), Number::New( point.x ));
	obj->Set(String::NewSymbol("y"), Number::New( point.y ));
	obj->Set(String::NewSymbol("z"), Number::New( 0 ));
	return scope.Close(obj);
}

void init(Handle<Object> target) {
	target->Set(String::NewSymbol("getRandomCoords3D"),
			FunctionTemplate::New(getRandomCoords3D)->GetFunction());
	target->Set(String::NewSymbol("debug"),
			FunctionTemplate::New(debug)->GetFunction());
	target->Set(String::NewSymbol("locatePoint"),
			FunctionTemplate::New(locatePoint)->GetFunction());

}
NODE_MODULE(track, init)
