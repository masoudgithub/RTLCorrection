TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    genOCM.cpp \
    Hungarian.cpp \
    mainNode.cpp

OTHER_FILES += \
    matching.pro.user

HEADERS += \
    genOCM.h \
    Hungarian.h \
    mainNode.h


QMAKE_CXXFLAGS += -std=c++11
