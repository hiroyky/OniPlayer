#ifndef __IMAGECONVERTER_H__
#define __IMAGECONVERTER_H__

#include <OpenNI.h>
#include <QImage>
#include <opencv2/opencv.hpp>>

/**
* 画像形式を変換する関数を定義したヘッダファイルです．
* @author Hirokazu Yokoyama
* @date 2013/09/15
*/

namespace ImageConverter {

    static const int MaxDistance = 9000;

    /**
    * @brief OpenNIの色画像フレームからOpenCVのMatイメージに変換します．
    * @details colorFrame.isValid()の戻り値がTrueであることを事前に確認してください．
    * @param colorFrame 有効な色画像フレーム
    * @return cv::Mat形式の8bit3色カラー画像
    */
    cv::Mat toCvColorImageFrom(openni::VideoFrameRef colorFrame);

    /**
    * @brief OpenNIの深度画像フレー卯からOpenCVの8bitグレースケールMatイメージに変換します．
    * @details 引数に与えるフレームが，有効であることを事前に確認してください．
    * @param depthFrame 有効な深度画像フレーム
    * @param maxDistance 深度測定の最大有効射程距離[mm] (デフォルト値は10000)
    * @return 8bitグレースケールの深度画像
    */
    cv::Mat toCvDepthImage8From(openni::VideoFrameRef depthFrame, int maxDistance = MaxDistance);

    /**
    * @brief OpenNIの深度画像フレー卯からOpenCVの16itグレースケールMatイメージに変換します．
    * @details 引数に与えるフレームが，有効であることを事前に確認してください．
    * @param depthFrame 有効な深度画像フレーム
    * @return 16bitグレースケールの深度画像
    */
    cv::Mat toCvDepthImage16From(openni::VideoFrameRef depthFrame);

    /**
    * @brief 色画像をQImage形式の画像に変換します．
    * @return 変換した画像
    */
    QImage toQImageFromRgb(openni::VideoFrameRef colorFrame);

    /**
    * @brief 距離画像QImage形式の画像に変換します．
    * @return 変換した画像
    */
    QImage toQImageFromDepth(openni::VideoFrameRef depthFrame);

    /**
    * @brief QImage形式の画像に変換します．
    * @param mat
    * @param format 変換後のフォーマット
    */
    QImage toQImageFrom(cv::Mat mat, QImage::Format format);
}
#endif /*  __IMAGECONVERTER_H__ */
