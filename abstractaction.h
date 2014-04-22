/**
 * @file abstractaction.h
 * @author Hirokazu Yokoyama
*/

#ifndef _abstractaction__
#define _abstractaction__

#include <iostream>

/**
 * メインの動作を管轄する概要を示すインターフェイスクラスです，
 */
class AbstractAction {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() = 0;
};

class EventArgs{
};

#endif /* _abstractaction__ */
