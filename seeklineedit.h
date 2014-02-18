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
#include "abstractaction.h"
#include "ni2interfaces.hpp"

class SeekLineEdit: public QLineEdit {
    Q_OBJECT
public:
    explicit SeekLineEdit(QWidget* parent = 0);
    explicit SeekLineEdit(NI2PlaybackControler* _controler, AbstractAction* _action, QWidget* parent = 0);
    void initialize(NI2PlaybackControler* _controler, AbstractAction* _action);
    int update();
protected:
protected slots:
    void mousePressEvent(QMouseEvent* e);
    void valueChangedEvent();
private:
    bool isInitialized();
    NI2PlaybackControler* controler;
    AbstractAction* action;
    bool connected;
};

#endif /* defined(SEEKLINEEDIT_H) */
