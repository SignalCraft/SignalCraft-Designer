#include "usb/deviceconnection.h"

#include <libusb.h>

DeviceConnection::DeviceConnection() {
    // initialize libusb
    lastError = libusb_init(&context);
    if (lastError)
        return;
    initialized = true;
    // discover device
    libusb_device **list;
    lastError = (int)libusb_get_device_list(context, &list);
    if (lastError < 0)
        return;
    ssize_t cnt = lastError;
    libusb_device *found = NULL;
    for (ssize_t i = 0; i < cnt; i++) {
        libusb_device *device = list[i];
        if (canUseDevice(device)) {
            found = device;
            break;
        }
    }
    // connect to device
    if (!found)
        return;
    lastError = libusb_open(found, &handle);
    if (lastError)
        return;
    connected = true;
    libusb_free_device_list(list, 1); // No error
    // claim interface
    //lastError = libusb_set_auto_detach_kernel_driver(handle, 1); // Error is inconsequential
    lastError = libusb_claim_interface(handle, 0);
    if (lastError)
        return;
    claimedInterface = true;
    interface = 0;
}

DeviceConnection::~DeviceConnection() {
    libusb_close(handle);
    libusb_exit(context);
}

bool DeviceConnection::canUseDevice(libusb_device *device) {
    libusb_device_descriptor d;
    lastError = libusb_get_device_descriptor(device, &d);
    if (lastError)
        return false;
    else
        return (d.idVendor == EXPECTED_VID && d.idProduct == EXPECTED_PID);
}

int DeviceConnection::toggleLED() {
    if (!claimedInterface)
        return -1;
    unsigned char data = 0x80;
    int actualLength;
    lastError = libusb_bulk_transfer(handle, (1 | LIBUSB_ENDPOINT_OUT), &data, 1, &actualLength, 0);
    if (lastError) {
        return lastError;
    }
    return 0;
}

int DeviceConnection::sendProgram() {
    if (!claimedInterface)
        return -1;
    unsigned char *data = new unsigned char[100000]();
    data[0] = 4;
    ((uint32_t*)data)[1] = 99992;
    data[8] = 1;
    data[9] = 2;
    data[10] = 3;
    data[11] = 4;
    data[12] = 5;
    data[99] = 10;
    data[999] = 9;
    data[9999] = 1;
    data[99999] = 1;
    int actualLength;
    lastError = libusb_bulk_transfer(handle, (1 | LIBUSB_ENDPOINT_OUT), data, 100000, &actualLength, 0);
    if (lastError) {
        return lastError;
    }
    lastError = libusb_bulk_transfer(handle, (1 | LIBUSB_ENDPOINT_IN), data, 64, &actualLength, 1000);
    if (lastError) {
        return lastError;
    }
    int sum = *(uint16_t *)(data+1);
    delete[] data;
    return sum;

}
