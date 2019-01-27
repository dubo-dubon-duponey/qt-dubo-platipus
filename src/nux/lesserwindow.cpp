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

#include "libduboplatipus/lesserwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>


namespace DuboPlatipus{

LesserWindow::LesserWindow(QWidget * window, QObject * parent): QObject(parent), m_window(window)
{
}

// The reason for this is that QT is broken when it comes to maximize and/or n/ne/w resizing
int LesserWindow::x() const
{
    return m_window->x();
}

int LesserWindow::y() const
{
    return m_window->y();
}

bool LesserWindow::fullscreen()
{
    return m_window->isFullScreen();
}

void LesserWindow::setFullscreen(bool value)
{
    if(!m_window->isFullScreen()){
        m_window->showFullScreen();
    }
    else if(m_window->isMaximized())
        m_window->showMaximized();
    else
        m_window->showNormal();
}


bool LesserWindow::shouldMinimizeOnDoubleClick()
{
    return true;
}

void LesserWindow::moveTo(int x, int y)
{
    return m_window->setGeometry(x, y, m_window->width(), m_window->height());

}

}
