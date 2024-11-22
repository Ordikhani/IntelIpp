QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    signalconvolver.cpp

HEADERS += \
    mainwindow.h \
    signalconvolver.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target







INCLUDEPATH += $$PWD/../intel/oneapi/ipp/2021.12/include/ipp


LIBS += -L$$PWD/../intel/oneapi/ipp/2021.12/lib/ -lipps -lippcore


DEPENDPATH += $$PWD/../intel/oneapi/ipp/2021.12/include/ipp
unix:!macx: LIBS += -L$$PWD/../intel/oneapi/ipp/2021.12/lib32/ -lippcore

INCLUDEPATH += $$PWD/../intel/oneapi/ipp/2021.12/lib32
DEPENDPATH += $$PWD/../intel/oneapi/ipp/2021.12/lib32

unix:!macx: LIBS += -L$$PWD/../intel/oneapi/ipp/2021.12/lib/ -lipps -lippcore

INCLUDEPATH += $$PWD/../intel/oneapi/ipp/2021.12/include/ipp
DEPENDPATH += $$PWD/../intel/oneapi/ipp/2021.12/include/ipp
