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

bool tieneComilla(string linea){
    int i = 0;
    i = linea.find('"', 0);
    if (i >= 0)
        return true;
    else
        return false;
}

bool coordenadasSonValidas(int coordX, int coordY){
    if (((abs(coordX)) > -122) && ((abs(coordY)) > 38)){
        return false;
    } else {
        return true;
    }
}

bool datosEstanCompletos(string distrito, string direccion){
    if ((distrito == "") && (direccion == "")){
        return false;
    } else {
        return true;
    }

}

void borrarRegistrosDefectuosos(){

    ifstream archivo;
    ofstream archivoSalida;
    string descarte, linea, strFecha, strCategoria, strDescripcion, strDiaSemana, strDistrito, strDireccion, strResolucion, strCoordenadaX, strCoordenadaY;
    int coordenadaX = 0, coordenadaY = 0, contador = 0;

    archivo.open("../archivos/train.csv");
    if(archivo.fail()){
        cout << "Error al abrir el archivo train.csv" << endl;
    }

    getline(archivo, descarte, '\n'); //Obtengo la primera linea, que es la que tiene las cabeceras y la descarto

    archivoSalida.open("../archivos/trainCorregido.csv");
    if(archivoSalida.fail()){
        cout << "Error al abrir el archivo trainCorregido.csv" << endl;
    }

    archivoSalida << "Dates,Category,Descript,DayOfWeek,PdDistrict,Resolution,Address,X,Y" << endl;

    while(true){

        if (archivo.eof()) break;
        getline(archivo, strFecha, ',');
        getline(archivo, strCategoria,',');
        getline(archivo, strDescripcion, ',' );
            if (tieneComilla(strDescripcion)){
                string strDescripcion1, strDescripcion2;
                getline(archivo,strDescripcion1, '"');
                getline(archivo,strDescripcion2, ',');
                strDescripcion = strDescripcion + ',' + strDescripcion1 + strDescripcion2 + '"';
            }
        getline(archivo, strDiaSemana, ',');
        getline(archivo, strDistrito, ',');
        getline(archivo, strResolucion, ',');
            if (tieneComilla(strResolucion)){
                string strResolucion1, strResolucion2;
                getline(archivo,strResolucion1, '"');
                getline(archivo,strResolucion2, ',');
                strResolucion = strResolucion + ',' + strResolucion1 + strResolucion2 + '"';
            }
        getline(archivo, strDireccion, ',');
        getline(archivo, strCoordenadaX, ',');
        getline(archivo, strCoordenadaY, '\n');

        coordenadaX = atoi(strCoordenadaX.c_str());
        coordenadaY = atoi(strCoordenadaY.c_str());

        linea = strFecha + ',' + strCategoria + ',' + strDescripcion + ',' + strDiaSemana + ',' + strDistrito + ',' + strResolucion + ',' + strDireccion + ',' + strCoordenadaX + ',' + strCoordenadaY;

        if (coordenadasSonValidas(coordenadaX,coordenadaY)){
            archivoSalida << linea << endl;
        } else {
            cout << "Se elimino el siguiente registro defectuoso: " << linea << endl;
            contador++;
        }
    }

    cout << contador <<" registros corregidos exitosamente." << endl;
}

int main() {

    borrarRegistrosDefectuosos();
    return 0;

}
