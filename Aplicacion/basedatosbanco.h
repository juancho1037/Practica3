#ifndef BASEDATOSBANCO_H
#define BASEDATOSBANCO_H

#include<iostream>
#include "cuenta.h"
#include <vector>

using namespace std;

class BaseDatosBanco
{
public:
    BaseDatosBanco();

    bool autenticarUsuario(int, int);

    double obtenerSaldoDisponible(int);
    double obtenerSaldoTotal(int numero);
    void abonar(int, double);
    void cargar(int numero, double);
    void cobro(int numero);

private:
    vector<Cuenta> cuentas;
    Cuenta * obtenerCuenta(int);
};

#endif // BASEDATOSBANCO_H
