#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    sensor = 0;
    action = 0;
        openDirPath = QDir::homePath();
        
    openni::OpenNI::initialize();
        
    connect(ui->colorShotButton, SIGNAL(clicked()), this, SLOT(colorShotButtonClicked()));
    connect(ui->depthShotButton, SIGNAL(clicked()), this, SLOT(depthShotButtonClicked()));
    connect(ui->colorDepthShotButton, SIGNAL(clicked()), this, SLOT(colorDepthShotButtonClicked()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(actionOpened()));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(playButtonClicked()));
    connect(ui->seekSlider, SIGNAL(valueChanged(int)), this, SLOT(seekSliderChanged(int)));
    connect(this, SIGNAL(frameUpdatedSignal()), this, SLOT(frameUpdatedSlot()), Qt::QueuedConnection);
}

MainWindow::~MainWindow() {
    action->stop();
    delete sensor;
    delete ui;
}

void MainWindow::initSensor(const char* filePath) {
    sensor = new DepthSensor();
    sensor->initialize(filePath);
    if(sensor->isValid()) {
        int frameNum = sensor->getNumberOfDepthFrames();
        ui->seekSlider->blockSignals(true);
        ui->frameEdit->blockSignals(true);
        frameCountable = (frameNum > 0);
        ui->frameEdit->setText(QString::number(0));
        ui->frameLabel->setText(QString::number(frameNum));
        ui->seekSlider->setEnabled(frameCountable);
        ui->seekSlider->setMaximum(frameCountable ? frameNum : 0);
        ui->seekSlider->setValue(0);
        ui->seekSlider->blockSignals(false);
        ui->frameEdit->blockSignals(false);
        
        action = new Action(sensor, 100);
        Action::FrameUpdatedEvent func1 = (Action::FrameUpdatedEvent)boost::bind(&MainWindow::frameUpdated, this, _1, _2);
        boost::function<void ()> func2 = boost::bind(&MainWindow::startSlot, this);
        boost::function<void ()> func3 = boost::bind(&MainWindow::stopSlot, this);
        
        action->connectFrameUpdated(func1);
        action->connectStarted(func2);
        action->connectStopped(func3);
        action->start();
        ui->frameEdit->initialize(sensor, action);
    } else {
        QMessageBox box(this);
        box.setText(tr("Depth sensor is not valiable."));
        box.exec();
        return;
    }
}

void MainWindow::colorShotButtonClicked() {
    action->stop();
    try {
        isValidateRuning();
        QString path = QFileDialog::getSaveFileName(this, tr("Save color image"), saveDirPath, "jpeg(*.jpg)|png(*.png)");
        if(path.length() > 0) {
            if(cv::imwrite(path.toStdString(), colorImage)) {
                saveDirPath = QFileInfo(path).dir().absolutePath();
            } else {
                QMessageBox::warning(this, "Saving failed.", "Saving failed.");
            }
        }
    } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void MainWindow::depthShotButtonClicked() {
    action->stop();
    try {
        isValidateRuning();
        QString path = QFileDialog::getSaveFileName(this, tr("Save depth image"), saveDirPath, "png(*.png)");
        if(path.length() > 0) {
            if(cv::imwrite(path.toStdString(), depthImage)) {
                saveDirPath = QFileInfo(path).dir().absolutePath();
            } else {
                QMessageBox::warning(this, "Saving failed.", "Saving failed.");
            }
        }
    } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void MainWindow::colorDepthShotButtonClicked() {
    action->stop();
    try {
        isValidateRuning();
        QString path = QFileDialog::getSaveFileName(this, tr("Save color image"), saveDirPath, "");
        if(path.length() > 0) {
            QString colorPath = path + ".jpg";
            QString depthPath = path + ".png";
            bool tf = cv::imwrite(colorPath.toStdString(), colorImage);
            tf &= cv::imwrite(depthPath.toStdString(), depthImage);
            if(tf) {
                saveDirPath = QFileInfo(path).dir().absolutePath();
            } else {
                QMessageBox::warning(this, "Saving failed.", "Saving failed.");
            }
        }
    } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void MainWindow::actionOpened() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open *.oni"), openDirPath, "oni(*.oni)");
    try {
        if(path.length() > 0) {
            initSensor(path.toStdString().c_str());
            QFileInfo info(path);
            openDirPath = info.dir().absolutePath();
        }
        
    } catch(std::exception& ex) {
        QString str = ex.what();
        str += ":" + path;
        QMessageBox::warning(this, "exception", str);
    }
}

void MainWindow::playButtonClicked() {
    try {
        isValidateRuning();
        if(action->isRunning()) {
            action->stop();
        } else {
            action->start();
        }
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void MainWindow::seekSliderChanged(int val) {
    if(frameCountable) {
        try {
            sensor->start();
            sensor->seek(val);
            ui->frameEdit->update();
        } catch(std::exception& ex) {
            QMessageBox::warning(this, "exception", ex.what());
        }
    }
}

void MainWindow::frameUpdatedSlot() {
    QImage color = ImageConverter::toQImageFrom(colorImage, QImage::Format_RGB888);
    color = color.rgbSwapped();
    color = color.scaled(ui->colorLabel->size());
    QImage depth = ImageConverter::toQImageFrom(depthImage, QImage::Format_Indexed8);
    depth = depth.convertToFormat(QImage::Format_RGB888);
    depth = depth.scaled(ui->depthLabel->size());
    ui->colorLabel->setPixmap(QPixmap::fromImage(color));
    ui->depthLabel->setPixmap(QPixmap::fromImage(depth));
    
    int frameIndex = ui->frameEdit->update();
    if(frameCountable) {
        ui->seekSlider->blockSignals(true);
        ui->seekSlider->setValue(frameIndex);
        ui->seekSlider->blockSignals(false);
    }
}

void MainWindow::frameUpdated(const cv::Mat& color, const cv::Mat& depth) {
    color.copyTo(colorImage);
    depth.copyTo(depthImage);
    emit frameUpdatedSignal();
}

void MainWindow::startSlot() {
    ui->playButton->setText("Pause");
}

void MainWindow::stopSlot() {
    ui->playButton->setText("Play");
}

bool MainWindow::isValidateRuning() {
    if(sensor == 0) {
        throw std::runtime_error("sensor is null pointer.");
    } else if(!sensor->isValid()) {
        throw std::runtime_error("sensor is initialized. but it is not valiable.");
    }
    
    if(action == 0) {
        throw std::runtime_error("action is null pointer.");
    }
    return true;
}