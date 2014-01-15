#ifndef DEPTHSENSOR_H
#define DEPTHSENSOR_H


#include <iostream>>
#include <string>
#include <OpenNI.h>
#include <QImage>>
#include <opencv2/opencv.hpp>
#include <stdexcept>
#include "ImageConverter.h"
#include "coordpoint.h"
#include "stdexcept"

/**
* カラー画像の解像度
*/
typedef enum RgbResolutionMode {
    Rgb320x240Fps30,
    Rgb320x240Fps60,
    Rgb640x480Fps30,
    Rgb1280x1024Fps30
} RgbResolutionMode;

/**
* 深度画像の解像度
*/
typedef enum DepthResolutionMode {
    Depth320x240Fps30,
    Depth320x240Fps60,
    Depth640x480Fps30
} DepthResolutionMode;

/**
 * 解像度
 */
typedef enum Resolution{
    Resolution320x240Fps30 = 0,
    Resolution640x480Fps30 = 2
} Resolution;

typedef enum OniRecordMode {
    NoRecord = 0,
    ColorRecord = 1,
    DepthRecord = 2,
    ColorAndDepth = ColorRecord + DepthRecord,
    LossyColorRecord = 0x10 + ColorRecord,
    LossyDepthRecord = 0x20 + DepthRecord,
    LossyColorAndDepth = 0x10 + ColorAndDepth,
    ColorAndLoddyDepth = 0x20 + ColorAndDepth,
    LossyColorAndLossyDepth = 0x30 + ColorAndDepth
} OniRecordMode;

class NotFileException: public std::runtime_error {
public:
    NotFileException(const std::string& message): std::runtime_error(message.c_str()) {}
};

/**
* @brief Xtion もしくはKinectと接続を行うクラスです．
*/
class DepthSensor {
public:

    DepthSensor();

    ~DepthSensor();

    /**
    * @brief センサとの接続を初期化します．
    * @detail
    *   カラーと距離データの入力を行うようにセンサを初期化します．
    *   入力値の記録をONIファイルで記録する場合は，recordUriに書き出すファイルへのURIを指定してください．
    *   recordUriが未指定の場合，ONIファイルでの記録は行いません．
    * @param deviceUri 使用するデバイスもしくは再生するONIファイルへのURI，未指定の場合はいずれかのデバイスに接続
    * @param recordUri 入力データを録画する場合での，記録するファイルへのURI，未指定の場合は記録しない
    * @param recordMode ONIファイルへの記録モード，未指定の場合はカラーと距離の両方を記録
    */
    void initialize(const char* deviceUri = openni::ANY_DEVICE,
                    std::string recordUri = "",
                    const OniRecordMode recordMode = ColorAndDepth,
                    const Resolution resolutionMode = Resolution640x480Fps30);
    void destroy();

    void start();

    void stop();

    bool isRunning();
    
    /**
     * OpenNIによってデバイスまたはファイルが利用可能であるかを取得します．
     */
    bool isValid();
    
    /**
       @brief フレームを更新します．
    */
    void update(int timeout = openni::TIMEOUT_FOREVER);

    /**
    * フレームの録画を開映します．
    */
    void startRecord();

    /**
    * フレームの録画を停止します．
    */
    void stopRecord();

    /**
    * フレームが録画中であるかを取得します．
    */
    bool isRecording();

    /**
    * @brief カラー画像をCv::Mat形式で取得します．
    * @return カラー画像
    */
    cv::Mat getColorCvMat();

    /**
    * @brief 深度画像をCv::Mat形式で取得します．
    * @return 深度画像
    */
    cv::Mat getDepthCvMat();

    cv::Mat getDepthCv16Mat();
    
    /**
    * 深度画像のXY座標からワールド座標系の座標値を取得します．
    * ワールド座標系の単位はミリメートルです，
    */
     CoordPointFrame getWorldCoordFromDepthAt(int depthX, int depthY);
#if 0
    /**
    * カラー画像をQImage形式で取得します．
    */
    QImage getColorQImage();

    /**
    * 深度画像をQImage形式で取得します．
    */
    QImage getDepthQImage();
#endif
    /**
    * カラー画像入力の解像度を設定します．
    * @param mode
    */
    void changeColorStreamResolution(RgbResolutionMode mode);

    /**
    * 深度画像の解像度を設定します．
    */
    void changeDepthStreamResolution(DepthResolutionMode mode);

    /**
    * カラーストリームの横幅を取得します．
    */
    int getColorWidth();

    /**
    * カラーストリームの縦幅を取得します．
    */
    int getColorHeight();

    /**
    * 深度ストリームの横幅を取得します．
    */
    int getDepthWidth();

    /**
    * 深度ストリームの縦幅を取得します．
    */
    int getDepthHeight();

    int getColorFps();
    int getDepthFps();

    /**
    * デバイス情報を取得します．
    * @return デバイス情報
    */
    const openni::DeviceInfo& getDeviceInfo();

    /**
    * センサ情報を取得します．
    * @param type 取得するセンサタイプ
    * @return センサ情報
    */
    const openni::SensorInfo& getSensorInfo(openni::SensorType type);

    /**
    * @return ファイルを再生しているかどうか
    */
    bool isFile();

    /**
    * @return PlaybackControlのインスタンス
    * @exception ファイルからの再生でないとき
    */
    const openni::PlaybackControl* getPlaybackControl();

    /**
    * @return カラーフレーム数，多すぎる場合は-1
    */
    int getNumberOfColorFrames();

    /**
    * @return 深度フレーム数，多すぎる場合は-1
    */
    int getNumberOfDepthFrames();

    /**
    * @return 現在の深度フレーム番号
    */
    int getDepthFrameIndex();
    
    /**
    * 現在の経過時間を秒で取得します．
    */
    int getDepthPassedTimeSec();

    /**
    * 指定したフレームにジャンプします．
    * @param index フレーム番号
    */
    void seek(int index);
    
    /**
    * 指定したフレームにジャンプします．
    * @param index フレーム番号
    * @param colorStatus ジャンプの状態を保持する変数
    * @param depthStatus ジャンプの状態を保持する変数
    */
    void seek(int index, openni::Status& colorStatus, openni::Status& depthStatus);

private:
    openni::Device device;
    openni::VideoStream colorStream;
    openni::VideoStream depthStream;
    std::vector<openni::VideoStream*> streams;
    openni::VideoFrameRef colorFrame;
    openni::VideoFrameRef depthFrame;
    openni::Recorder recorder;
    bool recording;
    bool running;
    void changeResolution(openni::VideoStream& stream, int width, int height, int framerate);
};



#endif // DEPTHSENSOR_H

