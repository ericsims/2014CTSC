#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include "Cordinates.h"

using namespace v8;


Handle<Value> getRandomCoords3D(const Arguments& args) {

	Cordinates cord;
	HandleScope scope;

	Local<Object> obj = Object::New();
	obj->Set(String::NewSymbol("x"), Number::New( cord.foo() ));
	obj->Set(String::NewSymbol("y"), Number::New( 1 + rand()));
	obj->Set(String::NewSymbol("z"), Number::New( 1 + rand()));
	return scope.Close(obj);
}


void init(Handle<Object> target) {
	target->Set(String::NewSymbol("getRandomCoords3D"),
			FunctionTemplate::New(getRandomCoords3D)->GetFunction());
}
NODE_MODULE(track, init)
