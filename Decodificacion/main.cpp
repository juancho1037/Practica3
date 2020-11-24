#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void binary(char, string &);
int potencia(int, int);
int igual(string &, int, string::iterator &); //igual numero de 1´s y 0´s
int menos(string &, int, string::iterator &); //menor numero de 1´s que de 0´s
int mas(string &, int, string::iterator &);   //mayor numero de 1´s que de 0´s

void block(string &, int,string &, string::iterator &); //Separar la codificacion en bloques de n bits
void correr(string &); //Segundo metodo de codificacion
void correrD(string &);//Desencriptar segundo metodo
char num(string&);     //convertir un string de binario a char
int ones(string &, int, string::iterator &); //cuenta el numero de 1´s en el ultimo bloque de n caracteres

int main()
{

    int n=0, metodo=0, unos = 0, opcion=0;
    char c;
    string fuente, salida, bin, codigo = "";
    fstream ArchivoIN, ArchivoOUT;

    bool cond = true;

    while (cond==true)
    {
        cout<<endl;
        cout<<":::  PROGRAMA PARA DECODIFICAR ARCHIVOS  :::"<<endl<<endl<<endl;
        cout<<":::  MENU:"<<endl<<"            1 - Semilla para la Decodificacion. "<<endl<<"            2 - Metodo para decodificar. "<<endl<<"            3 - Nombre del archivo que desea decodificar. "<<endl<<"            4 - Nombre del archivo decodificado de salida. "<<endl<<"            5 - Salir. "<<endl<<endl;
        cout<<"            ::: ";
        cin>>opcion;

        switch(opcion){

        case 1:
        {
            cout<<":::  Ingrese un numero entero: ";
            cin>>n;
            break;

        }

        case 2:
        {
            cout<<":::  Ingrese el metodo deseado, 1 o 2: ";
            cin>>metodo;
            cout<<endl<<endl;
            break;

        }

        case 3:
        {
            cout<<":::  Ingrese el nombre del archivo que desea decodificar, incluyendo la extension txt: ";
            cin>>fuente;
            ArchivoIN.open(fuente,ios_base::in);  //archivo fuente a codificar
            cout<<endl<<endl;
            break;

        }

        case 4:
        {
            cout<<":::  Ingrese el nombre del archivo decodificado de salida, incluyendo la extension txt: ";
            cin>>salida;

            ArchivoOUT.open(salida,ios_base::out); //archivo de salida codificado

            //*******************************************************************************************
            // DECODIFICACION
            if((metodo==1)||(metodo==2))              //bloque para desencriptar
            {
            while(ArchivoIN.good())
            {
                ArchivoIN.get(c);                       //capturar uno a uno, los caracteres del archivo
                codigo.push_back(c);                    //agregar cada caracter al string codigo

            }}

            //*******************************************************************************************
            //decodificar usando el metodo 1
            if(metodo == 1)
            {
                string bloque = "";
                string::iterator it = codigo.begin();

                unos = igual(codigo,n,it);              //decodificar el primer grupo
                unos = ones(codigo,n,it);               //contar el numero de 1´s en el bloque

                while(it<codigo.end())
                {
                    if((n%2==0) && (unos==(n/2)))
                    {
                        unos = igual(codigo,n,it);      //Decodificar, igual numero de 1´s y 0´s
                        unos = ones(codigo,n,it);
                    }
                    else if(unos > (n/2))
                    {
                        unos = mas(codigo,n,it);        //Decodificar, mas 1´s que 0´s
                        unos = ones(codigo,n,it);
                    }
                    else
                    { unos = menos(codigo,n,it);        //Decodificar, menos 1´s que 0´s
                        unos = ones(codigo,n,it);
                    }
                }
                it = codigo.begin();

                while(it<codigo.end())
                {
                    block(bloque, 8, codigo, it);       //capturar un byte de informacion
                    ArchivoOUT<<num(bloque);            //escribir el caracter correspondiente en el archivo
                }
            }

            //*********************************************************************************************
            //Decodificar usando el metodo 2.
            if(metodo == 2)
            {
                bin = "";
                string bloque = "";
                string::iterator it = codigo.begin();

                while(it<codigo.end())                  //aplicar el metodo de codificacion en sentido contrario
                {
                    block(bloque, n, codigo,it);
                    correrD(bloque);
                    bin = bin + bloque;
                }
                it = bin.begin();

                while(it<bin.end())
                {
                    block(bloque, 8, bin, it);          //capturar un byte de informacion
                    ArchivoOUT<<num(bloque);            //escribir el caracter correspondiente en el archivo
                }
            }


            ArchivoIN.close();
            ArchivoOUT.close();
            return 0;
        }

            break;

        case 5:{
            cout<<":::  Hasta la Proxima, Gracias por usar nuestro programa"<<endl<<endl;
            cond=false;
            break;
        }
        default:{
            cout<<":::  Por favor ingrese una opcion valida "<<endl;
        }}
    }
}





//*********************************************************************************************************************************************************************
//DEFINICION DE FUNCIONES


//Esta funcion se encarga de convertir caracter por caracter a Binario.
void binary(char car, string &code)
{
    code = "00000000";
    for(int i = 0; i<8; i++)
    {
        if(car>=potencia(2,7-i))
        {
            code[i] = '1';
            car -= potencia(2,7-i);
        }
    }
}

int potencia(int a, int b)
{
    int multiplicador=1;
    for(int i = 0; i<b; i++)
        multiplicador *= a;
    return multiplicador;
}

//**************************************************************************************************************
//Funcion para modificar el primer bloque de unos y ceros para iniciar la codificacion, usando el primer metodo.
int igual(string &codigo, int n, string::iterator & it)
{
    int unos = 0;
    for(int i = 0; i<n; i++, it++)
    {
        if(it == codigo.end()) break;   //terminar el ciclo al final del string
        if(*it == '1')
        {
            *it = '0';                  //reemplazar 1's por 0´s
            unos++;                     //contar el numero de 1´s
        }
        else *it = '1';                 //reemplazar 0´s por 1´s
    }
    return unos;                        //la funcion retorna el numero de 1's (int)
}

//***************************************************************************************************
//Funcion para cuando se cumple la condicion de que en el bloque anterior hallan mas ceros que unos.
int menos(string &codigo, int n, string::iterator &it)
{
    int unos = 0;
    for(int i = 1; i<=n; i++,it++)
    {
        if(it == codigo.end()) break;   //terminar el ciclo al final del string
        if(*it=='1')
            unos++;                     //contar el numero de 1´s
        if(i%2 == 0)                    //Condicion para cambiar los numeros cada dos bits.
        {
            if(*it == '1')              //condicion para reemplazar 1´s por 0´s
            {
                *it = '0';
            }
            else *it = '1';             //reemplazar 0´s por 1´s
        }
    }
    return unos;                        //retornar numero de 1´s en el bloque
}

//***************************************************************************************************
//Funcion para cuando se cumple la condicion de que en el bloque anterior hallan mas unos que ceros.
int mas(string &codigo, int n, string::iterator &it)
{
    int unos = 0;
    for(int i = 1; i<=n; i++,it++)
    {
        if(it == codigo.end()) break;   //terminar el ciclo al final del string
        if(*it=='1')
            unos++;                     //contar el numero de 1´s
        if(i%3 == 0)                    //Condicion para cambiar los numeros cada tres bits.
        {
            if(*it == '1')              //reemplazar 1´s por 0´s
            {
                *it = '0';

            }
            else *it = '1';             //reemplazar 0´s por 1´s
        }
    }
    return unos;                        //retornar numero de 1´s en el bloque
}


//********************************************************************************************************************
//funcion util para encriptar y desencriptar, la cual crea los bloques de tamanio n definido por el usuario.

void block(string &bloque, int n, string &codigo, string::iterator &it)
{
    bloque = "";                            //bloque de n bits
    for(int i = 0; i < n ; i++, it++)
    {
        if(it == codigo.end()) break;       //terminar el ciclo al final del string
        bloque = bloque + *it;              //recorrer codigo y crear el bloque
    }
}


//********************************************************************************************************************
//funcion creada para el metodo 2 de codificacion
void correr(string &bloque)
{
    string::iterator it = bloque.end();     //iterador al fin del string
    it--;                                   //Regresar el iterador a la posicion del ultimo caracter
    string temp = " ";
    temp[0] = *it;                          //cadena temporal con el ultimo caracter del bloque sin codificar
    bloque.pop_back();                      //eliminar ultimo caracter del bloque sin codificar
    bloque = temp + bloque;                 //crea bloque codificado, concatenando temp al inicio

}

//********************************************************************************************************************
//funcion creada para decodificar usando el metodo 2 de codificacion.
void correrD(string &bloque){
    string::iterator it = bloque.begin(); //iterador al primer caracter del string
    bloque.push_back(*it);                //agregar el primer caracter al final del string
    bloque.erase(it);                     //borrar el string al principio del string
}

//********************************************************************************************************************
//Funcion que convierte un string de binario a un char.
char num(string & codigo)
{
    char a = 0;
    for(int i = 0; i<8; i++)
    {
        if(codigo[i] == '1')
            a = a + potencia(2,7-i);
    }
    return a;
}

//*******************************************************************************************************************
//Funcion que cuenta el numero de unos en el ultimo bloque de caracteres.
int ones(string &, int n , string::iterator &it)
{
    int unos = 0;
    for(int i=1; i<=n; i++)
    {
        if(*(it-i) == '1')
            unos++;
    }
    return unos;
}
