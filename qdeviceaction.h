#ifndef QDEVICEACTION_H
#define QDEVICEACTION_H

#include <openni.h>
#include <qobject.h>
#include <qaction.h>

/**
* デバイス情報(openni::DeviceInfo)を保持できるQActionクラスです．
*/
class QDeviceAction: public QAction {
    Q_OBJECT
public:
    QDeviceAction(const openni::DeviceInfo& _device, QObject* parent) : QAction(parent) {       
        device = _device;
        setText(createText());
    }

    /**
    * @param deviceInfo デバイス情報
    * @param icon
    * @param *parent
    */
    QDeviceAction(const openni::DeviceInfo& _device, QIcon& icon, QObject* parent) : QAction(icon, tr(""), parent) {
        device = _device;
        setText(createText());
    }

    openni::DeviceInfo deviceInfo() const;

private:
    QString createText() const;
    openni::DeviceInfo device;
};

#endif /*QDEVICEACTION_H*/