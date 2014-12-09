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
INCLUDEPATH += C:\opt\include
DEPENDPATH += C:\opt\include
LIBS += -LC:\opt\lib\intel64\vc11 -LC:\opt\lib\intel64
CONFIG(release, debug|release): LIBS +=  -lopencv_core249 -lopencv_highgui249 -lopencv_imgproc249 -lopencv_gpu249 -lopencv_video249 -lopencv_objdetect249 -lopencv_features2d249 -lopencv_nonfree249d
CONFIG(debug, debug|release): LIBS += -lopencv_core249d -lopencv_highgui249d -lopencv_imgproc249d -lopencv_gpu249d -lopencv_video249d -lopencv_objdetect249d -lopencv_features2d249 -lopencv_nonfree249

INCLUDEPATH += "C:/Program Files/OpenNI2/Include/"
DEPENDPATH += "C:/Program Files/OpenNI2/Include/"
LIBS += -L"C:/Program Files/OpenNI2/Lib/" -lOpenNI2
PRE_TARGETDEPS += "C:/Program Files/OpenNI2/Lib/OpenNI2.lib"

BOOST_VERSION = vc110-mt-1_56
BOOST_VERSION_D = vc110-mt-gd-1_56
CONFIG(release, debug|release): LIBS += \
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

CONFIG(debug, debug|release): LIBS += \
-llibboost_atomic-$$BOOST_VERSION_D \
-llibboost_chrono-$$BOOST_VERSION_D \
-llibboost_context-$$BOOST_VERSION_D \
-llibboost_coroutine-$$BOOST_VERSION_D \
-llibboost_date_time-$$BOOST_VERSION_D \
-llibboost_exception-$$BOOST_VERSION_D \
-llibboost_filesystem-$$BOOST_VERSION_D \
-llibboost_graph-$$BOOST_VERSION_D \
-llibboost_iostreams-$$BOOST_VERSION_D \
-llibboost_locale-$$BOOST_VERSION_D \
-llibboost_log-$$BOOST_VERSION_D \
-llibboost_log_setup-$$BOOST_VERSION_D \
-llibboost_math_c99-$$BOOST_VERSION_D \
-llibboost_math_c99f-$$BOOST_VERSION_D \
-llibboost_math_c99l-$$BOOST_VERSION_D \
-llibboost_math_tr1-$$BOOST_VERSION_D \
-llibboost_math_tr1f-$$BOOST_VERSION_D \
-llibboost_math_tr1l-$$BOOST_VERSION_D \
-llibboost_prg_exec_monitor-$$BOOST_VERSION_D \
-llibboost_program_options-$$BOOST_VERSION_D \
-llibboost_python-$$BOOST_VERSION_D \
-llibboost_random-$$BOOST_VERSION_D \
-llibboost_regex-$$BOOST_VERSION_D \
-llibboost_serialization-$$BOOST_VERSION_D \
-llibboost_signals-$$BOOST_VERSION_D \
-llibboost_system-$$BOOST_VERSION_D \
-llibboost_test_exec_monitor-$$BOOST_VERSION_D \
-llibboost_thread-$$BOOST_VERSION_D \
-llibboost_timer-$$BOOST_VERSION_D \
-llibboost_unit_test_framework-$$BOOST_VERSION_D \
-llibboost_wave-$$BOOST_VERSION_D \
-llibboost_wserialization-$$BOOST_VERSION_D
}

macx:LIBS += -L/usr/local/lib
macx:INCLUDEPATH += /usr/local/include
macx:DEPENDPATH += /usr/local/include
macx:LIBS +=  -lboost_atomic-mt -lboost_chrono-mt -lboost_date_time-mt -lboost_exception-mt -lboost_filesystem-mt -lboost_graph-mt -lboost_iostreams-mt  -lboost_locale-mt -lboost_log-mt -lboost_log_setup-mt -lboost_math_c99-mt -lboost_math_c99f-mt -lboost_math_c99l-mt -lboost_math_tr1-mt -lboost_math_tr1f-mt -lboost_math_tr1l-mt -lboost_prg_exec_monitor-mt -lboost_program_options-mt -lboost_random-mt -lboost_regex-mt -lboost_serialization-mt -lboost_signals-mt -lboost_system-mt -lboost_test_exec_monitor-mt -lboost_thread-mt -lboost_timer-mt -lboost_unit_test_framework-mt -lboost_wave-mt -lboost_wserialization-mt
macx: LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_gpu -lopencv_video -lopencv_objdetect -lopencv_features2d -lopencv_nonfree
macx: LIBS += -ltbb

macx: LIBS += -L$$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Redist/ -lOpenNI2
macx: LIBS += -L$$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Redist/OpenNI2/Drivers -lOniFile -lPS1080 -lPSLink
macx:INCLUDEPATH += $$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Include
macx:DEPENDPATH += $$(HOME)/.local/OpenNI-MacOSX-x64-2.2/Include
