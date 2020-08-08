QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS+= -std=c++17
QMAKE_LFLAGS +=  -std=c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

linux-g++ | linux-g++-64 | linux-g++-32 {
    INCLUDEPATH += /usr/local/include/opencv4
    LIBS += -L/usr/local/lib \
            -lopencv_core \
            -lopencv_imgcodecs \
            -lopencv_highgui \
            -lopencv_imgproc \
            -lopencv_stitching \
            -lopencv_videoio \
            -lopencv_video \
            -lopencv_photo \
            -lopencv_bgsegm \
            -lpthread \
            -lX11
}

win32 {
    INCLUDEPATH += D:\Softwares\opencv_installation\opencv\build\include
    LIBS += -LD:\Softwares\opencv_installation\opencv\build\bin \
            -lopencv_core440 \
            -lopencv_imgcodecs440 \
            -lopencv_highgui440 \
            -lopencv_imgproc440 \
            -lopencv_stitching440 \
            -lopencv_videoio440 \
            -lopencv_video440 \
            -lopencv_photo440 \
            -lopencv_features2d440 \
            -lopencv_calib3d440 \
            -lopencv_bgsegm440
}

SOURCES += \
    CustomWidgets/ChainMenuWidget/chainmenuwidget.cpp \
    CustomWidgets/ClickableLabel/clickablelabel.cpp \
    CustomWidgets/ErrorDialog/errordialog.cpp \
    CustomWidgets/ParamAdjustWidget/paramadjustwidget.cpp \
    CustomWidgets/focusawarelineedit.cpp \
    Window/AboutDialog/aboutdialog.cpp \
    CustomWidgets/HybridSlider/hybridslider.cpp \
    main.cpp \
    Window/MainWindow/mainwindow.cpp

HEADERS += \
    CustomWidgets/ChainMenuWidget/chainmenuwidget.h \
    CustomWidgets/ClickableLabel/clickablelabel.h \
    CustomWidgets/ErrorDialog/errordialog.h \
    CustomWidgets/ParamAdjustWidget/paramadjustwidget.h \
    CustomWidgets/applyresetbuttonlayout.h \
    CustomWidgets/dividerline.h \
    CustomWidgets/duallineeditlayout.h \
    CustomWidgets/errorlabel.h \
    CustomWidgets/focusawarelineedit.h \
    CustomWidgets/labelledcombobox.h \
    CustomWidgets/lineeditlayout.h \
    CustomWidgets/HybridSlider/hybridslider.h \
    CustomWidgets/sliderlayout.h \
    CustomWidgets/baseconfigwidget.h \
    OpenCVFunction/backgroundsubtract.h \
    OpenCVFunction/bitwiseops.h \
    OpenCVFunction/blur.h \
    OpenCVFunction/cannyedge.h \
    OpenCVFunction/colorpicker.h \
    OpenCVFunction/colorspaces.h \
    OpenCVFunction/contours.h \
    OpenCVFunction/erodedilate.h \
    OpenCVFunction/harriscornerdetector.h \
    OpenCVFunction/histogram.h \
    OpenCVFunction/houghcircles.h \
    OpenCVFunction/houghlines.h \
    OpenCVFunction/imageflip.h \
    OpenCVFunction/inrange.h \
    Utils/captureinputsource.h \
    Utils/constants.h \
    Utils/logger.h \
    Utils/utils.h \
    Window/AboutDialog/aboutdialog.h \
    Window/MainWindow/mainwindow.h

FORMS += \
    CustomWidgets/ChainMenuWidget/chainmenuwidget.ui \
    CustomWidgets/ErrorDialog/errordialog.ui \
    Window/AboutDialog/aboutdialog.ui \
    CustomWidgets/HybridSlider/hybridslider.ui \
    Window/MainWindow/mainwindow.ui

RESOURCES += \
    res.qrc \
    qdarkstyle/style.qrc

DISTFILES += \
    CONTRIBUTING.md \
    LICENSE.txt \
    README.md \
    assets/app_logo.png \
    assets/capture_dark.png \
    assets/capture_disabled.png \
    assets/capture_light.png \
    assets/demo_video.gif \
    assets/done.png \
    assets/done_sel.png \
    assets/info.png \
    assets/info_light.png \
    assets/info_light_sel.png \
    assets/info_sel.png \
    assets/liberapay_donate.png \
    assets/minimize.png \
    assets/minimize_sel.png \
    assets/opencv_logo.png \
    assets/paypal_donate.png \
    assets/play_dark.png \
    assets/play_disabled.png \
    assets/play_light.png \
    assets/stop_dark.png \
    assets/stop_disabled.png \
    assets/stop_light.png \
    assets/undock.png \
    assets/undock_sel.png \
    media/minus_button.png \
    media/picture_gui.jpg \
    media/plus_button.png \
    media/radio_button.png \
    media/screenshot_adjust_params.png \
    media/screenshot_canny.png \
    media/screenshot_histogram.png \
    media/screenshot_hsv.png \
    media/screenshot_menu.png \
    media/screenshot_select_input_camera.png \
    media/screenshot_select_input_file.jpg \
    media/screenshot_select_input_file.png
