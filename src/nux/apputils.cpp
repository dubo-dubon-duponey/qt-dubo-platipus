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
#include <QScreen>
#include <QApplication>

namespace DuboPlatipus {

AppUtils::AppUtils(QObject * parent): QObject(parent)
{
    connect(
        QApplication::primaryScreen(), SIGNAL (geometryChanged(const QRect &)),
        this, SLOT (screenChanged())
     );
    connect(
        QApplication::primaryScreen(), SIGNAL (availableGeometryChanged(const QRect &)),
        this, SLOT (screenChanged())
     );
    connect(
        QApplication::primaryScreen(), SIGNAL (virtualGeometryChanged(const QRect &)),
        this, SLOT (screenChanged())
     );
}

AppUtils::~AppUtils()
{

}

void AppUtils::screenChanged(){
    emit updated();
}

void AppUtils::badge(const QString &/*text*/)
{
}

void AppUtils::annoy()
{
}

int AppUtils::renderx()
{
    QScreen * d = QApplication::primaryScreen();
    QRect r = d->availableGeometry();
    return static_cast<int>(r.x());
}

int AppUtils::rendery()
{
    QScreen * d = QApplication::primaryScreen();
    QRect r = d->availableGeometry();
    return static_cast<int>(r.y());
}

uint AppUtils::renderw()
{
    QScreen * d = QApplication::primaryScreen();
    QRect r = d->availableGeometry();
    return static_cast<uint>(r.width());
}

uint AppUtils::renderh()
{
    QScreen * d = QApplication::primaryScreen();
    QRect r = d->availableGeometry();
    return static_cast<uint>(r.height());
}

int AppUtils::screenx()
{
    QScreen * d = QApplication::primaryScreen();
    QRect r = d->geometry();
    return static_cast<int>(r.x());
}

int AppUtils::screeny()
{
    QScreen * d = QApplication::primaryScreen();
    QRect r = d->geometry();
    return static_cast<int>(r.y());
}

uint AppUtils::screenw()
{
    QScreen * d = QApplication::primaryScreen();
    QRect r = d->geometry();
    return static_cast<uint>(r.width());
}

uint AppUtils::screenh()
{
    QScreen * d = QApplication::primaryScreen();
    QRect r = d->geometry();
    return static_cast<uint>(r.height());
}

}
