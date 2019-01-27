/**
 * Copyright (c) 2018, Dubo Dubon Duponey <dubodubonduponey+github@pm.me>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "libduboplatipus/action.h"
#include <QKeySequence>

namespace DuboPlatipus{
namespace UI{

Action::Action( Menu * parent, int role ) :
    QObject(parent)
{
    qt = new QAction ( parent );
    qt->setIconVisibleInMenu(true);
    qt->setShortcutContext(Qt::ApplicationShortcut);
    qt->setMenuRole(static_cast<QAction::MenuRole>(role));
    parent->qt->addAction(qt);

    // Unfortunately, triggered is always dispatched first...
    connect(qt, SIGNAL(triggered()), this, SIGNAL(updated()));
    connect(qt, SIGNAL(triggered()), this, SIGNAL(triggered()));
    connect(qt, SIGNAL (changed()), this, SIGNAL (updated()));
    connect(qt, SIGNAL (toggled(bool)), this, SIGNAL (updated()));

    icon = new DuboPlatipus::UI::Icon(this);

    connect(icon, SIGNAL (updated()), this, SLOT (iconUpdated()));
}

const QString Action::text() const
{
    return qt->text();
}

void Action::setText(const QString &text) const
{
    qt->setText(text);
}

bool Action::enabled() const
{
    return qt->isEnabled();
}

void Action::setEnabled( bool ena ) const
{
    qt->setEnabled(ena);
}

bool Action::visible() const
{
    return qt->isVisible();
}

void Action::setVisible( bool vis ) const
{
    qt->setVisible(vis);
}

//void Action::remove()
//{
//    // XXX is pretty useless once removed
//    qt->menu()->removeAction(qt);
//}

const QString Action::shortcut() const
{
    return qt->shortcut().toString();
}

void Action::setShortcut(const QString & shortcut) const
{
    qt->setShortcut(QKeySequence(tr("%1").arg(shortcut)));
}


bool Action::autoRepeat() const
{
    return qt->autoRepeat();
}

void Action::setAutoRepeat( bool vis ) const
{
    qt->setAutoRepeat(vis);
}

bool Action::checked() const
{
    return qt->isChecked();
}

void Action::setChecked( bool vis ) const
{
    qt->setChecked(vis);
}

bool Action::checkable() const
{
    return qt->isCheckable();
}

void Action::setCheckable( bool vis ) const
{
    qt->setCheckable(vis);
}

}
}

