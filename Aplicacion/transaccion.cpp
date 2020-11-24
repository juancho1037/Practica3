#include "transaccion.h"

Transaccion::Transaccion(int numero, Pantalla &pantalla,BaseDatosBanco &base)
    :numeroCuenta(numero),
      pantalla(pantalla),
      baseDatosBanco(base)
{

}

Transaccion::Transaccion(Pantalla &pantalla, BaseDatosBanco &base)
    :pantalla(pantalla),
      baseDatosBanco(base)
{

}

int Transaccion::obtenerNumeroCuenta() const
{
    return numeroCuenta;
}

Pantalla &Transaccion::obtenerPantalla() const
{
    return pantalla;
}

BaseDatosBanco &Transaccion::obtenerBaseDatosBanco() const
{
    return baseDatosBanco;
}
