###############################################################################
# Copyright (C) 2009 InsideQt.com
#
# This file is part of the Input Method Programming Guideline,
# for Qt/Embedded 4.5.1 
# Official named as Qt 4.5.1 for Embedded Linux 
#
# This file may be distributed and/or modified under the terms of the
# GNU General Public License version 3 as published by the Free Software
# Foundation 
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# 
# Author:      Q-Kevin
# email:       qkevin@InsideQt.com
# Homepage:    http://www.InsideQt.com
# Create Date: May 11, 2009
# License:     GPL version 3 or later
# 
# Please visist http://www.InsideQt.com/bbs to get more details 
###############################################################################


TEMPLATE = app
INCLUDEPATH += src

# Input
HEADERS += src/ximewindow.h \
           src/xinputmethod.h \
           src/ximedata.h

SOURCES += src/main.cpp \
           src/ximewindow.cpp \
           src/xinputmethod.cpp 



CONFIG          +=      qt warn_on console

TARGET          =       xinputmethod
VERSION         =       0.0.1

OBJECTS_DIR = ./tmp_build
MOC_DIR     = ./tmp_build
UI_DIR      = ./tmp_build
