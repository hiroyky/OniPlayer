#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstring.h>
#include <qimage.h>
#include <qvector.h>
#include <qaction.h>
#include <string>
#include "depthsensor.h"
#include "action.h"
#include "qdeviceaction.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow,
    public openni::OpenNI::DeviceConnectedListener,
    public openni::OpenNI::DeviceDisconnectedListener {
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
    void recordButtonClicked();
    void frameUpdatedSlot();
    void seekSliderChanged(int);
    void triggeredDeviceAction();
    
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
    
    /**
     * センサデバイスを初期化して，動作を開始します．
     * @param devicePath 動作させるセンサデバイス，またはONIファイルへのパス
     * @param recordPath 録画する場合は，録画先のファイルへのパスを指定．録画しない場合は空白
     */
    void initSensor(const char* devicePath, const std::string& recordPath = "");
    
    /**
     * センサデバイス，再生動作を行う上で，各インスタンスなどが適切に設定されているかをチェックします．
     * @exception 不適切な項目があった場合
     * @return true=全て適切に設定されている場合
     */
    bool isValidateRuning();
    
    void frameUpdated(const cv::Mat& color, const cv::Mat& depth);

    /**
     * @return Actionクラスの初期化済みインスタンス
     */
    Action* initAction();
    
    /**
     * 再生動作を停止します．
     */
    void stopAction();
    
    /**
     * UIを何も再生，表示しない状態向けに設定します．
     */
    void initUiForNone();
    
    /**
     * ONIファイルを再生する向けにUIを設定します．
     */
    void initUiForOniPlaying();
    
    /**
     * 接続されたセンサデバイスを表示する向けにUIを設定します．
     */
    void initUiForRealTimeView();
    
    /**
    * 接続中のデバイスリストメニューを更新します．
    */
    void updateDeviceMenu();    

    /**
     * 再生コントロール用のUIの有効無効を一括して設定します．
     * @param tf true=有効にする, false=無効にする
     */
    void setShotButtonsEnabled(bool tf);
    
    /**
     * ショットボタンのUIの有効無効を一括して設定します．
     * @param tf true=有効にする, false=無効にする
     */
    void setPlayControlsEnabled(bool tf);
    
    /**
     * Oniファイルを開くダイアログを表示します．
     * @param path 開いたファイルへのパスを格納する変数
     * @return true=ファイルを開いた，false=キャンセルなどをして開いていない
     */
    bool showOpenOniDialog(QString& path);
    
    bool showSaveOniDialog(QString& path);
    
    void startSlot();
    void stopSlot();

    /**
    * デバイスが接続された時のイベント
    */
    void onDeviceConnected(const openni::DeviceInfo* device);

    /**
    * デバイスが外されたときのイベント
    */
    void onDeviceDisconnected(const openni::DeviceInfo* device);
};

#endif // MAINWINDOW_H
