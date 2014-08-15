
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"
typedef void (*ErrorCall)(std::string);
typedef void (*dataCall)(std::vector< std::vector<unsigned char> >);
class Serial {
public:
	static void pollBuffer(dataCall returnData, ErrorCall returnError) {
		unsigned int portI = 2, cports[] = {22, 23, 24, 25, 26, 27, 28};
		bool opened = false;
		int n, bdrate = 115200;
		unsigned char buf[4096] = "";

		unsigned int arraySize = sizeof(cports)/sizeof(unsigned int);

		for(portI = 0; portI < arraySize && !opened; portI++) {
			std::cout << portI <<std::endl;
			opened = !RS232_OpenComport(cports[portI], bdrate);
			if(opened) break;
			sleep(1);
		}

		if(opened)
			std::cout << "comport opened" << std::endl;
		else
			returnError("Can not open comport");

		while(true) {
			usleep(1000);
			/*
			std::string s = "123";
			unsigned char *a=new unsigned char[s.size()+1];
			a[s.size()]=0;
			memcpy(a,s.c_str(),s.size());
			RS232_SendBuf(cport_nr, a, s.size());
			 */
			n = RS232_PollComport(cports[portI], buf, 4096);

			if(n > 0) {
				std::vector< std::vector<unsigned char> > lines(1);
				int lineIndex = 0, charIndex = 0;
				for(int i = 0; i < n; i++) {
					if(buf[i] == 10 && lines[lineIndex][charIndex] != 10) { // '\n'
						lines[lineIndex].push_back('\n');
						lineIndex++;
						charIndex = 0;
						if(i < n-1) {
							std::vector<unsigned char> tmp (1,'\0');
							lines.push_back(tmp);
						}
					} else {
						lines[lineIndex].push_back(buf[i]);
						charIndex++;
					}
				}
				returnData(lines);
			}

#ifdef _WIN32
			Sleep(100);
#else
			usleep(100000);  // sleep for 100 milliSeconds
#endif
		}
	}
};
