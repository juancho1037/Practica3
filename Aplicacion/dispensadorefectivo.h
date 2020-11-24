#ifndef DISPENSADOREFECTIVO_H
#define DISPENSADOREFECTIVO_H

#include<map>
#include<string>
using namespace std;

typedef pair<short int,int> par;

class DispensadorEfectivo
{
public:
    DispensadorEfectivo();

    // simula el proceso de dispensar el monto especificado de efectivo
    void dispensarEfectivo(int monto);

    // indica si el dispensador de efectivo puede dispensar el monto deseado
    bool haySuficienteEfectivoDisponible() const;

private:
    const static int BILLETES = 1000;
    int cuenta;
    int CantBilletes[4]={0,0,0,0};
    //static map<int,int> billetes;
    void llenar();
};

#endif // DISPENSADOREFECTIVO_H
