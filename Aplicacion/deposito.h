#ifndef DEPOSITO_H
#define DEPOSITO_H

#include "transaccion.h"
#include "pantalla.h"
#include "basedatosbanco.h"
#include "teclado.h"
#include "ranuradeposito.h"


class Deposito: public Transaccion
{
public:
    Deposito(int numero,
             Pantalla &pantalla,
             BaseDatosBanco &base,
             Teclado &teclado,
             RanuraDeposito &ranura);

    virtual void ejecutar();

private:
    double monto;
    Teclado &teclado;
    RanuraDeposito &ranuraDeposito;
    double pedirMontoADepositar() const;
};

#endif // DEPOSITO_H
