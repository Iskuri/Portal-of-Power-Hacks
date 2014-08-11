/* 
 * File:   main.cpp
 * Author: christopher
 *
 * Created on 10 August 2014, 21:09
 */

#include <cstdlib>
#include "PortalHandler.h"
//#include "PortalHandler.cpp"
#include <stdio.h>
#include<sys/types.h>
#include<iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

	PortalHandler* portalHandler;

	printf("Starting interface\n");
	
//	portalHandler->connect();

	int a = clock();
	int b = time(NULL);
	int c = getpid();
	

	//ignore this later
	a=a-b;  a=a-c;  a=a^(c >> 13);
	b=b-c;  b=b-a;  b=b^(a << 8);
	c=c-a;  c=c-b;  c=c^(b >> 13);
	a=a-b;  a=a-c;  a=a^(c >> 12);
	b=b-c;  b=b-a;  b=b^(a << 16);
	c=c-a;  c=c-b;  c=c^(b >> 5);
	a=a-b;  a=a-c;  a=a^(c >> 3);
	b=b-c;  b=b-a;  b=b^(a << 10);
	c=c-a;  c=c-b;  c=c^(b >> 15);
	
	srand(c);
	
	char* data = new char[0x21];
	
//	data[1] = 'C';
//	data[2] = 0x00; // R
//	data[3] = 0x00; // G
//	data[4] = 0xFF; // B
//	portalHandler->writeData(data);
	
//	while(true) {
		data[1] = 'C';
		data[2] = 0 + (rand() % (int)(255 - 0 + 1));
		data[3] = 0 + (rand() % (int)(255 - 0 + 1));
		data[4] = 0 + (rand() % (int)(255 - 0 + 1));
		portalHandler->writeData(data);		
//	}
	
	return 0;
}