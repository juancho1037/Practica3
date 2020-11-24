#include <iostream>
#include <fstream>
#include <string>

//#define DEBUG 1

using namespace std;
string file2string(string fileName);
void string2binary(char, string &);
int potencia(int, int);
int igual(string &, int, string::iterator &); //igual numero de 1´s y 0´s
int menos(string &, int, string::iterator &); //menor numero de 1´s que de 0´s
int mas(string &, int, string::iterator &);   //mayor numero de 1´s que de 0´s

void block(string &, int,string &, string::iterator &); //Separar la codificacion en bloques de n bits
void correr(string &); //Segundo metodo de codificacion

int main()
{
    int n=0, metodo=0, unos = 0, opcion=0;
    char c;
    string fuente, salida, bin, contenidoString = "", codigo = "";
    fstream ArchivoIN, ArchivoOUT;
    bool cond = true;

    while (cond==true)
    {
        cout<<endl;
        cout<<":::  PROGRAMA PARA CODIFICAR ARCHIVOS  :::"<<endl<<endl<<endl;
        cout<<":::  MENU:"<<endl<<"            1 - Semilla para la codificacion. "<<endl<<"            2 - Metodo de codificacion, 1 o 2. "<<endl<<"            3 - Nombre del archivo que desea codificar. "<<endl<<"            4 - Nombre del archivo codificado de salida. "<<endl<<"            5 - Salir. "<<endl<<endl;
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
            cout<<":::  Ingrese el nombre del archivo que desea codificar, incluyendo la extension txt: ";
            cin>>fuente;
            cout<<endl<<endl;

            break;

        }

        case 4:
        {
            cout<<":::  Ingrese el nombre del archivo codificado de salida, incluyendo la extension txt: ";
            cin>>salida;

            //*****************************************************************************************************************
            //Ciclo para la conversion a binario para la posterior codificacion
            if((metodo == 1)||(metodo==2))
            {
                contenidoString = file2string(fuente);
                for (unsigned int i=0; i<contenidoString.length()-1; i++){
                    c = contenidoString.at(i);      //capturar un caracter del texto fuente.
                    string2binary(c, bin);          //encontrar la representacion del caracter en bianario en mi funcion binary
                    codigo = codigo + bin;          //agregar el byte a la lista
                }
            }

            ArchivoOUT.open(salida,ios_base::out); //archivo de salida codificado

            //**********************************************************************************************
            //Codificacion de mis caracteres segun las instrucciones del primer metodo.
            if(metodo == 1){
                string::iterator it = codigo.begin();   //Iterador al principio del string
                unos = igual(codigo,n,it);              //aplicar codificacion al primer bloque
                while(it<codigo.end())
                {
                    if((n%2==0) && (unos==(n/2)))
                        unos = igual(codigo,n,it);      //codificar, igual numero de 1´s y 0´s
                    else if(unos > (n/2))
                        unos = mas(codigo,n,it);        //codificar, mas 1´s que 0´s
                    else  unos = menos(codigo,n,it);    //codificar, menos 1´s que 0´s
                }

                ArchivoOUT<<codigo;                     //escribir el archivo codificado
            }

            //**********************************************************************************************
            //Codificacion de mis caracteres segun las instrucciones del segundo metodo.
            if(metodo == 2)
            {
                string::iterator it = codigo.begin();   //Iterador al principio del string
                string bloque = "";                     //string bloque vacio
                while(it<codigo.end())
                {
                    block(bloque, n,codigo, it);        //obtener el bloque de n bits
                    correr(bloque);                     //codificar el bloque de n bits
                    ArchivoOUT << bloque;               //escribir el bloque en el archivo de salida
                }                                       //repetir el proceso hasta el final
            }
            break;
        }

        case 5:{
            cout<<":::  Hasta la Proxima, Gracias por usar nuestro programa"<<endl<<endl;
            cond=false;
            break;
        }
        default:{
            cout<<":::  Por Favor ingrese una opcion valida "<<endl;
        }

        }}



#ifdef DEBUG
   fuente = "pruebas.txt";
   salida = "codMetodo1.txt";
#endif

}


//********************************************************************************************************************************************************************
//DEFINICION DE FUNCIONES

//A esta funcion se le estrega el nombre del Archivo fuente y extrae su contenido convirtiendolo en un string
string file2string(string fileName){
    char c;
    string cadena= "";
    fstream Archivo;

    Archivo.open(fileName,ios_base::in);  //archivo fuente a codificar

    if(!Archivo){
        cerr<<endl<<"       ...::: ADVERTENCIA: "<<endl;
        cerr<<"             ...::: No se pudo abrir el archivo."<<endl;
        exit(1);
    }

    while(!Archivo.eof())
    {
        Archivo.get(c);                   //capturar un caracter del texto fuente.
        cadena = cadena + c;                //agregar el byte a la lista
    }
#ifdef DEBUG
    cout<<"\nContenido: "<<cadena<<endl;
#endif
    Archivo.close();
    return cadena;
}

//**************************************************************************************************************
//Esta funcion se encarga de convertir caracter por caracter a Binario.
void string2binary(char car, string &code)
{
    code = "00000000";
#ifdef DEBUG
    cout<<car<<": ";
#endif
    for(int i = 0; i<8; i++)
    {
        if(car>=potencia(2,7-i))
        {
            code[i] = '1';
            car -= potencia(2,7-i);
        }
    }
#ifdef DEBUG
    cout<<code<<endl;
#endif
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
