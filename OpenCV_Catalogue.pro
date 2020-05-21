QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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
    aboutdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CustomWidgets/ClickableLabel/clickablelabel.h \
    CustomWidgets/applyresetbuttonlayout.h \
    CustomWidgets/errorlabel.h \
    CustomWidgets/hybridadjustlayout.h \
    CustomWidgets/lineeditlayout.h \
    CustomWidgets/sliderlayout.h \
    OpenCVFunction/backgroundsubtract.h \
    OpenCVFunction/blur.h \
    OpenCVFunction/cannyedge.h \
    OpenCVFunction/colorpicker.h \
    OpenCVFunction/colorspaces.h \
    OpenCVFunction/erosiondilation.h \
    OpenCVFunction/harriscornerdetector.h \
    OpenCVFunction/histogram.h \
    OpenCVFunction/houghcircles.h \
    OpenCVFunction/houghlines.h \
    OpenCVFunction/imageflip.h \
    OpenCVFunction/thresholding.h \
    Utils/baseconfigwidget.h \
    Utils/captureinputsource.h \
    Utils/constants.h \
    Utils/utils.h \
    aboutdialog.h \
    mainwindow.h

FORMS += \
    aboutdialog.ui \
    mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_stitching -lopencv_videoio -lopencv_video -lopencv_photo -lopencv_bgsegm -lpthread -lX11
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
    assets/liberapay_donate.png \
    assets/opencv_logo.png \
    assets/paypal_donate.png \
    assets/undock.png \
    assets/undock_sel.png
