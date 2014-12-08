#-------------------------------------------------
#
# Project created by QtCreator 2014-01-15T12:46:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OniPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageconverter.cpp \
    seeklineedit.cpp \
    action.cpp \
    qdeviceaction.cpp \
    ni2playbackcontroler.cpp \
    ni2driver.cpp

HEADERS  += mainwindow.h \
    imageconverter.h \
    coordpoint.h \
    seeklineedit.h \
    action.h \
    abstractaction.h \
    qdeviceaction.h \
    ni2playbackcontroler.h \
    ni2interfaces.hpp \
    ni2driver.h

FORMS    += mainwindow.ui

CONFIG(debug, debug|release): DEFINES += _Debug

win32 {
OPENCV_DIR = C:/OpenCV/opencv-2.4.9/build/x64/vc11/
OPENCV_VERSION = 249
BOOST_DIR = C:/boost/boost_1_55_0
BOOST_VERSION = vc110-mt-1_55
BOOST_VERSION_DEBUG = vc110-mt-gd-1_55

INCLUDEPATH += $$OPENCV_DIR/include
DEPENDPATH += $$OPENCV_DIR/include
INCLUDEPATH += "C:/Program Files/OpenNI2/Include"
DEPENDPATH += "C:/Program Files/OpenNI2/Include"
INCLUDEPATH += $$BOOST_DIR
DEPENDPATH += $$BOOST_DIR

CONFIG(release, debug|release): LIBS += -L$$OPENCV_DIR/lib -lopencv_core$$OPENCV_VERSION -lopencv_highgui$$OPENCV_VERSION -lopencv_imgproc$$OPENCV_VERSION -lopencv_gpu$$OPENCV_VERSION -lopencv_video$$OPENCV_VERSION -lopencv_objdetect$$OPENCV_VERSION -lopencv_features2d$$OPENCV_VERSION -lopencv_nonfree$$OPENCV_VERSION
else: CONFIG(debug, debug|release): LIBS += -L$$OPENCV_DIR/lib -lopencv_core$${OPENCV_VERSION}d -lopencv_highgui$${OPENCV_VERSION}d -lopencv_imgproc$${OPENCV_VERSION}d -lopencv_gpu$${OPENCV_VERSION}d -lopencv_video$${OPENCV_VERSION}d -lopencv_objdetect$${OPENCV_VERSION}d -lopencv_features2d$${OPENCV_VERSION}d -lopencv_nonfree$${OPENCV_VERSION}d

LIBS += -L"C:/Program Files/OpenNI2/Lib/" -lOpenNI2
PRE_TARGETDEPS += "C:/Program Files/OpenNI2/Lib/OpenNI2.lib"

CONFIG(release, debug|release): LIBS += -L$$BOOST_DIR\lib \
-llibboost_atomic-$$BOOST_VERSION \
-llibboost_chrono-$$BOOST_VERSION \
-llibboost_context-$$BOOST_VERSION \
-llibboost_coroutine-$$BOOST_VERSION \
-llibboost_date_time-$$BOOST_VERSION \
-llibboost_exception-$$BOOST_VERSION \
-llibboost_filesystem-$$BOOST_VERSION \
-llibboost_graph-$$BOOST_VERSION \
-llibboost_iostreams-$$BOOST_VERSION \
-llibboost_locale-$$BOOST_VERSION \
-llibboost_log-$$BOOST_VERSION \
-llibboost_log_setup-$$BOOST_VERSION \
-llibboost_math_c99-$$BOOST_VERSION \
-llibboost_math_c99f-$$BOOST_VERSION \
-llibboost_math_c99l-$$BOOST_VERSION \
-llibboost_math_tr1-$$BOOST_VERSION \
-llibboost_math_tr1f-$$BOOST_VERSION \
-llibboost_math_tr1l-$$BOOST_VERSION \
-llibboost_prg_exec_monitor-$$BOOST_VERSION \
-llibboost_program_options-$$BOOST_VERSION \
-llibboost_python-$$BOOST_VERSION \
-llibboost_random-$$BOOST_VERSION \
-llibboost_regex-$$BOOST_VERSION \
-llibboost_serialization-$$BOOST_VERSION \
-llibboost_signals-$$BOOST_VERSION \
-llibboost_system-$$BOOST_VERSION \
-llibboost_test_exec_monitor-$$BOOST_VERSION \
-llibboost_thread-$$BOOST_VERSION \
-llibboost_timer-$$BOOST_VERSION \
-llibboost_unit_test_framework-$$BOOST_VERSION \
-llibboost_wave-$$BOOST_VERSION \
-llibboost_wserialization-$$BOOST_VERSION

else: CONFIG(debug, debug|release): LIBS += -L$$BOOST_DIR\lib \
-llibboost_atomic-$$BOOST_VERSION_DEBUG \
-llibboost_chrono-$$BOOST_VERSION_DEBUG \
-llibboost_context-$$BOOST_VERSION_DEBUG \
-llibboost_coroutine-$$BOOST_VERSION_DEBUG \
-llibboost_date_time-$$BOOST_VERSION_DEBUG \
-llibboost_exception-$$BOOST_VERSION_DEBUG \
-llibboost_filesystem-$$BOOST_VERSION_DEBUG \
-llibboost_graph-$$BOOST_VERSION_DEBUG \
-llibboost_iostreams-$$BOOST_VERSION_DEBUG \
-llibboost_locale-$$BOOST_VERSION_DEBUG \
-llibboost_log-$$BOOST_VERSION_DEBUG \
-llibboost_log_setup-$$BOOST_VERSION_DEBUG \
-llibboost_math_c99-$$BOOST_VERSION_DEBUG \
-llibboost_math_c99f-$$BOOST_VERSION_DEBUG \
-llibboost_math_c99l-$$BOOST_VERSION_DEBUG \
-llibboost_math_tr1-$$BOOST_VERSION_DEBUG \
-llibboost_math_tr1f-$$BOOST_VERSION_DEBUG \
-llibboost_math_tr1l-$$BOOST_VERSION_DEBUG \
-llibboost_prg_exec_monitor-$$BOOST_VERSION_DEBUG \
-llibboost_program_options-$$BOOST_VERSION_DEBUG \
-llibboost_python-$$BOOST_VERSION_DEBUG \
-llibboost_random-$$BOOST_VERSION_DEBUG \
-llibboost_regex-$$BOOST_VERSION_DEBUG \
-llibboost_serialization-$$BOOST_VERSION_DEBUG \
-llibboost_signals-$$BOOST_VERSION_DEBUG \
-llibboost_system-$$BOOST_VERSION_DEBUG \
-llibboost_test_exec_monitor-$$BOOST_VERSION_DEBUG \
-llibboost_thread-$$BOOST_VERSION_DEBUG \
-llibboost_timer-$$BOOST_VERSION_DEBUG \
-llibboost_unit_test_framework-$$BOOST_VERSION_DEBUG \
-llibboost_wave-$$BOOST_VERSION_DEBUG \
-llibboost_wserialization-$$BOOST_VERSION_DEBUG
}

macx {
LIBS += -L/usr/local/lib
INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
LIBS +=  -lboost_atomic-mt -lboost_chrono-mt -lboost_date_time-mt -lboost_exception-mt -lboost_filesystem-mt -lboost_graph-mt -lboost_iostreams-mt  -lboost_locale-mt -lboost_log-mt -lboost_log_setup-mt -lboost_math_c99-mt -lboost_math_c99f-mt -lboost_math_c99l-mt -lboost_math_tr1-mt -lboost_math_tr1f-mt -lboost_math_tr1l-mt -lboost_prg_exec_monitor-mt -lboost_program_options-mt -lboost_random-mt -lboost_regex-mt -lboost_serialization-mt -lboost_signals-mt -lboost_system-mt -lboost_test_exec_monitor-mt -lboost_thread-mt -lboost_timer-mt -lboost_unit_test_framework-mt -lboost_wave-mt -lboost_wserialization-mt
LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_gpu -lopencv_video -lopencv_objdetect -lopencv_features2d -lopencv_nonfree
LIBS += -ltbb
LIBS += -L$$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Redist/ -lOpenNI2
LIBS += -L$$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Redist/OpenNI2/Drivers -lOniFile -lPS1080 -lPSLink
INCLUDEPATH += $$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Include
DEPENDPATH += $$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Include
}
