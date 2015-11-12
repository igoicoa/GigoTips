#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <vector>
#include <sstream>

const int MASPROBABLES = 6;

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

bool tieneComilla(string linea){
    int i = 0;
    i = linea.find('"', 0);
    if (i >= 0)
        return true;
    else
        return false;
}

string reemplazadorDeBarrasPorEspacio (string categoria){
    int posicion = categoria.find("/");
    if(posicion > 0 ){
        categoria.replace(posicion, 1, " ");
    }
    return categoria;
}

void crearArchivosPorDelito(){
    ifstream archivo;
    ofstream archivoSalida;
    string fechaHora, hora, fecha, categoria, diaSemana, coordenadaX, coordenadaY, descarte, ruta, strLinea;
    archivo.open("../archivos/train.csv");
    if(archivo.fail())
    {
        cout << "Error al abrir el archivo train.csv" << endl;
    }
    getline(archivo, descarte, '\n');
    while(true){
        if (archivo.eof()) break;
        getline(archivo, fechaHora,',');
        hora = obtenerHora(fechaHora);
        fecha = obtenerFecha(fechaHora);
        getline(archivo, categoria,',');
        getline(archivo, descarte,',');
        if (tieneComilla(descarte)){
            getline(archivo,descarte, '"');
            getline(archivo,descarte, ',');
        }
        getline(archivo, diaSemana, ',');
        getline(archivo, descarte, ',');
        getline(archivo, descarte, ',');
        if (tieneComilla(descarte)){
            getline(archivo,descarte, '"');
            getline(archivo,descarte, ',');
        }
        getline(archivo, descarte, ',');
        getline(archivo, coordenadaX, ',');
        getline(archivo, coordenadaY, '\n');
        categoria = reemplazadorDeBarrasPorEspacio(categoria);
        ruta = "../archivos/delitos/" + categoria + ".csv";
        archivoSalida.open(ruta.c_str(), std::ios::app);
        strLinea = hora + "," + fecha + "," + diaSemana + "," + coordenadaX + "," + coordenadaY;
        archivoSalida << strLinea << endl;
        archivoSalida.close();
    }
    archivo.close();
}
void mostrarMatrizFloat(int filas, int columnas, float **matriz) {
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void inicializarMatriz(int filas,int columnas,float **matriz) {
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            matriz[i][j] = 0;
        }
    }
}

void llenarDelitos(map<int, string> & indices, int cantidadDelitos){
    ifstream archivoDelitos;
    string tipoDelito;
    int fila = 1;
    archivoDelitos.open("../archivos/delitos.csv");
    if(archivoDelitos.fail())
    {
        cout << "Error al abrir el archivo delitos.csv" << endl;
    }
    while(true){
        if (archivoDelitos.eof()) break;
        getline(archivoDelitos, tipoDelito, ',' );
        tipoDelito = reemplazadorDeBarrasPorEspacio(tipoDelito);
        indices.insert(pair<int, string> (fila, tipoDelito));
        fila ++;
    }
    archivoDelitos.close();
    cantidadDelitos = fila;

    map<int, string>::iterator iteradorIndice = indices.begin();
    cout << "El tamaño del diccionario es: " << indices.size() << endl;
    while (iteradorIndice != indices.end())
    {
        cout << "El delito es: " << iteradorIndice->second << " Y su indice es: " << iteradorIndice->first << endl;
        iteradorIndice ++;
    }
}

void obtenerProbabilidadMenor(float **matrizProbabilidades, float *menor) {
    float menorProbabilidad = 1; //es la maxima posible, siempre habra una menor
    for (int j = 1; j < 6; j++) {
        float actual = matrizProbabilidades[1][j];
        if (actual < menorProbabilidad) {
            menorProbabilidad = actual;
            menor[0] = j; //posicion
            menor[1] = menorProbabilidad;
        }
    }
}

void guardarProbabilidad(float probabilidad, int contador, float **matrizProbabilidades) {
    float *menor = new float [2];
    menor[0] = 0;
    menor[1] = 0;
    if (contador < 6) {
        matrizProbabilidades[0][contador] = contador;
        matrizProbabilidades[1][contador] = probabilidad;
    } else {
        obtenerProbabilidadMenor(matrizProbabilidades, menor);
        int posicionMenor = (int) menor[0]; //OJO!!! Acordarse que devuelve la posicion en la matriz, no el ID
        float probabilidadMenor = menor[1];
        if (probabilidad > probabilidadMenor){
            matrizProbabilidades[0][posicionMenor] = contador;
            matrizProbabilidades[1][posicionMenor] = probabilidad;
        }
    }
}

void leerBayes(map<int, string> & indices, float **matrizProbabilidades, int cantidadDelitos) {
    ifstream resultadosBayes;
    ifstream test;
    ifstream archivoDelDelito;
    string descarte, strProbabilidad, idTest, fechaHora, fecha, hora, diaSemana, coordenadaX, coordenadaY, delito;
    string strID, ruta;
    float *vectorAClasificar = new float [5];
    float *vectorTrain = new float [5];
    float *vectorDistancias =
    int id = 0, contador;
    int numeroDelito = 0;
    double doubleProbabilidad = 0;
    float probabilidad = 0;
    test.open("../archivos/test.csv");
    resultadosBayes.open("../archivos/resultadosBayes.csv");

    getline(resultadosBayes, descarte, '\n');
    getline(test, descarte, '\n');
    while (true) {
        if ((resultadosBayes.eof()) && (test.eof())) break;
        contador = 1;
        getline(resultadosBayes, strID, ',');
        id = atoi(strID.c_str());
        matrizProbabilidades[0][0] = id;
        matrizProbabilidades[1][0] = id;
        getline(test, idTest,',');
        getline(test, fechaHora,',');
        hora = obtenerHora(fechaHora);
        fecha = obtenerFecha(fechaHora);
        getline(test, diaSemana, ',');
        getline(test, descarte, ',');
        getline(test, descarte, ',');
        getline(test, coordenadaX, ',');
        getline(test, coordenadaY, '\n');
        vectorAClasificar[0] = fecha;
        vectorAClasificar[1] = hora;
        vectorAClasificar[2] = diaSemana;
        vectorAClasificar[3] = coordenadaX;
        vectorAClasificar[4] = coordenadaY;
        while (contador < 40) {
            if (contador == 39) {
                getline(resultadosBayes, strProbabilidad, '\n');
            } else {
                getline(resultadosBayes, strProbabilidad, ',');
            }
            doubleProbabilidad = atof(strProbabilidad.c_str());
            probabilidad = (float) doubleProbabilidad;

            guardarProbabilidad(probabilidad, contador, matrizProbabilidades);

            contador ++;
        }
        if (idTest == strID) {
            for (int j = 1; j < MASPROBABLES; j ++) {
                numeroDelito = (int) matrizProbabilidades[0][j];
                delito = indices.at(numeroDelito);
                ruta = "../archivos/delitos/" + delito + ".csv";
                archivoDelDelito.open(ruta.c_str());
                while (true) {
                    if (archivoDelDelito.eof()) break;


                }
            }
        }
    }
    resultadosBayes.close();
}

int main() {
    map<int, string> indices;
    int cantidadDelitosTotales, filas;
    char respuesta;
    cantidadDelitosTotales = 0;
    filas = 2;

    llenarDelitos(indices, cantidadDelitosTotales);

    cout << "Desea generar los 39 archivos ? (S/N)" << endl;
    cin >> respuesta;

    if ((respuesta == 'S') || (respuesta == 's')) {
        crearArchivosPorDelito();
    }

    float** matrizProbabilidades = new float *[filas];
    for (int i = 0; i < filas; i++) {
        matrizProbabilidades[i] = new float [MASPROBABLES];
    }


    inicializarMatriz(filas, MASPROBABLES, matrizProbabilidades);
    leerBayes(indices, matrizProbabilidades, cantidadDelitosTotales);


    for (int i = 0; i < filas; i++) {
        delete [] matrizProbabilidades[i];
    }
    delete [] matrizProbabilidades;

    return 0;
}
