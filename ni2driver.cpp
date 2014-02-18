//
//  ni2driver.cpp
//  OniPlayer
//
//  Created by Hirokazu Yokoyama on 2014/02/17.
//
//

#include "ni2driver.h"
#include "imageconverter.h"
#include <sstream>
#include <stdexcept>
using namespace openni;

bool NI2Driver::apiInitialized = false;

NI2Driver::NI2Driver(const char* deviceUri, bool registrationSupport, bool frameSync) {
    initialize(deviceUri, registrationSupport, frameSync);
    isValidate();
}

NI2Driver::NI2Driver(const std::string& saveFilePath, const char* deviceUri,
                     bool lossyMode, bool registrationSupport, bool frameSync) {
    
    initialize(deviceUri, registrationSupport, frameSync);
    initializeRecorder(saveFilePath, lossyMode);
    isValidate();
}

NI2Driver::NI2Driver(const std::string& filePath) {
    initialize(filePath.c_str(), false, false);
    isValidate();
}

NI2Driver::~NI2Driver() {
    recorder.stop();
    recorder.destroy();
    colorStream.destroy();
    depthStream.destroy();
    device.close();
    openni::OpenNI::shutdown();
    apiInitialized = false;
}

void NI2Driver::start() {
    colorStream.start();
    depthStream.start();
    if(recorder.isValid()) {
        recorder.start();
        recording = true;
    }
    running = true;
}

void NI2Driver::stop() {
    if(recorder.isValid()) {
        recorder.stop();
        recording = false;
    }
    colorStream.stop();
    depthStream.stop();
    running = false;
}

bool NI2Driver::isRunning() const {
    return running;
}

bool NI2Driver::isRecording() const {
    return recording;
}

void NI2Driver::getNextFrame(unsigned char* color, unsigned char* depth, int timeout) {
    updateFrame(timeout);
    color = (unsigned char*)colorFrame.getData();
    depth = (unsigned char*)depthFrame.getData();
}

void NI2Driver::getNextFrame(unsigned char* color, short* depth, int timeout) {
    updateFrame(timeout);
    color = (unsigned char*)colorFrame.getData();
    depth = (short*)depthFrame.getData();
}

void NI2Driver::getNextFrame(cv::Mat &color, cv::Mat &depth, int timeout) {
    updateFrame(timeout);
    color = ImageConverter::toCvColorImageFrom(colorFrame);
    depth = ImageConverter::toCvDepthImage8From(depthFrame);
}

void NI2Driver::getNextFrame(VideoFrameRef &color, VideoFrameRef &depth, int timeout) {
    updateFrame(timeout);
    color = colorFrame;
    depth = depthFrame;
}

int NI2Driver::getFrameWidth() const {
    return colorStream.getVideoMode().getResolutionX();
}

int NI2Driver::getFrameHeight() const {
    return colorStream.getVideoMode().getResolutionY();
}

int NI2Driver::getFps() const {
    return colorStream.getVideoMode().getFps();
}

int NI2Driver::getFrameIndex() const {
    return colorFrame.getFrameIndex();
}

std::string NI2Driver::getDeviceName() const {
    return device.getDeviceInfo().getName();
}

std::string NI2Driver::getDeviceUri() const {
    return device.getDeviceInfo().getUri();
}

std::string NI2Driver::getDeviceVendor() const {
    return device.getDeviceInfo().getVendor();
}

NI2PlaybackControler* NI2Driver::getPlaybackControler() {
    if(!isFile()) {
        throw std::runtime_error("connected device is not from file.");
    }
    
    NI2PlaybackControler* controler = new NI2PlaybackControler(this);
    return controler;
}

std::vector<DeviceInfo> getConnectedDeviceInfoList() {
    Array<DeviceInfo> deviceInfoList;
    OpenNI::enumerateDevices(&deviceInfoList);
    std::vector<DeviceInfo> info(deviceInfoList.getSize());
    for(size_t i = 0; i < (size_t)deviceInfoList.getSize(); ++i) {
        info[i] = deviceInfoList[i];
    }
    return info;
}

bool NI2Driver::isFile() const {
    return device.isFile();
}

bool NI2Driver::isValid() const {
    return true;
}

bool NI2Driver::updateFrame(int timeout) {
    int changeIndex = 0;
    OpenNI::waitForAnyStream(&streams[0], streams.size(), &changeIndex, timeout);
    colorStream.readFrame(&colorFrame);
    depthStream.readFrame(&depthFrame);
    return (colorFrame.isValid() && depthFrame.isValid());
}

void NI2Driver::initialize(const char* deviceUri, bool registrationSupport, bool frameSync) {
    if(!apiInitialized) {
        Status status = OpenNI::initialize();
        if(status == STATUS_OK) {
            apiInitialized = (status == STATUS_OK);
        } else {
            apiInitialized = false;
            std::stringstream ss;
            ss << "openNI initialize is failed. status: " << status;
            throw std::runtime_error(ss.str());
        }
    }
    
    Status status = device.open(deviceUri);
    if(status != STATUS_OK) {
        std::stringstream ss;
        ss << "Device open failed. status: " << status;
        throw std::runtime_error(ss.str());
    }
    
    colorStream.create(device, openni::SENSOR_COLOR);
    depthStream.create(device, openni::SENSOR_DEPTH);
    streams.push_back(&colorStream);
    streams.push_back(&depthStream);
    
    if(registrationSupport
        && device.isImageRegistrationModeSupported(IMAGE_REGISTRATION_DEPTH_TO_COLOR)) {
        device.setImageRegistrationMode(IMAGE_REGISTRATION_DEPTH_TO_COLOR);
    } else {
        device.setImageRegistrationMode(IMAGE_REGISTRATION_OFF);
    }
    device.setDepthColorSyncEnabled(frameSync);
}

void NI2Driver::initializeRecorder(const std::string &saveFilePath, bool lossy) {
    recorder.create(saveFilePath.c_str());
    recorder.attach(colorStream, lossy);
    recorder.attach(depthStream, lossy);
}

bool NI2Driver::isValidate() {
    return true;
}