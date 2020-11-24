#ifndef PANTALLA_H
#define PANTALLA_H
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Pantalla
{
public:
    Pantalla();
    void mostrarMensaje( string ) const; // imprime un mensaje en pantalla
    void mostrarLineaMensaje( string ) const; // imprime un mensaje con nueva línea
    void mostrarMontoDolares( double ) const; // imrime un monto en dólares
};

#endif // PANTALLA_H
