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

#ifndef DUBOMODULES_UI_ICON_H
#define DUBOMODULES_UI_ICON_H

#include <QObject>
#include <QMenu>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>

// Helper scriptable object that passes uris around
namespace DuboPlatipus{
namespace UI{

class Icon : public QObject
{
    Q_OBJECT
public:
    explicit Icon(QObject * parent = nullptr): QObject(parent){
        connect(
            &netManager, SIGNAL (finished(QNetworkReply*)),
            this, SLOT (iconDownloaded(QNetworkReply*))
         );
    }

    Q_PROPERTY(QString  URI    READ getURI WRITE setURI  NOTIFY updated)

    QPixmap * internalIcon = new QPixmap();

signals:
    void updated();

private slots:
    void iconDownloaded(QNetworkReply* pReply){
        QByteArray data = pReply->readAll();
        pReply->deleteLater();
        internalIcon->loadFromData(data);
        emit updated();
    }

private:
    QNetworkAccessManager netManager;

    QString getURI() const {
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        internalIcon->save(&buffer, "PNG");
        return QString::fromLatin1("data:image/png;base64,") + QString::fromLatin1(byteArray.toBase64());
    }

    void setURI(const QString url) {
        netManager.get(QNetworkRequest(url));
    }

};
}
}

#endif // DUBOMODULES_UI_ICON_H
