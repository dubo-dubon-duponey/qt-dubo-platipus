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

#include <AppKit/NSWindow.h>

#include "libduboplatipus/merguez.h"
#include "cocoainit.h"
#include "AppleRemote.h"
#include "RemoteControl.h"

@class AppleRemote;
@interface SaucisseMain : NSObject {
//	MultiClickRemoteBehavior* remoteBehavior;
//	IBOutlet NSView*		feedbackView;
//	IBOutlet NSTextField*	feedbackText;
}

@property (atomic) RemoteControl* remoteControl;
@property (atomic) DuboPlatipus::RemoteMerguez* memere;

//- (RemoteControl*) remoteControl;
//- (void) setRemoteControl: (RemoteControl*) newControl;

- (void) setupBase: (DuboPlatipus::RemoteMerguez *) merguez;
- (void) start;
- (void) stop;

@end

@implementation SaucisseMain{

}
/*
- (void) dealloc {
    [self.remoteControl autorelease];
    [self.memere autorelease];
    [super dealloc];
}
*/
// implementation file
- (void) sendRemoteButtonEvent: (RemoteControlEventIdentifier) event
                   pressedDown: (BOOL) pressedDown
                   remoteControl: (RemoteControl*) remoteControl
{
    #pragma unused (remoteControl)
    self.memere->hello(event, pressedDown);
}

-(void) setupBase: (DuboPlatipus::RemoteMerguez *) merguez
 {
    self.memere = merguez;

    self.remoteControl = [[[AppleRemote alloc] initWithDelegate: self] autorelease];
    [self.remoteControl setDelegate: self];
/*
    AppleRemote* newRemoteControl = [[[AppleRemote alloc] initWithDelegate: self] autorelease];
    [newRemoteControl setDelegate: self];
    [self setRemoteControl: newRemoteControl];
*/
    //	// OPTIONAL CODE
//	// The MultiClickRemoteBehavior adds extra functionality.
//	// It works like a middle man between the delegate and the remote control
//	remoteBehavior = [MultiClickRemoteBehavior new];
//	[remoteBehavior setDelegate: self];
//	[newRemoteControl setDelegate: remoteBehavior];

}

// for bindings access
/*
- (RemoteControl*) remoteControl {
    return self.remoteControl;
}
- (void) setRemoteControl: (RemoteControl*) newControl {
    [self.remoteControl autorelease];
    self.remoteControl = [newControl retain];
}
*/

-(void) start
 {
    [self.remoteControl startListening: self];
 }

-(void) stop
 {
    [self.remoteControl stopListening: self];
 }
@end


class DuboPlatipus::RemoteMerguez::Private{
public:
    RemoteControl * rem;
    SaucisseMain * saucisse;
};

namespace DuboPlatipus{

RemoteMerguez::RemoteMerguez(QWidget * win, QObject *parent) :
QObject(parent)
{
    CocoaInitializer initializer;
    d = new Private();
    d->saucisse = [SaucisseMain alloc];
    [d->saucisse setupBase: this];
    if(win->isActiveWindow()){
        [d->saucisse start];
    }else{
        [d->saucisse stop];
    }
    win->installEventFilter(this);
}

bool RemoteMerguez::eventFilter(QObject */*object*/, QEvent *event)
{
    if((event->type() == QEvent::WindowDeactivate) || (event->type() == QEvent::WindowDeactivate))
        CocoaInitializer initializer;
    switch(event->type()){
    case QEvent::WindowActivate:
        [d->saucisse start];
        break;
    case QEvent::WindowDeactivate:
        [d->saucisse stop];
        break;
    default:
        break;
    }
    return false;
}

void RemoteMerguez::hello(int sig, bool pressed){
    emit merguez(sig, pressed);
}

}

