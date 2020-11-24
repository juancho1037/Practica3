#include "basedatosbanco.h"

BaseDatosBanco::BaseDatosBanco()
{
    //crea dos objetos Cuenta para evaluar
    Cuenta cuenta1(12345, 54321, 2850000, 2850000);

    // agrega los objetos Cuenta al vector cuentas
    cuentas.push_back(cuenta1);
}

// obtiene el objeto Cuenta que contiene el numero de cuenta especificado
Cuenta * BaseDatosBanco::obtenerCuenta(int numeroCuenta)
{
    for (size_t i = 0; i < cuentas.size(); i++){
        if (cuentas[i].obtenerClave() == numeroCuenta)
            return &cuentas[i];
    }
    return NULL;
}

// determina si el número de cuenta y CC especificados por el usuario coinciden con los de una cuenta en la base de datos
bool BaseDatosBanco::autenticarUsuario(int numero,int cc ){
    Cuenta *const cuenta = obtenerCuenta(numero);
    if (cuenta != NULL)
        return cuenta->validarCC(cc);
    else
        return false;
}

// devuelve el saldo disponible de la Cuenta con el numero de cuenta especificado
double BaseDatosBanco::obtenerSaldoDisponible(int numero){
    Cuenta *const cuenta = obtenerCuenta(numero);
    return cuenta->obtenerSaldoDisponible();
}

// devuelve el saldo total de la Cuenta con el número de cuenta especificado
double BaseDatosBanco::obtenerSaldoTotal(int numero){
    Cuenta *const cuenta = obtenerCuenta(numero);
    return cuenta->obtenerSaldoTotal();
}

//Realiza una consignacion
void BaseDatosBanco::abonar(int numero, double monto){
    Cuenta *const cuenta = obtenerCuenta(numero);
    cuenta->abonar(monto);
}

// carga un monto a la Cuenta con el número de cuenta especificado
void BaseDatosBanco::cargar(int numero, double monto){
    Cuenta *const cuenta = obtenerCuenta(numero);
    cuenta->cargar(monto);
}

//Cobro por retiro o por consulta de saldo
void BaseDatosBanco::cobro(int numero)
{
    Cuenta *const cuenta = obtenerCuenta(numero);
    cuenta->restar();
}
