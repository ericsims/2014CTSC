
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"
class Serial {
public:
	static void test() {
		int i, n,
		cport_nr=24,        // /dev/ttyS0 (COM1 on windows)
		bdrate=115200;      // 9600 baud

		unsigned char buf[4096];


		if(RS232_OpenComport(cport_nr, bdrate)) {
			std::cout << "Can not open comport" << std::endl;
		}
		/*
		std::cout<<("asdf")<<std::endl;
		while(true) {
			n = RS232_PollComport(cport_nr, buf, 4095);

			if(n > 0) {
				buf[n] = 0;   // always put a "null" at the end of a string!

				for(i=0; i < n; i++) {
					if(buf[i] < 32) { // replace unreadable control-codes by dots
						buf[i] = '.';
					}
				}
				std::cout << "received %i bytes: %s\n" << std::endl;
			}

#ifdef _WIN32
			Sleep(100);
#else
			usleep(100000);  // sleep for 100 milliSeconds
#endif
		}*/
	}
};
