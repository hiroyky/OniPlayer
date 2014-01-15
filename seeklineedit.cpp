//
//  seeklineedit.cpp
//  Medusa
//
//  Created by Hirokazu Yokoyama on 2013/11/15.
//
//

#include "seeklineedit.h"

SeekLineEdit::SeekLineEdit(QWidget* parent): QLineEdit(parent) {
    connected = false;
    initialize(0, 0);
}

SeekLineEdit::SeekLineEdit(DepthSensor* _sensor, AbstractAction* _action, QWidget* parent): QLineEdit(parent) {
    connected = false;
    initialize(_sensor, _action);
}

void SeekLineEdit::initialize(DepthSensor* _sensor, AbstractAction* _action) {
    sensor = _sensor;
    action = _action;
    
    if(!connected) {
        connect(this, SIGNAL(editingFinished()), this, SLOT(valueChangedEvent()));
        connected = true;
    }
}

int SeekLineEdit::update() {
    int frameIndex = -1;
    if(isInitialized()) {
        QString str;
        frameIndex = sensor->getDepthFrameIndex();
        str.setNum(frameIndex);
        blockSignals(true);
        setText(str);
        blockSignals(false);
    }
    return frameIndex;
}

void SeekLineEdit::mousePressEvent(QMouseEvent* e) {
    if(isInitialized()) {
        action->stop();
        sensor->stop();
        selectAll();
    }
}

void SeekLineEdit::valueChangedEvent() {
    if(!isInitialized()) {
#if _Debug
        std::cout << "not initialized, return." << std::endl;
#endif
        return; // false
    }
    
    bool isOk;
    int val = text().toInt(&isOk, 10);
    try {
        if(!isOk) {
            throw std::invalid_argument("Entered value is not correct.");
        }
        
        int numOfFrames = sensor->getNumberOfDepthFrames();
        if(numOfFrames > 0 && val >= numOfFrames) {
            val = 1;
        }
        
        action->stop();
        
        openni::Status colorStatus, depthStatus;
        sensor->start();
        sensor->seek(val, colorStatus, depthStatus);
        action->start();
        
        setStyleSheet("background: white;");
    } catch (std::invalid_argument&) {
        setStyleSheet("background: pink;");
    }
}

bool SeekLineEdit::isInitialized() {
    if(sensor == 0 || action == 0) {
        return false;
    }
    if(!sensor->isValid()) {
        return false;
    }
    if(!sensor->isFile()) {
        return false;
    }
    
    return true;
}