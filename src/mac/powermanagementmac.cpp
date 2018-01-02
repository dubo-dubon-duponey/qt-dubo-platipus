#include "powermanagementmac.h"

#include <QtCore/qdebug.h>

PowerManagementMac::PowerManagementMac(QObject *parent) :
    BasePowerManagement(parent), m_assertionID(0)
{
    qDebug() << " [M/Mac]System/PowerManagement: constructor";
    //    @param master_device_port  Just pass in MACH_PORT_NULL for master device port.
    //    @result Returns a io_connect_t handle on the root domain. Must be released with IOServiceClose() when done.
    m_connectIO = IOPMFindPowerManagement( MACH_PORT_NULL );
}

PowerManagementMac::~PowerManagementMac()
{
    qDebug() << " [M/Mac] System/PowerManagement: destructor";
    IOServiceClose(m_connectIO);
    if(m_assertionID){
        IOPMAssertionRelease(m_assertionID);
        m_assertionID = 0;
    }
}

void PowerManagementMac::setState(const uint busy, const QString & reason)
{
    qDebug() << " [M/Mac] System/PowerManagement: set new state";
    if(m_busy == busy){
        return;
    }

    IOReturn success;
    // Release any previous assertion
    if(m_assertionID){
        success = IOPMAssertionRelease(m_assertionID);
        m_assertionID = 0;
    }

    CFStringRef reasonForActivity = CFStringCreateWithCString(NULL, reason.toStdString().c_str(), kCFStringEncodingUTF8);

    // kIOPMAssertionTypePreventSystemSleep - general system sleep prevention (dark wake)
    switch(busy){
    case BasePowerManagement::SYSTEM:
        success = IOPMAssertionCreateWithName(kIOPMAssertionTypePreventUserIdleSystemSleep, kIOPMAssertionLevelOn, reasonForActivity, &m_assertionID);
        break;
    case BasePowerManagement::SCREEN:
        success = IOPMAssertionCreateWithName(kIOPMAssertionTypePreventUserIdleDisplaySleep, kIOPMAssertionLevelOn, reasonForActivity, &m_assertionID);
        break;
    case BasePowerManagement::NONE:
        break;
    default:
        success = kIOReturnError;
        break;
    }
    if(success != kIOReturnSuccess){
        m_busy = BasePowerManagement::NONE;
        qDebug() << " [M/Mac] System/PowerManagement: FAILED setting new state";
    }else{
        m_busy = busy;
    }
    return;
}



//- (void) receiveSleepNote: (NSNotification*) note
//{
//    NSLog(@"receiveSleepNote: %@", [note name]);
//}

//- (void) receiveWakeNote: (NSNotification*) note
//{
//    NSLog(@"receiveSleepNote: %@", [note name]);
//}

//- (void) fileNotifications
//{
//    //These notifications are filed on NSWorkspace's notification center, not the default
//    // notification center. You will not receive sleep/wake notifications if you file
//    //with the default notification center.
//    [[[NSWorkspace sharedWorkspace] notificationCenter] addObserver: self
//            selector: @selector(receiveSleepNote:)
//            name: NSWorkspaceWillSleepNotification object: NULL];

//    [[[NSWorkspace sharedWorkspace] notificationCenter] addObserver: self
//            selector: @selector(receiveWakeNote:)
//            name: NSWorkspaceDidWakeNotification object: NULL];
//}
