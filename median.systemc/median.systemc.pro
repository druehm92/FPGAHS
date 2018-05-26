## Copyright (C) 2014 University of Kaiserslautern
## Microelectronic System Design Research Group
##
## This file is part of the FPGAHS Course
## de.uni-kl.eit.course.fpgahs
##
## Matthias Jung <jungma@eit.uni-kl.de>
## Christian De Schryver <schryver@eit.uni-kl.de>
## Markus Steffes <steffesm@rhrk.uni-kl.de>

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
SOURCES += median_tb.cpp
SOURCES += median_top.cpp
SOURCES += median_module.cpp
SOURCES += memory.cpp
SOURCES += EasyBMP/EasyBMP.cpp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += median_tb.h
HEADERS += median_top.h
HEADERS += median_module.h
HEADERS += memory.h

unix:!macx: LIBS += -L/opt/systemc/lib/ -lsystemc

INCLUDEPATH += /opt/systemc/include
DEPENDPATH += /opt/systemc/include
