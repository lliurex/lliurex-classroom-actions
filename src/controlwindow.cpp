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

#include <QApplication>
#include <QScreen>
#include <QStyle>
#include <QDesktopWidget>
#include <QFrame>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QDirIterator>
#include <QDebug>

using namespace std;

static void loadDesktops(QDirIterator& it,vector<ClassroomAction*>& actions)
{
    while (it.hasNext()) {
        QString file_name=it.next();
        if (file_name.endsWith(".desktop")) {
            qDebug()<<"* "<<file_name;
            
            actions.push_back(new ClassroomAction(file_name));
        }
    }
}

ControlWindow::ControlWindow(): QMainWindow()
{
    setWindowTitle("LliureX Classroom Actions");
    //setMaximumHeight(500);
    setFixedSize(QSize(400, 550));
    setWindowFlags(Qt::Dialog);
    
    // ehhm... maybe this code needs a best effort
    QScreen* screen = QApplication::primaryScreen();
    setGeometry(
        QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,size(),
        screen->geometry()));
    
    QFrame* mainFrame;
    QVBoxLayout* mainLayout;
    
    mainFrame = new QFrame();
    mainLayout = new QVBoxLayout();
    mainFrame->setLayout(mainLayout);
    setCentralWidget(mainFrame);
    
    QFrame* desktopsFrame;
    QVBoxLayout* desktopsLayout;
    QScrollArea* desktopsScroll;
    
    desktopsFrame = new QFrame();
    desktopsFrame->setFrameShape(QFrame::StyledPanel);
    //desktopsFrame->setMaximumHeight(600);
    //desktopsFrame->setMinimumHeight(100);
    desktopsLayout = new QVBoxLayout();
    desktopsScroll = new QScrollArea();
    desktopsScroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    desktopsScroll->setWidgetResizable(true);
    desktopsFrame->setLayout(desktopsLayout);
    desktopsScroll->setWidget(desktopsFrame);
    mainLayout->addWidget(desktopsScroll);
    
    QDialogButtonBox* buttonBox;
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);
    connect(buttonBox,&QDialogButtonBox::clicked, [this](QAbstractButton* button) {
        this->hide();
    });
    mainLayout->addWidget(buttonBox);
    
    QDirIterator localDesktops(".",QDir::Files);
    loadDesktops(localDesktops,actions);
    
    QDirIterator shareDesktops("/usr/share/lliurex-classroom-actions/actions/",QDir::Files);
    loadDesktops(shareDesktops,actions);    
    
    for (auto a : actions) {
        QPushButton* button;
        QIcon icon=QIcon::fromTheme(a->icon());
        
        button = new QPushButton(icon,a->name());
        button->setIconSize(QSize(32,32));
        button->setStyleSheet("text-align:left;");
        
        desktopsLayout->addWidget(button);
        
        connect(button, &QPushButton::clicked, [this,a] { 
            qDebug()<<"run:"<<a->name();
            a->run();
            this->hide();
        });
    }
    
    systray = new KStatusNotifierItem(this);
    systray->setIconByName("folder-public");
    systray->setStatus(KStatusNotifierItem::ItemStatus::Active);
    systray->setCategory(KStatusNotifierItem::ItemCategory::Communications);
}

ControlWindow::~ControlWindow()
{
    
}
