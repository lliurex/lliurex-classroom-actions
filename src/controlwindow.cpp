/*
    Lliurex classroom actions

    Copyright (C) 2020  Enrique Medina Gremaldos <quiqueiii@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "controlwindow.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QDirIterator>
#include <QDebug>

ControlWindow::ControlWindow(): QMainWindow()
{
    setWindowTitle("LliureX Classroom Actions");
    
    QDirIterator it(".",QDir::Files);
    
    while (it.hasNext()) {
        QString file_name=it.next();
        if (file_name.endsWith(".desktop")) {
            qDebug()<<"* "<<file_name;
            
            actions.push_back(new ClassroomAction(file_name));
        }
    }
    
    QVBoxLayout *layout = new QVBoxLayout;
    
    for (auto a : actions) {
        QPushButton* button;
        
        button = new QPushButton(a->name());
        qDebug()<<"exec:["<<a->exec()<<"]";
        
        layout->addWidget(button);
        
        connect(button, &QPushButton::clicked, [this,a] { 
            qDebug()<<"run:"<<a->name();
            a->run();
        });
    }
    
    setCentralWidget(new QWidget());
    centralWidget()->setLayout(layout);
    
}

ControlWindow::~ControlWindow()
{
    
}
