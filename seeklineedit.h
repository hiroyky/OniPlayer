//
//  seeklineedit.h
//  Medusa
//
//  Created by Hirokazu Yokoyama on 2013/11/15.
//
//

#ifndef SEEKLINEEDIT_H
#define SEEKLINEEDIT_H

#include <iostream>
#include <QLineEdit>
#include "depthsensor.h"
#include "abstractaction.h"

class SeekLineEdit: public QLineEdit {
    Q_OBJECT
public:
    explicit SeekLineEdit(QWidget* parent = 0);
    explicit SeekLineEdit(DepthSensor* _sensor, AbstractAction* _action, QWidget* parent = 0);
    void initialize(DepthSensor* _sensor, AbstractAction* _action);
    int update();
protected:
protected slots:
    void mousePressEvent(QMouseEvent* e);
    void valueChangedEvent();
private:
    bool isInitialized();
    DepthSensor* sensor;
    AbstractAction* action;
    bool connected;
};

#endif /* defined(SEEKLINEEDIT_H) */
