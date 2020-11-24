#include "solicitudsaldo.h"

SolicitudSaldo::SolicitudSaldo(int numero, Pantalla &pantalla,BaseDatosBanco &base)
    : Transaccion(numero, pantalla, base)
{
}

void SolicitudSaldo::ejecutar()
{
    // obtiene referencias a la base de datos del banco y la pantalla
    BaseDatosBanco &base = obtenerBaseDatosBanco();
    Pantalla &pantalla = obtenerPantalla();

    // obtiene el saldo disponible para la Cuenta del usuario actual
    //double saldoDisp = base.obtenerSaldoDisponible(obtenerNumeroCuenta());

    // obtiene el saldo total para la Cuenta del usuario actual
    double saldoTotal = base.obtenerSaldoTotal(obtenerNumeroCuenta());

    // muestra la informacion del saldo en la pantalla
    pantalla.mostrarLineaMensaje( "\n ...::: Informacion de saldo :::...\n" );
    //pantalla.mostrarMensaje( "\n    ...::: Saldo disponible: " );
    //pantalla.mostrarMontoDolares(saldoDisp);cout<<endl;
    pantalla.mostrarMensaje( "\n      ...::: Saldo total: " );
    pantalla.mostrarMontoDolares(saldoTotal);cout<<endl;
    pantalla.mostrarLineaMensaje( "" );
    base.cobro(obtenerNumeroCuenta()); //cobro de la solicitud de saldo.
}
