#ifndef REGISTRO_H
#define REGISTRO_H

#include "transaccion.h"
#include "pantalla.h"
#include "basedatosbanco.h"
#include "teclado.h"

#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

class Registro
{
private:
    int numCuenta;
    int cedula;
    float dinero;
    Teclado &teclado;
    Pantalla &pantalla;
    BaseDatosBanco &base;

public:
    Registro(Teclado &teclado,Pantalla &pantalla,BaseDatosBanco &base,int numero, int cedula, double saldo);


    int getNumCuenta() const;
    void setNumCuenta(int value);

    int getCedula() const;
    void setCedula(int value);

    float getDinero() const;
    void setDinero(float value);

    virtual void ejecutar();
    int mostrarMenu() const;

    fstream crearArchivo();
    void crearArchivo(fstream &archivo, Registro cliente);

    void actualizaRegistro(fstream &archivo);
    void nuevoRegistro(fstream &archivo);
    void eliminarRegistro(fstream &archivo);
    void imprimir(ostream &archivo, const Registro &registro);

    Pantalla &obtenerPantalla() const;
    BaseDatosBanco &obtenerBaseDatosBanco() const;


};

#endif // REGISTRO_H
