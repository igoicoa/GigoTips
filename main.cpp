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

void procesarArchivo(map<string, int> & indices) {
    ifstream archivo;
    string tipoDelito, descripcion, diaSemana, distrito, fecha, franjaHoraria, descarte, linea;
    int fila, columna;
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

int main()
{
    map<string, int> indices;
    procesarArchivo(indices);
    return 0;
}
