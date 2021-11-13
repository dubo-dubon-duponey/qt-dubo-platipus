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

#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QTimer>
#include <QDebug>

#include <libduboplatipus/root.h>
#include <libduboplatipus/apputils.h>
#include <libduboplatipus/lesserwindow.h>
#include <libduboplatipus/mediakeys.h>
#include <libduboplatipus/merguez.h>
#include <libduboplatipus/powermanager.h>

#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
#include <QtWebEngine>
#endif
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QFileInfo>
#include <QDir>
#include <QWebChannel>

void OutputLibraryInfo(){
    DuboPlatipus::Root * root = new DuboPlatipus::Root();
    qDebug() << root->property("NAME");
    qDebug() << root->property("VENDOR");
    qDebug() << root->property("VERSION");
    qDebug() << root->property("REVISION");
    qDebug() << root->property("CHANGESET");
    qDebug() << root->property("BUILD");
    qDebug() << root->property("LINK");
    qDebug() << root->property("QT");
    qDebug() << root->property("PLUGIN_NAME");
    qDebug() << root->property("PLUGIN_VERSION");
    qDebug() << root->property("PLUGIN_REVISION");
}


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    QtWebEngine::initialize();
#endif

    // Get your app going
    QApplication app(argc, argv);

    QFileInfo jsFileInfo(QDir::currentPath() + QString::fromLatin1("/qwebchannel.js"));

    if (!jsFileInfo.exists())
        QFile::copy(QString::fromLatin1(":/qtwebchannel/qwebchannel.js"), jsFileInfo.absoluteFilePath());

    QWebEngineView * view = new QWebEngineView();

    QWebChannel * chan = new QWebChannel(view->page());
    view->page()->setWebChannel(chan);

    // Attach objects to the javascript context
    DuboPlatipus::Root * root = new DuboPlatipus::Root();
    DuboPlatipus::PowerManager * b = new DuboPlatipus::PowerManager();
    DuboPlatipus::AppUtils * au = new DuboPlatipus::AppUtils(view);
    DuboPlatipus::LesserWindow * lw = new DuboPlatipus::LesserWindow(view, view);

    chan->registerObject(QString::fromLatin1("Root"), root);
    chan->registerObject(QString::fromLatin1("PowerManager"), b);
    chan->registerObject(QString::fromLatin1("AppUtils"), au);
    chan->registerObject(QString::fromLatin1("Window"), lw);

    view->load(QUrl(QString::fromLatin1("qrc:/demo.html")));
    view->show();

    DuboPlatipus::MediaKeys * d = new DuboPlatipus::MediaKeys(view);
    DuboPlatipus::RemoteMerguez * e = new DuboPlatipus::RemoteMerguez(view);

    d->hello(1, 1, true);
    e->hello(1, true);

    return app.exec();
}
