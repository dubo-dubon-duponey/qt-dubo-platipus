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

#ifndef DUBOPLATIPUS_APPUTILS_H
#define DUBOPLATIPUS_APPUTILS_H

#include "libduboplatipus/global.h"

#include <QObject>
#include <QString>
#include <QWidget>

namespace DuboPlatipus {

class LIBDUBOPLATIPUSSHARED_EXPORT AppUtils: public QObject {
    Q_OBJECT
public:
    explicit AppUtils(QObject * parent = nullptr);
    ~AppUtils();

    Q_INVOKABLE void badge(const QString &text);
    Q_INVOKABLE void annoy();

    // Note: the mac implementation differs from the QT one on:
    // - origin (bottom vs. top)
    // - the screen returned is the one holding the current active window, versus the screen where new windows are going to pop-up
    Q_PROPERTY(int renderx  READ renderx NOTIFY updated)
    Q_PROPERTY(int rendery  READ rendery NOTIFY updated)
    Q_PROPERTY(uint renderw READ renderw NOTIFY updated)
    Q_PROPERTY(uint renderh READ renderh NOTIFY updated)

    Q_PROPERTY(int screenx  READ screenx NOTIFY updated)
    Q_PROPERTY(int screeny  READ screeny NOTIFY updated)
    Q_PROPERTY(uint screenw READ screenw NOTIFY updated)
    Q_PROPERTY(uint screenh READ screenh NOTIFY updated)

    static int renderx();
    static int rendery();
    static uint renderw();
    static uint renderh();

    static int screenx();
    static int screeny();
    static uint screenw();
    static uint screenh();

public slots:
    void screenChanged();

signals:
    void updated();

private:
    class Private;
    Private* d;
};

}

#endif // DUBOPLATIPUS_APPUTILS_H
