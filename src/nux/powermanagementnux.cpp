#include "powermanagementnux.h"

#include <QtCore/qdebug.h>

#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusPendingCall>
#include <QDBusPendingReply>

PowerManagementNux::PowerManagementNux(QObject *parent) :
    BasePowerManagement(parent)
{
    qDebug() << " [M/Nux] System/PowerManagement: constructor";
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

void PowerManagementNux::setState(uint dobusy, const QString &/* reason*/)
{
    qDebug() << " [M/Nux] System/PowerManagement: set new state";
    if(m_busy == dobusy){
        return;
    }
    m_intended_state = dobusy ? busy : idle;
    if (m_state == error || m_state == m_intended_state || m_state == request_busy || m_state == request_idle)
        return;
    QDBusMessage call;
    if (!m_use_gsm)
        call = QDBusMessage::createMethodCall(
                "org.freedesktop.PowerManagement",
                "/org/freedesktop/PowerManagement/Inhibit",
                "org.freedesktop.PowerManagement.Inhibit",
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


void PowerManagementNux::OnAsyncReply(QDBusPendingCallWatcher *call)
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
            qDebug("D-Bus: PowerManagementInhibitor: Request successful");
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
            qDebug("D-Bus: PowerManagementInhibitor: Request successful, cookie is %d", m_cookie);
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
