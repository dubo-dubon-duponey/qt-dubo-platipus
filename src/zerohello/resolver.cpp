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

#include "libduboplatipus/zerohello/resolver.h"

namespace DuboPlatipus{
namespace ZeroHello{

Resolver::Resolver(QObject *parent) : GenericZero(parent)
{
}

void Resolver::resolve(const Record &record)
{
    if (dnssref) {
        qWarning("Resolve already in process");
        return;
    }

    DNSServiceErrorType err = DNSServiceResolve(
                &dnssref,
                0,
                0,
                record.serviceName.toUtf8().constData(),
                record.registeredType.toUtf8().constData(),
                record.replyDomain.toUtf8().constData(),
                (DNSServiceResolveReply) replyHandler,
                this
                );

    goBaby(err);
}

void Resolver::replyHandler(
        DNSServiceRef,
        DNSServiceFlags, quint32,
        DNSServiceErrorType errorCode, const char *,
        const char *hostTarget,
        quint16 port,
        quint16,
        const unsigned char *,
        void *context
        )
{
    Resolver *resolver = static_cast<Resolver *>(context);
    if (errorCode != kDNSServiceErr_NoError) {
        emit resolver->error(errorCode);
        return;
    }

#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    port = ((port & 0x00ff) << 8) | ((port & 0xff00) >> 8);
#endif
    resolver->bonjourPort = port;
    QHostInfo::lookupHost(QString::fromUtf8(hostTarget), resolver, SLOT(finishConnect(const QHostInfo &)));
}


void Resolver::finishConnect(const QHostInfo &hostInfo)
{
    emit resolved(hostInfo, bonjourPort);
}

}
}
