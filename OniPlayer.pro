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
    depthsensor.cpp \
    imageconverter.cpp \
    seeklineedit.cpp \
    action.cpp \
    qdeviceaction.cpp

HEADERS  += mainwindow.h \
    depthsensor.h \
    imageconverter.h \
    coordpoint.h \
    seeklineedit.h \
    action.h \
    abstractaction.h \
    qdeviceaction.h

FORMS    += mainwindow.ui

CONFIG(debug, debug|release): DEFINES += _Debug

win32: INCLUDEPATH += C:/OpenCV/opencv-2.4.6/build/x64/vc10/include
win32: DEPENDPATH += C:/OpenCV/opencv-2.4.6/build/x64/vc10/include
win32: INCLUDEPATH += "C:/Program Files/OpenNI2/Include"
win32: DEPENDPATH += "C:/Program Files/OpenNI2/Include"
win32: INCLUDEPATH += C:/boost/boost_1_54_0
win32: DEPENDPATH += C:/boost/boost_1_54_0

win32: CONFIG(release, debug|release): LIBS += -LC:/OpenCV/opencv-2.4.6/build/x64/vc10/lib/ -lopencv_core246 -lopencv_highgui246 -lopencv_imgproc246 -lopencv_gpu246 -lopencv_video246 -lopencv_objdetect246 -lopencv_features2d246 -lopencv_nonfree246d
else: win32:CONFIG(debug, debug|release): LIBS += -LC:/OpenCV/opencv-2.4.6/build/x64/vc10/lib/ -lopencv_core246d -lopencv_highgui246d -lopencv_imgproc246d -lopencv_gpu246d -lopencv_video246d -lopencv_objdetect246d -lopencv_features2d246 -lopencv_nonfree246

win32: LIBS += -L"C:/Program Files/OpenNI2/Lib/" -lOpenNI2
win32: PRE_TARGETDEPS += "C:/Program Files/OpenNI2/Lib/OpenNI2.lib"

win32: CONFIG(release, debug|release): LIBS += -LC:\boost\boost_1_54_0\stage\lib \
-llibboost_atomic-vc100-mt-1_54 \
-llibboost_chrono-vc100-mt-1_54 \
-llibboost_context-vc100-mt-1_54 \
-llibboost_coroutine-vc100-mt-1_54 \
-llibboost_date_time-vc100-mt-1_54 \
-llibboost_exception-vc100-mt-1_54 \
-llibboost_filesystem-vc100-mt-1_54 \
-llibboost_graph-vc100-mt-1_54 \
-llibboost_iostreams-vc100-mt-1_54 \
-llibboost_locale-vc100-mt-1_54 \
-llibboost_log-vc100-mt-1_54 \
-llibboost_log_setup-vc100-mt-1_54 \
-llibboost_math_c99-vc100-mt-1_54 \
-llibboost_math_c99f-vc100-mt-1_54 \
-llibboost_math_c99l-vc100-mt-1_54 \
-llibboost_math_tr1-vc100-mt-1_54 \
-llibboost_math_tr1f-vc100-mt-1_54 \
-llibboost_math_tr1l-vc100-mt-1_54 \
-llibboost_prg_exec_monitor-vc100-mt-1_54 \
-llibboost_program_options-vc100-mt-1_54 \
-llibboost_python-vc100-mt-1_54 \
-llibboost_random-vc100-mt-1_54 \
-llibboost_regex-vc100-mt-1_54 \
-llibboost_serialization-vc100-mt-1_54 \
-llibboost_signals-vc100-mt-1_54 \
-llibboost_system-vc100-mt-1_54 \
-llibboost_test_exec_monitor-vc100-mt-1_54 \
-llibboost_thread-vc100-mt-1_54 \
-llibboost_timer-vc100-mt-1_54 \
-llibboost_unit_test_framework-vc100-mt-1_54 \
-llibboost_wave-vc100-mt-1_54 \
-llibboost_wserialization-vc100-mt-1_54

else: win32:CONFIG(debug, debug|release): LIBS += -LC:\boost\boost_1_54_0\stage\lib \
-llibboost_atomic-vc100-mt-gd-1_54 \
-llibboost_chrono-vc100-mt-gd-1_54 \
-llibboost_context-vc100-mt-gd-1_54 \
-llibboost_coroutine-vc100-mt-gd-1_54 \
-llibboost_date_time-vc100-mt-gd-1_54 \
-llibboost_exception-vc100-mt-gd-1_54 \
-llibboost_filesystem-vc100-mt-gd-1_54 \
-llibboost_graph-vc100-mt-gd-1_54 \
-llibboost_iostreams-vc100-mt-gd-1_54 \
-llibboost_locale-vc100-mt-gd-1_54 \
-llibboost_log-vc100-mt-gd-1_54 \
-llibboost_log_setup-vc100-mt-gd-1_54 \
-llibboost_math_c99-vc100-mt-gd-1_54 \
-llibboost_math_c99f-vc100-mt-gd-1_54 \
-llibboost_math_c99l-vc100-mt-gd-1_54 \
-llibboost_math_tr1-vc100-mt-gd-1_54 \
-llibboost_math_tr1f-vc100-mt-gd-1_54 \
-llibboost_math_tr1l-vc100-mt-gd-1_54 \
-llibboost_prg_exec_monitor-vc100-mt-gd-1_54 \
-llibboost_program_options-vc100-mt-gd-1_54 \
-llibboost_python-vc100-mt-gd-1_54 \
-llibboost_random-vc100-mt-gd-1_54 \
-llibboost_regex-vc100-mt-gd-1_54 \
-llibboost_serialization-vc100-mt-gd-1_54 \
-llibboost_signals-vc100-mt-gd-1_54 \
-llibboost_system-vc100-mt-gd-1_54 \
-llibboost_test_exec_monitor-vc100-mt-gd-1_54 \
-llibboost_thread-vc100-mt-gd-1_54 \
-llibboost_timer-vc100-mt-gd-1_54 \
-llibboost_unit_test_framework-vc100-mt-gd-1_54 \
-llibboost_wave-vc100-mt-gd-1_54 \
-llibboost_wserialization-vc100-mt-gd-1_54



macx:LIBS += -L/usr/local/Cellar/boost/1.54.0/lib  -lboost_atomic-mt -lboost_chrono-mt\
                                                   -lboost_chrono -lboost_date_time-mt\
                                                   -lboost_date_time -lboost_exception-mt\
                                                   -lboost_exception -lboost_filesystem-mt\
                                                   -lboost_filesystem -lboost_graph-mt\
                                                   -lboost_graph -lboost_iostreams-mt\
                                                   -lboost_iostreams -lboost_locale-mt\
                                                   -lboost_log-mt -lboost_log\
                                                   -lboost_log_setup-mt -lboost_log_setup\
                                                   -lboost_math_c99-mt -lboost_math_c99\
                                                   -lboost_math_c99f-mt -lboost_math_c99f -lboost_math_c99l-mt\
                                                   -lboost_math_c99l -lboost_math_tr1-mt\
                                                   -lboost_math_tr1 -lboost_math_tr1f-mt\
                                                   -lboost_math_tr1f -lboost_math_tr1l-mt\
                                                   -lboost_math_tr1l -lboost_prg_exec_monitor-mt\
                                                   -lboost_prg_exec_monitor -lboost_program_options-mt\
                                                   -lboost_program_options -lboost_python-mt\
                                                   -lboost_python -lboost_random-mt\
                                                   -lboost_random -lboost_regex-mt\
                                                   -lboost_regex -lboost_serialization-mt\
                                                   -lboost_serialization -lboost_signals-mt\
                                                   -lboost_signals -lboost_system-mt\
                                                   -lboost_system -lboost_test_exec_monitor-mt\
                                                   -lboost_test_exec_monitor -lboost_thread-mt\
                                                   -lboost_timer-mt -lboost_timer\
                                                   -lboost_unit_test_framework-mt -lboost_unit_test_framework\
                                                   -lboost_wave-mt -lboost_wave\
                                                   -lboost_wserialization-mt -lboost_wserialization\

macx:INCLUDEPATH += /usr/local/Cellar/boost/1.54.0/include
macx:DEPENDPATH += /usr/local/Cellar/boost/1.54.0/include

macx: LIBS += -L$$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Redist/ -lOpenNI2
macx:INCLUDEPATH += /usr/local/Cellar/opencv/2.4.6.1/include
macx:DEPENDPATH += /usr/local/Cellar/opencv/2.4.6.1/include

macx:INCLUDEPATH += $$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Include
macx:DEPENDPATH += $$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Include

macx: LIBS += -L/usr/local/Cellar/opencv/2.4.6.1/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_gpu -lopencv_video -lopencv_objdetect -lopencv_features2d -lopencv_nonfree

