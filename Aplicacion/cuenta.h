#ifndef CUENTA_H
#define CUENTA_H

class Cuenta
{
public:
    Cuenta();
    Cuenta(int clave, int cc, double saldot, double saldod);

    bool validarCC(int)const;
    double obtenerSaldoDisponible()const;
    double obtenerSaldoTotal()const;
    void abonar(double);
    void restar();
    void cargar(double);
    int obtenerClave() const;

private:
    int clave;
    int CC;
    double saldoDisponible;
    double saldoTotal;
};

#endif // CUENTA_H
