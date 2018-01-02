#include "libduboplatipus/apputils.h"
#include <QDesktopWidget>
#include <QApplication>

namespace DuboPlatipus {

void AppUtils::badgeMe(const QString &/*text*/)
{
}

void AppUtils::bitchMe()
{
}

bool AppUtils::hasCustomFullscreen(QWidget * /*mainWindow*/)
{
    return false;
}

bool AppUtils::isFullScreen(QWidget * mainWindow)
{
    return mainWindow->isFullScreen();
}

bool AppUtils::fullscrenToggle(QWidget * mainWindow)
{
    if(!mainWindow->isFullScreen()){
        mainWindow->showFullScreen();
    }
    else if(mainWindow->isMaximized())
        mainWindow->showMaximized();
    else
        mainWindow->showNormal();
    return mainWindow->isFullScreen();
}

int AppUtils::renderx()
{
    QDesktopWidget * d = QApplication::desktop();
    QRect r = d->availableGeometry();
    return r.x();
}

int AppUtils::rendery()
{
    QDesktopWidget * d = QApplication::desktop();
    QRect r = d->availableGeometry();
    return r.y();
}

int AppUtils::renderw()
{
    QDesktopWidget * d = QApplication::desktop();
    QRect r = d->availableGeometry();
    return r.width();
}

int AppUtils::renderh()
{
    QDesktopWidget * d = QApplication::desktop();
    QRect r = d->availableGeometry();
    return r.height();
}

int AppUtils::screenx()
{
    return 0;
//    return [[NSScreen mainScreen] frame].origin.x;
}

int AppUtils::screeny()
{
    return 0;
//    return [[NSScreen mainScreen] frame].origin.y;
}

int AppUtils::screenw()
{
    return 0;
//    return [[NSScreen mainScreen] frame].size.width;
}

int AppUtils::screenh()
{
    return 0;
//    return [[NSScreen mainScreen] frame].size.height;
}



}

