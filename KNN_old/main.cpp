#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <vector>
#include <sstream>

const int FEATURES = 6;
using namespace std;

string obtenerFecha(string fechaHora){
    string fechaStr;
    fechaStr = fechaHora.substr(0,10);
    return fechaStr;
}

string obtenerHora(string fechaHora){
    string horaStr;
    horaStr = fechaHora.substr(11,8);
    return horaStr;
}

void inicializarMatriz(int filas,string **matriz) {
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < FEATURES; j++){
            matriz[i][j] = "";
        }
    }
}

bool tieneComilla(string linea){
    int i = 0;
    i = linea.find('"', 0);
    if (i >= 0)
        return true;
    else
        return false;
}

void leerArchivo (string **matrizDatos,int cantidadDelitos) {
    ifstream archivo;
    string fechaHora, fecha, hora, categoria, diaSemana, coordenadaX, coordenadaY, descarte;

    archivo.open("../archivos/train.csv");
    if(archivo.fail())
    {
        cout << "Error al abrir el archivo train.csv" << endl;
    }
    getline(archivo, descarte, '\n');

    for (int i = 0; i < cantidadDelitos; i++){
        for (int j = 0; i < FEATURES; j++){
            cout << matrizDatos[i][j] << " ";
        }
        cout << endl;
    }

    int i = 0;
    int j = 0;
    while(true){
        j = 0;
        if (archivo.eof()) break;
        getline(archivo, fechaHora,',');
        hora = obtenerHora(fechaHora);
        matrizDatos[i][j] = hora;
        j++;
        fecha = obtenerFecha(fechaHora);
        matrizDatos[i][j] = fecha;
        j++;
        getline(archivo, categoria,',');
        matrizDatos[i][j] = categoria;
        j++;
        getline(archivo, descarte,',');
            if (tieneComilla(descarte)){
                getline(archivo,descarte, '"');
                getline(archivo,descarte, ',');
            }
        getline(archivo, diaSemana, ',');
        matrizDatos[i][j] = diaSemana;
        j++;
        getline(archivo, descarte, ',');
        getline(archivo, descarte, ',');
        getline(archivo, descarte, ',');
        getline(archivo, coordenadaX, ',');
        matrizDatos[i][j] = coordenadaX;
        j++;
        getline(archivo,coordenadaY, '\n');
        matrizDatos[i][j] = coordenadaY;
        j++;
        i++;
    }

    archivo.close();
}

int contarDelitos(){
    ifstream archivo;
    int contador = 0;
    string descarte = "";

    archivo.open("../archivos/train.csv");
    getline(archivo, descarte, '\n');

    while (true){
    if (archivo.eof()) break;
        getline(archivo,descarte, '\n');
        contador ++;
    }
    archivo.close();
    return contador;
}

int main()
{
    int cantidadDelitos = 0;
    cantidadDelitos = contarDelitos();

    cout << cantidadDelitos << endl;

    string **matrizDatos = new string*[cantidadDelitos];
    for (int i = 0; i < cantidadDelitos; i++){
        matrizDatos[i] = new string[FEATURES];
    }

    inicializarMatriz(cantidadDelitos,matrizDatos);
    leerArchivo(matrizDatos,cantidadDelitos);

    for (int i = 0; i < cantidadDelitos; i++){
        for (int j = 0; j < FEATURES; j++){
            cout << matrizDatos[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < cantidadDelitos; i++) {
        delete [] matrizDatos[i];
    }
    delete [] matrizDatos;

    return 0;
}
