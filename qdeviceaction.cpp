#include "qdeviceaction.h"

QString QDeviceAction::createText() const {
    return QString("%1 %2").arg(device.getVendor()).arg(device.getName());
}

openni::DeviceInfo QDeviceAction::deviceInfo() const {
    return device;
}