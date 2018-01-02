/**
 * Copyright (c) 2018, Dubo Dubon Duponey <dubodubonduponey@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "libduboplatipus/zerohello/registrar.h"

namespace DuboPlatipus{
namespace ZeroHello{

Registrar::Registrar(QObject *parent)
    : GenericZero(parent)
{
}

void Registrar::registerService(const Record &record, quint16 servicePort)
{
    if (dnssref) {
        qWarning("Already registered a service");
        return;
    }

    quint16 bigEndianPort = servicePort;
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    bigEndianPort = ((servicePort & 0x00ff) << 8) | ((servicePort & 0xff00) >> 8);
#endif
    // Call register
    DNSServiceErrorType err = DNSServiceRegister(
                &dnssref,
                0,
                0,
                record.serviceName.toUtf8().constData(),
                record.registeredType.toUtf8().constData(),
                record.replyDomain.isEmpty() ? 0 : record.replyDomain.toUtf8().constData(),
                0,
                bigEndianPort,
                0,
                0,
                registerHandler,
                this
                );

    goBaby(err);
}

void Registrar::registerHandler(
        DNSServiceRef,
        DNSServiceFlags,
        DNSServiceErrorType errorCode,
        const char *name,
        const char *regType,
        const char *domain,
        void *data)
{
    // Get context back
    Registrar *registrar = static_cast<Registrar *>(data);

    // On err
    if (errorCode != kDNSServiceErr_NoError) {
        emit registrar->error(errorCode);
        return;
    }

    // Store record
    registrar->finalRecord = Record(QString::fromUtf8(name), QString::fromUtf8(regType), QString::fromUtf8(domain));

    // Say we registered
    emit registrar->registered(registrar->finalRecord);
}

}
}
