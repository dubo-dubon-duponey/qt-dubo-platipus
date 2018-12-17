#ifndef POWERMANAGEMENTMAC_H
#define POWERMANAGEMENTMAC_H

#include "libduboplatipus/basepowermanagement.h"
#include <IOKit/pwr_mgt/IOPMLib.h>

class PowerManagementMac : public DuboPlatipus::BasePowerManagement
{
    Q_OBJECT
public:
    explicit PowerManagementMac(QObject * parent = nullptr);
    ~PowerManagementMac();

    void setState(const uint /* busy */, const QString & /*reason*/ );

signals:

public slots:

private:
//  uint m_busy;
  IOPMAssertionID m_assertionID;
  io_connect_t m_connectIO;
};

#endif // POWERMANAGEMENTMAC_H
