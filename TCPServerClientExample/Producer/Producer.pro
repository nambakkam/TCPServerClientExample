QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        generators/bodytemperaturegenerator.cpp \
        generators/ecggenerator.cpp \
        generators/etco2generator.cpp \
        generators/heartrategenerator.cpp \
        generators/idatagenerator.cpp \
        generators/nibpdiastolicgenerator.cpp \
        generators/nibpsystolicgenerator.cpp \
        generators/ppggenerator.cpp \
        generators/resprategenerator.cpp \
        generators/respwaveformgenerator.cpp \
        generators/spo2generator.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include("$$PWD/../Common/common.pri")

HEADERS += \
    generators/bodytemperaturegenerator.h \
    generators/ecggenerator.h \
    generators/etco2generator.h \
    generators/heartrategenerator.h \
    generators/idatagenerator.h \
    generators/nibpdiastolicgenerator.h \
    generators/nibpsystolicgenerator.h \
    generators/ppggenerator.h \
    generators/resprategenerator.h \
    generators/respwaveformgenerator.h \
    generators/spo2generator.h
