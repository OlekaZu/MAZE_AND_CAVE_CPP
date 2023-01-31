QT       += core gui network

RC_ICONS = icon/maze_icon.ico
ICON = icon/maze_icon.icns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/eller_labyrinth.cc \
    Model/find_way.cc \
    Model/matrix.cc \
    Model/model_cave.cc \
    View/main.cc \
    View/mainwindow.cc \
    Model/parse_file.cc \
    Controller/controller.cc

HEADERS += \
    Model/eller_labyrinth.h \
    Model/find_way.h \
    Model/matrix.h \
    Model/model_cave.h \
    View/mainwindow.h \
    Model/parse_file.h \
    Controller/controller.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc
