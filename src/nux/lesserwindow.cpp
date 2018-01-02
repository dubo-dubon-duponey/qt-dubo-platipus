/*
 * Copyright (c) 2018, Dubo Dubon Duponey <dubodubonduponey@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */

#include "libduboplatipus/lesserwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QApplication>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>


namespace DuboPlatipus{


LesserWindow::LesserWindow(QWidget *parent)
    : QWidget(parent)
{
//    this->setWindowFlags(Qt::FramelessWindowHint);//  | Qt::WindowSystemMenuHint);
}

// The reason for this is that QT is broken when it comes to maximize and/or n/ne/w resizing
int LesserWindow::x() const
{
    return QWidget::x();
}

int LesserWindow::y() const
{
    return QWidget::y();
}

bool LesserWindow::minimizeOnDoubleClick() const
{
    return true;
}

bool LesserWindow::hasNaturalStyle() const
{
    return true;
}

bool LesserWindow::needsResizer() const
{
    return true;
}

void LesserWindow::startMovable()
{

}

void LesserWindow::stopMovable()
{

}

void LesserWindow::move(int /*x*/, int /*y*/)
{

}


}
