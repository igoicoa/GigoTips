#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <vector>
#include <sstream>

const int CARACTERISTICAS = 21;
using namespace std;

bool tieneComilla(string linea);
string obtenerFranjaHoraria(string fecha);

void llenarDelitos(map<string, int> & indices, int *indicesFinales){
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
    indicesFinales[0] = fila;
}
int *crearDiccionario(map<string, int> & indices) {
    ifstream archivo;
    string tipoDelito, descripcion, diaSemana, distrito, fecha, franjaHoraria, descarte, linea;
    int columna;
    int *indicesFinales = new int[2];
    archivo.open("../archivos/train.csv");
    columna = 0;

    llenarDelitos(indices, indicesFinales);

    if(archivo.fail())
    {
        cout << "Error al abrir el archivo train.csv" << endl;
    }
    getline(archivo, descarte, '\n');
    while(true)
    {
        if (archivo.eof()) break;
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

void mostrarMatrizInt(int filas, int columnas, int **matriz) {
    for(int i = 0; i < filas; i++) {
        //cout << "fila:" << i << endl;
        for(int j = 0; j < columnas; j++) {
            //cout << "columna" << j << endl;
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void mostrarMatrizFloat(int filas, int columnas, float **matriz) {
    for(int i = 0; i < filas; i++) {
        //cout << "fila:" << i << endl;
        for(int j = 0; j < columnas; j++) {
            //cout << "columna" << j << endl;
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void llenarMatrizFrecuencias(map<string, int> & indices, int **matrizFrecuencias, int *vectorFrecuencias) {
    ifstream archivo;
    string tipoDelito, descripcion, diaSemana, distrito, fecha, franjaHoraria, descarte, linea;
    int filaDelito, columnaHora, columnaDiaSemana, columnaDistrito;
    archivo.open("../archivos/train.csv");

    if(archivo.fail())
    {
        cout << "Error al abrir el archivo train.csv" << endl;
    }

    getline(archivo, descarte, '\n');

    while(true)
    {
        if (archivo.eof()) break;

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
        vectorFrecuencias[filaDelito] += 1;
    }

}

void llenarVector(int filas, int columnas, float *vectorSumaColumnas, int **matrizFrec) {
    int j = 0;
    while (j < columnas) {
        for (int i = 0; i < filas; i++) {
            vectorSumaColumnas[j] += matrizFrec[i][j];
        }
        j ++;
    }
}

void inicializarVectorFloat (int posiciones, float *vectora) {
    float cero = 0;
    for (int i = 0; i < posiciones; i++) {
        vectora[i] = cero;
    }
}

void inicializarVectorInt (int posiciones, int *vectora) {
    int cero = 0;
    for (int i = 0; i < posiciones; i++) {
        vectora[i] = cero;
    }
}

void llenarVectorProbabilidades(int filas, int *vectorFrecuencias, float *vectorProbabilidades) {
    float delitosTotales = 0;
    for (int i = 0; i < filas; i++) {
        delitosTotales += (float)vectorFrecuencias[i];
    }
    for(int j = 0; j < filas; j++){
        vectorProbabilidades[j] = (float)vectorFrecuencias[j]/delitosTotales;
    }

}

void llenarMatrizProbabilidades(int filas, int columnas, float **matrizProb, int **matrizFrec) {
    float * vectorSumaColumnas = new float[columnas];
    inicializarVectorFloat(columnas, vectorSumaColumnas);
    llenarVector(filas, columnas, vectorSumaColumnas, matrizFrec);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matrizProb[i][j] = matrizFrec[i][j]/vectorSumaColumnas[j];
        }
    }
    delete [] vectorSumaColumnas;
}

void calculoDeProbabilidades(int columnas, int filas, int **matrizFrec, float **matrizProbabilidades, int *vectorFrecuencias){
    float probabilidad = 0;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            probabilidad = (float)(matrizFrec[i][j] + 1)/(float)(vectorFrecuencias[i]*3 + CARACTERISTICAS);
            matrizProbabilidades[i][j] = probabilidad;
        }
    }
}

void clasificarDelito(float **matrizProbabilidades, float *vectorResultados, float *vectorProbabilidades, string franjaHoraria, string diaSemana, string distrito, int filas, map<string, int> & indices) {
    int j, k, l;
    for(int i = 0; i < filas; i++) {
        map<string, int>::iterator iteradorIndice = indices.find(franjaHoraria);
        if (iteradorIndice != indices.end()){
            j = iteradorIndice -> second;
        }
        iteradorIndice = indices.find(diaSemana);
        if (iteradorIndice != indices.end()){
            k = iteradorIndice -> second;
        }
        iteradorIndice = indices.find(distrito);
        if (iteradorIndice != indices.end()){
            l = iteradorIndice -> second;
        }

        vectorResultados[i] = log (vectorProbabilidades[i]) + log(matrizProbabilidades[i][j]) + log(matrizProbabilidades[i][k]) + log(matrizProbabilidades[i][l]);
    }
}

void clasificacion(int filas, int columnas, float **matrizProbabilidades, float *vectorProbabilidades, map<string, int> & indices){
    ifstream archivo;
    ofstream archivoSalida;
    string id, fecha, diaSemana, distrito, descarte, franjaHoraria;
    float *vectorResultados = new float [filas];
    inicializarVectorFloat(filas, vectorResultados);

    archivo.open("../archivos/test.csv");
    if(archivo.fail())
    {
        cout << "Error al abrir el archivo test.csv" << endl;
    }
    getline(archivo, descarte, '\n');

    archivoSalida.open("../archivos/resultadosBayes.csv");
    if(archivo.fail())
    {
        cout << "Error al abrir el archivo archivoBayes.csv" << endl;
    }

    while(true){

        if (archivo.eof()) break;
        getline(archivo, id, ',');
        getline(archivo, fecha,',');
        franjaHoraria = obtenerFranjaHoraria(fecha);
        getline(archivo, diaSemana, ',' );
        getline(archivo, distrito, '\n');

        clasificarDelito(matrizProbabilidades, vectorResultados, vectorProbabilidades, franjaHoraria, diaSemana, distrito, filas, indices);

        archivoSalida << id << ',';
        for(int i = 0; i < filas; i++) {
            archivoSalida << vectorResultados[i] << ',';
        }
        archivoSalida << endl;

    }

}

int main() {
    int filas, columnas;
    int *indicesFinales = new int[2];
    map<string, int> indices;
    indicesFinales = crearDiccionario(indices); //Creamos el diccionario de los indices de la matriz
    filas = indicesFinales[0];
    columnas = indicesFinales[1];

    int** matrizFrecuencias =  new int *[filas];
    for (int i = 0; i < filas; i++) {
        matrizFrecuencias[i] = new int [columnas];
    }
    int *vectorFrecuencias = new int[filas];
    inicializarVectorInt(filas, vectorFrecuencias); //Tiene las frecuencias de cada delito

    inicializarMatriz(filas, columnas, matrizFrecuencias);
    llenarMatrizFrecuencias(indices, matrizFrecuencias, vectorFrecuencias);
    //mostrarMatrizInt(filas, columnas, matrizFrecuencias);

    float** matrizProbabilidades =  new float *[filas];
    for (int i = 0; i < filas; i++) {
        matrizProbabilidades[i] = new float [columnas];
    }

    float *vectorProbabilidades = new float [filas];
    inicializarVectorFloat(filas, vectorProbabilidades);
    llenarVectorProbabilidades(filas, vectorFrecuencias, vectorProbabilidades);

    calculoDeProbabilidades(columnas,filas, matrizFrecuencias, matrizProbabilidades, vectorFrecuencias);
    //mostrarMatrizFloat(filas,columnas,matrizProbabilidades);

    //llenarMatrizProbabilidades(filas, columnas, matrizProbabilidades, matrizFrecuencias);
    //mostrarMatrizFloat(filas, columnas, matrizProbabilidades);
    clasificacion(filas, columnas, matrizProbabilidades, vectorProbabilidades, indices);

    for (int i = 0; i < filas; i++) {
        delete [] matrizFrecuencias[i];
    }
    delete [] matrizFrecuencias;

    for (int i = 0; i < filas; i++) {
        delete [] matrizProbabilidades[i];
    }
    delete [] matrizProbabilidades;
    delete [] vectorFrecuencias;
    delete [] vectorProbabilidades;
    return 0;
}
