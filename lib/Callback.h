#include <string>
#include <v8.h>
using namespace v8;
class Callback {
public:
	void init(Local<Value>, Local<Value>);
	void call(std::string);
private:
	Local<Value> arg0, arg1;
	Local<Function> cb;
};
