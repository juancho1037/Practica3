#include "registro.h"

enum Opciones{NUEVO = 1, ACTUALIZAR, ELIMINAR, MOSTRAR, TERMINAR};

Registro::Registro(Teclado &teclado, Pantalla &pantalla, BaseDatosBanco &base, int numero, int cedula, double saldo)
    :teclado(teclado),
     pantalla(pantalla),
     base(base)
{
    setNumCuenta(numero);
    setCedula(cedula);
    setDinero(saldo);
}

int Registro::getNumCuenta() const
{
    return numCuenta;
}

void Registro::setNumCuenta(int value)
{
    numCuenta = value;
}

int Registro::getCedula() const
{
    return cedula;
}

void Registro::setCedula(int value)
{
    cedula = value;
}

float Registro::getDinero() const
{
    return dinero;
}

void Registro::setDinero(float value)
{
    dinero = value;
}

void Registro::ejecutar()
{
    bool autenticar = false;
    BaseDatosBanco &base = obtenerBaseDatosBanco();
    Pantalla &pantalla = obtenerPantalla();

    int seleccion = 0;
    fstream Archivo = crearArchivo();
    while (seleccion = mostrarMenu() != TERMINAR) {
        switch (seleccion) {
        case NUEVO:
            nuevoRegistro(Archivo);
            break;
        case ACTUALIZAR:
            //actualizaRegistro(Archivo);
            break;
        case ELIMINAR:
            eliminarRegistro(Archivo);
            break;
        case MOSTRAR:
            break;
        default:
            cerr << "   ...::: Opcion incorrecta :::... " << endl;
            break;
        }
        Archivo.clear();
    }
}

int Registro::mostrarMenu() const
{
    int opcion = 0;
    Pantalla &pantalla = obtenerPantalla();

    pantalla.mostrarLineaMensaje( "\n   ...::: REGISTRO DE USUARIOS :::... \n");
    pantalla.mostrarLineaMensaje( "     ...::: 1 ::: Nuevo usuario :::...");
    pantalla.mostrarLineaMensaje( "     ...::: 2 ::: Actualizar usuario :::...");
    pantalla.mostrarLineaMensaje( "     ...::: 3 ::: Eliminar usuario :::...");
    pantalla.mostrarLineaMensaje( "     ...::: 4 ::: Mostar usuarios :::...");
    pantalla.mostrarLineaMensaje( "     ...::: 5 ::: Terminar :::...");

    opcion = teclado.obtenerEntrada();
    return opcion;
}


fstream Registro::crearArchivo()
{
    fstream archivoBase("Semilla.dat",ios::in | ios::out | ios::binary);
    if(!archivoBase){
        cerr << "   ...::: No se pudo abrir el archivo :::... " <<endl;
        exit(1);
    }
    return archivoBase;
}

void Registro::crearArchivo(fstream & archivo, Registro cliente)
{
    ofstream usuarios("registro.dat", ios::out | ios::binary);

    if(!usuarios){
        cerr << "   ...::: No se pudo abrir el archivo :::... " <<endl;
        exit(1);
    }
    usuarios << left << setw(10) << "Cedula" << setw(16)
             << "Clave" << setw(11) << "Saldo" << right
             << setw(10) << endl;

    // establece el apuntador de posicion del archivo en el inicio
    archivo.seekg(0);

    //archivo.read(reinterpret_cast<char *>(&cliente), sizeof (Registro));
    //Esta parte aun no estoy seguro como se maneja bien, para lo de los archivos de acceso aleatorio, me falta leer mas profe.

}

void Registro::nuevoRegistro(fstream &archivo)
{

}

void Registro::eliminarRegistro(fstream &archivo)
{

}

void Registro::imprimir(ostream &archivo, const Registro &registro)
{

}

Pantalla &Registro::obtenerPantalla() const
{
    return this->pantalla;
}

BaseDatosBanco &Registro::obtenerBaseDatosBanco() const
{
    return this->base;
}


// crea un archivo de texto con formato para imprimirlo
void crearArchivoTexto(fstream &leerDelArchivo)
{
/*

    // lee el primer registro del archivo de registros
    leerDelArchivo.read( reinterpret_cast< char * >( &cliente ),
                         sizeof( DatosCliente ) );

    // copia todos los registros del archivo de registros al archivo de texto
    while ( !leerDelArchivo.eof() )
    {
        // escribe un solo registro en el archivo de texto
        if ( cliente.obtenerNumeroCuenta() != 0 ) // omite los registros vacíos
            imprimirLinea( archivoImprimirSalida, cliente );

        // lee el siguiente registro del archivo de registros
        leerDelArchivo.read( reinterpret_cast< char * >( &cliente ),
                             sizeof( DatosCliente ) );
    }
    */
}
