#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qimage.h>
#include <string>
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
    void initSensor(const char* devicePath, const std::string& recordPath = "");
    bool isValidateRuning();
    void frameUpdated(const cv::Mat& color, const cv::Mat& depth);

    Action* initAction();
    void stopAction();
    
    void initUiForOniPlaying();
    void initUiForRecoding();
    
    void startSlot();
    void stopSlot();
};

#endif // MAINWINDOW_H
