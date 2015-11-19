#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>

const int MASPROBABLES = 6;
const int CANTIDAD_DELITOS = 1000;
const int FEATURES = 4;
const int K = 30;
const int CANTIDAD_TEST = 884261;

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

string obtenerAnio(string fechaHora)
{
    string anioStr;
    anioStr = fechaHora.substr(0,4);
    return anioStr;
}

string obtenerFranjaHoraria(string fecha)
{
    string horaStr;
    string franja;
    horaStr = fecha.substr(11, 2);
    int hora = atoi(horaStr.c_str());
    if (hora < 3)
    {
        franja = "MadrugadaI";
    }

    if ((hora >= 3) && (hora < 6))
    {
        franja = "MadrugadaII";
    }

    if ((hora >= 6) && (hora < 9))
    {
        franja = "ManianaI";
    }

    if ((hora >= 9) && (hora < 12))
    {
        franja = "ManianaII";
    }

    if ((hora >= 12) && (hora < 15))
    {
        franja = "MedioDia";
    }

    if ((hora >= 15) && (hora < 18))
    {
        franja = "TardeI";
    }

    if ((hora >= 18) && (hora < 21))
    {
        franja = "TardeII";
    }

    if ((hora >= 21) && (hora < 24))
    {
        franja = "NocheI";
    }


    return franja;
}

void crearArchivosPorDelito(){
    ifstream archivo;
    ofstream archivoSalida;
    ifstream archivoVerificar;
    string fechaHora, hora, franjaHoraria, fecha, anio, categoria, diaSemana, coordenadaX, coordenadaY, descarte, ruta, strLinea;
    archivo.open("../archivos/trainCorregido.csv");
    if(archivo.fail())
    {
        cout << "Error al abrir el archivo trainCorregido.csv" << endl;
    }
    getline(archivo, descarte, '\n');
    while(true){
        if (archivo.eof()) break;
        getline(archivo, fechaHora,',');
        franjaHoraria = obtenerFranjaHoraria(fechaHora);
        hora = obtenerHora(fechaHora);
        fecha = obtenerFecha(fechaHora);
        anio = obtenerAnio(fechaHora);
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
        ruta = "../archivos/delitos/" + categoria + "-" + franjaHoraria + "-" + anio + ".csv";
        strLinea = hora + "," + fecha + "," + diaSemana + "," + coordenadaX + "," + coordenadaY;
        archivoSalida.open(ruta.c_str(), std::ios::app);
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

void limpiarArchivoDeResultados() {
    ofstream archivoDeDistancias;
    string nombreDelArchivoDeDistancias = "../archivos/archivoDistancias.csv";
    archivoDeDistancias.open(nombreDelArchivoDeDistancias.c_str());
    archivoDeDistancias.clear();
}

void convertirFechaEnVector(string fecha, float *vectorFecha){
    string anioStr, mesStr, diaStr;
    double doubleAnio, doubleMes, doubleDia;
    float anio, mes, dia;
    anioStr = fecha.substr(0, 4);
    doubleAnio = atof(anioStr.c_str());
    anio = (float) doubleAnio;
    anio = anio *365;
    mesStr = fecha.substr(5, 2);
    doubleMes = atof(mesStr.c_str());
    mes = (float) doubleMes;
    mes = mes *30;
    diaStr = fecha.substr(8, 2);
    doubleDia = atof(diaStr.c_str());
    dia = (float) doubleDia;
    vectorFecha[0] = anio;
    vectorFecha[1] = mes;
    vectorFecha[2] = dia;
}

float calcularDistanciaFecha(string fecha1, string fecha2){
    float distancia = 0;
    float *vectorFecha1 = new float[3];
    float *vectorFecha2 = new float[3];
    for (int i = 0; i < 3; i++){
        vectorFecha1[i] = 0;
        vectorFecha2[i] = 0;
    }
    convertirFechaEnVector(fecha1, vectorFecha1 );
    convertirFechaEnVector(fecha2, vectorFecha2);
    for (int i = 0; i < 3; i++) {
        if (vectorFecha1[i] >= vectorFecha2[i])
            distancia += vectorFecha1[i] - vectorFecha2[i];
        else
            distancia += vectorFecha2[i] - vectorFecha1[i];
    }

    delete [] vectorFecha1;
    delete [] vectorFecha2;
    return distancia;
}

float devolverNumeroSemana(string dia){
    string vectorDias[] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

    int i = 0;
    for (i = 0; i < 7; i++) {
        if(dia == vectorDias[i]){
            return i+1;
        }
    }
    return 0;
}

float calcularDistanciaDiaSemana(string fecha1, string fecha2){

    float dia1 = (float)devolverNumeroSemana(fecha1);
    float dia2 = (float)devolverNumeroSemana(fecha2);
    float distancia = abs(dia1-dia2);

    if (distancia == 4){
        return distancia = 3;
    }

    if (distancia == 5){
        return distancia = 2;
    }

    if (distancia == 6){
        return distancia = 1;
    }

    return 0;
}

float calcularDistanciaCoordenadas(string coordenada1str, string coordenada2str) {
    float coordenada1 = 0;
    float coordenada2 = 0;

    coordenada1 = abs((float)atof(coordenada1str.c_str()));
    coordenada2 = abs((float)atof(coordenada2str.c_str()));
    return abs(coordenada1 - coordenada2);

}

void calcularDistancias(string vectorAClasificar[], string vectorDelDelito[], string tipoDeDelito) {
    ofstream archivoDeDistancias;
    string nombreDelArchivoDeDistancias = "../archivos/archivoDistancias.csv";
    archivoDeDistancias.open(nombreDelArchivoDeDistancias.c_str(), std::ios::app);
    //float distancia1 = 0;
    //float distancia2 = 0;
    float distancia3 = 0;
    float distancia4 = 0;
    float distanciaTotal = 0;

    archivoDeDistancias << tipoDeDelito << ",";
    //distancia1 = calcularDistanciaFecha(vectorAClasificar[0], vectorDelDelito[0]);
    //distancia2 = calcularDistanciaDiaSemana(vectorAClasificar[1], vectorDelDelito[1]);
    distancia3 = calcularDistanciaCoordenadas(vectorAClasificar[2], vectorDelDelito[2]);
    distancia4 = calcularDistanciaCoordenadas(vectorAClasificar[3], vectorDelDelito[3]);

    //distanciaTotal = sqrt((distancia1*distancia1) + (distancia2*distancia2) +(distancia3*distancia3) + (distancia4*distancia4));
    distanciaTotal = sqrt((distancia3*distancia3) + (distancia4*distancia4));
    archivoDeDistancias << distanciaTotal << endl;

    archivoDeDistancias.close();

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
    //Elimine este vector que no lo habiamos borrado
    delete []menor;
}

void prepararArchivoResultados(){
    ofstream resultadosKNN;
    string nombreDelArchivoResultados = "../archivos/resultadosKNN.csv";

    resultadosKNN.open(nombreDelArchivoResultados.c_str());
    resultadosKNN << "Id,ARSON,ASSAULT,BAD CHECKS,BRIBERY,BURGLARY,DISORDERLY CONDUCT,DRIVING UNDER THE INFLUENCE,DRUG/NARCOTIC,DRUNKENNESS,EMBEZZLEMENT,EXTORTION,FAMILY OFFENSES,FORGERY/COUNTERFEITING,FRAUD,GAMBLING,KIDNAPPING,LARCENY/THEFT,LIQUOR LAWS,LOITERING,MISSING PERSON,NON-CRIMINAL,OTHER OFFENSES,PORNOGRAPHY/OBSCENE MAT,PROSTITUTION,RECOVERED VEHICLE,ROBBERY,RUNAWAY,SECONDARY CODES,SEX OFFENSES FORCIBLE,SEX OFFENSES NON FORCIBLE,STOLEN PROPERTY,SUICIDE,SUSPICIOUS OCC,TREA,TRESPASS,VANDALISM,VEHICLE THEFT,WARRANTS,WEAPON LAWS" << endl;
    resultadosKNN.close();
}

void obtenerDistanciaMayor(float **matrizDistancia, float *mayor) {
    float mayorDistancia = 999; //tomo una distancia grande
    for (int j = 0; j < 30; j++) {
        float actual = matrizDistancia[1][j];
        if (actual > mayorDistancia) {
            mayorDistancia = actual;
            mayor[0] = j; //posicion
            mayor[1] = mayorDistancia;
        }
    }
}

void obtenerKDelitosMasCercanos(float distancia, float delito, int contador, float **matrizDelitos) {
    float *mayor = new float [2];
    mayor[0] = 0;
    mayor[1] = 0;
    if (contador < 30) {
        matrizDelitos[0][contador] = delito;
        matrizDelitos[1][contador] = distancia;
    } else {
        obtenerDistanciaMayor(matrizDelitos, mayor);
        int posicionMayor = (int) mayor[0]; //OJO!!! Acordarse que devuelve la posicion en la matriz, no el ID
        float distanciaMayor = mayor[1];
        if (distancia < distanciaMayor){
            matrizDelitos[0][posicionMayor] = delito;
            matrizDelitos[1][posicionMayor] = distancia;
        }
    }
    //Elimine este vector que no lo habiamos borrado.
    delete []mayor;
}

map<float,float> obtenerElDelitoMasOcurrente(float **matrizDelitosMasCercanos, float ** matrizProbabilidades){
    map<float, float> indices;
    float idDelitoAInsertar = 0;

    idDelitoAInsertar = matrizDelitosMasCercanos[0][0];
    indices.insert(pair<float, float> (idDelitoAInsertar, 1));
    for(int i = 1; i < K; i++){
        idDelitoAInsertar = matrizDelitosMasCercanos[0][i];
        map<float, float>::iterator iteradorIndice = indices.find(idDelitoAInsertar);
        if(iteradorIndice != indices.end()){
            iteradorIndice -> second++;
            cout << iteradorIndice ->second << endl;
        }
        else{
            indices.insert(pair<float, float> (idDelitoAInsertar, 1));
        }
    }

    map<float, float>::iterator iteradorDelitos = indices.begin();
    while(iteradorDelitos != indices.end()) {
        iteradorDelitos -> second = (iteradorDelitos -> second) / K;
        iteradorDelitos ++;
        cout << iteradorDelitos ->second << endl;
    }
    return indices;
}

void inicializarVector(float *vectorAInicializar){
    for (int i = 0; i < 39; i++){
        vectorAInicializar[i] = 0;
    }

}
void aplicarKNN(int longitud, map<int, string> &indices, float **matrizProbabilidades, string id){
    int indiceDelito = 0;
    ifstream archivoDistancias;
    ofstream resultadosKNN;
    map<string,float> diccionarioDistancias;
    map<float,float> diccionarioProbabilidades;
    string delito;
    string distanciaStr;
    float distancia = 0;
    double distanciaDouble = 0;
    string nombreDelArchivoDeDistancias = "../archivos/archivoDistancias.csv";
    string nombreDelArchivoResultados = "../archivos/resultadosKNN.csv";
    float **matrizDelitosMasCercanos = new float *[2];
    matrizDelitosMasCercanos[0] = new float [K];
    matrizDelitosMasCercanos[1] = new float [K];

    inicializarMatriz(2, K, matrizDelitosMasCercanos);

    resultadosKNN.open(nombreDelArchivoResultados.c_str(), std::ios::app);
    archivoDistancias.open(nombreDelArchivoDeDistancias.c_str());
    int contador = 0;
    for (int i = 0; i < longitud; i++){
        getline(archivoDistancias, delito, ',');
        getline(archivoDistancias, distanciaStr, '\n');
        map<int, string>::iterator iterador = indices.begin();
        while (true) {
            if ((iterador -> second) == delito) {
                break;
            } else {
                iterador ++;
            }
        }

        indiceDelito = (float) (iterador -> first);
        distanciaDouble = atof(distanciaStr.c_str());
        distancia = (float)distanciaDouble;

        obtenerKDelitosMasCercanos(distancia, indiceDelito, contador, matrizDelitosMasCercanos);
        contador ++;
    }

    resultadosKNN << id << ',';
    diccionarioProbabilidades = obtenerElDelitoMasOcurrente(matrizDelitosMasCercanos, matrizProbabilidades);
    map<float,float>::iterator iteradorDelitos = diccionarioProbabilidades.begin();
    float *vectorAAlmacenar = new float[39];
    inicializarVector(vectorAAlmacenar);
    int j = 0;
    while (iteradorDelitos != diccionarioProbabilidades.end()){
        j = iteradorDelitos -> first;
        vectorAAlmacenar[j] = iteradorDelitos -> second;
    }

    for (int i = 0; i < 39; i++){
        resultadosKNN << vectorAAlmacenar[i] << ',';
    }
    resultadosKNN << vectorAAlmacenar[39] << endl;

    archivoDistancias.close();
    resultadosKNN.close();

    for (int i = 0; i < 2; i++) {
        delete [] matrizDelitosMasCercanos[i];
    }
    delete [] matrizDelitosMasCercanos;
    delete [] vectorAAlmacenar;

}


void leerBayes(map<int, string> & indices, float **matrizProbabilidades, int cantidadDelitos) {
    ifstream resultadosBayes;
    ifstream test;
    ifstream archivoDelDelito;
    string descarte, strProbabilidad, idTest, fechaHora, fecha, hora, anio, franjaHoraria, diaSemana, coordenadaX, coordenadaY, delito;
    string fechaHoraTest, fechaTest, horaTest, diaSemanaTest,coordenadaXTest, coordenadaYTest;
    string strID, ruta;
    string *vectorAClasificar = new string [FEATURES];
    string *vectorDelito = new string [FEATURES];
    int id = 0, contador, i, longitud = 0;
    int numeroDelito = 0;
    double doubleProbabilidad = 0;
    float probabilidad = 0;
    test.open("../archivos/test.csv");
    resultadosBayes.open("../archivos/resultadosBayes.csv");

    int contadorCouts = 0;

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
        getline(test, fechaHoraTest,',');
        franjaHoraria = obtenerFranjaHoraria(fechaHoraTest);
        hora = obtenerHora(fechaHoraTest);
        fechaTest = obtenerFecha(fechaHoraTest);
        anio = obtenerAnio(fechaHoraTest);
        getline(test, diaSemanaTest, ',');
        getline(test, descarte, ',');
        getline(test, descarte, ',');
        getline(test, coordenadaXTest, ',');
        getline(test, coordenadaYTest, '\n');
        vectorAClasificar[0] = fechaTest;
        vectorAClasificar[1] = diaSemanaTest;
        vectorAClasificar[2] = coordenadaXTest;
        vectorAClasificar[3] = coordenadaYTest;
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
            limpiarArchivoDeResultados();
            longitud = 0;
            if(contadorCouts == 1000){
                cout << idTest << endl;
                contadorCouts = 0;
            }
            for (int j = 1; j < MASPROBABLES; j ++) {
                numeroDelito = (int) matrizProbabilidades[0][j];
                delito = indices.at(numeroDelito);
                ruta = "../archivos/delitos/" + delito + "-" + franjaHoraria + "-" + anio + ".csv";
                archivoDelDelito.open(ruta.c_str());
                while (true) {
                    i = 0;
                    if (archivoDelDelito.eof()) break;
                    getline(archivoDelDelito, hora, ',' );
                    getline(archivoDelDelito, fecha, ',' );
                    vectorDelito[i] = fecha;
                    i++;
                    getline(archivoDelDelito, diaSemana, ',' );
                    vectorDelito[i] = diaSemana;
                    i++;
                    getline(archivoDelDelito, coordenadaX, ',' );
                    vectorDelito[i] = coordenadaX;
                    i++;
                    getline(archivoDelDelito, coordenadaY, '\n' );
                    vectorDelito[i] = coordenadaY;
                    if (fechaTest.substr(0,9) == fecha.substr(0,9)){
                        calcularDistancias(vectorAClasificar, vectorDelito, delito);
                        longitud ++;

                    }

                }
                archivoDelDelito.close();
            }
            aplicarKNN(longitud, indices, matrizProbabilidades, idTest);
            contadorCouts ++;
        }
    }
    resultadosBayes.close();
    //Elimine estos vectores que faltaban
    delete []vectorAClasificar;
    delete []vectorDelito;
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

    prepararArchivoResultados();
    inicializarMatriz(filas, MASPROBABLES, matrizProbabilidades);
    leerBayes(indices, matrizProbabilidades, cantidadDelitosTotales);


    for (int i = 0; i < filas; i++) {
        delete [] matrizProbabilidades[i];
    }
    delete [] matrizProbabilidades;

    return 0;
}
