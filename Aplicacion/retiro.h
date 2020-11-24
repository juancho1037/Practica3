#ifndef RETIRO_H
#define RETIRO_H

#include "pantalla.h"
#include "basedatosbanco.h"
#include "teclado.h"
#include "dispensadorefectivo.h"
#include "transaccion.h"

class Retiro: public Transaccion
{
public:
    Retiro(int numero, Pantalla &pantalla, BaseDatosBanco &base, Teclado &teclado,DispensadorEfectivo &dispensador);
    void ejecutar();

private:   
    int monto;
    Teclado &teclado;
    DispensadorEfectivo &dispensador;
    int mostrarMenuDeMontos() const;
};

#endif // RETIRO_H
