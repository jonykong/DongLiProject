#-------------------------------------------------
#
# Project created by QtCreator 2021-05-07T21:59:55
#
#-------------------------------------------------

QT       += core gui network websockets multimedia multimediawidgets
 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DongLiProject
RC_FILE += DongLiProject.rc
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH +=\
    include    \
    include/NetWork

SOURCES += \
        main.cpp \
        MainWindow.cpp \
        DListWidget.cpp \
        DBaseWidget.cpp \
        DProgramItemFrame.cpp \
        VideoFrame.cpp \
        DSingleApplication.cpp \
		DVideoWidget.cpp \
        src/NetWork/DNetworkRequest.cpp \
        src/NetWork/DNetworkManager.cpp \
        src/NetWork/DNetworkManager.cpp \
        src/NetWork/DNetworkRequest.cpp \
        src/NetWork/DNetworkRequestWorker.cpp \
        src/DPlatform.cpp \
        src/DVideoInformation.cpp \
        src/DEventLoop.cpp \
        src/DVideoList.cpp \
        src/DVideoListManagement.cpp \
        src/DDownLoadThread.cpp \
        src/PlayDialog.cpp \
		src/player.cpp \
		src/histogramwidget.cpp \
		src/playercontrols.cpp \
		src/playlistmodel.cpp \
		src/videowidget.cpp
		

HEADERS += \
        MainWindow.h \
        DListWidget.h \
        DBaseWidget.h \
        DProgramItemFrame.h \
        VideoFrame.h \
		DVideoWidget.h \
        DSingleApplication.h \
        include/NetWork/DNetworkDef.h \
        include/NetWork/DNetworkRequest.h \
        include/NetWork/DNetworkManager.h \
        include/NetWork/DNetworkDef.h \
        include/NetWork/DNetworkDef.h \
        include/NetWork/DNetworkManager.h \
        include/NetWork/DNetworkRequest.h \
        include/NetWork/DNetworkRequestWorker.h \
        include/NetWork/DSingleton.h \
        include/DPublicDef.h \
        include/DPublicDef.h \
        include/DPlatform.h \
        include/DPublicDef.h \
        include/DVideoInformation.h \
        include/DEventLoop.h \
        include/DVideoList.h \
        include/DVideoListManagement.h \
        include/DDownLoadThread.h \
        include/PlayDialog.h \
		include/player.h \
		include/histogramwidget.h \
		include/playercontrols.h \
		include/playlistmodel.h \
		include/videowidget.h

FORMS += \
        MainWindow.ui \
        DProgramItemFrame.ui \
        VideoFrame.ui \
    src/PlayDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
