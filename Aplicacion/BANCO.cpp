#include "BANCO.h"

// constantes de enumeración que representan las opciones del menú principal
enum OpcionMenu { SOLICITUD_SALDO = 1, RETIRO, REGISTRO, DEPOSITO, SALIR };

BANCO::BANCO(): usuarioAutenticado (false), numeroCuentaActual(0)
{
}

void BANCO::ejecutar()
{
    while (true){
        while (!usuarioAutenticado){
            pantalla.mostrarLineaMensaje( "\n         ...::: BIENVENIDO! :::..." );
            autenticarUsuario();    // autentica al usuario
        }
        realizarTransacciones();    // ahora el usuario es autenticado
        usuarioAutenticado = false; // restablece antes de la siguiene sesion
        numeroCuentaActual = 0;     // restablece antes de la siguiente sesion
        pantalla.mostrarLineaMensaje( "\n ...::: Gracias! Hasta luego! :::...\n" );
    }
}

void BANCO::autenticarUsuario(){
    pantalla.mostrarMensaje( "\n ...::: Escriba su numero de cuenta: " );
    int numeroCuenta = teclado.obtenerEntrada();

    pantalla.mostrarMensaje( "\n ...::: Escriba su Cedula: " );
    int cc = teclado.obtenerEntrada();

    // establece usuarioAutenticado con el valor bool devuelto por la base de datos
    usuarioAutenticado = baseDatosBanco.autenticarUsuario(numeroCuenta, cc);
    if (usuarioAutenticado){
        numeroCuentaActual = numeroCuenta;
    }
    else
        pantalla.mostrarLineaMensaje(" ...::: Numero de cuenta o CC invalido. Intente de nuevo.");
}

// muestra el menu principal y realiza las transacciones
void BANCO::realizarTransacciones(){

    Transaccion *transaccionActualPtr;// apuntador local para almacenar la transaccion actual en proceso
    bool usuarioSalio = false; // el usuario no ha elegido salir

    while (!usuarioSalio){

        int seleccion = mostrarMenuPrincipal();

        // decide como proceder con base en la opcion del menu elegida por el usuario
        switch (seleccion){
        case SOLICITUD_SALDO:
            transaccionActualPtr = crearTransaccion(seleccion);
            transaccionActualPtr->ejecutar();
            delete transaccionActualPtr;
            break;
        case RETIRO:
            transaccionActualPtr = crearTransaccion(seleccion);
            transaccionActualPtr->ejecutar();
            delete transaccionActualPtr;
            break;
        case REGISTRO:

            break;
        case SALIR:
            pantalla.mostrarLineaMensaje( "\n ...::: Saliendo del sistema..." );
            usuarioSalio = true;
            break;
        default:
            pantalla.mostrarLineaMensaje("\n ...::: No introdujo una seleccion valida. Intente de nuevo." );
            break;
        }
    }
}

// muestra el menú principal y devuelve una selección de entrada
int BANCO::mostrarMenuPrincipal() const
{
    pantalla.mostrarLineaMensaje( "\n      ...::: MENU PRINCIPAL :::... \n" );
    pantalla.mostrarLineaMensaje( "        ::: 1 ::: Ver mi saldo"     );
    pantalla.mostrarLineaMensaje( "        ::: 2 ::: Retirar efectivo" );
    pantalla.mostrarLineaMensaje( "        ::: 3 ::: Registro usuario" );
    pantalla.mostrarLineaMensaje( "        ::: 4 ::: Depositar fondos" );
    pantalla.mostrarLineaMensaje( "        ::: 5 ::: Salir\n"          );
    pantalla.mostrarMensaje( "        ...::: Introduzca una opcion: "  );
    return teclado.obtenerEntrada();
}

Transaccion *BANCO::crearTransaccion(int tipo){
    Transaccion *temporal; // apuntador Transaccion temporal
    // determina que tipo de Transaccion crear
    switch (tipo){
    case SOLICITUD_SALDO:{ // crea nueva transaccion SolicitudSaldo
        temporal = new SolicitudSaldo(numeroCuentaActual, pantalla, baseDatosBanco);
        break;}
    case RETIRO:{ // crea nueva transaccion Retiro
        temporal = new Retiro(numeroCuentaActual, pantalla,baseDatosBanco, teclado, dispensadorEfectivo);
        break;}
    case REGISTRO:{

    }
    case DEPOSITO:{ // crea nueva transaccion Deposito
        temporal = new Deposito(numeroCuentaActual, pantalla,baseDatosBanco, teclado, ranuraDeposito);
        break;}
    }
    return temporal; // devuelve el objeto recién creado
}


