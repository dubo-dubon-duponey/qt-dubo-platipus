TEMPLATE = lib
QT = core widgets network

PROJECT_ROOT = $$PWD/..
include($$PROJECT_ROOT/config/qmakeitup.pri)

INCLUDEPATH += $$PWD

HEADERS +=  $$PWD/lib$${TARGET}/global.h \
            $$PWD/lib$${TARGET}/root.h \
            $$PWD/lib$${TARGET}/lesserwindow.h \
            $$PWD/lib$${TARGET}/meanerwindow.h \
            $$PWD/lib$${TARGET}/apputils.h \
            $$PWD/lib$${TARGET}/merguez.h \
            $$PWD/lib$${TARGET}/mediakeys.h \
            $$PWD/lib$${TARGET}/powermanager.h \
            $$PWD/lib$${TARGET}/icon.h \
            $$PWD/lib$${TARGET}/tray.h \
            $$PWD/lib$${TARGET}/menu.h \
            $$PWD/lib$${TARGET}/menubar.h \
            $$PWD/lib$${TARGET}/action.h \
            $$PWD/ospowermanager.h

SOURCES +=  $$PWD/root.cpp\
            $$PWD/meanerwindow.cpp \
            $$PWD/powermanager.cpp \
            $$PWD/icon.cpp \
            $$PWD/tray.cpp \
            $$PWD/menu.cpp \
            $$PWD/menubar.cpp \
            $$PWD/action.cpp

win32{
#    INCLUDEPATH += $$PWD/win

    HEADERS += $$PWD/win/powermanagerwindows.h
    SOURCES += $$PWD/win/powermanagerwindows.cpp
    SOURCES += $$PWD/win/apputils.cpp
    SOURCES += $$PWD/win/lesserwindow.cpp

    SOURCES += $$PWD/win/merguez.cpp
    SOURCES += $$PWD/win/mediakeys.cpp
}

unix:!mac{
#    INCLUDEPATH += $$PWD/nux

    QT += dbus
    # The linux/dbus code is largely copied from  qBitTorrent Bittorrent Client,
    # Copyright (C) 2011  Vladimir Golovnev <glassez@yandex.ru>
    # Released under the GPL with an exception clause for OpenSSL
    HEADERS += $$PWD/nux/powermanagernux.h
    SOURCES += $$PWD/nux/powermanagernux.cpp
    SOURCES += $$PWD/nux/apputils.cpp
    SOURCES += $$PWD/nux/lesserwindow.cpp

    SOURCES += $$PWD/nux/merguez.cpp
    SOURCES += $$PWD/nux/mediakeys.cpp
}
mac{
    ###################
    # Dependencies
    ###################

    LIBS += -framework AppKit -framework IOKit
    INCLUDEPATH += $${PWD}/../third-party/SPMediaKeyTap
    INCLUDEPATH += $${PWD}/../third-party/apple_remote_control

    OBJECTIVE_SOURCES +=    $${PWD}/../third-party/apple_remote_control/AppleRemote.m\
                            $${PWD}/../third-party/apple_remote_control/RemoteControl.m\
                            $${PWD}/../third-party/apple_remote_control/MultiClickRemoteBehavior.m\
                            $${PWD}/../third-party/apple_remote_control/HIDRemoteControlDevice.m

    OBJECTIVE_HEADERS +=    $${PWD}/../third-party/apple_remote_control/AppleRemote.h\
                            $${PWD}/../third-party/apple_remote_control/RemoteControl.h\
                            $${PWD}/../third-party/apple_remote_control/MultiClickRemoteBehavior.h\
                            $${PWD}/../third-party/apple_remote_control/HIDRemoteControlDevice.h

    LIBS += -framework Carbon
    OBJECTIVE_HEADERS +=    $${PWD}/../third-party/SPMediaKeyTap/SPMediaKeyTap.h
    OBJECTIVE_SOURCES +=    $${PWD}/../third-party/SPMediaKeyTap/SPMediaKeyTap.m

    ####################
    ## Main lib
    ####################

#    INCLUDEPATH += $$PWD/mac

    HEADERS += $$PWD/mac/powermanagermac.h
    SOURCES += $$PWD/mac/powermanagermac.cpp

    # Cocoa helper
    HEADERS +=              $$PWD/mac/cocoainit.h
    OBJECTIVE_SOURCES +=    $$PWD/mac/cocoainit.mm

    # Implementation
    OBJECTIVE_SOURCES +=    $$PWD/mac/apputils.mm
    OBJECTIVE_SOURCES +=    $$PWD/mac/lesserwindow.mm

    OBJECTIVE_SOURCES +=    $$PWD/mac/merguez.mm
    OBJECTIVE_SOURCES +=    $$PWD/mac/mediakeys.mm

}
