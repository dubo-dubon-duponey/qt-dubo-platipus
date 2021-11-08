/*
 * Copyright (c) 2019, Dubo Dubon Duponey <dubodubonduponey+github@pm.me>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "powermanagermac.h"

// #include <QDebug>

PowerManagerMac::PowerManagerMac(QObject *parent) :
    OSPowerManager(parent), m_assertionID(0)
{
    //    @param master_device_port  Just pass in MACH_PORT_NULL for master device port.
    //    @result Returns a io_connect_t handle on the root domain. Must be released with IOServiceClose() when done.
    m_connectIO = IOPMFindPowerManagement( MACH_PORT_NULL );
}

PowerManagerMac::~PowerManagerMac()
{
    IOServiceClose(m_connectIO);
    if(m_assertionID){
        IOPMAssertionRelease(m_assertionID);
        m_assertionID = 0;
    }
}

void PowerManagerMac::setState(const uint busy, const QString & reason)
{
    if(m_busy == busy){
        return;
    }

    IOReturn success;
    // Release any previous assertion
    if(m_assertionID){
        success = IOPMAssertionRelease(m_assertionID);
        m_assertionID = 0;
    }

    CFStringRef reasonForActivity = CFStringCreateWithCString(nullptr, reason.toStdString().c_str(), kCFStringEncodingUTF8);

    // kIOPMAssertionTypePreventSystemSleep - general system sleep prevention (dark wake)
    success = kIOReturnError;
    switch(busy){
    case OSPowerManager::SYSTEM:
        success = IOPMAssertionCreateWithName(kIOPMAssertionTypePreventUserIdleSystemSleep, kIOPMAssertionLevelOn, reasonForActivity, &m_assertionID);
        break;
    case OSPowerManager::SCREEN:
        success = IOPMAssertionCreateWithName(kIOPMAssertionTypePreventUserIdleDisplaySleep, kIOPMAssertionLevelOn, reasonForActivity, &m_assertionID);
        break;
    case OSPowerManager::NONE:
        success = kIOReturnSuccess;
        break;
    }
    if(success != kIOReturnSuccess){
        m_busy = OSPowerManager::NONE;
        // qDebug() << " [M/Mac] System/PowerManager: FAILED setting new state";
    }else{
        m_busy = busy;
        // qDebug() << " [M/Mac] Did set power manager to" << busy;
    }
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
