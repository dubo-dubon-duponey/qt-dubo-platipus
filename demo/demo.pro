TEMPLATE = app
QT = core widgets webengine webenginewidgets webchannel

QMAKE_TARGET_BUNDLE_PREFIX=com.dubo-dubon-duponey

PROJECT_ROOT = $$PWD/..
include($$PROJECT_ROOT/config/qmakeitup.pri)

INCLUDEPATH += $$PWD

LIBS += -l$${DUBO_LINK_NAME}

contains(DUBO_LINK_TYPE, static){
    DEFINES += LIBDUBOPLATIPUS_USE_STATIC
}

SOURCES += $$PWD/main.cpp
RESOURCES += $$PWD/demo.qrc

mac{
    # Add plist, and a nice icon
    OTHER_FILES += $$PWD/Info.plist \
        $$PWD/demo.icns

    QMAKE_INFO_PLIST = $${PWD}/Info.plist
    ICON = $${PWD}/demo.icns
}
