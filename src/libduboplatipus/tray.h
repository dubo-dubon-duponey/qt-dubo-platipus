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

#ifndef DUBOMODULES_UI_TRAY_H
#define DUBOMODULES_UI_TRAY_H

#include "menu.h"
#include "icon.h"
#include <QSystemTrayIcon>

/*
 * XXX Issues - on Mac:
 * - middle clicks do open context menu while they should not
 * - double clicks are not dispatched if there is a menu
 * - double clicks are unreliably dispatched
 */

namespace DuboPlatipus{
namespace UI{

class Tray : public QObject
{
    Q_OBJECT
public:
    explicit Tray(QWidget *parent = nullptr);

    Q_PROPERTY(Icon * icon  MEMBER icon CONSTANT)
    Q_PROPERTY(Menu * menu  MEMBER menu CONSTANT)

    Q_PROPERTY(QString tooltip      READ tooltip WRITE setTooltip   NOTIFY updated)
    Q_PROPERTY(bool visible         READ visible WRITE setVisible   NOTIFY updated)

    /*
    // XXX not working on macos
    Q_PROPERTY(int CLICK            READ CLICK          CONSTANT)
    Q_PROPERTY(int DOUBLE_CLICK     READ DOUBLE_CLICK   CONSTANT)
    Q_PROPERTY(int MIDDLE_CLICK     READ MIDDLE_CLICK   CONSTANT)
    Q_PROPERTY(int CONTEXT_CLICK    READ CONTEXT_CLICK  CONSTANT)
    Q_PROPERTY(int UNKNOWN_CLICK    READ UNKNOWN_CLICK  CONSTANT)
    */


signals:
    void activated( int type ) const;
    void updated() const;

private:
    Icon * icon;
    Menu * menu;
    QSystemTrayIcon * qt;

    const QString tooltip() const;
    void setTooltip(const QString &tooltip) const;

    bool visible() const;
    void setVisible(bool visible) const;

    /*
    QSystemTrayIcon::Unknown	0	Unknown reason
    QSystemTrayIcon::Context	1	The context menu for the system tray entry was requested
    QSystemTrayIcon::DoubleClick	2	The system tray entry was double clicked
    QSystemTrayIcon::Trigger	3	The system tray entry was clicked
    QSystemTrayIcon::MiddleClick	4	The system tray entry was clicked with the middle mouse button
    */

    // XXX this is broken on mac, QT!
    /*
    int CLICK()         const {return QSystemTrayIcon::Trigger;}
    int DOUBLE_CLICK()  const {return QSystemTrayIcon::DoubleClick;}
    int MIDDLE_CLICK()  const {return QSystemTrayIcon::MiddleClick;}
    int CONTEXT_CLICK() const {return QSystemTrayIcon::Context;}
    int UNKNOWN_CLICK() const {return QSystemTrayIcon::Unknown;}
    */

private slots:
    void qtActivated(QSystemTrayIcon::ActivationReason reason)
    {
        // Indirection because of the type
        emit activated(reason);
    }

    void iconUpdated()
    {
        qt->setIcon(QIcon(* icon->internalIcon));
        emit updated();
    }
};

}
}

#endif // DUBOMODULES_UI_TRAY_H
