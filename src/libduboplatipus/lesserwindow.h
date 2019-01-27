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

#ifndef DUBOPLATIPUS_LESSERWINDOW_H
#define DUBOPLATIPUS_LESSERWINDOW_H

#include "libduboplatipus/global.h"
#include <QWidget>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QDebug>

namespace DuboPlatipus {

class LIBDUBOPLATIPUSSHARED_EXPORT LesserWindow: public QObject {
    Q_OBJECT
public:
    explicit LesserWindow(QWidget * window, QObject * parent = nullptr);
//    ~LesserWindow();

    Q_PROPERTY(bool moveable    READ moveable    WRITE setMoveable   NOTIFY updated)
    Q_PROPERTY(bool shadow      READ shadow      WRITE setShadow     NOTIFY updated)
    Q_PROPERTY(double alpha     READ alpha       WRITE setAlpha      NOTIFY updated)

    Q_PROPERTY(bool fullscreen  READ fullscreen   WRITE setFullscreen NOTIFY updated)
    bool fullscreen();
    void setFullscreen(bool value);

    // XXX these are not properties yet for we do not listen on changes
    Q_INVOKABLE bool shouldMinimizeOnDoubleClick();
    Q_INVOKABLE bool isDarkMode();
    Q_INVOKABLE int accentColor();

    Q_PROPERTY(int x            READ x                                  NOTIFY updated)
    Q_PROPERTY(int y            READ y                                  NOTIFY updated)
    Q_INVOKABLE void moveTo(int x, int y);

    bool moveable();
    bool shadow();
    double alpha();

    void setMoveable(bool value);
    void setShadow(bool value);
    void setAlpha(double value);

    int x() const;
    int y() const;

    // XXX temporarily public
    QWidget * m_window;


signals:
    void updated();

private:
//    QWidget * m_window;




//    bool hasNaturalStyle() const;

    //    bool eventFilter(QObject * object, QEvent *event);

//    void setGeometry(int x, int y, int w, int h);


//    void emitClicky();
//signals:
//    void dockIconClicked();

//private:
//    class Private;
//    Private* d;

public slots:
//    void repaint();
//    void update();
    //    void toto();
//    void setGeometry(int x, int y, int w, int h);

    //protected:
//    void paintEvent(QPaintEvent *event);
//    void resizeEvent(QResizeEvent *event);
//    void mousePressEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseDoubleClickEvent(QMouseEvent *event);

//    void keyPressEvent(QKeyEvent *event);
//    void focusInEvent(QFocusEvent *event);
//    void focusOutEvent(QFocusEvent *event);

//    void mouseMoveEvent(QMouseEvent *event);
//    void keyReleaseEvent(QKeyEvent * event);
//    void wheelEvent(QWheelEvent * event);

//    void enterEvent(QEvent * event);
//    void leaveEvent(QEvent * event);
//    void moveEvent(QMoveEvent * event);
//    void closeEvent(QCloseEvent * event);

//    bool event(QEvent * event)
//    {
//        qDebug() << "tipie" << event->type();
////        if(event->type() == QEvent::Resize){
////        if(event->type() == QEvent::LayoutRequest){
//        if(event->type() == QEvent::UpdateRequest){
//            qDebug() << "Getting relayout in main widget";
//            QRect r(0, 0, this->width(), this->height());
//            QStackedLayout * l = (QStackedLayout *) this->layout();
//            l->currentWidget()->setGeometry(r);
//            qDebug() << "Realyouting" << l->currentWidget();
//            event->accept();
//            return true;
////            this->setGeometry(0, 0, 1000, 1000);
//        }
//        QWidget::event(event);
//    }

//    void setGeometry(int x, int y, int w, int h)
//    {
//        qDebug() << "INTERCEPTING SHIT";
////        if(w < this->minimumWidth())
////            w = this->minimumWidth();
////        if(h < this->minimumHeight())
////            h = this->minimumHeight();
//        QRect r(x, y, w, h);
//        QWidget::setGeometry(r);
//        QRect r2d2(0, 0, this->width(), this->height());
//        this->layout()->setGeometry(r2d2);
//    }



protected:
    // Emit mouse moves over the video player
//    void mouseMoveEvent(QMouseEvent *)
//    {
//        qDebug() << "GOT A MOVE DAMNITE";
////        emit outboundMouseMove(event);
//    }

    //    void resizeEvent(QResizeEvent * event)
//    {
//        qDebug() << "Cancelling resize on child view";
//        event->accept();
//    }


//    bool macEvent ( EventHandlerCallRef caller, EventRef event )
//    {
////        [NSApplication sharedApplication];
//        qDebug() << " Mac event handling on the container";
//        qDebug() << event;
//        return false;
////        return QWidget::macEvent(caller, event);
//    }


    //    void outboundMouseMove();
//    void hasFileDrop(const QString & path);
//    void hasDirectoryDrop(const QString & path);

//public slots:
};
}

#endif // DUBOPLATIPUS_LESSERWINDOW_H

