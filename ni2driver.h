//
//  ni2driver.h
//  OniPlayer
//
//  Created by Hirokazu Yokoyama on 2014/02/17.
//
//

#ifndef __OniPlayer__ni2driver__
#define __OniPlayer__ni2driver__

#include <iostream>
#include <string>
#include <vector>
#include <OpenNI.h>
#include <opencv2/opencv.hpp>
#include "ni2interfaces.hpp"

/**
 * OpenNI2.0との接続を担う機能を持つクラスです．
 */
class NI2Driver {
    friend class NI2PlaybackControler;
public:
    /**
     * センサ実機を使用するモードで初期化します．
     * @param deviceUri 使用するデバイスへのURI, 未指定の場合，接続されたデバイスのいずれかを自動選択します．
     * @param registrationSupport 
     *   センサデバイスによる光学画像と深度画像の位置補正を行うかどうかを指定． 
     *   true=補整する(初期値), false=補整しない．
     *   ただし，センサデバイスが補整機能を持っていない場合はtrueを指定しても補整機能が有効になりません．
     * @param frameSync 
     *    光学画像と深度画像の入力時に，それぞれを同期させるかどうかを指定．
     *    true=同期する(初期値), false=同期しない
     */
    NI2Driver(const char* deviceUri = openni::ANY_DEVICE,
              bool registrationSupport = true,
              bool frameSync = true);
    
    /**
     * センサ実機を使用し，ファイルに録画するモードで初期化します．
     * @param saveFilePath 保存先のファイルへのパス
     * @param deviceUri 使用するデバイスへのURI, 未指定の場合，接続されたデバイスのいずれかを自動選択します．
     * @param lossyMode true=圧縮録画する(初期値), false=圧縮せずに録画する
     * @param registrationSupport
     *   センサデバイスによる光学画像と深度画像の位置補正を行うかどうかを指定．
     *   true=補整する(初期値), false=補整しない．
     *   ただし，センサデバイスが補整機能を持っていない場合はtrueを指定しても補整機能が有効になりません．
     * @param frameSync
     *    光学画像と深度画像の入力時に，それぞれを同期させるかどうかを指定．
     *    true=同期する(初期値), false=同期しない
     */
    NI2Driver(const std::string& saveFilePath,
              const char* deviceUri = openni::ANY_DEVICE,
              bool lossyMode = true,
              bool registrationSupport = true,
              bool frameSync = true);
    
    /**
     * センサをファイルからシミュレーションするモードで初期化します．
     * @param filePath ファイルへのパス
     */
    NI2Driver(const std::string& filePath);
    
    /** センサの動作を開始します． */
    void start();
    
    /** センサの動作を終了します． */
    void stop();
    
    /**
     * センサが動作中であるかどうかを取得します．
     * @retrun true=動作中， false=停止中
     */
    bool isRunning() const;
    
    bool isRecording() const;
    
    /**
     * 次のフレームを取得します．深度画像は8bitに詰めます．
     * @param *color 光学画像の配列を格納する変数へのポインタ
     * @param *depth 深度画像の配列を格納する変数へのポインタ
     * @param timeout 取得時にタイムアウトする時間
     */
    void getNextFrame(unsigned char* color, unsigned char* depth, int timeout = openni::TIMEOUT_FOREVER);
    
    /**
     * 次のフレームを取得します．深度画像は16ビットのまま
     * @param *color
     * @param *depth
     */
    void getNextFrame(unsigned char* color, short* depth, int timeout = openni::TIMEOUT_FOREVER);
    
    void getNextFrame(cv::Mat& color, cv::Mat& depth, int timeout = openni::TIMEOUT_FOREVER);
    
    void getNextFrame(openni::VideoFrameRef& color, openni::VideoFrameRef& depth, int timeout = openni::TIMEOUT_FOREVER);
    
    /**
     * @return 入力画像の横幅
     */
    int getFrameWidth() const;
    
    /**
     * @return 入力画像の縦幅
     */
    int getFrameHeight() const;
    
    /**
     * @return フレームレート
     */
    int getFps() const;
    
    /**
     * @return 現在のフレーム番号
     */
    int getFrameIndex() const;
    
    /**
     * @return 使用中のデバイスの名前
     */
    std::string getDeviceName() const;
    
    /**
     * @return 使用中のデバイスへのURI
     */
    std::string getDeviceUri() const;
    
    /**
     * @return 使用中のデバイスの製造元
     */
    std::string getDeviceVendor() const;
    
    NI2PlaybackControler* getPlaybackControler();
    
    /**
     * @return 接続されているデバイス情報リスト
     */
    static std::vector<openni::DeviceInfo> getConnectedDeviceInfoList();
    
    /**
     * @return true=ファイルを再生中である， false=実機からである
     */
    bool isFile() const;
    
    /**
     * @return true=センサデバイスが初期化済みで有効である, false=そうでない場合
     */
    bool isValid() const;
    
    ~NI2Driver();
    
protected:
    static bool apiInitialized;
    
private:
    void initialize(const char* deviceUri, bool registrationSupport, bool frameSync);
    void initializeRecorder(const std::string& saveFilePath, bool lossy);
    bool isValidate();
    bool updateFrame(int timeout);
    
    openni::Device device;
    std::vector<openni::VideoStream*> streams;
    openni::VideoStream colorStream;
    openni::VideoStream depthStream;
    openni::VideoFrameRef colorFrame;
    openni::VideoFrameRef depthFrame;
    openni::Recorder recorder;
    bool recording;
    bool running;
};

#endif /* defined(__OniPlayer__ni2driver__) */
