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

#include "libduboplatipus/mediakeys.h"
#include "cocoainit.h"
#import <Cocoa/Cocoa.h>
#import "SPMediaKeyTap.h"

@interface SPMediaKeyTapExampleAppDelegate : NSObject <NSApplicationDelegate> {
}
@property (atomic) DuboPlatipus::MediaKeys * mk;
@end

@implementation SPMediaKeyTapExampleAppDelegate{
}

-(void)mediaKeyTap:(SPMediaKeyTap*)keyTap receivedMediaKeyEvent:(NSEvent*)event
{
    #pragma unused (keyTap)
    NSAssert([event type] == NSSystemDefined && [event subtype] == SPSystemDefinedEventMediaKeys, @"Unexpected NSEvent in mediaKeyTap:receivedMediaKeyEvent:");
    // here be dragons...
    int keyCode = (([event data1] & 0xFFFF0000) >> 16);
    int keyFlags = ([event data1] & 0x0000FFFF);
    BOOL keyIsPressed = (((keyFlags & 0xFF00) >> 8)) == 0xA;
    int keyRepeat = (keyFlags & 0x1);

    if (keyIsPressed) {
        NSLog(@"Down");
        self.mk->hello(keyCode, keyRepeat, false);
    }else{
        NSLog(@"Up");
        self.mk->hello(keyCode, keyRepeat, true);
    }
//        NSString *debugString = [NSString stringWithFormat:@"%@", keyRepeat?@", repeated.":@"."];
//        switch (keyCode) {
//            case NX_KEYTYPE_PLAY:
//                debugString = [@"Play/pause pressed" stringByAppendingString:debugString];
//                break;

//            case NX_KEYTYPE_FAST:
//                debugString = [@"Ffwd pressed" stringByAppendingString:debugString];
//                break;

//            case NX_KEYTYPE_REWIND:
//                debugString = [@"Rewind pressed" stringByAppendingString:debugString];
//                break;
//            default:
//                debugString = [NSString stringWithFormat:@"Key %d pressed%@", keyCode, debugString];
//                break;
//            // More cases defined in hidsystem/ev_keymap.h
//        }
}
//#define NX_KEYTYPE_PLAY			16
//#define NX_KEYTYPE_NEXT			17
//#define NX_KEYTYPE_PREVIOUS		18
//#define NX_KEYTYPE_FAST			19
//#define NX_KEYTYPE_REWIND		20
@end

class DuboPlatipus::MediaKeys::Private{
public:
    SPMediaKeyTapExampleAppDelegate * delegate;
    SPMediaKeyTap * keyTap;
};

namespace DuboPlatipus{

MediaKeys::MediaKeys(QWidget * win, QObject *parent) :
QObject(parent)
{
    d = new DuboPlatipus::MediaKeys::Private();
    CocoaInitializer initializer;
    d->delegate = [SPMediaKeyTapExampleAppDelegate alloc];
    d->delegate.mk = this;
    [[NSUserDefaults standardUserDefaults] registerDefaults:[NSDictionary dictionaryWithObjectsAndKeys:
        [SPMediaKeyTap defaultMediaKeyUserBundleIdentifiers], kMediaKeyUsingBundleIdentifiersDefaultsKey,
    nil]];

    d->keyTap = [[SPMediaKeyTap alloc] initWithDelegate: d->delegate];
    if([SPMediaKeyTap usesGlobalMediaKeyTap]){
        [d->keyTap startWatchingMediaKeys];
    }
    // Deactivate on background
    win->installEventFilter(this);
}

bool MediaKeys::eventFilter(QObject */*object*/, QEvent *event)
{
    switch(event->type()){
    case QEvent::WindowActivate:
        [d->keyTap startWatchingMediaKeys];
        break;
    case QEvent::WindowDeactivate:
        [d->keyTap stopWatchingMediaKeys];
        break;
    default:
        break;
    }
    return false;
}

void MediaKeys::hello(int keyCode, int keyRepeat, bool isUp){
    // XXX store lastdown repeat to reforward it as well in up and pressed?
    // Match as closely as possible the merguez behavior, even if it's brain dead for now
    emit this->merguez(keyCode, (keyRepeat == 1), !isUp);
}

}
