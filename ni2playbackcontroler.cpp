//
//  ni2playbackcontroler.cpp
//  OniPlayer
//
//  Created by Hirokazu Yokoyama on 2014/02/17.
//
//

#include "ni2playbackcontroler.h"
#include <stdexcept>
using namespace openni;

NI2PlaybackControler::NI2PlaybackControler(NI2Driver* _driver) {
    driver = _driver;
    controler = (PlaybackControl*)driver->device.getPlaybackControl();
    controler->setRepeatEnabled(true);
    isValidate();
}

void NI2PlaybackControler::start() {
    driver->start();
}

void NI2PlaybackControler::stop() {
    driver->stop();
}

int NI2PlaybackControler::getNumberOfFrames() const {
    return controler->getNumberOfFrames(driver->colorStream);
}

int NI2PlaybackControler::getFrameIndex() const {
    return driver->getFrameIndex();
}

void NI2PlaybackControler::seek(int index) {
    if(!driver->isFile()) {
        std::cout << "abort seek because driver is not file." << std::endl;
        return;
    }
    
    bool running = driver->isRunning();
    if(!running) {
        driver->start();
    }
    controler->seek(driver->colorStream, index);
    controler->seek(driver->depthStream, index);
    
    // seek前にセンサが停止中であった場合，センサ動作を停止する．
    if(!running) {
        driver->stop();
    }
}

void NI2PlaybackControler::setRepeatEnabled(bool repeat) {
    controler->setRepeatEnabled(repeat);
}

bool NI2PlaybackControler::isValidate() {
    if(driver == 0) {
        throw std::invalid_argument("driver must be null pointer.");
    }
    if(!driver->isFile()) {
        throw std::invalid_argument("active device is not file.");
    }
    return true;
}