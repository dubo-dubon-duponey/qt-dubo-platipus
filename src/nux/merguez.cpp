#include "libduboplatipus/merguez.h"

class DuboPlatipus::RemoteMerguez::Private{
public:
};

namespace DuboPlatipus{

RemoteMerguez::RemoteMerguez(QWidget * /*win*/, QObject * parent) :
QObject(parent)
{
}

bool RemoteMerguez::eventFilter(QObject */*object*/, QEvent */*event*/)
{
    return false;
}

void RemoteMerguez::hello(int /*sig*/, bool /*pressed*/){
}

}

