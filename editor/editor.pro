QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cursor.cpp \
    level.cpp \
    main.cpp \
    mainwindow.cpp \
    ogl_out.cpp \
    opendialog.cpp \
    sphere.cpp

HEADERS += \
    cursor.h \
    level.h \
    level_common.h \
    mainwindow.h \
    ogl_out.h \
    opendialog.h \
    sphere.h

FORMS += \
    mainwindow.ui \
    opendialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
