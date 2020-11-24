#include "deposito.h"

const static int CANCELO = 0;

Deposito::Deposito(int numero, Pantalla &pantalla,
                   BaseDatosBanco &base, Teclado &teclado,
                   RanuraDeposito &ranura)

    : Transaccion(numero, pantalla, base),
      teclado(teclado), ranuraDeposito(ranura)
{  
}

void Deposito::ejecutar()
{
    BaseDatosBanco &baseDatosBanco = obtenerBaseDatosBanco();   // obtiene una referencia
    Pantalla &pantalla = obtenerPantalla();                     // obtiene una referencia

    monto = pedirMontoADepositar(); // obtiene el monto a depositar del usuario

    // comprueba si el usuario introdujo un monto a depositar o canceló
    if (monto != CANCELO)
    {
        // solicita el sobre de deposito que contiene el monto especificado
        pantalla.mostrarMensaje(
                    "\n ...::: Inserte un sobre de deposito que contenga ");
        pantalla.mostrarMontoDolares(monto);
        pantalla.mostrarLineaMensaje(" en la ranura de deposito." );

        // recibe el sobre de deposito
        bool sobreRecibido = ranuraDeposito.seRecibioSobre();

        // comprueba si se recibio el sobre de deposito
        if ( sobreRecibido )
        {
            pantalla.mostrarLineaMensaje( "\n...::: Se recibio su sobre."
                                          "\n...::: NOTA: El dinero depositado no estara disponible sino hasta"
                                          "\n             verificar el monto de cualquier efectivo incluido, "
                                          "               junto con los cheques." );

            // abona a la cuenta para reflejar el deposito
            baseDatosBanco.abonar(obtenerNumeroCuenta(), monto);
        }
        else
        {
            pantalla.mostrarLineaMensaje( "\n ...::: Usted no inserto un "
                                          "sobre, por lo que el Banco cancelo su transaccion." );
        }
    }
    else
    {
        pantalla.mostrarLineaMensaje( "\n ...::: Cancelando la transaccion..." );
    }
}

// pide al usuario que introduzca un monto a depositar en centavos
double Deposito::pedirMontoADepositar() const
{
    Pantalla &pantalla = obtenerPantalla(); // obtiene referencia a la pantalla

    // muestra el indicador y recibe la entrada
    pantalla.mostrarMensaje( "\n ...::: Introduzca un monto a depositar en "
                             "          PESOS (o 0 para cancelar): " );
    int entrada = teclado.obtenerEntrada(); // recibe la entrada del monto a depositar

    // comprueba si el usuario cancelo o introdujo un monto valido
    if (entrada == CANCELO)
        return CANCELO;
    else
    {
        return static_cast<double>(entrada)/100; // devuelve el monto en pesos
    }
}


