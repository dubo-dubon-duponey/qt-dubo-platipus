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

#include "libduboplatipus/powermanager.h"
#include "ospowermanager.h"

#ifdef Q_OS_MAC
#include "mac/powermanagermac.h"
#elif defined(Q_OS_WIN)
#include "win/powermanagerwindows.h"
#elif defined(Q_OS_UNIX) && defined(Q_DBUS_EXPORT)
#include "nux/powermanagernux.h"
#endif

namespace DuboPlatipus{

class PowerManager::Private
{
    public:
    OSPowerManager * pm;
};

PowerManager::PowerManager(QObject * parent): QObject(parent)
{
    d = new PowerManager::Private();
#ifdef Q_OS_MAC
    d->pm = new PowerManagerMac(this);
#elif defined(Q_OS_WIN)
    d->pm = new PowerManagerWindows(this);
#elif defined(Q_OS_UNIX) && defined(Q_DBUS_EXPORT)
    d->pm = new PowerManagerNux(this);
#endif
    qDebug() << " [M] PowerManager: constructor";
}

uint PowerManager::getState()
{
    return d->pm->getState();
}

void PowerManager::setState(const uint busy, const QString & reason )
{
    d->pm->setState(busy, reason);
    emit stateChanged();
}

uint PowerManager::getSystem()
{
    return OSPowerManager::SYSTEM;
}

uint PowerManager::getScreen()
{
    return OSPowerManager::SCREEN;
}

uint PowerManager::getNone()
{
    return OSPowerManager::NONE;
}

}
