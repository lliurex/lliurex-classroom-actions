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

#ifndef LCA_CLASSROOM_ACTION
#define LCA_CLASSROOM_ACTION

#include <QString>
#include <KDesktopFile>

class ClassroomAction
{
    protected:
    
    QString m_name;
    QString m_exec;
    QString m_icon;
    KDesktopFile* m_desktop;
    
    public:
    
    ClassroomAction(QString file_name);
    virtual ~ClassroomAction();
    
    QString name()
    {
        return m_name;
    }
    
    QString exec()
    {
        return m_exec;
    }
    
    QString icon()
    {
        return m_icon;
    }
    
    void run();
};
#endif