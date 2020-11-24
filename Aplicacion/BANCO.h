#ifndef CAJERO_H
#define CAJERO_H

#include "pantalla.h"
#include "teclado.h"
#include "dispensadorefectivo.h"
#include "basedatosbanco.h"
#include "ranuradeposito.h"
#include "transaccion.h"
#include "solicitudsaldo.h"
#include "retiro.h"
#include "deposito.h"

class Transaccion;

class BANCO
{
public:
    BANCO();
    void ejecutar();

private:
    bool usuarioAutenticado;
    int numeroCuentaActual;

    Pantalla pantalla;
    Teclado teclado;
    DispensadorEfectivo dispensadorEfectivo;
    BaseDatosBanco baseDatosBanco;
    RanuraDeposito ranuraDeposito;

    // funciones utilitarias privadas
    void autenticarUsuario();
    void realizarTransacciones();
    int mostrarMenuPrincipal() const;

    // devuelve un objeto de la clase derivada de Transaccion que se especifica
    Transaccion *crearTransaccion(int);
};

#endif // CAJERO_H
