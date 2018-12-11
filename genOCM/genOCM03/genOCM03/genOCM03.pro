TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


# The c++11 support flag is added
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    genOCM.cpp

HEADERS += \
    genOCM.h

