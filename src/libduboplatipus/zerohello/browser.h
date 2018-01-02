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

#ifndef DUBOPLATIPUS_ZEROHELLO_BROWSER_H
#define DUBOPLATIPUS_ZEROHELLO_BROWSER_H

#include "libduboplatipus/libduboplatipus_global.h"
#include "libduboplatipus/zerohello/genericzero.h"
#include "libduboplatipus/zerohello/record.h"
#include "libduboplatipus/zerohello/resolver.h"

#include <QSocketNotifier>
#include <QDebug>
#include <QObject>

#include <dns_sd.h>

namespace DuboPlatipus {

namespace ZeroHello {

class LIBDUBOPLATIPUSSHARED_EXPORT Browser : public GenericZero
{
    Q_OBJECT
public:
    explicit Browser(QObject *parent = 0);

    /*! \brief Call this to start browsing for serviceType */
    Q_INVOKABLE void browse(const QString &serviceType);

    /*! \brief Access the current records */
    QList<Record> records() const
    {
        return bonjourRecords;
    }

    /*! \brief Access the current serviceType (last call to browseForServiceType) */
    QString serviceType() const
    {
        return browsingType;
    }

signals:
    void changed(const QList<Record> &list);

private slots:

private:
    static void DNSSD_API browseHandler(
            DNSServiceRef,
            DNSServiceFlags,
            quint32,
            DNSServiceErrorType,
            const char *,
            const char *,
            const char *,
            void *
            );

    QList<Record> bonjourRecords;
    QString browsingType;

signals:
    
public slots:
    
};

}
}


#endif // DUBOPLATIPUS_ZEROHELLO_BROWSER_H
