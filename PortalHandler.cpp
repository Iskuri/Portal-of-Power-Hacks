/* 
 * File:   PortalHandler.cpp
 * Author: christopher
 * 
 * Created on 11 August 2014, 17:49
 */

#include "PortalHandler.h"

PortalHandler::PortalHandler() {
	
	connect();
}

PortalHandler::~PortalHandler() {
	
}

void PortalHandler::writeData(char* data) {

//	char* data = new char[0x21];
	
//	printf("Data being used: %s\n",data);
	
	data[0] = 0;
//	data[1] = 'R';
	int dataLength = 0x21;
	int retVal;
//	data[1] = 'C';
//	data[2] = 0xFF; // R
//	data[3] = 0xFF; // G
//	data[4] = 0xFF; // B
	
	int reportNumber = data[0];

	if (reportNumber == 0x0) {
		data++;
		dataLength--;
	}
	
	libusb_device_handle* tryDeviceHandler = connect();
	
	if (libusb_kernel_driver_active(tryDeviceHandler, 0) == 1) {
		retVal = libusb_detach_kernel_driver(tryDeviceHandler, 0);
		if (retVal < 0) {
			libusb_close(tryDeviceHandler);
		}
	}
	
	retVal = libusb_claim_interface(tryDeviceHandler, 0);
	
	retVal = libusb_control_transfer(tryDeviceHandler,
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

libusb_device_handle* PortalHandler::connect(void) {
	
	printf("Connecting to device\n");
	
	struct hid_device_info* deviceList;
	libusb_device** devices;
	libusb_context* context;
	struct libusb_device_handle* tryDeviceHandler;

	libusb_init(&context);
	int devicesCount = libusb_get_device_list(context, &devices);
	
//	printf("Found %d devices\n",devicesCount);
	
	int error;
	
	for(int i = 0 ; i < devicesCount ; i++) {
		
		struct libusb_device_descriptor descriptor;
		struct libusb_interface_descriptor interfaceDescriptor;
		
		libusb_open(devices[i], &tryDeviceHandler);
		
		libusb_get_device_descriptor(devices[i], &descriptor);
		
		if(descriptor.idVendor == 0x1430 && descriptor.idProduct == 0x150) {
//			printf("Found suitable device!\n");
			
			libusb_open(devices[i], &tryDeviceHandler);

//			libusb_device_handle = tryDeviceHandler;
			
//			printf("Set global device variable\n");
			
			return tryDeviceHandler;
			break;
		}
	}
}