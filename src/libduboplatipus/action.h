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

#ifndef DUBOMODULES_UI_ACTION_H
#define DUBOMODULES_UI_ACTION_H

#include <QObject>
#include "menu.h"

namespace DuboPlatipus{
namespace UI{

class Action : public QObject
{
    Q_OBJECT
public:
    explicit Action( Menu * parent, int role = 0 );

    Q_PROPERTY(DuboPlatipus::UI::Icon * icon    MEMBER icon         CONSTANT)

    Q_PROPERTY(QString title    READ text       WRITE setText       NOTIFY updated)

    Q_PROPERTY(bool visible     READ visible    WRITE setVisible    NOTIFY updated)
    Q_PROPERTY(bool checked     READ checked    WRITE setChecked    NOTIFY updated)
    Q_PROPERTY(bool checkable   READ checkable  WRITE setCheckable  NOTIFY updated)
    Q_PROPERTY(bool enabled     READ enabled    WRITE setEnabled    NOTIFY updated)

    Q_PROPERTY(QString shortcut READ shortcut   WRITE setShortcut   NOTIFY updated)
    Q_PROPERTY(bool autoRepeat  READ autoRepeat WRITE setAutoRepeat NOTIFY updated)

    QAction * qt;

/*
    //    Q_INVOKABLE void remove();
    Q_PROPERTY(QString iconText READ iconText WRITE setIconText NOTIFY changed)
    Q_PROPERTY(QString toolTip READ toolTip WRITE setToolTip NOTIFY changed)
    Q_PROPERTY(QString statusTip READ statusTip WRITE setStatusTip NOTIFY changed)
    Q_PROPERTY(QString whatsThis READ whatsThis WRITE setWhatsThis NOTIFY changed)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY changed)
#ifndef QT_NO_SHORTCUT
    Q_PROPERTY(Qt::ShortcutContext shortcutContext READ shortcutContext WRITE setShortcutContext NOTIFY changed)
#endif
    Q_PROPERTY(MenuRole menuRole READ menuRole WRITE setMenuRole NOTIFY changed)
    Q_PROPERTY(bool iconVisibleInMenu READ isIconVisibleInMenu WRITE setIconVisibleInMenu NOTIFY changed)
    Q_PROPERTY(bool shortcutVisibleInContextMenu READ isShortcutVisibleInContextMenu WRITE setShortcutVisibleInContextMenu NOTIFY changed)
    Q_PROPERTY(Priority priority READ priority WRITE setPriority)
*/

signals:
    void triggered() const;
    void updated() const;

private slots:
    void iconUpdated()
    {
        qt->setIcon(QIcon(* icon->internalIcon));
    }

private:

    DuboPlatipus::UI::Icon * icon;

    const QString text() const;
    void setText(const QString &text) const;

    const QString shortcut() const;
    void setShortcut(const QString & shortcut) const;

    bool enabled() const;
    void setEnabled( bool ena ) const;

    bool visible() const;
    void setVisible( bool vis ) const;

    bool autoRepeat() const;
    void setAutoRepeat( bool ena ) const;

    bool checked() const;
    void setChecked( bool ena ) const;

    bool checkable() const;
    void setCheckable( bool ena ) const;

    // Ignored:
    //    font : QFont
    //    iconText : QString
    //    toolTip : QString
    //    statusTip : QString
    //    whatsThis : QString
    //    priority : Priority

};

}
}

#endif // DUBOMODULES_UI_ACTION_H


    /*
    QSystemTrayIcon::NoIcon	0	No icon is shown.
    QSystemTrayIcon::Information	1	An information icon is shown.
    QSystemTrayIcon::Warning	2	A standard warning icon is shown.
    QSystemTrayIcon::Critical	3	A critical warning icon is shown.
    */
//    Q_PROPERTY(int NOICON READ NOICON)
//    int NOICON(){return QSystemTrayIcon::NoIcon;}
//    Q_PROPERTY(int INFO_ICON READ INFO_ICON)
//    int INFO_ICON(){return QSystemTrayIcon::Information;}
//    Q_PROPERTY(int WARNING_ICON READ WARNING_ICON)
//    int WARNING_ICON(){return QSystemTrayIcon::Warning;}
//    Q_PROPERTY(int CRITICAL_ICON READ CRITICAL_ICON)
//    int CRITICAL_ICON(){return QSystemTrayIcon::Critical;}

//    (const QString & title, const QString & message, MessageIcon icon = Information, int millisecondsTimeoutHint = 10000)
/*
    Q_INVOKABLE void clearMenu();
    Q_INVOKABLE void addMenuSeparator();

    Q_INVOKABLE QVariant addMenuItem(const QString &text);// , const QKeySequence &shortcut
*/


//signals:
//    void notificationClick();


//    QMenu *_menu;


//private slots:
//    void messageClicked();
