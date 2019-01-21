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

#include "powermanagementnux.h"

#include <QDebug>

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QDBusPendingReply>

PowerManagerNux::PowerManagerNux(QObject *parent) :
    OSPowerManager(parent)
{
    qDebug() << " [M/Nux] System/PowerManager: constructor";
    if(!QDBusConnection::sessionBus().isConnected())
    {
        qDebug("D-Bus: Could not connect to session bus");
        m_state = error;
    }
    else
    {
        m_state = idle;
    }

    m_intended_state = idle;
    m_cookie = 0;
    m_use_gsm = false;
}

void PowerManagerNux::setState(uint dobusy, const QString &/* reason*/)
{
    qDebug() << " [M/Nux] System/PowerManager: set new state";
    if(m_busy == dobusy){
        return;
    }
    m_intended_state = dobusy ? busy : idle;
    if (m_state == error || m_state == m_intended_state || m_state == request_busy || m_state == request_idle)
        return;
    QDBusMessage call;
    if (!m_use_gsm)
        call = QDBusMessage::createMethodCall(
                "org.freedesktop.PowerManager",
                "/org/freedesktop/PowerManager/Inhibit",
                "org.freedesktop.PowerManager.Inhibit",
                dobusy ? "Inhibit" : "UnInhibit");
    else
        call = QDBusMessage::createMethodCall(
                "org.gnome.SessionManager",
                "/org/gnome/SessionManager",
                "org.gnome.SessionManager",
                 dobusy ? "Inhibit" : "UnInhibit");
    m_state = dobusy ? request_busy : request_idle;

    QList<QVariant> args;
    if(dobusy){
        // XXX reason
        args << "Hello there";
        if (m_use_gsm) args << (uint)0;
        args << "User is busy doing something";
        if (m_use_gsm) args << (uint)8;
    }else{
        args << m_cookie;
    }
    call.setArguments(args);
    QDBusPendingCall pcall = QDBusConnection::sessionBus().asyncCall(call, 1000);
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pcall, this);
    connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
            this, SLOT(OnAsyncReply(QDBusPendingCallWatcher*)));

    // XXX untested
    m_busy = dobusy;
}


void PowerManagerNux::OnAsyncReply(QDBusPendingCallWatcher *call)
{
    if (m_state == request_idle)
    {
        QDBusPendingReply<> reply = *call;

        if(reply.isError())
        {
            qDebug("D-Bus: Reply: Error: %s", qPrintable(reply.error().message()));
            m_state = error;
        }
        else
        {
            m_state = idle;
            qDebug("D-Bus: PowerManagerInhibitor: Request successful");
            if (m_intended_state == busy)
                this->setState(1, QString::fromLatin1(""));
        }
    }
    else if (m_state == request_busy)
    {
        QDBusPendingReply<uint> reply = *call;

        if(reply.isError())
        {
            qDebug("D-Bus: Reply: Error: %s", qPrintable(reply.error().message()));

            if (!m_use_gsm)
            {
                qDebug("D-Bus: Falling back to org.gnome.SessionManager");
                m_use_gsm = true;
                m_state = idle;
                if (m_intended_state == busy)
                    // XXX
                    this->setState(1, QString("Busy"));
            }
            else
            {
                m_state = error;
            }
        }
        else
        {
            m_state = busy;
            m_cookie = reply.value();
            qDebug("D-Bus: PowerManagerInhibitor: Request successful, cookie is %d", m_cookie);
            if (m_intended_state == idle)
                // XXX
                this->setState(0, QString("Iddle"));
        }
    }
    else
    {
        qDebug("D-Bus: Unexpected reply in state %d", m_state);
        m_state = error;
    }

    call->deleteLater();
}
