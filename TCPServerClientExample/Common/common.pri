INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/commonMessages.h \
    $$PWD/encryption.h

SOURCES += \
    $$PWD/encyrption.cpp

#LIBS += -lcrypto
#LIBS += -lssl
INCLUDEPATH += C:/msys64/mingw64/include
LIBS += -LC:/msys64/mingw64/lib -lcrypto -lssl

