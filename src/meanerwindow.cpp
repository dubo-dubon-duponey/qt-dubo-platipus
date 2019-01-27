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

#include "libduboplatipus/meanerwindow.h"
#include <QApplication>
#include <QDebug>
#include <QWindowStateChangeEvent>

namespace DuboPlatipus{

MeanerWindow::MeanerWindow(QWidget * window, QObject * parent): LesserWindow(window, parent)
{
    // Allow mouse tracking in ther
    m_window->setMouseTracking(true);
    // Controls various eventing on the main window (activate and stuff)
    m_window->installEventFilter(this);
}

bool MeanerWindow::eventFilter(QObject * object, QEvent *event)
{
    // Intercepted mouse moves (from the stacked player for eg) emit a signal
    // So do activate / deactivate
    // QWindowStateChangeEvent * canard = (QWindowStateChangeEvent *) event;
    switch(event->type()){
//    case QEvent::KeyPress:
//    case QEvent::KeyRelease:
//        emit outboundKey((QKeyEvent *) event);
//        break;
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseMove:
//        qDebug() << "SOME MOUSE MOVE" << ((QMouseEvent *) event)->x() << ((QMouseEvent *) event)->y();
        // This is meant to be reforwarded to another widget
        emit outboundMouse((QMouseEvent *) event);
        return true;
        break;
    case QEvent::WindowActivate:
        m_window->setMouseTracking(true);
        emit activated();
        break;
    case QEvent::WindowDeactivate:
        emit deactivated();
        break;
    case QEvent::WindowStateChange:
    // Window states are unusable with our hacks and lion FS support - emit as is and let js do the dance
//            qDebug() << canard->oldState();
//            qDebug() << widget->windowState();
//            qDebug() << (widget->windowState() & canard->oldState());
        emit windowStateChanged();
        break;
    default:
        break;
    }
    return QObject::eventFilter(object, event);
}


//    widget->setAttribute(Qt::WA_NoSystemBackground, true);

//    widget->setAttribute(Qt::WA_TranslucentBackground, true);
//    widget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);


//    noredraw = false;

    //    widget->showMinimized();
    // menuBar()->addMenu(tr("&File"));
    // | Qt::WindowShadeButtonHint);

//    this->setAttribute(Qt::WA_TranslucentBackground ,true );

//    this->setStyleSheet("*{background-color: red;}");
//    this->setAttribute(Qt::WA_MacMetalStyle,true );
//    this->setAttribute(Qt::WA_MacMetalStyle,true );


    //    QWidget::setVisible(false);
    // setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
//    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint );// | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
//    QWidget::setVisible(true);
//        ChangeWindowAttributes(qt_mac_window_for(this), kWindowNoAttributes, kWindowFullZoomAttribute);

//MeanerWindow::~MeanerWindow()
//{

//}


//        case QEvent::Resize:
//            event->accept();
//            return true;
//        break;
//        case QEvent::LayoutRequest:
//            qDebug() << "Cancelling layout request";
//            event->accept();
//            return true;
//        break;

        //        case QEvent::Drop:
//        qDebug() << "***************************** DROPPED";
//        break;
//        case QEvent::Wheel:
//        qDebug() << "Bitch wheely";
//        break;
//        default:
//        break;
//        case QEvent::Paint:
//            QPainter painter(this->widget);
//            painter.setRenderHint(QPainter::Antialiasing);
//            painter.setRenderHint(QPainter::HighQualityAntialiasing);///	0x08	An OpenGL-specific rendering hint indicating that the engine should use fragment programs and offscreen rendering for antialiasing.
//            painter.setRenderHint(QPainter::TextAntialiasing);//	0x02	Indicates that the engine should antialias text if possible. To forcibly disable antialiasing for text, do not use this hint. Instead, set QFont::NoAntialias on your font's style strategy.
//            painter.save();

//            if(noredraw){
///*                QRect rect = this->widget->rect();
//                QRegion t;
//                t += rect;
//                this->widget->setMask(t);*/
//                this->widget->clearMask();
//                qDebug() << "NO REDRAW!!!!";
//                return false;
//            }

//            qDebug() << "REDRAW";
/*            this->setRoundCorner();
            return true;*/


/*            qreal opacity(1);
            int roundness(12);
            QRect widget_rect = this->widget->rect();

            painter.setPen(Qt::red);

            // clip
            QPainterPath rounded_rect;
            rounded_rect.addRoundRect(1, 1, widget_rect.width() - 2, widget_rect.height() - 2, roundness, roundness);
            painter.setClipPath(rounded_rect);

            // get clipping region
            QRegion maskregion = painter.clipRegion();

            // mask the widget
            this->widget->setMask(maskregion);
            painter.setOpacity(opacity);

            // fill path with color
            painter.fillPath(rounded_rect,QBrush(Qt::black));

            // restore painter
            painter.restore();*/
/*
            QRect widget_rect = this->widget->rect();
            int roundness(12);


            QPainter painter(this->widget);
            painter.save();

            painter.setRenderHint(QPainter::Antialiasing);
            QPainterPath rounded_rect;
            rounded_rect.addRoundRect(1, 1, widget_rect.width() - 2, widget_rect.height() - 2, roundness, roundness);
            painter.setClipPath(rounded_rect);

            // get clipping region
            QRegion maskregion = painter.clipRegion();

            // mask the widget
            this->widget->setMask(maskregion);

            painter.restore();
*/

            // WORTH TRYING BETTER THAN THE REST OF THE CRAP
//            QPixmap pixmap(this->widget->size());
//            QPainter painter(&pixmap);
//            painter.fillRect(pixmap.rect(), Qt::white);
//            painter.setBrush(Qt::black);
//            painter.drawRoundRect(pixmap.rect());
//            this->widget->setMask(pixmap.createMaskFromColor(Qt::white));


//            QPainter painter(this->widget);
//            painter.setRenderHints(QPainter::Antialiasing);

//            QRegion region;
//            int r = 5;
//            QRect rect = this->widget->rect();

//            region += rect.adjusted(r, 0, -r, 0);
//            region += rect.adjusted(0, r, 0, -r);

//            // top left
//            QRect corner(rect.topLeft(), QSize(r * 2, r * 2));
//            region += QRegion(corner, QRegion::Ellipse);

//            // top right
//            corner.moveTopRight(rect.topRight());
//            region += QRegion(corner, QRegion::Ellipse);

//            // bottom left
//            corner.moveBottomLeft(rect.bottomLeft());
//            region += QRegion(corner, QRegion::Ellipse);

//            // bottom right
//            corner.moveBottomRight(rect.bottomRight());
//            region += QRegion(corner, QRegion::Ellipse);

////            QRegion maskedRegion(region);
////            int side = qMin(this->widget->width(), this->widget->height());
////            QRegion maskedRegion(this->widget->width() / 2 - side / 2, this->widget->height() / 2 - side / 2, side,
////                                 side, QRegion::Ellipse);
///*            QPixmap pixmap(":/images/tux.png");
//               topLevelLabel.setPixmap(pixmap);
//               topLevelLabel.setMask(pixmap.mask());*/

////            QPixmap alpha = QPixmap(":/logo.png");
////            this->widget->setMask(alpha.mask());
///*            QPixmap alphacopy = alpha;
//            alphacopy.setMask(alphacopy.mask());*/
////            QBitmap theMask = alpha.createHeuristicMask(false);

//            this->widget->setMask(region);


//void MeanerWindow::setRoundCorner()
//{
//    qDebug() << "Forceful redraw";
////        this->widget->clearMask();
//    QRegion region;
//    int r = 50;
//    // middle and borders
//    QRect rect = this->widget->rect();

//    region += rect.adjusted(r, 0, -r, 0);
//    region += rect.adjusted(0, r, 0, -r);

//    // top left
//    QRect corner(rect.topLeft(), QSize(r*2, r*2));
//    region += QRegion(corner, QRegion::Ellipse);

//    // top right
//    corner = QRect(rect.topRight(), QSize(r*2, r*2));
////        corner.moveTopRight(rect.topRight());
//    region += QRegion(corner, QRegion::Ellipse);

//    // bottom left
//    corner = QRect(rect.bottomLeft(), QSize(r*2, r*2));
////        corner.moveBottomLeft(rect.bottomLeft());
//    region += QRegion(corner, QRegion::Ellipse);

//    // bottom right
//    corner = QRect(rect.bottomRight(), QSize(r*2, r*2));
////        corner.moveBottomRight(rect.bottomRight());
//    region += QRegion(corner, QRegion::Ellipse);

//    QRegion maskedRegion(region);
////            int side = qMin(this->widget->width(), this->widget->height());
////            QRegion maskedRegion(this->widget->width() / 2 - side / 2, this->widget->height() / 2 - side / 2, side,
////                                 side, QRegion::Ellipse);
//    this->widget->setMask(maskedRegion);
//}

//void MeanerWindow::toggleRedraw()
//{
//    noredraw = !noredraw;
//    if(!noredraw){
////        QRect rect = this->widget->rect();
////        QRegion region;
////        region += rect.adjusted(50, 50, -50, -50);
////        this->widget->setMask(region);

//        // XXX FIXME - thin borders are back

//        QRegion region;
//        QRect rect = this->widget->rect();
//        int r = 5;

//        region += rect.adjusted(r, 0, -r, 0);
//        region += rect.adjusted(0, r, 0, -r);

//        // top left
//        QRect corner(rect.topLeft(), QSize(r * 2, r * 2));
//        region += QRegion(corner, QRegion::Ellipse);

//        // top right
//        corner.moveTopRight(rect.topRight());
//        region += QRegion(corner, QRegion::Ellipse);

//        // bottom left
//        corner.moveBottomLeft(rect.bottomLeft());
//        region += QRegion(corner, QRegion::Ellipse);

//        // bottom right
//        corner.moveBottomRight(rect.bottomRight());
//        region += QRegion(corner, QRegion::Ellipse);

//        this->widget->setMask(region);

//    }else{
//        this->widget->clearMask();
//    }

//}

void MeanerWindow::show()
{
    m_window->show();
}

void MeanerWindow::hide()
{
    m_window->hide();
}

void MeanerWindow::raise()
{
    m_window->raise();
}

void MeanerWindow::lower()
{
    m_window->lower();
}

void MeanerWindow::close()
{
    m_window->close();
    emit updated();
}

void MeanerWindow::maximize()
{
    if (this->fullscreen())
        this->setFullscreen(false);
    m_window->showMaximized();
    emit updated();
}

void MeanerWindow::minimize()
{
    if (this->fullscreen())
        this->setFullscreen(false);
    m_window->showMinimized();
    emit updated();
}

void MeanerWindow::normal()
{
    // Quit fullscreen if any
    if (this->fullscreen())
        this->setFullscreen(false);
    m_window->showNormal();
    emit updated();
}

void MeanerWindow::activate()
{
    m_window->activateWindow();
    emit updated();
}




bool MeanerWindow::isMaximized()
{
    return m_window->isMaximized();
}

bool MeanerWindow::isMinimized()
{
    return m_window->isMinimized();
}

bool MeanerWindow::isActive()
{
    return m_window->isActiveWindow();
}


// Geometry
int MeanerWindow::w()
{
    // XXX likely inaccurate (see frame geometry)
    return m_window->width();
}

int MeanerWindow::h()
{
    return m_window->height();
}

int MeanerWindow::minw()
{
    return m_window->minimumWidth();
}

int MeanerWindow::minh()
{
    return m_window->minimumHeight();
}

int MeanerWindow::maxw()
{
    return m_window->maximumWidth();
}

int MeanerWindow::maxh()
{
    return m_window->maximumHeight();
}

void MeanerWindow::setMinh(int h)
{
    m_window->setMinimumHeight(h);
    emit updated();
}

void MeanerWindow::setMinw(int w)
{
    m_window->setMinimumWidth(w);
    emit updated();
}

void MeanerWindow::setMaxh(int h)
{
    m_window->setMaximumHeight(h);
    emit updated();
}

void MeanerWindow::setMaxw(int w)
{
    m_window->setMaximumWidth(w);
    emit updated();
}

void MeanerWindow::setSize(int w, int h)
{
    m_window->setGeometry(this->x(), this->y(), w, h);
    emit updated();
}

void MeanerWindow::moveBy(int x, int y)
{
    this->moveTo(this->x() + x, this->y() + y);
}

}
