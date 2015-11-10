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

void inicializarMatriz(int filas,int columnas,float **matriz) {
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matriz[i][j] = 0;
        }
    }
}

void llenarDelitos(map<string, int> & indices, int cantidadDelitos){
    ifstream archivoDelitos;
    string tipoDelito;
    int fila = 0;
    archivoDelitos.open("../archivos/delitos.csv");
    if(archivoDelitos.fail())
    {
        cout << "Error al abrir el archivo delitos.csv" << endl;
    }
    while(true){
        if (archivoDelitos.eof()) break;
        getline(archivoDelitos, tipoDelito, ',' );
        indices.insert(pair<string, int> (tipoDelito, fila));
        fila ++;
    }
    archivoDelitos.close();
    cantidadDelitos = fila;
}

void leerBayes(map<string, int> & indices, float **matrizProbabilidades, int cantidadDelitos) {
    ifstream resultadosBayes;
    string descarte;
    float *
    int id = 0, contador = 0;
    float probabilidad = 0;

    resultadosBayes.open("../archivos/resultadosBayes.csv");
    getline(resultadosBayes, descarte, '\n');

    while (true) {
        getline(resultadosBayes,probabilidad,',');
    }
}

int main() {
    map<string, int> indices;
    int cantidadDelitosTotales, masProbables;
    cantidadDelitosTotales = 0;
    masProbables = 6; //5 probables mas el ID
    llenarDelitos(indices, cantidadDelitos);
    float** matrizProbabilidades = new float *[masProbables];
    for (int i = 0; i < masProbables; i++) {
        matrizProbabilidades[i] = new int [2];
    }

    inicializarMatriz(2, masProbables, matrizFrecuencias);
    leerBayes(indices, matrizProbabilidades, cantidadDelitos);

    for (int i = 0; i < masProbables; i++) {
        delete [] matrizProbabilidades[i];
    }
    delete [] matrizProbabilidades;

    return 0;
}
