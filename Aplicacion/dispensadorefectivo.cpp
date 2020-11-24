#include "dispensadorefectivo.h"

DispensadorEfectivo::DispensadorEfectivo()
{
    cuenta = BILLETES;
}

// simula el proceso de dispensar el monto especificado de efectivo; asume que hay suficiente efectivo
// disponible (la llamada anterior a haySuficienteEfectivoDisponible devolvio true)
void DispensadorEfectivo::dispensarEfectivo(int monto){
     // numero de billetes requeridos
    const int denominacion[4]={100000, 50000, 20000, 10000};
    for(int i=0;i<4;i++){
        int cantidad = monto/(*(denominacion+i));
        cuenta -= cantidad; // actualiza la cuenta de billetes
        this->CantBilletes[i]=cantidad;
        monto%=*(denominacion+i);
    }
    llenar();
    //restamos los billetes que se usaron para dispensar efectivo
   /* map<int,int>::iterator it;
    it= billetes.begin();
    short int i=0;
    for (; it != billetes.end() ; it++){
        it->second -= CantBilletes[i];
        i++;
    }
    */
}

// indica si el dispensador de efectivo puede dispensar el monto deseado
bool DispensadorEfectivo::haySuficienteEfectivoDisponible() const{

    /*
    if(CantBilletes[0]<billetes.find(1)->second && CantBilletes[1]<billetes.find(2)->second && CantBilletes[2]<billetes.find(3)->second && CantBilletes[3]<billetes.find(4)->second)
        return true;
    else
        return false;
        */
}

void DispensadorEfectivo::llenar()
{

    //llenamos el mapa de billetes disponibles del cajero
    /*
    this->billetes.insert(par(4,200));
    this->billetes.insert(par(3,200));
    this->billetes.insert(par(2,400));
    this->billetes.insert(par(1,200));
    */
}
