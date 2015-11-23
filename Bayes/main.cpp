#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <vector>
#include <sstream>

const int CARACTERISTICAS = 69;
using namespace std;

bool tieneComilla(string linea);
string obtenerFranjaHoraria(string fecha);
string obtenerAnio(string fecha);
string obtenerMes(string fecha);
string obtenerSemana(string fecha);

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
    string tipoDelito, descripcion, diaSemana, distrito, fecha, franjaHoraria, descarte, linea, anio, mes, semana;
    int columna;
    int *indicesFinales = new int[2];
    archivo.open("../archivos/trainCorregido.csv");
    columna = 0;

    llenarDelitos(indices, indicesFinales);

    if(archivo.fail())
    {
        cout << "Error al abrir el archivo trainCorregido.csv" << endl;
    }
    getline(archivo, descarte, '\n');
    while(true)
    {
        if (archivo.eof()) break;
        getline(archivo, fecha,',');
        franjaHoraria = obtenerFranjaHoraria(fecha);
        anio = obtenerAnio(fecha);
        mes = obtenerMes(fecha);
        semana = obtenerSemana(fecha);
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
        map<string, int>::iterator iteradorIndiceColumna1 = indices.find(anio);
        if(iteradorIndiceColumna1 == indices.end())
        {
            indices.insert(pair<string, int> (anio, columna));
            columna += 1;
        }
          map<string, int>::iterator iteradorIndiceColumna2 = indices.find(mes);
        if(iteradorIndiceColumna2 == indices.end())
        {
            indices.insert(pair<string, int> (mes, columna));
            columna += 1;
        }
        map<string, int>::iterator iteradorIndiceColumna3 = indices.find(semana);
        if(iteradorIndiceColumna3 == indices.end())
        {
            indices.insert(pair<string, int> (semana, columna));
            columna += 1;
        }

        map<string, int>::iterator iteradorIndiceColumna4 = indices.find(diaSemana);
        if(iteradorIndiceColumna4 == indices.end())
        {
            indices.insert(pair<string, int> (diaSemana, columna));
            columna += 1;
        }
        map<string, int>::iterator iteradorIndiceColumna5 = indices.find(distrito);
        if(iteradorIndiceColumna5 == indices.end())

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

string obtenerAnio(string fecha){
    string anioStr;
    anioStr = fecha.substr(0, 4);

    return anioStr;

}

string obtenerMes(string fecha){
    string mesStr;
    mesStr = fecha.substr(5,2);
    if(mesStr == "01"){
        return "Enero";
    }
    if(mesStr == "02"){
        return "Febrero";
    }
    if(mesStr == "03"){
        return "Marzo";
    }
     if(mesStr == "04"){
        return "Abril";
    }
     if(mesStr == "05"){
        return "Mayo";
    }
     if(mesStr == "06"){
        return "Junio";
    }
     if(mesStr == "07"){
        return "Julio";
    }
     if(mesStr == "08"){
        return "Agosto";
    }
     if(mesStr == "09"){
        return "Septiembre";
    }
     if(mesStr == "10"){
        return "Octubre";
    }
     if(mesStr == "11"){
        return "Noviembre";
    }
     if(mesStr == "12"){
        return "Diciembre";
    }

    return 0;

}

string obtenerFranjaHoraria(string fecha)
{
    string horaStr;
    string franja;
    horaStr = fecha.substr(11, 2);
    int hora = atoi(horaStr.c_str());

    if ((hora >= 0) && (hora < 1)){
        franja = "00";
    }else if ((hora >= 1) && (hora < 2)){
        franja = "01";
    }
    else if ((hora >= 2) && (hora < 3)){
        franja = "02";
    }
    else if ((hora >= 3) && (hora < 4)){
        franja = "03";
    }
    else if ((hora >= 4) && (hora < 5)){
        franja = "04";
    }
    else if ((hora >= 5) && (hora < 6)){
        franja = "05";
    }
    else if ((hora >= 6) && (hora < 7)){
        franja = "06";
    }
    else if ((hora >= 7) && (hora < 8)){
        franja = "07";
    }
    else if ((hora >= 8) && (hora < 9)){
        franja = "08";
    }
    else if ((hora >= 9) && (hora < 10)){
        franja = "09";
    }
    else if ((hora >= 10) && (hora < 11)){
        franja = "10";
    }
    else if ((hora >= 11) && (hora < 12)){
        franja = "11";
    }
    else if ((hora >= 12) && (hora < 13)){
        franja = "12";
    }
    else if ((hora >= 13) && (hora < 14)){
        franja = "13";
    }
    else if ((hora >= 14) && (hora < 15)){
        franja = "14";
    }
    else if ((hora >= 15) && (hora < 16)){
        franja = "15";
    }
    else if ((hora >= 16) && (hora < 17)){
        franja = "16";
    }
    else if ((hora >= 17) && (hora < 18)){
        franja = "17";
    }
    else if ((hora >= 18) && (hora < 19)){
        franja = "18";
    }
    else if ((hora >= 19) && (hora < 20)){
        franja = "19";
    }
    else if ((hora >= 20) && (hora < 21)){
        franja = "20";
    }
    else if ((hora >= 21) && (hora < 22)){
        franja = "21";
    }
    else if ((hora >= 22) && (hora < 23)){
        franja = "22";
    }
    else if (hora >= 23){
        franja = "23";
    }

    return franja;
}

string obtenerSemana(string fecha){
    string diaStr;
    diaStr = fecha.substr(8, 2);
    int dia = atoi(diaStr.c_str());

    if((dia >=1) && (dia <8)){
        return "Semana 1";
    }
    if((dia >=8) && (dia <15)){
        return "Semana 2";
    }
    if((dia >=15) && (dia <22)){
        return "Semana 3";
    }
    if((dia >=22) && (dia <32)){
        return "Semana 4";
    }
    return 0;

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
    string tipoDelito, descripcion, diaSemana, distrito, fecha, franjaHoraria, descarte, linea, anio, mes,semana;
    int filaDelito, columnaHora, columnaDiaSemana, columnaDistrito, columnaAnio, columnaMes, columnaSemana;
    archivo.open("../archivos/trainCorregido.csv");

    if(archivo.fail())
    {
        cout << "Error al abrir el archivo trainCorregido.csv" << endl;
    }

    getline(archivo, descarte, '\n');

    while(true)
    {
        if (archivo.eof()) break;

        getline(archivo, fecha,',');
        franjaHoraria = obtenerFranjaHoraria(fecha);
        anio = obtenerAnio(fecha);
        mes = obtenerMes(fecha);
        semana = obtenerSemana(fecha);
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
        columnaAnio = indices[anio];
        columnaMes = indices[mes];
        columnaSemana = indices[semana];
        columnaDiaSemana = indices[diaSemana];
        columnaDistrito = indices[distrito];
        //cout << filaDelito << endl;
        matrizFrecuencias[filaDelito][columnaHora] +=1;
        matrizFrecuencias[filaDelito][columnaAnio] +=1;
        matrizFrecuencias[filaDelito][columnaMes] +=1;
        matrizFrecuencias[filaDelito][columnaSemana] +=1;
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

void clasificarDelito(float **matrizProbabilidades, float *vectorResultados, float *vectorProbabilidades, string franjaHoraria, string diaSemana, string distrito, int filas, map<string, int> & indices, string anio, string mes, string semana) {
    int j = 0, k = 0, l = 0, m = 0, n = 0, o = 0;

    for(int i = 0; i < filas; i++) {
        map<string, int>::iterator iteradorIndice = indices.find(franjaHoraria);
        if (iteradorIndice != indices.end()){
            j = iteradorIndice -> second;
        }
        iteradorIndice = indices.find(anio);
        if(iteradorIndice!=indices.end()){
            m = iteradorIndice -> second;
        }
        iteradorIndice = indices.find(mes);
        if (iteradorIndice != indices.end()){
            n = iteradorIndice -> second;
        }
        iteradorIndice = indices.find(semana);
        if(iteradorIndice!=indices.end()){
            o = iteradorIndice -> second;
        }
        iteradorIndice = indices.find(diaSemana);
        if (iteradorIndice != indices.end()){
            k = iteradorIndice -> second;
        }
        iteradorIndice = indices.find(distrito);
        if (iteradorIndice != indices.end()){
            l = iteradorIndice -> second;
        }

        vectorResultados[i] = (vectorProbabilidades[i]) * (matrizProbabilidades[i][j]) * (matrizProbabilidades[i][k]) * (matrizProbabilidades[i][l])*(matrizProbabilidades[i][m])*(matrizProbabilidades[i][n])*(matrizProbabilidades[i][o]);
    }
}

void clasificacion(int filas, int columnas, float **matrizProbabilidades, float *vectorProbabilidades, map<string, int> & indices){
    ifstream archivo;
    ofstream archivoSalida;
    string id, fecha, diaSemana, distrito, descarte, franjaHoraria, anio, mes, semana;
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
    archivoSalida << "Id,ARSON,ASSAULT,BAD CHECKS,BRIBERY,BURGLARY,DISORDERLY CONDUCT,DRIVING UNDER THE INFLUENCE,DRUG/NARCOTIC,DRUNKENNESS,EMBEZZLEMENT,EXTORTION,FAMILY OFFENSES,FORGERY/COUNTERFEITING,FRAUD,GAMBLING,KIDNAPPING,LARCENY/THEFT,LIQUOR LAWS,LOITERING,MISSING PERSON,NON-CRIMINAL,OTHER OFFENSES,PORNOGRAPHY/OBSCENE MAT,PROSTITUTION,RECOVERED VEHICLE,ROBBERY,RUNAWAY,SECONDARY CODES,SEX OFFENSES FORCIBLE,SEX OFFENSES NON FORCIBLE,STOLEN PROPERTY,SUICIDE,SUSPICIOUS OCC,TREA,TRESPASS,VANDALISM,VEHICLE THEFT,WARRANTS,WEAPON LAWS" << endl;
    int contador = 0;
    while(true){

        if (archivo.eof()) break;
        getline(archivo, id, ',');
        getline(archivo, fecha,',');
        franjaHoraria = obtenerFranjaHoraria(fecha);
        anio = obtenerAnio(fecha);
        mes = obtenerMes(fecha);
        semana = obtenerSemana(fecha);
        getline(archivo, diaSemana, ',' );
        getline(archivo, distrito, ',');
        getline(archivo, descarte, '\n');

        clasificarDelito(matrizProbabilidades, vectorResultados, vectorProbabilidades, franjaHoraria, diaSemana, distrito, filas, indices, anio,mes, semana);

        archivoSalida << id << ',';
        for(int i = 0; i < filas-1; i++) {
            archivoSalida << vectorResultados[i] << ',';
        }
        archivoSalida << vectorResultados[filas-1];
        cout << "clasifico y escribio delito " << contador << endl;
        contador ++;
        if (!(archivo.eof())){
            archivoSalida << endl;
        }
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
