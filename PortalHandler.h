/* 
 * File:   PortalHandler.h
 * Author: christopher
 *
 * Created on 11 August 2014, 17:49
 */

#ifndef PORTALHANDLER_H
#define	PORTALHANDLER_H

#include <stdio.h>
#include "libusb-1.0/libusb.h"
#include <string.h>
#include <stdlib.h> 

#define writeBufferSize  0x21;

class PortalHandler {
public:
	PortalHandler();
	virtual ~PortalHandler();
	libusb_device_handle* connect(void);
	void writeData(char* data);
	libusb_device_handle* deviceHandler;
	void setColour(int r, int g, int b);
	void reset();
	unsigned char* readData(unsigned char* data);
	unsigned char* getFigures();
	void getFiguresInnerTest();
private:
	int deviceId;
};

#endif	/* PORTALHANDLER_H */

