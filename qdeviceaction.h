#ifndef QDEVICEACTION_H
#define QDEVICEACTION_H

#include <openni.h>
#include <qobject.h>
#include <qaction.h>

/**
* �f�o�C�X���(openni::DeviceInfo)��ێ��ł���QAction�N���X�ł��D
*/
class QDeviceAction: public QAction {
    Q_OBJECT
public:
    QDeviceAction(const openni::DeviceInfo& _device, QObject* parent) : QAction(parent) {       
        device = _device;
        setText(createText());
    }

    /**
    * @param deviceInfo �f�o�C�X���
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