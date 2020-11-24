#ifndef TRANSACCION_H
#define TRANSACCION_H

class Pantalla;
class BaseDatosBanco;


#include<iostream>
using namespace std;

class Transaccion
{
public:
    Transaccion(int numero, Pantalla &pantalla,BaseDatosBanco &base);
    Transaccion(Pantalla &pantalla,BaseDatosBanco &base);
    virtual ~Transaccion() { }

    int obtenerNumeroCuenta() const;
    Pantalla &obtenerPantalla() const;
    BaseDatosBanco &obtenerBaseDatosBanco() const;

    virtual void ejecutar() = 0;

private:
    int numeroCuenta;
    Pantalla &pantalla;
    BaseDatosBanco &baseDatosBanco;
};

#endif // TRANSACCION_H
