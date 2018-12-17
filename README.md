# Platipus

This library is meant to provide functionalities and fixes that QT doesn't.
As such it contains chunks of platform dependent code.
If something can be done using simply QT APIs, then it shouldn't be here.

Currently, here is what it provides:

OSX:
- media keys support
- apple remote support
- Lion fullscreen (fallback on regular if not available)
- some QT4/QT5 migration quirks
- zeroconf support
- power management support

All:
- cross-platform "growl-like" notifier

Older bits of code in there were meant to help positioning windows, proper frameless windows, etc.

ZeroConf stuff largely borrowed from: http://doc.qt.digia.com/qq/qq23-bonjour.html
Third party dependencies (MediaKeys and Remote code), check the third-party folder for license information.
Linux notificator borrowed form BitCoin repository.

Licensed under BSD2.

## TODO

Test (specifically powermanagement).
Cleanup old hacks.
Hide entirely zeroconf.
