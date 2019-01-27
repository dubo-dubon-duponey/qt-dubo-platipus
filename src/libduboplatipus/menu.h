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

#ifndef DUBOMODULES_UI_MENU_H
#define DUBOMODULES_UI_MENU_H

#include <QObject>
#include <QMenu>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>

#include "icon.h"

namespace DuboPlatipus{
namespace UI{

class Menu : public QObject
{
    Q_OBJECT
public:
    explicit Menu(QObject * parent = nullptr);
    explicit Menu(Menu * parent = nullptr);

    Q_PROPERTY(DuboPlatipus::UI::Icon * icon  MEMBER icon CONSTANT)
    Q_PROPERTY(QString title                READ title  WRITE setTitle  NOTIFY updated)

    Q_INVOKABLE QVariant addAction(int role = 0);
    Q_INVOKABLE QVariant addMenu();
    Q_INVOKABLE void addSeparator() const;
    Q_INVOKABLE void clear() const;


    //    QAction::NoRole	0	This action should not be put into the application menu
    //    QAction::TextHeuristicRole	1	This action should be put in the application menu based on the action's text as described in the QMenuBar documentation.
    //    QAction::ApplicationSpecificRole	2	This action should be put in the application menu with an application specific role
    //    QAction::AboutQtRole	3	This action matches handles the "About Qt" menu item.
    //    QAction::AboutRole	4	This action should be placed where the "About" menu item is in the application menu. The text of the menu item will be set to "About <application name>". The application name is fetched from the Info.plist file in the application's bundle (See Deploying an Application on Mac OS X).
    //    QAction::PreferencesRole	5	This action should be placed where the "Preferences..." menu item is in the application menu.
    //    QAction::QuitRole	6	This action should be placed where the Quit menu item is in the application menu.

    Q_PROPERTY(int NOROLE       READ NOROLE         CONSTANT)
    Q_PROPERTY(int TEXT         READ TEXT           CONSTANT)
    Q_PROPERTY(int APPLICATION  READ APPLICATION    CONSTANT)
    Q_PROPERTY(int ABOUTQT      READ ABOUTQT        CONSTANT)
    Q_PROPERTY(int ABOUT        READ ABOUT          CONSTANT)
    Q_PROPERTY(int PREFERENCES  READ PREFERENCES    CONSTANT)
    Q_PROPERTY(int QUIT         READ QUIT           CONSTANT)

    QMenu * qt;

signals:
    void updated();

public slots:

private slots:
    void iconUpdated()
    {
        qt->setIcon(QIcon(* icon->internalIcon));
    }

private:
    DuboPlatipus::UI::Icon * icon;
    const QString title() const;
    void setTitle(const QString &title) const;

    int NOROLE()       const {return QAction::NoRole;}
    int TEXT()         const {return QAction::TextHeuristicRole;}
    int APPLICATION()  const {return QAction::ApplicationSpecificRole;}
    int ABOUTQT()      const {return QAction::AboutQtRole;}
    int ABOUT()        const {return QAction::AboutRole;}
    int PREFERENCES()  const {return QAction::PreferencesRole;}
    int QUIT()         const {return QAction::QuitRole;}
};
}
}

#endif // DUBOMODULES_UI_MENU_H
