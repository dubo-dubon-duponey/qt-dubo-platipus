#include "libduboplatipus/mediakeys.h"


class DuboPlatipus::MediaKeys::Private{
public:

};

namespace DuboPlatipus{

MediaKeys::MediaKeys(QWidget * /*win*/, QObject *parent) :
QObject(parent)
{
}

bool MediaKeys::eventFilter(QObject */*object*/, QEvent */*event*/)
{
    return false;
}

void MediaKeys::hello(int keyCode, int keyRepeat, bool isUp){
    emit this->merguez(keyCode, (keyRepeat == 1), !isUp);
}

}
