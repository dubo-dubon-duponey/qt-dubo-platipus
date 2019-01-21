TEMPLATE = lib
QT = core widgets network

PROJECT_ROOT = $$PWD/..
include($$PROJECT_ROOT/config/qmakeitup.pri)

INCLUDEPATH += $$PWD

DEFINES += LIBDUBOPLATIPUS_LIBRARY
contains(DUBO_LINK_TYPE, static){
    DEFINES += LIBDUBOPLATIPUS_USE_STATIC
}

copyToDestdir($$PWD/lib$${TARGET}/*.h, $$DESTDIR/../include/lib$${TARGET})
copyToDestdir($$PWD/../res/redist/*, $$DESTDIR/../share/lib$${TARGET})

SOURCES +=  $$PWD/root.cpp\
            $$PWD/powermanager.cpp

HEADERS +=  $$PWD/lib$${TARGET}/global.h \
            $$PWD/lib$${TARGET}/root.h \
            $$PWD/lib$${TARGET}/lesserwindow.h \
            $$PWD/lib$${TARGET}/apputils.h \
            $$PWD/lib$${TARGET}/merguez.h \
            $$PWD/lib$${TARGET}/mediakeys.h \
            $$PWD/lib$${TARGET}/basepowermanagement.h \
            $$PWD/lib$${TARGET}/powermanager.h

win32{
#    INCLUDEPATH += $$PWD/win

    SOURCES += $$PWD/win/apputils.cpp
    SOURCES += $$PWD/win/merguez.cpp
    SOURCES += $$PWD/win/mediakeys.cpp
    HEADERS += $$PWD/win/powermanagementwindows.h
    SOURCES += $$PWD/win/powermanagementwindows.cpp
    SOURCES += $$PWD/win/lesserwindow.cpp
}

unix:!mac{
#    INCLUDEPATH += $$PWD/nux

    QT += dbus
    # The linux/dbus code is largely copied from  qBitTorrent Bittorrent Client,
    # Copyright (C) 2011  Vladimir Golovnev <glassez@yandex.ru>
    # Released under the GPL with an exception clause for OpenSSL
    HEADERS += $$PWD/nux/powermanagementnux.h
    SOURCES += $$PWD/nux/powermanagementnux.cpp

    SOURCES += $$PWD/nux/apputils.cpp
    SOURCES += $$PWD/nux/merguez.cpp
    SOURCES += $$PWD/nux/mediakeys.cpp
    SOURCES += $$PWD/nux/lesserwindow.cpp
}
mac{
    # Use Lion Fullscreen if available
    DEFINES += PLATIPUS_FULLSCREEN

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

    HEADERS += $$PWD/mac/powermanagementmac.h

    # Cocoa helper
    HEADERS +=              $$PWD/mac/cocoainit.h
    OBJECTIVE_SOURCES +=    $$PWD/mac/cocoainit.mm

    # Implementation
    OBJECTIVE_SOURCES +=    $$PWD/mac/apputils.mm
    OBJECTIVE_SOURCES +=    $$PWD/mac/merguez.mm
    OBJECTIVE_SOURCES +=    $$PWD/mac/mediakeys.mm
    OBJECTIVE_SOURCES +=    $$PWD/mac/lesserwindow.mm

    SOURCES += $$PWD/mac/powermanagementmac.cpp
}
