//
//  action.cpp
//  OniPlayer
//
//  Created by Hirokazu Yokoyama on 2014/01/15.
//
//

#include "action.h"
#include <stdexcept>

using namespace boost::signals2;

Action::Action(DepthSensor* _sensor, int _intervalMsec) {
    sensor = _sensor;
    intervalMsec = _intervalMsec;
    running = false;
    isValidate();
}

void Action::start() {
    if(!sensor->isValid()) {
        throw std::runtime_error("sensor is not still standing by.");
    }
    if(running) {
        throw std::runtime_error("thread is already runnning.");
    }
    
    running = true;
    sensor->start();
    actionThread = boost::thread(boost::bind(&Action::process, this));
    
    if(!startedSignal.empty()) {
        startedSignal();
    }
}

void Action::stop() {
    if(running) {
        running = false;
        actionThread.join();
        sensor->stop();
        
        if(!stoppedSignal.empty()) {
            stoppedSignal();
        }
    }
}

bool Action::isRunning() {
    return running;
}

void Action::process() {
    while(running) {
        sensor->update();
        
        cv::Mat color = sensor->getColorCvMat();
        cv::Mat depth = sensor->getDepthCvMat();
        
        if(!frameUpdatedSignal.empty()) {
            frameUpdatedSignal(color, depth);
        }
        
        boost::this_thread::sleep(boost::posix_time::milliseconds(intervalMsec));
    }
}

connection Action::connectFrameUpdated(FrameUpdatedEvent& func) {
    return frameUpdatedSignal.connect(func);
}

connection Action::connectStarted(boost::function<void ()>& func) {
    return startedSignal.connect(func);
}

connection Action::connectStopped(boost::function<void ()>& func) {
    return stoppedSignal.connect(func);
}

bool Action::isValidate() {
    if(sensor == 0) {
        throw std::runtime_error("depthsensor is null pointer.");
    }
    if(intervalMsec <= 0) {
        throw std::runtime_error("intervalMsec must be a positive number without 0.");
    }
    return true;
}