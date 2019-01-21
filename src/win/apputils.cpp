/*
 * Copyright (c) 2019, Dubo Dubon Duponey <dubodubonduponey+github@pm.me>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
