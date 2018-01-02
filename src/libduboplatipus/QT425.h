/**
 * Copyright (c) 2018, Dubo Dubon Duponey <dubodubonduponey@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DUBOPLATIPUS_QT425_H
#define DUBOPLATIPUS_QT425_H

#include "libduboplatipus/libduboplatipus_global.h"

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#include <QString>
#include <QDesktopServices>

class LIBDUBOPLATIPUSSHARED_EXPORT QStandardPaths: public QObject {
    Q_OBJECT
public:
    // Do not re-order, must match QDesktopServices
    enum StandardLocation {
        DesktopLocation,
        DocumentsLocation,
        FontsLocation,
        ApplicationsLocation,
        MusicLocation,
        MoviesLocation,
        PicturesLocation,
        TempLocation,
        HomeLocation,
        DataLocation,
        CacheLocation,
        GenericDataLocation,
        RuntimeLocation,
        ConfigLocation,
        DownloadLocation,
        GenericCacheLocation
    };

    static QString writableLocation(StandardLocation type)
    {
        switch(type){
        case QStandardPaths::CacheLocation:
            return QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
            break;
        case QStandardPaths::DocumentsLocation:
            return QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);
            break;
        case QStandardPaths::TempLocation:
            return QDesktopServices::storageLocation(QDesktopServices::TempLocation);
            break;
        case QStandardPaths::DataLocation:
            return QDesktopServices::storageLocation(QDesktopServices::DataLocation);
            break;
        default:
            break;
        }
        return QString("");
    }

//    static QStringList standardLocations(StandardLocation type)
//    {
//    }

//    enum LocateOption {
//        LocateFile = 0x0,
//        LocateDirectory = 0x1
//    };
//    Q_DECLARE_FLAGS(LocateOptions, LocateOption)

//    static QString locate(StandardLocation type, const QString &fileName, LocateOptions options = LocateFile);
//    static QStringList locateAll(StandardLocation type, const QString &fileName, LocateOptions options = LocateFile);
//    static QString displayName(StandardLocation type);

//    static QString findExecutable(const QString &executableName, const QStringList &paths = QStringList());

//    static void enableTestMode(bool testMode);
//    static bool isTestModeEnabled();

private:
    // prevent construction
//    QStandardPaths()
//    ~QStandardPaths();
};
#else
#include <QStandardPaths>
#endif


#endif // DUBOPLATIPUS_QT425_H
