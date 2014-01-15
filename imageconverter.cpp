#include "imageconverter.h"

namespace ImageConverter {

    cv::Mat toCvColorImageFrom(openni::VideoFrameRef colorFrame) {
        openni::VideoMode mode = colorFrame.getVideoMode();
        cv::Mat image = cv::Mat(mode.getResolutionY(), mode.getResolutionX(), CV_8UC3, (char*)colorFrame.getData());
        cv::cvtColor(image, image, CV_RGB2BGR);
        return image;
    }

    cv::Mat toCvDepthImage8From(openni::VideoFrameRef depthFrame, int maxDistance) {
        openni::VideoMode mode = depthFrame.getVideoMode();
        cv::Mat depthImage = cv::Mat(mode.getResolutionY(), mode.getResolutionX(), CV_16U, (char*)depthFrame.getData());
        depthImage.convertTo(depthImage, CV_8U, 255.0 / maxDistance);
        return depthImage;
    }

    cv::Mat toCvDepthImage16From(openni::VideoFrameRef depthFrame) {
        openni::VideoMode mode = depthFrame.getVideoMode();
        return cv::Mat(mode.getResolutionY(), mode.getResolutionX(), CV_16U, (unsigned short*)depthFrame.getData());
    }

    QImage toQImageFromRgb(openni::VideoFrameRef colorFrame) {
        QImage image = QImage((uchar*)colorFrame.getData(),
                      colorFrame.getWidth(), colorFrame.getHeight(),
                      QImage::Format_RGB888);
        image = image.rgbSwapped();
        return image;
    }

    QImage toQImageFromDepth(openni::VideoFrameRef depthFrame) {
        cv::Mat depthMat = toCvDepthImage8From(depthFrame);
        QImage image = QImage(depthMat.data,
                      depthFrame.getWidth(), depthFrame.getHeight(),
                      QImage::Format_Indexed8);
        return image.convertToFormat(QImage::Format_RGB32);
    }

    QImage toQImageFrom(cv::Mat mat, QImage::Format format) {
        return QImage(mat.data, mat.cols, mat.rows, format);
    }
}
