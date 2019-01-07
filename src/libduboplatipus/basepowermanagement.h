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

#ifndef DUBOPLATIPUS_BASEPOWERMANAGEMENT_H
#define DUBOPLATIPUS_BASEPOWERMANAGEMENT_H

#include "libduboplatipus/global.h"
#include <QObject>
#include <QDebug>

namespace DuboPlatipus {

class LIBDUBOPLATIPUSSHARED_EXPORT BasePowerManagement : public QObject
{
  Q_OBJECT

public:
  BasePowerManagement(QObject * parent = nullptr): QObject(parent), m_busy(0)
  {
      qDebug() << " [M] Base System/PowerManagement: constructor";
  }

  static const uint NONE = 0;
  static const uint SYSTEM = 1;
  static const uint SCREEN = 2;

  uint getState()
  {
      qDebug() << " [M] PowerManagement: query state";
      return m_busy;
  }

  virtual void setState(const uint /* busy */, const QString & /*reason*/ ){}

protected:
  uint m_busy;

};

}

#endif // DUBOPLATIPUS_BASEPOWERMANAGEMENT_H
