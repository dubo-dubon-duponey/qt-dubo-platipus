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

#include "libduboplatipus/zerohello/browser.h"

namespace DuboPlatipus{
namespace ZeroHello{

Browser::Browser(QObject *parent) :
    GenericZero(parent), browsingType(QString::fromUtf8(""))
{
}

void Browser::browse(const QString &serviceType)
{
    browsingType = serviceType;
    // Call browse
    DNSServiceErrorType err = DNSServiceBrowse(
                &dnssref,
                0,
                0,
                serviceType.toUtf8().constData(),
                0,
                browseHandler,
                this
                );

    goBaby(err);
}

void Browser::browseHandler(
        DNSServiceRef,
        DNSServiceFlags flags,
        quint32,
        DNSServiceErrorType errorCode,
        const char *serviceName,
        const char *regType,
        const char *replyDomain,
        void *context
        )
{
    // Get context back
    Browser *browser = static_cast<Browser *>(context);

    // Handle error
    if (errorCode != kDNSServiceErr_NoError) {
        emit browser->error(errorCode);
        return;
    }
    // Create record
    Record record(serviceName, regType, replyDomain);
    // Handle read
    if (flags & kDNSServiceFlagsAdd) {
        if (!browser->bonjourRecords.contains(record))
            browser->bonjourRecords.append(record);
    } else {
        browser->bonjourRecords.removeAll(record);
    }
    if (!(flags & kDNSServiceFlagsMoreComing)) {
        emit browser->changed(browser->bonjourRecords);
    }
}

}
}
