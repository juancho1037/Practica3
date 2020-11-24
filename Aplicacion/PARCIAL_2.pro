TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        BANCO.cpp \
        basedatosbanco.cpp \
        cuenta.cpp \
        deposito.cpp \
        dispensadorefectivo.cpp \
        main.cpp \
        pantalla.cpp \
        proceso.cpp \
        ranuradeposito.cpp \
        registro.cpp \
        retiro.cpp \
        solicitudsaldo.cpp \
        teclado.cpp \
        transaccion.cpp

HEADERS += \
    BANCO.h \
    basedatosbanco.h \
    cuenta.h \
    deposito.h \
    dispensadorefectivo.h \
    pantalla.h \
    proceso.h \
    ranuradeposito.h \
    registro.h \
    retiro.h \
    solicitudsaldo.h \
    teclado.h \
    transaccion.h
