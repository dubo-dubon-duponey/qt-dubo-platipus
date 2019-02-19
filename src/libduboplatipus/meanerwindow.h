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

#ifndef DUBOPLATIPUS_MEANERWINDOW_H
#define DUBOPLATIPUS_MEANERWINDOW_H

#include "libduboplatipus/global.h"
#include "libduboplatipus/lesserwindow.h"
#include <QWidget>
#include <QMouseEvent>

namespace DuboPlatipus {

/**
 * @brief The MeanerWindow class
 * The purpose of this is to extend on LesserWindow (the subset of windows controls that have to be implemented natively),
 * using QT provided APIs.
 * The end-result is a disjoint set of APIs (less than QT, hiding away the not so useful stuff, and more than QT, exposing additional macOS thingies)
 */
class LIBDUBOPLATIPUSSHARED_EXPORT MeanerWindow: public LesserWindow {
    Q_OBJECT
public:
    explicit MeanerWindow(QWidget * window, QObject * parent = nullptr);

    // Helper building on top of moveTo
    Q_INVOKABLE void moveBy(int x, int y);

    Q_INVOKABLE void show();
    Q_INVOKABLE void hide();
    Q_INVOKABLE void raise();
    Q_INVOKABLE void lower();

    Q_INVOKABLE void close();

    Q_PROPERTY(bool isActive READ isActive)

    Q_INVOKABLE void activate();

    // XXX Most of this is incorrect in QT if using native controls on OSX
    Q_PROPERTY(bool isMaximized READ isMaximized)
    Q_PROPERTY(bool isMinimized READ isMinimized)
    Q_INVOKABLE void maximize();
    Q_INVOKABLE void minimize();
    Q_INVOKABLE void normal();

    // XXX BELOW IS (KINDA) OK
    Q_PROPERTY(int w READ w NOTIFY updated)
    Q_PROPERTY(int h READ h NOTIFY updated)

    Q_PROPERTY(int minw READ minw WRITE setMinw NOTIFY updated)
    Q_PROPERTY(int minh READ minh WRITE setMinh NOTIFY updated)

    Q_PROPERTY(int maxw READ maxw WRITE setMaxw NOTIFY updated)
    Q_PROPERTY(int maxh READ maxh WRITE setMaxh NOTIFY updated)

    Q_INVOKABLE void setSize(int w, int h);

signals:
    void activated();
    void deactivated();
    void outboundMouse(QMouseEvent * e);
//    void outboundKey(QKeyEvent * e);
    void windowStateChanged();
    // XXX Older versions of QT do not support signal inheritance... so... this here...
    void updated();

protected:

private:
    bool isActive();
    bool isMaximized();
    bool isMinimized();
    int w();
    int h();

    int minw();
    int minh();
    int maxw();
    int maxh();
    void setMinw(int w);
    void setMinh(int h);
    void setMaxw(int w);
    void setMaxh(int h);

    bool eventFilter(QObject *object, QEvent *event);

};

}

#endif // DUBOPLATIPUS_MEANERWINDOW_H
