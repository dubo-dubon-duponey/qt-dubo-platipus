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

    DuboPlatipus::PowerManager * b = new DuboPlatipus::PowerManager();
    qDebug() << b->getState();

    DuboPlatipus::LesserWindow * c = new DuboPlatipus::LesserWindow();
    DuboPlatipus::MediaKeys * d = new DuboPlatipus::MediaKeys(view);
    DuboPlatipus::RemoteMerguez * e = new DuboPlatipus::RemoteMerguez(view);
    DuboPlatipus::PowerManager * f = new DuboPlatipus::PowerManager();
    qDebug() << QStandardPaths::writableLocation(QStandardPaths::CacheLocation);



    // Attach objects to the javascript context
    DuboPlatipus::Root * root = new DuboPlatipus::Root();
    chan->registerObject("Root", root);
    // chan->registerObject("Dubo", notifier);

    return app.exec();



}
