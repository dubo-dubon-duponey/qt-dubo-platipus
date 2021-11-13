# DuboPlatipus

> "Dubo Components" are lightweight, targeted c++ libraries meant for QT applications.
> They aim at providing *simple to use* interfaces for a range of functionality
(notification, crash reporting, zero conf, application update, torrent, etc).
> Fully scriptable, they are primarily meant for javascript (from a QWebEngine) - thought they are usable as well in plain QT.
> Put together, these components should provide a comprehensive foundation for these building a "WebRunner", similarly to Electron.

This library is meant to provide functionalities and fixes that QT doesn't.
As such it contains chunks of platform dependent code.
If something can be done using simply QT APIs, then it shouldn't be here.

Currently, here is what it provides:

OSX:
- media keys support
- apple remote support
- Lion fullscreen (fallback on regular if not available)
- some QT version migration quirks
- power management support

All:
- cross-platform "growl-like" notifier

Older bits of code in there were meant to help positioning windows, proper frameless windows, etc.

Third party dependencies (MediaKeys and Remote code), check the third-party folder for license information.
Linux notificator borrowed form BitCoin repository.

Licensed under BSD2.

## TODO

Test (specifically powermanagement).
Cleanup old hacks.

Draggable is bust with QT6
