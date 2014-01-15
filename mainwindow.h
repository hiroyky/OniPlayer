#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qimage.h>
#include "depthsensor.h"
#include "action.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void colorShotButtonClicked();
    void depthShotButtonClicked();
    void colorDepthShotButtonClicked();
    void actionOpened();
    void playButtonClicked();
    void frameUpdatedSlot();
    void seekSliderChanged(int);
    
signals:
    void frameUpdatedSignal();
    
private:
    Ui::MainWindow *ui;
    DepthSensor* sensor;
    Action* action;
    QString openDirPath, saveDirPath;
    cv::Mat colorImage, depthImage;
    
    bool frameCountable;
    bool seekSliderMoving;
    void initSensor(const char* filePath);
    bool isValidateRuning();
    void frameUpdated(const cv::Mat& color, const cv::Mat& depth);
    
    void startSlot();
    void stopSlot();
};

#endif // MAINWINDOW_H
