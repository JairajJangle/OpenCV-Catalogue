QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomWidgets/ClickableLabel/clickablelabel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CustomWidgets/ClickableLabel/clickablelabel.h \
    OpenCVFunction/colorpicker.h \
    OpenCVFunction/colorspaces.h \
    OpenCVFunction/erosiondilation.h \
    OpenCVFunction/imageflip.h \
    OpenCVFunction/thresholding.h \
    Utils/baseconfigwidget.h \
    Utils/captureinputsource.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_stitching -lopencv_videoio -lopencv_video -lopencv_photo -lpthread -lX11 -lbluetooth -lbluetooth  -lmysqlclient -lpthread
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    README.md \
    assets/demo_video.gif \
    assets/done.png \
    assets/done_sel.png \
    assets/info.png \
    assets/info_sel.png \
    assets/opencv_logo.png
