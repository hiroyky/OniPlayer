//
//  action.h
//  OniPlayer
//
//  Created by Hirokazu Yokoyama on 2014/01/15.
//
//

#ifndef __OniPlayer__action__
#define __OniPlayer__action__

#include <iostream>
#ifndef Q_MOC_RUN
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/signals2/signal.hpp>
#endif
#include "depthsensor.h"
#include "abstractaction.h"

class Action: public AbstractAction {
public:
    typedef boost::function<void (const cv::Mat&, const cv::Mat&)> FrameUpdatedEvent;
    
    Action(DepthSensor* _sensor, int _intervalMsec);
    void start();
    void stop();
    boost::signals2::connection connectFrameUpdated(FrameUpdatedEvent& func);
    boost::signals2::connection connectStarted(boost::function<void ()>& func);
    boost::signals2::connection connectStopped(boost::function<void ()>& func);
    bool isRunning();
    
protected:
    void process();
private:
    boost::thread actionThread;
    DepthSensor* sensor;
    int intervalMsec;
    bool isValidate();
    bool running;
    boost::signals2::signal<void (const cv::Mat&, const cv::Mat&)> frameUpdatedSignal;
    boost::signals2::signal<void ()> startedSignal;
    boost::signals2::signal<void ()> stoppedSignal;
};

#endif /* defined(__OniPlayer__action__) */
