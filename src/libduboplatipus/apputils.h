/**
 * Copyright (c) 2018, Dubo Dubon Duponey <dubodubonduponey@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DUBOPLATIPUS_APPUTILS_H
#define DUBOPLATIPUS_APPUTILS_H

#include "libduboplatipus/libduboplatipus_global.h"
#include <QtCore/qobject.h>

#include <QtCore/QString>
#include <QWidget>

namespace DuboPlatipus {

class LIBDUBOPLATIPUSSHARED_EXPORT AppUtils: public QObject {
    Q_OBJECT
public:

    static void badgeMe(const QString &text);
    static void bitchMe();

    static bool hasCustomFullscreen(QWidget * mainWindow);
    static bool isFullScreen(QWidget * mainWindow);
    static bool fullscrenToggle(QWidget * mainWindow);

    static int renderx();
    static int rendery();
    static int renderw();
    static int renderh();

    static int screenx();
    static int screeny();
    static int screenw();
    static int screenh();
};

}

#endif // DUBOPLATIPUS_APPUTILS_H
