#include "teclado.h"

Teclado::Teclado()
{

}

int Teclado::obtenerEntrada() const
{
    int entrada; // variable para almacenar la entrada
    cin >> entrada; // asumimos que el usuario introduce un entero
    return entrada; // devuelve el valor introducido por el usuario
}
