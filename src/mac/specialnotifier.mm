/**
 * Copyright (c) 2018, Dubo Dubon Duponey <dubodubonduponey+github@pm.me>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mac/specialnotifier.h"

#include <Cocoa/Cocoa.h>
#include <QPixmap>
#include <QDir>
#include <QCoreApplication>
#include <QTemporaryFile>
#include <QImageWriter>
#include <QDebug>

/*
- (IBAction)showNotification:(id)sender{
NSUserNotification *notification = [[NSUserNotification alloc] init];

notification.responsePlaceholder = @"Reply";
notification.hasReplyButton = true;

[[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:notification];
}

- (void)userNotificationCenter:(NSUserNotificationCenter *)center didActivateNotification:(NSUserNotification *)notification
{
    if (notification.activationType == NSUserNotificationActivationTypeReplied){
        NSString* userResponse = notification.response.string;
    }
}

*/

SpecialNotifier::SpecialNotifier(QObject * parent): BaseNotifier(parent)
{
}

bool SpecialNotifier::notify(const QString &appName, const QString &title, const QString &subtitle, const QString &text, const QIcon &icon, int /*time*/)
{
    // We don't yet link against 10.8 SDK so can't use this API directly yet.
    id userNotificationCenterClass = NSClassFromString(@"NSUserNotificationCenter");
    if (userNotificationCenterClass != nil) {
        this->notifyCenter(title, subtitle, text);
        return true;
    }

    // Check if Growl is installed
    CFURLRef cfurl;
    OSStatus status = LSGetApplicationForInfo(kLSUnknownType, kLSUnknownCreator, CFSTR("growlTicket"), kLSRolesAll, 0, &cfurl);
    if (status != kLSApplicationNotFoundErr) {
        CFBundleRef bundle = CFBundleCreate(0, cfurl);
        if (CFStringCompare(CFBundleGetIdentifier(bundle), CFSTR("com.Growl.GrowlHelperApp"), kCFCompareCaseInsensitive | kCFCompareBackwards) == kCFCompareEqualTo) {
            if (CFStringHasSuffix(CFURLGetString(cfurl), CFSTR("/Growl.app/")))
                this->notifyGrowl("Growl", appName, title, text, icon);
            else
                this->notifyGrowl("GrowlHelperApp", appName, title, text, icon);
            CFRelease(cfurl);
            CFRelease(bundle);
            return true;
        }
        CFRelease(cfurl);
        CFRelease(bundle);
    }
    return false;
}

bool SpecialNotifier::canNotify()
{
    id userNotificationCenterClass = NSClassFromString(@"NSUserNotificationCenter");
    if (userNotificationCenterClass != nil)
        return true;

    CFURLRef cfurl;
    OSStatus status = LSGetApplicationForInfo(kLSUnknownType, kLSUnknownCreator, CFSTR("growlTicket"), kLSRolesAll, 0, &cfurl);
    if (status != kLSApplicationNotFoundErr) {
        CFBundleRef bundle = CFBundleCreate(0, cfurl);
        if (CFStringCompare(CFBundleGetIdentifier(bundle), CFSTR("com.Growl.GrowlHelperApp"), kCFCompareCaseInsensitive | kCFCompareBackwards) == kCFCompareEqualTo) {
            CFRelease(cfurl);
            CFRelease(bundle);
            return true;
        }
        CFRelease(cfurl);
        CFRelease(bundle);
    }
    return false;
}

void SpecialNotifier::notifyCenter(const QString &title, const QString &subtitle, const QString &text)
{
    id userNotificationCenterClass = NSClassFromString(@"NSUserNotificationCenter");
    QByteArray utf8 = title.toUtf8();
    char* cString = (char *)utf8.constData();
    NSString *titleMac = [[NSString alloc] initWithUTF8String:cString];

    utf8 = subtitle.toUtf8();
    cString = (char *)utf8.constData();
    NSString *subtitleMac = [[NSString alloc] initWithUTF8String:cString];

    utf8 = text.toUtf8();
    cString = (char *)utf8.constData();
    NSString *textMac = [[NSString alloc] initWithUTF8String:cString];

    Class userNotificationClass = NSClassFromString(@"NSUserNotification");
    id userNotification = [[userNotificationClass alloc] init];

    [userNotification setValue:titleMac forKey:@"title"];
    [userNotification setValue:subtitleMac forKey:@"subtitle"];
    [userNotification setValue:textMac forKey:@"informativeText"];

//    if ([userNotification respondsToSelector:NSSelectorFromString(@"contentImage")]){
        NSString *responsePlaceholder = @"foobar";// [[NSString alloc] initWithUTF8String:@"foobar"];
//        NSAttributedString * response = @"foobar";
        NSMutableAttributedString * response = [[NSMutableAttributedString alloc] initWithString:@"firstsecondthird"];
        [userNotification setValue:@(false) forKey:@"hasReplyButton"];
        [userNotification setValue:response forKey:@"response"];
        [userNotification setValue:responsePlaceholder forKey:@"responsePlaceholder"];

/*
        - (void)userNotificationCenter:(NSUserNotificationCenter *)center didActivateNotification:(NSUserNotification *)notification
        {
            if (notification.activationType == NSUserNotificationActivationTypeReplied){
                NSString* userResponse = notification.response.string;
            }
        }
*/
        //    }

/*
    contentImage;
    identifier;
    response;
    responsePlaceholder
*/

    [[userNotificationCenterClass performSelector:@selector(defaultUserNotificationCenter)] performSelector:@selector(deliverNotification:) withObject:userNotification];

    [titleMac release];
    [textMac release];
    [userNotification release];



/*
    NSUserNotification* notification = [[NSUserNotification alloc] init];
    notification.title = title.toNSString();
    notification.subtitle = subtitle.toNSString();
    notification.informativeText = message.toNSString();
    notification.soundName = NSUserNotificationDefaultSoundName;   //Will play a default sound
    [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification: notification];
    [notification autorelease];*/

}





void SpecialNotifier::notifyGrowl(const QString & growlApp, const QString &appName, const QString &title, const QString &text, const QIcon &icon)
{
    const QString script(
        "tell application \"%5\"\n"
        "  set the allNotificationsList to {\"Notification\"}\n" // -- Make a list of all the notification types (all)
        "  set the enabledNotificationsList to {\"Notification\"}\n" // -- Make a list of the notifications (enabled)
        "  register as application \"%1\" all notifications allNotificationsList default notifications enabledNotificationsList\n" // -- Register our script with Growl
        "  notify with name \"Notification\" title \"%2\" description \"%3\" application name \"%1\"%4\n" // -- Send a Notification
        "end tell"
    );

    QString notificationApp(appName);
    QPixmap notificationIconPixmap;
    QSize size = icon.actualSize(QSize(48, 48));
    notificationIconPixmap = icon.pixmap(size);

    QString notificationIcon;
    QTemporaryFile notificationIconFile;
    if (!notificationIconPixmap.isNull() && notificationIconFile.open()) {
        QImageWriter writer(&notificationIconFile, "PNG");
        if (writer.write(notificationIconPixmap.toImage()))
            notificationIcon = QString(" image from location \"file://%1\"").arg(notificationIconFile.fileName());
    }else{
        // XXX Hackish way to get the bundle icon
        QDir iconPath = QCoreApplication::applicationDirPath();
        iconPath.cd("..");
        iconPath.cd("Resources");
        NSString * hack = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleIconFile"];
        NSRange range;
        range.location = 0;
        range.length = [hack length];
        unichar *chars = new unichar[range.location];
        [hack getCharacters:chars range:range];
        QString result = QString::fromUtf16(chars, range.length);
        delete[] chars;
        notificationIcon = QString(" image from location \"file://%1\"").arg(iconPath.filePath(result + ".icns"));
    }

    QString quotedTitle(title), quotedText(text);
    quotedTitle.replace("\\", "\\\\").replace("\"", "\\");
    quotedText.replace("\\", "\\\\").replace("\"", "\\");
    this->sendAppleScript(script.arg(notificationApp, quotedTitle, quotedText, notificationIcon, growlApp));
}

void SpecialNotifier::sendAppleScript(const QString &script) {
    QByteArray utf8 = script.toUtf8();
    char* cString = (char *)utf8.constData();
    NSString *scriptApple = [[NSString alloc] initWithUTF8String:cString];

    NSAppleScript *as = [[NSAppleScript alloc] initWithSource:scriptApple];
    NSDictionary *err = nil;
    [as executeAndReturnError:&err];
    [as release];
    [scriptApple release];
}
