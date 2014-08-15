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
#include <vector>
#include "Cv.h"
#include "Callback.h"
#include "Serial.cc"
#include "Map.h"

using namespace v8;

Cv cv;
static Callback parent;
Cordinate currentPoint(0,0);
int displacement[2];
Map map;

std::string currentStatus = "null";
int aVar = 0;
pthread_t threads[4];

Handle<v8::Value> stdStringTov8(const std::string& value) {
	return v8::String::New(value.c_str(), value.size());
}

void error(std::string err) {
	//parent.call("error");
	std::cout << "\033[1;31m" << "Error: " << err << "\033[0m\n";
	exit(1);
}

void serialData(std::vector< std::vector<unsigned char> > buf) {
	for (unsigned int lineIndex = 0; lineIndex < buf.size(); lineIndex++) {
		for(unsigned int charIndex = 0; charIndex < buf[lineIndex].size(); charIndex++) {
			cout << buf[lineIndex][charIndex];
		}
	}
}

void *startCvLocate(void *t) {
	cv.locatePoint(currentPoint, &error);
	return (void*)0;
}
void *startCvDisplacement(void *t) {
	cv.displacement(displacement[0], &error);
	return (void*)0;
}
void *startPollBuffer(void *t) {
	Serial::pollBuffer(&serialData, &error);
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
	pthread_create(&threads[0], NULL, startCvLocate, (void *)0 );
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
	//pthread_create(&threads[1], NULL, startCvDisplacement, (void *)0 );
	pthread_create(&threads[2], NULL, startPollBuffer, (void *)0 );
	/*for(int i = 0; i < 180; ++i) {
		ostringstream ss;
		ss << displacement[0];
		ss << ",";
		ss << serialBuffer;
		ss << (round((rand()%100+100) * cos(((i) * 71.0) / 4068.0)));
		ss << ",";
		ss << (round((rand()%100+100) * sin(((i) * 71.0) / 4068.0)));
		ss << "\n";
		map.write(ss.str());
		sleep(1);
	}
	while(true) {
		std::cout << serialBuffer << endl;
		sleep(1);
	}*/
	sleep(120);
	error("times up!");
	//map.close();
	return scope.Close(Undefined());
}

void init(Handle<Object> exports) {
	exports->Set(String::NewSymbol("debug"),
			FunctionTemplate::New(debug)->GetFunction());
	exports->Set(String::NewSymbol("locatePoint"),
			FunctionTemplate::New(locatePoint)->GetFunction());
	exports->Set(String::NewSymbol("getDataPoint"),
			FunctionTemplate::New(getDataPoint)->GetFunction());
	exports->Set(String::NewSymbol("cords"),
			FunctionTemplate::New(cords)->GetFunction());
}

NODE_MODULE(track, init)
