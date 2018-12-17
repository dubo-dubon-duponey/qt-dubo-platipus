#ifndef POWERMANAGEMENTWINDOWS_H
#define POWERMANAGEMENTWINDOWS_H

#include "libduboplatipus/basepowermanagement.h"

class PowerManagementWindows : public DuboPlatipus::BasePowerManagement
{
    Q_OBJECT
public:
    explicit PowerManagementWindows(QObject * parent = nullptr);
//    ~PowerManagementWindows();
    void setState(const uint busy, const QString & reason);

signals:
    
public slots:
    
private:
  uint m_busy;
};

#endif // POWERMANAGEMENTWINDOWS_H
