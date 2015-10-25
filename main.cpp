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

void procesarArchivo(string nombreArchivo) {
    ifstream archivo;
    string tipoDelito, descripcion, diaSemana, distrito, fecha, franjaHoraria;
    int fila, columna;
    map<string, int> indices;
    archivo.open("archivos/train.csv");
    fila = 0;
    columna = 0;

    if(archivo.fail())
    {
        cout << "Error al abrir el archivo train.csv" << endl;
    }
    getline();
    while(true)
    {
        getline(archivo, fecha,',' );
        getline(archivo, tipoDelito, ',' );
        getline(archivo, descripcion, ',' );
        getline(archivo, diaSemana, ',' );
        getline(archivo, distrito, ',' );
        if (archivo.eof()) break;
        franjaHoraria = obtenerFranjaHoraria(fecha);
        map<string, int>::iterator iteradorIndiceFila = indices.find(tipoDelito);
        if(iteradorIndiceFila != iteradorIndiceFila.end())
        {
            indices.insert(pair<string, int> (tipoDelito, fila));
            fila += 1;
        }
        map<string, int>::iterator iteradorIndiceColumna = indices.find(franjaHoraria);
        if(iteradorIndiceColumna != iteradorIndiceColumna.end())
        {
            indices.insert(pair<string, int> (franjaHoraria, columna));
            columna += 1;
        }
        map<string, int>::iterator iteradorIndiceColumna = indices.find(diaSemana);
        if(iteradorIndiceColumna != iteradorIndiceColumna.end())
        {
            indices.insert(pair<string, int> (diaSemana, columna));
            columna += 1;
        }
        map<string, int>::iterator iteradorIndiceColumna = indices.find(distrito);
        if(iteradorIndiceColumna != iteradorIndiceColumna.end())
        {
            indices.insert(pair<string, int> (distrito, columna));
            columna += 1;
        }
    }

    archivo.close();

    reviewsTotales = reviewsPositivos + reviewsNegativos;

    cout << "En total hay  " << reviewsTotales << " reviews totales" << endl;
    cout << "En total hay  " << reviewsPositivos << " reviews positivos" << endl;
    cout << "En total hay  " << reviewsNegativos << " reviews negativos" << endl;
}


}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
