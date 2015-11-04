#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

bool tieneComilla(string linea);
string obtenerFranjaHoraria(string fecha);

int *crearDiccionario(map<string, int> & indices) {
    ifstream archivo;
    string tipoDelito, descripcion, diaSemana, distrito, fecha, franjaHoraria, descarte, linea;
    int fila, columna;
    int *indicesFinales = new int[2];
    archivo.open("archivos/train.csv");
    fila = 0;
    columna = 0;

    if(archivo.fail())
    {
        cout << "Error al abrir el archivo train.csv" << endl;
    }
    getline(archivo, descarte, '\n');
    while(true)
    {

        getline(archivo, fecha,',');
        franjaHoraria = obtenerFranjaHoraria(fecha);
        getline(archivo, tipoDelito, ',' );
        getline(archivo, descripcion, ',' );
            if (tieneComilla(descripcion))
            {
                getline(archivo,descripcion, '"');
                getline(archivo,descripcion, ',');
            }
        getline(archivo, diaSemana, ',' );
        getline(archivo, distrito, ',' );
        getline(archivo, descarte, '\n' );

        if (archivo.eof()) break;
        map<string, int>::iterator iteradorIndiceFila = indices.find(tipoDelito);
        if(iteradorIndiceFila == indices.end())
        {
            indices.insert(pair<string, int> (tipoDelito, fila));
            fila += 1;
        }
        map<string, int>::iterator iteradorIndiceColumna = indices.find(franjaHoraria);
        if(iteradorIndiceColumna == indices.end())
        {
            indices.insert(pair<string, int> (franjaHoraria, columna));
            columna += 1;
        }
        map<string, int>::iterator iteradorIndiceColumna2 = indices.find(diaSemana);
        if(iteradorIndiceColumna2 == indices.end())
        {
            indices.insert(pair<string, int> (diaSemana, columna));
            columna += 1;
        }
        map<string, int>::iterator iteradorIndiceColumna3 = indices.find(distrito);
        if(iteradorIndiceColumna3 == indices.end())

        {
            indices.insert(pair<string, int> (distrito, columna));
            columna += 1;
        }

    }

    archivo.close();
    map<string, int>::iterator iteradorIndice = indices.begin();
    cout << "El tamaño del diccionario es: " << indices.size() << endl;
    while (iteradorIndice != indices.end())
    {
        cout << "El feature/delito es: " << iteradorIndice->first << " Y su fila/columna es: " << iteradorIndice->second << endl;
        iteradorIndice ++;

    }
    indicesFinales[0] = fila;
    indicesFinales[1] = columna;
    return indicesFinales;
}

bool tieneComilla(string linea)
{
    int i = 0;
    i = linea.find('"', 0);
    if (i >= 0)
        return true;
    else
        return false;
}

string obtenerFranjaHoraria(string fecha)
{
    string horaStr;
    string franja;
    horaStr = fecha.substr(11, 2);
    int hora = atoi(horaStr.c_str());
    if (hora < 7)
    {
        franja = "Madrugada";
    }

    if ((hora >= 7) && (hora < 12))
    {
        franja = "Maniana";
    }

    if ((hora >= 12) && (hora < 18))
    {
        franja = "Tarde";
    }

    if ((hora >= 18) && (hora < 24))
    {
        franja = "Noche";
    }

    return franja;
}

void inicializarMatriz(int filas,int columnas,int **matriz) {
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matriz[i][j] = 0;
        }
    }
}

void mostrarMatriz(int filas,int columnas,int **matriz) {
    for(int i = 0; i < filas; i++){
        //cout << "fila:" << i << endl;
        for(int j = 0; j < columnas; j++){
            //cout << "columna" << j << endl;
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}


void llenarMatriz(map<string, int> & indices, int **matrizFrecuencias) {

    ifstream archivo;
    string tipoDelito, descripcion, diaSemana, distrito, fecha, franjaHoraria, descarte, linea;
    int filaDelito, columnaHora, columnaDiaSemana, columnaDistrito;
    archivo.open("archivos/train.csv");

    if(archivo.fail())
    {
        cout << "Error al abrir el archivo train.csv" << endl;
    }

    getline(archivo, descarte, '\n');

    while(true)
    {

        getline(archivo, fecha,',');
        franjaHoraria = obtenerFranjaHoraria(fecha);
        getline(archivo, tipoDelito, ',' );
        getline(archivo, descripcion, ',' );
            if (tieneComilla(descripcion))
            {
                getline(archivo,descripcion, '"');
                getline(archivo,descripcion, ',');
            }
        getline(archivo, diaSemana, ',' );
        getline(archivo, distrito, ',' );
        getline(archivo, descarte, '\n' );

        if (archivo.eof()) break;

        /* Se obtiene la fila y las columnas correspondientes a la linea leida
          para llenar la posicion [fila][columna] de la matriz con +1 */
        filaDelito = indices[tipoDelito];
        columnaHora = indices[franjaHoraria];
        columnaDiaSemana = indices[diaSemana];
        columnaDistrito = indices[distrito];
        //cout << filaDelito << endl;
        matrizFrecuencias[filaDelito][columnaHora] +=1;
        matrizFrecuencias[filaDelito][columnaDiaSemana] += 1;
        matrizFrecuencias[filaDelito][columnaDistrito] += 1;

    }

}


int main() {
    int filas, columnas;
    int *indicesFinales = new int[2];
    map<string, int> indices;
    indicesFinales = crearDiccionario(indices); //Creamos el diccionario de los indices de la matriz
    filas = indicesFinales[0];
    columnas = indicesFinales[1];
    cout <<  filas << columnas << endl;

    int** matrizFrecuencias =  new int *[filas];
    for (int i = 0; i < filas; i++) {
        matrizFrecuencias[i] = new int [columnas];
    }

    inicializarMatriz(filas, columnas, matrizFrecuencias);
    llenarMatriz(indices, matrizFrecuencias);
    mostrarMatriz(filas,columnas,matrizFrecuencias);
    return 0;
}
