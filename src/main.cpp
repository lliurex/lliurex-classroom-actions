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
#include "util.hpp"

#include <QApplication>
#include <QString>

#include <iostream>

using namespace std;

int main(int argc,char* argv[])
{
    vector<string> groups = getUserGroups();
    
    bool allowed=false;
    
    for (string s:groups) {
        if (s=="teachers" or s=="admins") {
            allowed=true;
            break;
        }
    }
    
    if (!allowed) {
        #ifdef NDEBUG
        cerr<<"User not in teachers or admins group"<<endl;
        return 1;
        #else
        cerr<<"Warning: User not in a valid group"<<endl;
        #endif
    }
    
    QApplication app(argc,argv);
    
    ControlWindow* win=new ControlWindow();
    app.exec();
    
    delete win;
    
    return 0;
}