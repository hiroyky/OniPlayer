//
//  seeklineedit.cpp
//  Medusa
//
//  Created by Hirokazu Yokoyama on 2013/11/15.
//
//

#include "seeklineedit.h"
#include <stdexcept>
#include <QIntValidator>
#include <limits.h>

SeekLineEdit::SeekLineEdit(QWidget* parent): QLineEdit(parent) {
    connected = false;
    initialize(0, 0);
}

SeekLineEdit::SeekLineEdit(NI2PlaybackControler* _controler, AbstractAction* _action, QWidget* parent): QLineEdit(parent) {    
    connected = false;
    initialize(controler, _action);
}

void SeekLineEdit::initialize(NI2PlaybackControler* _controler, AbstractAction* _action) {
    controler = _controler;
    action = _action;
    
    if(controler != 0) {
        int maxFrame = controler->getNumberOfFrames();
        maxFrame = (maxFrame == -1 ? INT_MAX : maxFrame);
        setValidator(new QIntValidator(0, maxFrame));
        setEnabled(true);
    } else {
        setEnabled(false);
    }
        
    if(!connected) {
        connect(this, SIGNAL(editingFinished()), this, SLOT(valueChangedEvent()));
        connected = true;
    }
}

int SeekLineEdit::update() {
    int frameIndex = -1;
    if(isInitialized()) {
        QString str;
        frameIndex = controler->getFrameIndex();
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
        
        action->stop();
        
        controler->start();
        controler->seek(val);
        action->start();
        
        setStyleSheet("background: white;");
    } catch (std::invalid_argument&) {
        setStyleSheet("background: pink;");
    }
}

bool SeekLineEdit::isInitialized() {
    if(controler == 0 || action == 0) {
        return false;
    }
    return true;
}