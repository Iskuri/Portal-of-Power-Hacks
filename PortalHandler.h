/* 
 * File:   PortalHandler.h
 * Author: christopher
 *
 * Created on 11 August 2014, 17:49
 */

#ifndef PORTALHANDLER_H
#define	PORTALHANDLER_H

#include "hidapi.h"
#include <stdio.h>
#include "libusb-1.0/libusb.h"
#include <string.h>

#define writeBufferSize  0x21;

class PortalHandler {
public:
	PortalHandler();
	virtual ~PortalHandler();
	hid_device* portal;
	libusb_device_handle* connect(void);
	void writeData(char* data);
private:
	struct libusb_device_handle* deviceHandler;
};

#endif	/* PORTALHANDLER_H */

