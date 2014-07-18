#include <string>
using namespace std;
class Cordinate {
public:
	Cordinate(int, int);
	string toString();
	int getX();
	int getY();
private:
	int x;
	int y;
};
