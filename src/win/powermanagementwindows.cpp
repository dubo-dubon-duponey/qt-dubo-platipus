#include "powermanagementwindows.h"

#include <Windows.h>
#include <QDebug>

PowerManagementWindows::PowerManagementWindows(QObject *parent) :
    BasePowerManagement(parent)
{
    qDebug() << " [M/Win] System/PowerManagement: constructor";
}

void PowerManagementWindows::setState(const uint busy, const QString & /*reason*/)
{
    qDebug() << " [M/Win] System/PowerManagement: set new state";
    if(m_busy == busy){
        return;
    }
    if(busy){
        SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
    }else{
        SetThreadExecutionState(ES_CONTINUOUS);
    }
    m_busy = busy;
    return;
}

