#ifndef DEVICECONNECTION_H
#define DEVICECONNECTION_H

#include <libusb/libusb.h>

class DeviceConnection
{
public:
    DeviceConnection();
    ~DeviceConnection();
    int toggleLED();
protected:
    libusb_context *context = NULL;
    bool initialized = false;
    bool connected = false;
    libusb_device_handle *handle;
    bool claimedInterface = false;
    int interface;
    int lastError = 0;
    static const int EXPECTED_VID = 0x04D8;
    static const int EXPECTED_PID = 0x0053;
    bool canUseDevice(libusb_device *device);
};

#endif // DEVICECONNECTION_H
