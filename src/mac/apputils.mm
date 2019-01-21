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

#include "libduboplatipus/apputils.h"
#include "mac/cocoainit.h"
#include <AppKit/NSDockTile.h>
#include <AppKit/NSApplication.h>
#include <AppKit/NSWindow.h>
#include <AppKit/NSScreen.h>
#include <Foundation/NSString.h>

#include <QDebug>

namespace DuboPlatipus {

void AppUtils::badgeMe(const QString &text)
{
    [[NSApp dockTile] setBadgeLabel:text.toNSString()];
}

void AppUtils::bitchMe()
{
    [NSApp requestUserAttention:NSCriticalRequest];
}

bool AppUtils::isFullScreen(QWidget * mainWindow)
{
    NSView * nsview = reinterpret_cast<NSView *>(mainWindow->winId());
    NSWindow * nswindow = [nsview window];
    return [nswindow styleMask] & NSFullScreenWindowMask;
}

bool AppUtils::fullscrenToggle(QWidget * mainWindow)
{
    NSView * nsview = reinterpret_cast<NSView *>(mainWindow->winId());
    NSWindow * nswindow = [nsview window];
    NSWindowCollectionBehavior behavior = [nswindow collectionBehavior];
    behavior |= NSWindowCollectionBehaviorFullScreenPrimary;
    [nswindow setCollectionBehavior:behavior];
    [nswindow toggleFullScreen:nil];
    return [nswindow styleMask] & NSFullScreenWindowMask;
}

int AppUtils::renderx()
{
    return static_cast<int>([[NSScreen mainScreen] visibleFrame].origin.x);
}

int AppUtils::rendery()
{
    return static_cast<int>([[NSScreen mainScreen] visibleFrame].origin.y);
}

int AppUtils::renderw()
{
    return static_cast<int>([[NSScreen mainScreen] visibleFrame].size.width);
}

int AppUtils::renderh()
{
    return static_cast<int>([[NSScreen mainScreen] visibleFrame].size.height);
}

int AppUtils::screenx()
{
    return static_cast<int>([[NSScreen mainScreen] frame].origin.x);
}

int AppUtils::screeny()
{
    return static_cast<int>([[NSScreen mainScreen] frame].origin.y);
}

int AppUtils::screenw()
{
    return static_cast<int>([[NSScreen mainScreen] frame].size.width);
}

int AppUtils::screenh()
{
    return static_cast<int>([[NSScreen mainScreen] frame].size.height);
}


}

// XXX dispatch move event instead of setGeometry when moving window???
// That stuff is interesting - we could ditch the js driven resize - BUT - for windows et all... :(
//    [[NSApp mainWindow] setMovableByWindowBackground: YES];
//    [[NSApp mainWindow] setStyleMask: NSClosableWindowMask|NSMiniaturizableWindowMask|NSResizableWindowMask];
    // NSTexturedBackgroundWindowMask | NSResizableWindowMask | NSBorderlessWindowMask];
    //    styleMask = NSBorderlessWindowMask | NSResizableWindowMask;
    //    self = [super initWithContentRect:contentRect styleMask:styleMask
    //                              backing:backingType defer:flag];
    //    [self setMovableByWindowBackground: YES];

// Flip spaces / workspace / desktop:
// http://developer.apple.com/library/mac/#documentation/Cocoa/Reference/ApplicationKit/Classes/NSWindow_Class/Reference/Reference.html
// QDesktopWidget?
// http://stackoverflow.com/questions/6250864/change-to-other-space-macosx-programmatically
// http://stackoverflow.com/questions/1694582/is-there-a-way-to-make-a-custom-nswindow-work-with-spaces/6847930#6847930
//CGSConnection connection = _CGSDefaultConnection();
//CGSMoveWorkspaceWindowList(connection, &windowNumber, 1, newSpaceNumber);
//http://code.google.com/p/undocumented-goodness/source/browse/trunk/CoreGraphics/CGSPrivate.h?spec=svn13&r=13

// Not doable without using private APIs

//void MacSaucisse::flipSpace(void * winId, int newSpaceNumber)
//{
////extern CGError CGSMoveWorkspaceWindowList(const CGSConnection connection, CGSWindow *wids, int count, CGSWorkspace toWorkspace);
//    CGSConnection connection = _CGSDefaultConnection();
//    CGSMoveWorkspaceWindowList(connection, winId, 1, newSpaceNumber);
//}

// Not sure this is doable while still supporting 10.6? Check what VLC does?
// Native Lion fullscreen
// http://comments.gmane.org/gmane.comp.lib.qt.qt5-feedback/584
// https://bugreports.qt-project.org/browse/QTBUG-22043



// https://developer.apple.com/library/mac/#DOCUMENTATION/Carbon/Conceptual/customizing_docktile/docktasks_cocoa/docktasks_cocoa.html
