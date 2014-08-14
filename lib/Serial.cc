
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"
typedef void (*ErrorCall)(std::string);
typedef void (*dataCall)(unsigned char*);
class Serial {
public:
	static void pollBuffer(unsigned char buffer[4096], dataCall, ErrorCall returnError) {
		int i, n,
		cport_nr=27,        // /dev/ttyS0 (COM1 on windows)
		bdrate=9600;      // 9600 baud

		unsigned char buf[4096];


		if(RS232_OpenComport(cport_nr, bdrate)) {
			returnError("Can not open comport");
		}

		while(true) {
			usleep(100);
			/*
			std::string s = "123";
			unsigned char *a=new unsigned char[s.size()+1];
			a[s.size()]=0;
			memcpy(a,s.c_str(),s.size());
			RS232_SendBuf(cport_nr, a, s.size());
			 */
			n = RS232_PollComport(cport_nr, buf, 4095);

			if(n > 0) {
				buf[n] = 0;   // always put a "null" at the end of a string!

				/*for(i=0; i < n; i++) {
					if(buf[i] < 32) { // replace unreadable control-codes by dots
						buf[i] = '.';
					}
				}*/

				dataCall(buf);
				//memcpy(buffer, buf,n);
				std::cout << "received %i bytes: %s    " << buf;
			}

#ifdef _WIN32
			Sleep(100);
#else
			usleep(100000);  // sleep for 100 milliSeconds
#endif
		}
	}
};
