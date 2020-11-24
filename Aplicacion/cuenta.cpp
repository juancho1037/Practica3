#include "cuenta.h"

Cuenta::Cuenta(int clave, int cc, double saldot, double saldod)
    : clave(clave),
      CC(cc),
      saldoDisponible(saldot),
      saldoTotal(saldod)
{

}

// Validar Cedula
bool Cuenta::validarCC(int cc) const{
    if (cc == CC)
        return true;
    else
        return false;
}

// Obtener saldo disponible
double Cuenta::obtenerSaldoDisponible() const{
    return saldoDisponible;
}

// devuelve el saldo total
double Cuenta::obtenerSaldoTotal() const{
    return saldoTotal;
}

void Cuenta::abonar(double monto){
    saldoTotal += monto; // lo suma al saldo total
}

void Cuenta::restar()
{
    saldoTotal -=1000; //costo de los retiros
    saldoDisponible -=1000; // restar tambien del saldo disponible
}

// carga un monto a la cuenta
void Cuenta::cargar(double monto){
    saldoDisponible -= monto; // resta del saldo disponible
    saldoTotal -= monto; // resta del saldo total
}

// Obtener la clave
int Cuenta::obtenerClave() const
{
    return clave;
}
