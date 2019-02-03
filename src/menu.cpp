/**
 * Copyright (c) 2019, Dubo Dubon Duponey <dubodubonduponey+github@pm.me>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "libduboplatipus/menu.h"
#include "libduboplatipus/action.h"

namespace DuboPlatipus{
namespace UI{

Menu::Menu(QObject *parent) :
    QObject(parent)
{
    qt = new QMenu();
    // Default behavior
    qt->setSeparatorsCollapsible(true);
    qt->setTearOffEnabled(false);

    icon = new DuboPlatipus::UI::Icon(this);

    connect(
        icon, SIGNAL (updated()),
        this, SLOT (iconUpdated())
     );
}

Menu::Menu(Menu *parent) :
    QObject(parent)
{
    qt = new QMenu();
    // Default behavior
    qt->setSeparatorsCollapsible(true);
    qt->setTearOffEnabled(false);

    icon = new DuboPlatipus::UI::Icon(this);

    connect(
        icon, SIGNAL (updated()),
        this, SLOT (iconUpdated())
     );

    if(parent)
        parent->qt->addMenu(qt);
}

const QString Menu::title() const
{
    return qt->title();
}

// Can't this be a member?
void Menu::setTitle(const QString &title) const
{
    qt->setTitle(title);
}

void Menu::clear() const
{
    qt->clear();
}

void Menu::addSeparator() const
{
    qt->addSeparator();
}

QVariant Menu::addAction(int role)
{
    Action * action = new Action(this, role);
    return QVariant::fromValue(static_cast<QObject*>(action));
}

QVariant Menu::addMenu()
{
    Menu * menu = new Menu(this);
    return QVariant::fromValue(static_cast<QObject*>(menu));
}

}
}
