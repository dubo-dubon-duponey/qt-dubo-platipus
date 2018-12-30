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

#ifndef DUBOPLATIPUS_POWERMANAGER_H
#define DUBOPLATIPUS_POWERMANAGER_H

#include "libduboplatipus/global.h"
#include <QObject>
#include "libduboplatipus/basepowermanagement.h"

namespace DuboPlatipus
{
//class LIBDUBOPLATIPUSSHARED_EXPORT PowerManager: public QObject {
//    Q_OBJECT
//public:
//    static DuboPlatipus::BasePowerManagement * getManager(QObject * parent = nullptr);

//signals:
    
//public slots:
    

class LIBDUBOPLATIPUSSHARED_EXPORT PowerManager : public QObject
{
  Q_OBJECT

public:
    PowerManager(QObject * parent = nullptr);

    Q_PROPERTY(uint state READ getState)

    uint getState();

    Q_PROPERTY(uint NONE READ getNone)
    Q_PROPERTY(uint SYSTEM READ getSystem)
    Q_PROPERTY(uint SCREEN READ getScreen)

    uint getSystem()
    {
        return BasePowerManagement::SYSTEM;
    }

    uint getScreen()
    {
        return BasePowerManagement::SCREEN;
    }

    uint getNone()
    {
        return BasePowerManagement::NONE;
    }

    Q_INVOKABLE void setState(const uint busy, const QString & reason );

private:
  BasePowerManagement * pm;

};

}

#endif // DUBOPLATIPUS_POWERMANAGER_H
