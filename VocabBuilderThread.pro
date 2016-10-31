HEADERS       = headers/window.h \
                headers/worker.h \
                headers/basedata.h

SOURCES       = src/main.cpp \
                src/window.cpp \
                src/worker.cpp \
                src/basedata.cpp

RESOURCES     = systray.qrc

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -pthread
LIBS += -pthread
CONFIG += c++11

QT += widgets
QT += sql

# install

