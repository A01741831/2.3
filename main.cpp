#include "bitacora.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

void leerArchivo(vector<Bitacora>& datos);
int mesANum(string mesTemp);
void archivoOrdenado(vector<Bitacora>& datos);
void swapD(int i, int j, vector<Bitacora>& vec);
void quickSort(vector<Bitacora>& vec);
void quickSort(int ini, int fin, vector<Bitacora>& vec);
int particion(int ini, int fin, vector<Bitacora>& vec);
int busqueda(vector<Bitacora>& vec);

int main()
{
    vector<Bitacora> datos;

    cout << "Leyendo datos." << endl;
    leerArchivo(datos);
    
    cout << "Ordenando datos." << endl;
    quickSort(datos);

    cout << "Creando archivo ordenado." << endl;
    archivoOrdenado(datos);
    cout << "Archivo ordenado listo." << endl;

    cout << "\nBUSQUEDAS" << endl;
    busqueda(datos);

    return 0;
}

// Funcion que lee los datos del archivo y los guarda en el vector.
void leerArchivo(vector<Bitacora>& datos) {
    ifstream archivo("bitacora-1.txt");
    string mesTemp, hora, IP, razon;
    int dia, mes;

    if (!archivo) {
        cout << "El archivo no se pudo abrir" << endl;
        exit(1);
    }

    while (archivo >> mesTemp >> dia >> hora >> IP) {
        getline(archivo, razon);
        razon = razon.substr(1);
        mes = mesANum(mesTemp);
        Bitacora registro(mes, mesTemp, dia, hora, IP, razon);
        datos.push_back(registro);
    }

    archivo.close();

    cout << "Se han leído " << datos.size() << " registros." << endl;
}

// Funcion que convierte el nombre del mes al valor numerico correspondiente.
int mesANum(string mesTemp)
{
    unordered_map<string,int> meses={
    {"Jan",1}, {"Feb",2}, {"Mar",3}, {"Apr",4}, {"May",5}, {"Jun",6}, {"Jul",7}, {"Aug",8}, {"Sep",9}, {"Oct",10}, {"Nov",11}, {"Dec",12}
    };

    return meses[mesTemp];
}

// Funcion que intercambia dos elementos en el vector, para usarse dentro de Quick Sort.
void swapD(int i, int j, vector<Bitacora>& vec) {

    Bitacora aux=vec[i];
    vec[i]=vec[j];
    vec[j]=aux;
}

// Funciones para la implementacion del algoritmo de ordenamiento Quick Sort.
// Complejidad O(n log n)

// Funcion que realiza particiones en el vector para usarse en el Quick Sort.
int particion(int ini, int fin, vector<Bitacora>& vec)
{
    int pivote=ini;
    int i=ini+1;

    for (int j=i;j<=fin;j++) {
        if (vec[j]<vec[pivote]) {
            swapD(i,j,vec);
            i+=1;
        }
    }

    swapD(ini,i-1,vec);

    return i-1;
}

void quickSort(vector<Bitacora>& vec)
{
    int sizeV=vec.size();
    quickSort(0,sizeV-1,vec);
}

void quickSort(int ini, int fin, vector<Bitacora>& vec)
{
    if (ini<fin) {
        int posPivote=particion(ini,fin,vec);
        quickSort(ini,posPivote-1,vec);
        quickSort(posPivote+1,fin,vec);
    }
}

// Funcion en donde se crea un nuevo archivo con los datos ordenados.
void archivoOrdenado(vector<Bitacora>& datos)
{
    ofstream archivo;
    int sizeV;

    archivo.open("bitacoraOrdenada1.3-eq3.txt",ios::out);
    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir";
                exit(1);
    }

    sizeV=datos.size();

    for(int i=0;i<sizeV;i++){
        archivo<<datos[i].getMesS()<<" "<<datos[i].getDia()<<" "<<datos[i].getHora()<<" "<<datos[i].getIP()<<" "<<datos[i].getRazon()<<endl;
    }
    archivo.close();
}

// Funcion para realizar las busquedas y guardarlas en archivos. Implementa la busqueda secuencial.
// Complejidad O(n)

int busqueda(vector<Bitacora>& datos)
{
    int repetir = 1;
    string fechaInicio, fechaFin;
    static int contador = 1;

    do {
        cout << "\nIngrese la fecha de inicio (MMM DD): ";
        getline(cin, fechaInicio);
        cout << "Ingrese la fecha de fin (MMM DD): ";
        getline(cin, fechaFin);

        int mesInicio = mesANum(fechaInicio.substr(0, 3));
        int diaInicio = stoi(fechaInicio.substr(4));
        int mesFin = mesANum(fechaFin.substr(0, 3));
        int diaFin = stoi(fechaFin.substr(4));

        cout << "Buscando registros entre " << fechaInicio << " y " << fechaFin << "." << endl;

        string nombreArchivo = "salida" + to_string(contador) + "-eq3.txt";
        ofstream archivoSalida(nombreArchivo);

        if (!archivoSalida) {
            cout << "No se pudo crear el archivo de salida." << endl;
            return 1;
        }

        for (size_t i = 0; i < datos.size(); i++) {
            Bitacora entry = datos[i];
            int mes = entry.getMes();
            int dia = entry.getDia();

            if ((mes > mesInicio || (mes == mesInicio && dia >= diaInicio)) &&
                (mes < mesFin || (mes == mesFin && dia <= diaFin))) {
                archivoSalida << entry.getMesS() << " " << entry.getDia() << " " << entry.getHora() << " "
                              << entry.getIP() << " " << entry.getRazon() << endl;
            }
        }

        archivoSalida.close();
        cout << "Registros guardados en el archivo " << nombreArchivo << endl;

        cout << "\nRealizar otra búsqueda?\n<0> No\n<1> Si" << endl;
        cin >> repetir;
        cin.ignore();

        contador++;
    } while (repetir == 1);

    return 0;
}