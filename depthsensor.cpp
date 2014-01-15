#include "depthsensor.h"

DepthSensor::DepthSensor() {
    recording = false;
}

DepthSensor::~DepthSensor() {

}

void DepthSensor::initialize(const char *deviceUri,
                             std::string recordUri,
                             const OniRecordMode recordMode,
                             const Resolution resolutionMode) {
    
    openni::Status status = device.open(deviceUri);
    if(status != openni::STATUS_OK) {
        throw std::runtime_error("device open failed.");
    }

    colorStream.create(device, openni::SENSOR_COLOR);
    depthStream.create(device, openni::SENSOR_DEPTH);
    streams.push_back(&colorStream);
    streams.push_back(&depthStream);
    changeColorStreamResolution((RgbResolutionMode)resolutionMode);
    changeDepthStreamResolution((DepthResolutionMode)resolutionMode);

    if(recordUri != "" && recordMode != NoRecord) {
        recorder.create(recordUri.c_str());
        if (ColorRecord & recordMode) {
            // 0x10 ビットは高圧縮モードのフラグ
            recorder.attach(colorStream, (0x10 & recordMode));
        }
        if (DepthRecord & recordMode) {
            // 0x20 ビットは高圧縮モードのフラグ
            recorder.attach(depthStream, (0x20 & recordMode));
        }
    }
}

void DepthSensor::destroy() {
    recorder.stop();
    recorder.destroy();
    colorStream.destroy();
    depthStream.destroy();
    device.close();
}

void DepthSensor::start() {
    colorStream.start();
    depthStream.start();
    running = true;
}

void DepthSensor::stop() {
    colorStream.stop();
    depthStream.stop();
    running = false;
}

bool DepthSensor::isRunning() {
    return running;
}

void DepthSensor::update(int timeout) {
    openni::VideoFrameRef _colorFrame;
    openni::VideoFrameRef _depthFrame;

    int changedIndex;
    openni::OpenNI::waitForAnyStream(&streams[0], streams.size(), &changedIndex, timeout);
    colorStream.readFrame(&_colorFrame);
    depthStream.readFrame(&_depthFrame);

    if(_colorFrame.isValid()) {
        this->colorFrame = _colorFrame;
    }
    if(_depthFrame.isValid()) {
        this->depthFrame = _depthFrame;
    }
}

bool DepthSensor::isValid() {
    return device.isValid();
}

void DepthSensor::startRecord() {
    if(recorder.isValid()) {
        recorder.start();
        recording = true;
    } else {
        throw  std::runtime_error("DepthSensor recorder is not initialized.");
    }
}

void DepthSensor::stopRecord() {
    recorder.stop();
    recording = false;
}

bool DepthSensor::isRecording() {
    return recording;
}

cv::Mat DepthSensor::getColorCvMat() {
    return ImageConverter::toCvColorImageFrom(colorFrame);
}

cv::Mat DepthSensor::getDepthCvMat() {
    return ImageConverter::toCvDepthImage8From(depthFrame);
}

cv::Mat DepthSensor::getDepthCv16Mat() {
    return ImageConverter::toCvDepthImage16From(depthFrame);
}

CoordPointFrame DepthSensor::getWorldCoordFromDepthAt(int depthX, int depthY) {
    float wx, wy, wz;
    unsigned short* depthArray = (unsigned short* )depthFrame.getData();
    float depthZ = depthArray[depthY * depthFrame.getWidth() + depthX];
    openni::CoordinateConverter::convertDepthToWorld(depthStream,
                                                     (float)depthX, (float)depthY, depthZ,
                                                     &wx, &wy, &wz);
    CoordPointFrame coord;
    coord.depthX = depthX;
    coord.depthY = depthY;
    coord.depthZ = depthZ;
    coord.worldX = wx;
    coord.worldY = wy;
    coord.frameIndex = getDepthFrameIndex();
    return coord;
}
#if 0
QImage DepthSensor::getColorQImage() {
    QImage image = ImageConverter::toQImageFromRgb(colorFrame);
    return image;
}

QImage DepthSensor::getDepthQImage() {
    return ImageConverter::toQImageFromDepth(depthFrame);
}
#endif
void DepthSensor::changeColorStreamResolution(RgbResolutionMode mode) {
    int width, height, framerate;
    switch(mode){
    case Rgb320x240Fps30:
        width = 640;
        height = 480;
        framerate = 30;
        break;
    case Rgb320x240Fps60:
        width = 320;
        height = 240;
        framerate = 60;
        break;
    case Rgb640x480Fps30:
        width = 640;
        height = 480;
        framerate = 30;
        break;
    case Rgb1280x1024Fps30:
        width = 1280;
        height = 1024;
        framerate = 30;
        break;
    default:
        width = 640;
        height = 320;
        framerate = 30;
    }
    changeResolution(colorStream, width, height, framerate);
}

void DepthSensor::changeDepthStreamResolution(DepthResolutionMode mode) {
    int width, height, framerate;
    switch(mode) {
    case Depth320x240Fps30:
        width = 320;
        height = 240;
        framerate = 30;
        break;
    case Depth320x240Fps60:
        width = 320;
        height = 240;
        framerate = 60;
        break;
    case Depth640x480Fps30:
        width = 640;
        height = 480;
        framerate = 30;
        break;
    default:
        width = 640;
        height = 480;
        framerate = 30;
    }
    changeResolution(depthStream, width, height, framerate);
}

int DepthSensor::getColorWidth() {
    return colorStream.getVideoMode().getResolutionX();
}


int DepthSensor::getColorHeight() {
    return colorStream.getVideoMode().getResolutionY();
}


int DepthSensor::getDepthWidth() {
    return depthStream.getVideoMode().getResolutionX();
}


int DepthSensor::getDepthHeight() {
    return depthStream.getVideoMode().getResolutionY();
}

int DepthSensor::getColorFps() {
    openni::VideoMode mode = colorStream.getVideoMode();
    return mode.getFps();
}

int DepthSensor::getDepthFps() {
    openni::VideoMode mode = depthStream.getVideoMode();
    return mode.getFps();
}

void DepthSensor::changeResolution(openni::VideoStream& stream,
                                   int width, int height, int framerate) {
    openni::VideoMode mode = stream.getVideoMode();
    mode.setResolution(width, height);
    mode.setFps(framerate);
    stream.setVideoMode(mode);
}

const openni::DeviceInfo& DepthSensor::getDeviceInfo() {
    return device.getDeviceInfo();
}

const openni::SensorInfo& DepthSensor::getSensorInfo(openni::SensorType type) {
    return *device.getSensorInfo(type);
}

bool DepthSensor::isFile() {
    return device.isFile();
}

const openni::PlaybackControl* DepthSensor::getPlaybackControl() {
    if(!device.isFile()) {
        throw NotFileException("Stream is not from file.");
    }

    return device.getPlaybackControl();    
}

int DepthSensor::getNumberOfColorFrames() {
    const openni::PlaybackControl* control = getPlaybackControl();
    return control->getNumberOfFrames(colorStream);
}

int DepthSensor::getNumberOfDepthFrames() {
    const openni::PlaybackControl* control = getPlaybackControl();
    return control->getNumberOfFrames(depthStream);    
}

int DepthSensor::getDepthFrameIndex() {
    return depthFrame.getFrameIndex();
}

int DepthSensor::getDepthPassedTimeSec() {
    return getDepthFrameIndex() / colorStream.getVideoMode().getFps();
}

void DepthSensor::seek(int index) {
    openni::Status st1, st2;
    seek(index, st1, st2);
}

void DepthSensor::seek(int index, openni::Status& colorStatus, openni::Status& depthStatus) {
    int limit = std::min(getNumberOfColorFrames(), getNumberOfDepthFrames());
    index = (index <= 0 ? 1 : index);
    index = (index >= limit && limit > 0 ? limit : index);
    openni::PlaybackControl* control = (openni::PlaybackControl* )getPlaybackControl();
    colorStatus = control->seek(colorStream, index);
    depthStatus = control->seek(depthStream, index);
}