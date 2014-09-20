/* 
 * File:   PortalHandler.cpp
 * Author: christopher
 * 
 * Created on 11 August 2014, 17:49
 */

#include "PortalHandler.h"

PortalHandler::PortalHandler() {
	
	deviceId = 0;

	deviceHandler = connect();
}

PortalHandler::~PortalHandler() {
	
}

unsigned char* PortalHandler::readData(unsigned char* data) {

//	unsigned char* data;
	int retVal = -7;
	int transferred;
	
	while(retVal == -7) {

//		printf("Retval looping\n");
		retVal = libusb_interrupt_transfer(deviceHandler, 129, data, 0x21, &transferred, 500);

//		printf("Error code: %d\n",retVal);
//		printf("Error name: %s\n",libusb_error_name(retVal));
	}
	
//	printf("transferred: %d\n", transferred);
//	printf("Returned string %s\n",data);
//	
//	printf("About to return data\n");
	
	return data;
}

unsigned char PortalHandler::getByte(unsigned int pos) {
	
	char* data = new char[0x21];
	unsigned char* figureData = new unsigned char[0x21];
	data[1] = 'Q';
	char followup;

	if(pos == 0) {
		followup = 0x11;
		if(pos == 0) {
			data[2] = 0x21;
		} else {
			data[2] = followup;
		}
	} else {
		followup = 0x10;
		if(pos == 0) {
			data[2] = 0x20;
		} else {
			data[2] = followup;
		}
	}

//	data[2] = 0x20;
	data[3] = pos;
	
	writeData(data);
	
	figureData = readData(figureData);

	printf("Returned Fig values: %c, %x, %x\n",figureData[0],figureData[1],figureData[2]);

	return figureData[0];
}

unsigned char* PortalHandler::getFigures() {
	
	char* data = new char[0x21];
	unsigned char* figureData = new unsigned char[0x21];
//	unsigned char* returnFigureData = new unsigned char[0x21];

	data[1] = 'Q';
	data[2] = 0x0+0x10;
	data[3] = (unsigned char)1;
	
	writeData(data);

	figureData = readData(figureData);

	printf("Returned values: %c, %x, %x\n",figureData[0],figureData[1],figureData[2]);

	return figureData;
	
}

void PortalHandler::writeData(char* data) {

//	char* data = new char[0x21];
	
//	printf("Data being used: %s\n",data);
	
	data[0] = 0;
//	data[1] = 'R';
	int dataLength = 0x21;
	int retVal;

	int reportNumber = data[0];

	if (reportNumber == 0x0) {
		data++;
		dataLength--;
	}
	
//	libusb_device_handle* tryDeviceHandler = connect();
	
	if (libusb_kernel_driver_active(deviceHandler, 0) == 1) {
		retVal = libusb_detach_kernel_driver(deviceHandler, 0);
		if (retVal < 0) {
			libusb_close(deviceHandler);
		}
	}
	
	retVal = libusb_claim_interface(deviceHandler, 0);
	
	retVal = libusb_control_transfer(deviceHandler,
			LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT,
			0x09,
			(2 << 8) | reportNumber,
			0,
			(unsigned char *)data, dataLength,
			1000);
	
	if(retVal < 0) {
		printf("Returned val %d\n",retVal);
		printf("Got error %s\n",libusb_error_name(retVal));
	}
}

void PortalHandler::setColour(int r, int g, int b) {
	
	char* data = new char[0x21];
	data[1] = 'C';
	data[2] = r;
	data[3] = g;
	data[4] = b;
	writeData(data);
}

void PortalHandler::reset() {
	char* data = new char[0x21];
	data[1] = 'R';
	writeData(data);	
}

libusb_device_handle* PortalHandler::connect(void) {
	
//	printf("Connecting to device\n");
	
	libusb_device** devices;
	libusb_context* context;
	struct libusb_device_handle* tryDeviceHandler;

	libusb_init(&context);
	int devicesCount = libusb_get_device_list(context, &devices);
	
//	printf("Found %d devices\n",devicesCount);
	
	int error;

	struct libusb_device_descriptor descriptor;
	
	for(int i = 0 ; i < devicesCount ; i++) {
		
		int retVal = libusb_open(devices[i], &tryDeviceHandler);
		
		if(retVal < 0) {
			continue;
		}
		
		libusb_get_device_descriptor(devices[i], &descriptor);

		if(descriptor.idVendor == 0x1430 && descriptor.idProduct == 0x150) {
			
			deviceId = i;
			
			return tryDeviceHandler;
			break;
		}
		
	}
}