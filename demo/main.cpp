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
#include <QStandardPaths>

#include <libduboplatipus/root.h>
#include <libduboplatipus/apputils.h>
#include <libduboplatipus/basepowermanagement.h>
#include <libduboplatipus/lesserwindow.h>
#include <libduboplatipus/mediakeys.h>
#include <libduboplatipus/merguez.h>
#include <libduboplatipus/powermanager.h>

#include <QtWebEngine>
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


void bitchMe()
{
    // Will bump the dock icon if the app is in the background to attract user attention
    DuboPlatipus::AppUtils * q = new DuboPlatipus::AppUtils();
    q->bitchMe();
}

int main(int argc, char *argv[])
{
    // Get your app going
    QApplication app(argc, argv);

    // Display the webview
    QFileInfo jsFileInfo(QDir::currentPath() + "/qwebchannel.js");

    if (!jsFileInfo.exists())
        QFile::copy(":/qtwebchannel/qwebchannel.js", jsFileInfo.absoluteFilePath());

    QtWebEngine::initialize();
    QWebEngineView * view = new QWebEngineView();

    QWebChannel * chan = new QWebChannel(view->page());
    view->page()->setWebChannel(chan);

    // Attach objects to the javascript context
    DuboPlatipus::Root * root = new DuboPlatipus::Root();
    DuboPlatipus::PowerManager * b = new DuboPlatipus::PowerManager();
    qDebug() << b->getState();

    chan->registerObject("Root", root);
    chan->registerObject("PowerManager", b);
    // chan->registerObject("Dubo", notifier);

    view->load(QUrl("qrc:/demo.html"));
    view->show();

    /**
     * AppUtils
     */
    // Adds a dock icon badge
    DuboPlatipus::AppUtils::badgeMe("Badge ∞!");

    // See the method above
    QTimer::singleShot(5000, bitchMe);

    qDebug() << "Is fullscreen:";
    qDebug() << DuboPlatipus::AppUtils::isFullScreen(view);
    qDebug() << "Screen dimensions:";
    qDebug() << DuboPlatipus::AppUtils::screenx();
    qDebug() << DuboPlatipus::AppUtils::screeny();
    qDebug() << DuboPlatipus::AppUtils::screenw();
    qDebug() << DuboPlatipus::AppUtils::screenh();
    qDebug() << "Render dimensions:";
    qDebug() << DuboPlatipus::AppUtils::renderx();
    qDebug() << DuboPlatipus::AppUtils::rendery();
    qDebug() << DuboPlatipus::AppUtils::renderw();
    qDebug() << DuboPlatipus::AppUtils::renderh();

    // Toggle fullscreen
    // XXX comment out for now DuboPlatipus::AppUtils::fullscrenToggle(w);


    DuboPlatipus::MediaKeys * d = new DuboPlatipus::MediaKeys(view);
    DuboPlatipus::RemoteMerguez * e = new DuboPlatipus::RemoteMerguez(view);
    DuboPlatipus::PowerManager * f = new DuboPlatipus::PowerManager();
    qDebug() << QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

    return app.exec();

    DuboPlatipus::LesserWindow * c = new DuboPlatipus::LesserWindow();



    return app.exec();
}
