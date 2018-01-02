#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>

#include <libduboplatipus/root.h>
#include <libduboplatipus/apputils.h>
#include <libduboplatipus/basepowermanagement.h>
#include <libduboplatipus/lesserwindow.h>
#include <libduboplatipus/mediakeys.h>
#include <libduboplatipus/merguez.h>
#include <libduboplatipus/powermanager.h>
#include <libduboplatipus/QT425.h>

#include "zero.h"


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    DuboPlatipus::Root * root = new DuboPlatipus::Root();
    qDebug() << root->getName();
    qDebug() << root->getBuildType();
    qDebug() << root->getLinkType();
    qDebug() << root->getQt();
    qDebug() << root->getVendor();
    qDebug() << root->getVersion();
    qDebug() << root->getRevision();
    qDebug() << root->getChangeset();

    qDebug() << root->getLibName();
    qDebug() << root->getLibVersion();
    qDebug() << root->getLibRevision();

    QWidget * w = new QWidget();
    w->show();

    new Zero();


    //    DuboPlatipus::AppUtils * a;
//    DuboPlatipus::BasePowerManagement * b;
//    DuboPlatipus::LesserWindow * c;
//    DuboPlatipus::MediaKeys * d;
//    DuboPlatipus::RemoteMerguez * e;
//    DuboPlatipus::PowerManager * f;
//    qDebug() << QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

    return app.exec();
}
