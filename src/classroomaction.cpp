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

#include "classroomaction.hpp"

#include <KConfigGroup>
#include <QProcess>
#include <QDebug>

ClassroomAction::ClassroomAction(QString file_name)
{
    m_desktop = new KDesktopFile(file_name);
    m_name=m_desktop->readName();
    m_icon=m_desktop->readIcon();
    
    auto group = m_desktop->group("Desktop Entry");
    m_exec=group.readEntry("Exec","");
}

ClassroomAction::~ClassroomAction()
{
    
}

void ClassroomAction::run()
{
    QProcess child;
    
    QStringList tmp = m_exec.split(' ');
    QStringList args;
    
    for (size_t n=1;n<tmp.size();n++) {
        args.append(tmp[n]);
    }
    qDebug()<<m_exec;
    qDebug()<<tmp[0];
    qDebug()<<args;
    
    child.setArguments(args);
    child.setProgram(tmp[0]);
    child.startDetached(nullptr);
}