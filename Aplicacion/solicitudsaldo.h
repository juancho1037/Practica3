#ifndef SOLICITUDSALDO_H
#define SOLICITUDSALDO_H

#include "transaccion.h"
#include "pantalla.h"
#include "basedatosbanco.h"

class SolicitudSaldo: public Transaccion
{
public:
    SolicitudSaldo(int numero, Pantalla &pantalla,BaseDatosBanco &base);
    virtual void ejecutar();
};

#endif // SOLICITUDSALDO_H
