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
	
	double flashCount = 0;
	
//	portalHandler.reset();
	
	while(true) {
		
		double flashColour = abs((long)(sin((double)flashCount)*0xFF));
		
		unsigned char* figureInfo = portalHandler.getFigures();
		
		if(figureInfo[0] == 'S' && figureInfo[1] != 0) {
			
			for(int i = 0 ; i < 0x40 ; i++) {
				portalHandler.getByte(i);
			}
		}
		
		if((int)figureInfo[1] != 0 ) {
			portalHandler.setColour(0,(int)flashColour,0);
		} else {
			portalHandler.setColour((int)flashColour,0,0);
		}
		
//		printf("Got figures\n");
		
		flashCount+=0.1;
		usleep(20000);
	}
	
	return 0;
}