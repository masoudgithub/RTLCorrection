TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    genOCM.cpp

HEADERS += \
    genOCM.h

QMAKE_CXXFLAGS += -std=c++11
