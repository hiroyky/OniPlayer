//
//  ni2playbackcontroler.h
//  OniPlayer
//
//  Created by Hirokazu Yokoyama on 2014/02/17.
//
//

#ifndef __OniPlayer__ni2playbackcontroler__
#define __OniPlayer__ni2playbackcontroler__

#include <iostream>
#include <OpenNI.h>
#include "ni2interfaces.hpp"

/**
 * ONIファイルの再生コントロールを行うクラスです．
 */
class NI2PlaybackControler {
public:
    /**
     * @param _driver 初期化済みのセンサインスタンスへのポインタ
     */
    NI2PlaybackControler(NI2Driver* _driver);
    
    /**
     * @return ファイルの総フレーム数，多すぎるなど測定不能な場合は-1
     */
    int getNumberOfFrames() const;
    
    /**
     * @return 現在のフレーム番号
     */
    int getFrameIndex() const;
    
    /**
     * フレームに移動します．
     * @param index 移動先のフレーム番号
     */
    void seek(int index);
    
    /**
     * 繰り返し再生するかどうかを指定します．
     * @param repeat true=繰り返す， false=繰り返さない
     */
    void setRepeatEnabled(bool repeat);
    
private:
    NI2Driver* driver;
    bool isValidate();
    openni::PlaybackControl* controler;
};

#endif /* defined(__OniPlayer__ni2playbackcontroler__) */
