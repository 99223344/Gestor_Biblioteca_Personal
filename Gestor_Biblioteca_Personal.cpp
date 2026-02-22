#include <iostream>
#include <list>
#include <string>
#include <iomanip> //Agregar formato a la impresion
#include <cstdlib>//usar el "cls"
#include <algorithm> //usar el transform
#include <fstream> //Manejo de archivos



using namespace std;

struct libro {
    string titulo, autor, genero,editorial;
    int num_pag=0;
};

void Agregar_libro(std::list<libro>& ejemplares);
void Mostrar_libros(std::list<libro>& ejemplares);
void Modificar_libro(std::list<libro>& ejemplares);
void Eliminar_libro(std::list<libro>& ejemplares);
void Buscar(std::list<libro>& ejemplares);
void Generar_archivo(std::list<libro>& ejemplares);

int Verificar_entrada_numero();
void Pausa();

int main()
{
    //Inicializamos la lista
    std::list<libro> ejemplares;
    
    int x=0;
    do {  
        system("cls");
        //Menu de opciones
        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "+++++++++++++++++++++++ Gestor de biblioteca ++++++++++++++++++++++++" << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << endl;
        cout << "Agregar libro..............................................1" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "Mostrar todos los libros...................................2" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "Modificar libro............................................3" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "Eliminar libro.............................................4" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "Buscar libro por titulo....................................5" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "Generar archivo con el listado de libros...................6" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        cout << "Salir......................................................7" << endl;
        cout << "---------------------------------------------------------------------" << endl;
        
        //Verificacion que sea solo la entrada permitida
        while (true) {
            cout << "Ingrese el numero de la opcion: ";
            if (cin >> x && x>= 1 && x <= 7) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Selcione una de las opcines..." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        system("cls");

        switch (x) {
        case 1:
            Agregar_libro(ejemplares);
            break;
        case 2:
            Mostrar_libros(ejemplares);
            break;
        case 3:
            Modificar_libro(ejemplares);
            break;
        case 4:
            Eliminar_libro(ejemplares);
            break;
        case 5:
            Buscar(ejemplares);
            break;
        case 6:
            Generar_archivo(ejemplares);
            break;

        }
     
    } while (x != 7);
    return 0;
}

void Agregar_libro(std::list<libro>& ejemplares) {
    
    libro aux; //se crea una variable aux de tipo libro para hacer un llenado del strut
    string Mayuscula;
    char E = '0';
    do {
        cout << "######################################### Registro de libros ###################################################" << endl<<endl;
        
        cout << "Titulo: ";
        getline(cin, aux.titulo);
        transform(aux.titulo.begin(), aux.titulo.end(), aux.titulo.begin(),::toupper);//Pasar la cadena a puras mayusculas
        cout << "--------------------------------------------------------------------------------------------------------" << endl;
        
        cout << "Autor: ";
        getline(cin, aux.autor);
        transform(aux.autor.begin(), aux.autor.end(), aux.autor.begin(), ::toupper);
        cout << "--------------------------------------------------------------------------------------------------------" << endl;
        
        cout << "Genero: ";
        getline(cin, aux.genero);
        transform(aux.genero.begin(), aux.genero.end(), aux.genero.begin(), ::toupper);
        cout << "--------------------------------------------------------------------------------------------------------" << endl;
        
        cout << "Editorial: ";
        getline(cin, aux.editorial);
        transform(aux.editorial.begin(), aux.editorial.end(), aux.editorial.begin(), ::toupper);
        cout << "--------------------------------------------------------------------------------------------------------" << endl;
        
        cout << "No. Paginas: ";
        aux.num_pag = Verificar_entrada_numero();
        cout << "---------------------------------------------------------------------------------------------------------" << endl;

        //Insertamos el nodo con los datos
        ejemplares.push_back(aux);

        cout << "Ejemplar ingresado con exito..." << endl<<endl;

        cout << "Agregar otro: NO=0 SI=Cualquie caracter: ";
        cin >> E;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');//Para limpiar el buffer de entrada
        system("cls");

    } while (E != '0');
}
void Mostrar_libros(std::list<libro>& ejemplares) {

    cout << "######################################### Tabla de libros registrados ###################################################" << endl<<endl;
    cout<< left << setw(35) << "Titulo"
        << left << setw(25) << "Autor"
        << left << setw(25) << "Genero"
        << left << setw(25) << "Editorial"
        << right << setw(10) << "Paginas"
        << endl;
    cout << string(150, '-') << endl;

    for (auto it = ejemplares.begin(); it != ejemplares.end(); ++it) { //it es el iterador con el vamos a recorrer la lista 
        cout<< left << setw(35) << it->titulo
            << left << setw(25) << it->autor
            << left << setw(25) << it->genero
            << left << setw(25) << it->editorial
            << right << setw(10) << it->num_pag
            << endl;
        cout << string(150, '-') << endl;
    }

    Pausa();

    
}

void Modificar_libro(std::list<libro>& ejemplares) {
    cout << "######################################### Modificacion de datos de libros ###################################################" << endl<<endl;

    if (ejemplares.empty()) {//Primero verifica si la lista esta vacia
        cout << "Registro de libros Vacio..." << endl;

        Pausa();
        return;
    }
    string Titulo_buscado;

    cout << "Ingresa el tirulo del libro a modificar: ";
    getline(cin, Titulo_buscado);
    transform(Titulo_buscado.begin(), Titulo_buscado.end(), Titulo_buscado.begin(), ::toupper);

    bool encontrado = false;
    for (auto& Modi : ejemplares) { //for each, para modficar y recorrer
        if (Titulo_buscado == Modi.titulo) {
            encontrado = true;
            cout << "///////////////////////Libro encontrado///////////////////////" << endl << endl;
            cout << "Nuevo titulo: ";
            getline(cin, Modi.titulo);
            transform(Modi.titulo.begin(), Modi.titulo.end(), Modi.titulo.begin(), ::toupper);
            cout <<"---------------------------------------------------------------------------------------------------------"<< endl;

            cout << "Nuevo Autor: ";
            getline(cin, Modi.autor);
            transform(Modi.autor.begin(), Modi.autor.end(), Modi.autor.begin(), ::toupper);
            cout << "---------------------------------------------------------------------------------------------------------" << endl;

            cout << "Nuevo Genero: ";
            getline(cin, Modi.genero);
            transform(Modi.genero.begin(), Modi.genero.end(), Modi.genero.begin(), ::toupper);
            cout << "---------------------------------------------------------------------------------------------------------" << endl;

            cout << "Nueva Editorial: ";
            getline(cin, Modi.editorial);
            transform(Modi.editorial.begin(), Modi.editorial.end(), Modi.editorial.begin(), ::toupper);
            cout << "--------------------------------------------------------------------------------------------------------" << endl;

            cout << "Nuevo No. Paginas: ";
            Modi.num_pag = Verificar_entrada_numero();
            cout << "---------------------------------------------------------------------------------------------------------" << endl;
            
            cout << "///////////////////////Libro Modificado///////////////////////" << endl << endl;

            Pausa();

        }
    }

    if (encontrado == false) {
        cout << "///////////////////////Libro no encontrado///////////////////////" << endl<<endl;

        Pausa();

    }



}

void Eliminar_libro(std::list<libro>& ejemplares) {
    cout << "######################################### Eliminacion de libros ###################################################" << endl<<endl;
    if (ejemplares.empty()) {//Primero verifica si la lista esta vacia
        cout << "Registro de libros Vacio..." << endl<<endl;

        Pausa();
        return;
    }

    string Titulo_buscado;


    cout << "Ingresa el tirulo del libro a eliminar: ";
    getline(cin, Titulo_buscado);
    transform(Titulo_buscado.begin(), Titulo_buscado.end(), Titulo_buscado.begin(), ::toupper);

    bool encontrado = false;
    for (auto it = ejemplares.begin(); it != ejemplares.end(); it++) {
        if (it->titulo==Titulo_buscado) {
            encontrado = true;
            ejemplares.erase(it);
            cout << "Elemento borrado del registro..." << endl<<endl;

            Pausa();

            return;
        }
    }
    if (encontrado == false) {
        cout << "Libro no encontrado..." << endl << endl;

        Pausa();

    }
}

void Buscar(std::list<libro>& ejemplares) {
    cout << "######################################### Busqueda de libros ###################################################" << endl<<endl;
    if (ejemplares.empty()) {//Primero verifica si la lista esta vacia
        cout << "Registro de libros Vacio..." << endl<<endl;

        Pausa();

        return;
    }

    string Titulo_buscado;
    cout << "Ingresa el titulo del libro a buscar: ";
    getline(cin, Titulo_buscado);
    transform(Titulo_buscado.begin(), Titulo_buscado.end(), Titulo_buscado.begin(), ::toupper);

    
    for (auto& it : ejemplares) {
        if (it.titulo == Titulo_buscado) {
            
            cout << "///////////////////////Libro Encontrado///////////////////////" << endl << endl;
            cout << "Titulo: " << it.titulo << endl;
            cout << "Autor: " << it.autor << endl;
            cout << "Genero: " << it.genero << endl;
            cout << "Editorial: " << it.editorial << endl;
            cout << "No. Paganinas: " << it.num_pag << endl;

            Pausa();

            return;
        }
    }
    
    cout << "Libro no encontrado..." << endl;
    Pausa();

}

void Generar_archivo(std::list<libro>& ejemplares) {
    fstream archivo("Lista_de_Libros.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo..." << endl;
        return;
    }

    for (auto& it : ejemplares) {
        archivo << "Titulo: " << it.titulo << "\n"
            << "Autor: " << it.autor << "\n"
            << "Genero: " << it.genero << "\n"
            << "Editorial: " << it.editorial << "\n"
            << "Paginas: " << it.num_pag << "\n"
            << "----------------------------------------\n";
    }

    archivo.close();
    cout << "Archivo generado con exito: Libros.txt\n";
    Pausa();
}



int Verificar_entrada_numero() {
    int numero;
    while (true) {
        if (cin >> numero) {
            return numero;
        }
        else {
            cout << "------Entrada invalida. Solo se permiten numeros------" << endl;
            cout << "Ingrese solo numeros: ";
            cin.clear(); // limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia el buffer
        }
    }
}


void Pausa() {
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}