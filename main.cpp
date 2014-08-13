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
#include <math.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

	PortalHandler portalHandler;

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
	
	double flashCount = 0;
	
//	portalHandler.reset();
	
	while(true) {
		
		double flashColour = abs((long)(sin((double)flashCount)*0xFF));

//		printf("Setting colour\n");
		portalHandler.setColour((int)flashColour,0,0);
		
//		printf("Reading data\n");
		
		unsigned char* figureInfo = portalHandler.getFigures();
		
//		printf("Got figures\n");
		
		flashCount+=0.1;
		usleep(70000);
	}
	
	return 0;
}