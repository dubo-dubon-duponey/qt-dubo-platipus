#ifndef ZERO_H
#define ZERO_H

#include <QObject>
#include <QtNetwork/QHostInfo>
#include <libduboplatipus/zerohello/record.h>
#include <libduboplatipus/zerohello/registrar.h>

using namespace DuboPlatipus::ZeroHello;

class Zero : public QObject
{
    Q_OBJECT
public:
    explicit Zero(QObject *parent = 0);
    
signals:

private:
    Registrar * registrar;
    
public slots:
    // Called when we are registered
    void registeredSlot(const Record &);
    // Called when someone is detected
    void newAnnounceSlot(const QList<Record> &list);
    // Called when resolve completes
    void resolveCompleteSlot(const QHostInfo & qhi,int port);
};

#endif // ZERO_H
