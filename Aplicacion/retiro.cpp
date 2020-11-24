#include "retiro.h"

const static int CANCELO = 8;

Retiro::Retiro(int numero, Pantalla &pantalla, BaseDatosBanco &base, Teclado &teclado,DispensadorEfectivo &dispensador)
    : Transaccion(numero, pantalla, base),
    teclado(teclado),
    dispensador(dispensador)
{

}

void Retiro::ejecutar()
{
    bool efectivoDispensado = false;
    bool transaccionCancelada = false;

    BaseDatosBanco &baseDatosBanco = obtenerBaseDatosBanco();
    Pantalla &pantalla = obtenerPantalla();

    //ciclo para retirar efectivo hasta que el usuario cancele o retire
    do
    {
        int seleccion = mostrarMenuDeMontos();
        if (seleccion != CANCELO)
        {
            monto = seleccion;
            double saldoDisponible = baseDatosBanco.obtenerSaldoDisponible(obtenerNumeroCuenta());

            if (monto <= saldoDisponible)
            {
                if (dispensador.haySuficienteEfectivoDisponible())
                {
                    baseDatosBanco.cargar(obtenerNumeroCuenta(), monto);
                    dispensador.dispensarEfectivo(monto);
                    efectivoDispensado = true;
                    pantalla.mostrarLineaMensaje(
                                "\n  ...::: Por favor tome su efectivo del dispensador de efectivo." );
                    baseDatosBanco.cobro(obtenerNumeroCuenta()); //Resta de la cuenta el costo de la transaccion
                }
                else
                    pantalla.mostrarLineaMensaje(
                                "\n ...::: No hay suficiente efectivo disponible en el Cajero."
                                "\n\n ...::: Elija una cantidad menor." );
            }
            else
            {
                pantalla.mostrarLineaMensaje(
                            "\n ...::: No hay suficientes fondos en su cuenta."
                            "\n\n ...::: Elija una cantidad menor." );
            }
        }
        else
        {
            pantalla.mostrarLineaMensaje( "\nCancelando la transaccion..." );
            transaccionCancelada = true; // el usuario canceló la transacción
        }
    } while ( !efectivoDispensado && !transaccionCancelada );
}


int Retiro::mostrarMenuDeMontos() const
{
    int opcion = 0;
    Pantalla &pantalla = obtenerPantalla();
    int montos[] = { 0, 10000, 20000, 50000, 100000, 200000, 500000, 1000000 };

    while (opcion == 0)
    {
        pantalla.mostrarLineaMensaje( "\n ...::: Monto a Retirar:\n");
        pantalla.mostrarLineaMensaje( "      ::: 1 ::: 10.000"      );
        pantalla.mostrarLineaMensaje( "      ::: 2 ::: 20.000"      );
        pantalla.mostrarLineaMensaje( "      ::: 3 ::: 50.000"      );
        pantalla.mostrarLineaMensaje( "      ::: 4 ::: 100.000"     );
        pantalla.mostrarLineaMensaje( "      ::: 5 ::: 200.000"     );
        pantalla.mostrarLineaMensaje( "      ::: 6 ::: 500.000"     );
        pantalla.mostrarLineaMensaje( "      ::: 7 ::: 1'000.000"   );
        pantalla.mostrarLineaMensaje( "      ::: 8 ::: Cancelar transaccion"    );
        pantalla.mostrarMensaje( "\n ...::: Elija una opcion de retiro (1-8): " );

        int entrada = teclado.obtenerEntrada();

        // determina como proceder con base en el valor de la entrada
        switch (entrada)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            opcion = montos[entrada];
            break;
        case CANCELO:
            opcion = CANCELO;
            break;
        default:
            pantalla.mostrarLineaMensaje(
                        "\n ...::: Seleccion invalida. Intente de nuevo." );
        }
    }
    return opcion;
}
