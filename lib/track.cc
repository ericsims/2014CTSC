#include <node.h>
#include <v8.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "Cv.h"
#include "Callback.h"
#include "Serial.cc"
#include "Map.h"

using namespace v8;

Cv cv;
static Callback parent;
Cordinate currentPoint(0,0);
Map map;

std::string currentStatus = "null";
int aVar = 0;
pthread_t threads[2];

Handle<v8::Value> stdStringTov8(const std::string& value) {
	return v8::String::New(value.c_str(), value.size());
}

void error(std::string err) {
	//parent.call("error");
	std::cout << "\033[1;31m" << "Error: " << err << "\033[0m\n" << err << std::endl;
}

void *startCV(void *t) {
	cv.locatePoint(currentPoint, &error);
	return (void*)0;
}

void *startSerial(void *t) {
	//serial.test();
	return (void*)0;
}

Handle<Value> debug(const Arguments& args) {
	HandleScope scope;
	cv.debug();
	return scope.Close(String::NewSymbol("0"));
}

Handle<Value> locatePoint(const Arguments& args) {
	HandleScope scope;
	parent.init(*args[0], *args[1]);
	pthread_create(&threads[0], NULL, startCV, (void *)0 );
	return scope.Close(Undefined());
}

Handle<Value> serialTest(const Arguments& args) {
	HandleScope scope;
	//parent.init(*args[0], *args[1]);
	//pthread_create(&threads[0], NULL, startSerial, (void *)0 );
	//while(true);
	Serial::test();
	return scope.Close(Undefined());
}

Handle<Value> getDataPoint(const Arguments& args) {
	HandleScope scope;

	Local<Object> obj = Object::New();
	obj->Set(String::NewSymbol("x"), Number::New( currentPoint.getX() ));
	obj->Set(String::NewSymbol("y"), Number::New( currentPoint.getY() ));
	return scope.Close(obj);
}

Handle<Value> cords(const Arguments& args) {
	HandleScope scope;
	for(int i = 0; i < 180; ++i) {
		ostringstream ss;
		ss << (round((rand()%100+100) * cos(((i + 90) * 71.0) / 4068.0)));
		ss << ",";
		ss << (round((rand()%100+100) * sin(((i + 90) * 71.0) / 4068.0)));
		ss << "\n";
		map.write(ss.str());
	}
	map.close();
	return scope.Close(Undefined());
}

void init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("debug"),
			FunctionTemplate::New(debug)->GetFunction());
	exports->Set(String::NewSymbol("locatePoint"),
			FunctionTemplate::New(locatePoint)->GetFunction());
	exports->Set(String::NewSymbol("getDataPoint"),
			FunctionTemplate::New(getDataPoint)->GetFunction());
	exports->Set(String::NewSymbol("serialTest"),
			FunctionTemplate::New(serialTest)->GetFunction());
	exports->Set(String::NewSymbol("cords"),
			FunctionTemplate::New(cords)->GetFunction());
}

NODE_MODULE(track, init)
