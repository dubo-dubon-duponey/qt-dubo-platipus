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
    QRect r = d->availableGeometry(d);
    return r.x();
}

int AppUtils::rendery()
{
    QDesktopWidget * d = QApplication::desktop();
    QRect r = d->availableGeometry(d);
    return r.y();
}

int AppUtils::renderw()
{
    QDesktopWidget * d = QApplication::desktop();
    QRect r = d->availableGeometry(d);
    return r.width();
}

int AppUtils::renderh()
{
    QDesktopWidget * d = QApplication::desktop();
    QRect r = d->availableGeometry(d);
    return r.height();
}

int AppUtils::screenx()
{
    return 0;
}

int AppUtils::screeny()
{
    return 0;
}

int AppUtils::screenw()
{
    return 0;
}

int AppUtils::screenh()
{
    return 0;
}

}
