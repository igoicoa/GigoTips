#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cmath>
#include <set>
#include <vector>
#include <sstream>

const int CANTIDAD_TEST = 884261;
using namespace std;

void prepararArchivoResultados(){
    ofstream resultadosMerge;
    string nombreDelArchivoResultados = "../archivos/resultadosMerge.csv";

    resultadosMerge.open(nombreDelArchivoResultados.c_str());
    resultadosMerge << "Id,ARSON,ASSAULT,BAD CHECKS,BRIBERY,BURGLARY,DISORDERLY CONDUCT,DRIVING UNDER THE INFLUENCE,DRUG/NARCOTIC,DRUNKENNESS,EMBEZZLEMENT,EXTORTION,FAMILY OFFENSES,FORGERY/COUNTERFEITING,FRAUD,GAMBLING,KIDNAPPING,LARCENY/THEFT,LIQUOR LAWS,LOITERING,MISSING PERSON,NON-CRIMINAL,OTHER OFFENSES,PORNOGRAPHY/OBSCENE MAT,PROSTITUTION,RECOVERED VEHICLE,ROBBERY,RUNAWAY,SECONDARY CODES,SEX OFFENSES FORCIBLE,SEX OFFENSES NON FORCIBLE,STOLEN PROPERTY,SUICIDE,SUSPICIOUS OCC,TREA,TRESPASS,VANDALISM,VEHICLE THEFT,WARRANTS,WEAPON LAWS" << endl;
    resultadosMerge.close();
}

void inicializarVector(float *vectorAInicializar){
    for(int i = 0; i < 40; i++){
        vectorAInicializar[i] = 0;
    }

}

float* convertirLineaEnVector(string delito){
    float *probabilidades = new float[40];
    inicializarVector(probabilidades);
    double delitoDouble = 0;
    float delitoFloat = 0;

    for (int i = 0 ; i < 39 ; i++){
        int posicion = delito.find(',');
        delitoDouble = (atof)(delito.substr(0,posicion+1).c_str());
        delitoFloat = (float)delitoDouble;
        probabilidades[i] = delitoFloat;
        delito = delito.substr(posicion+1,delito.length());
    }
    delitoDouble = (atof)(delito.c_str());
    delitoFloat = (float)delitoDouble;
    probabilidades[39] = delitoFloat;

    return probabilidades;
}

void escribirArchivoMerge(float * resultados){
    ofstream resultadosMerge;
    resultadosMerge.open("../archivos/resultadosMerge.csv", std::ios::app);
    int id = 0;

    for (int i = 0; i < 39; i++) {
        resultadosMerge << resultados[i] << ',';
    }
    id = (int)resultados[0];
    if (id == CANTIDAD_TEST){
        resultadosMerge << resultados[39];
    }
    else {
        resultadosMerge << resultados[39] << endl;
    }
    resultadosMerge.close();

}

void compararProbabilidades(float* probabilidadesBayes, float* probabilidadesKNN){
    float *resultados = new float[40];
    float contador = 0;
    float numerador = 0;
    inicializarVector(resultados);
    resultados[0] = probabilidadesBayes[0];
    for (int i = 1; i < 40; i++){
        if ((probabilidadesKNN[i] != 0) && (probabilidadesKNN[i] != 1)){
            for (int j = 0; j < 40; j++){
                if ((i != j) && (probabilidadesKNN[j] != 0)){
                    numerador = numerador + ((probabilidadesKNN[i]/probabilidadesKNN[j])*probabilidadesBayes[j]);
                    contador ++;
                }
            }
            resultados[i] = numerador / contador ;
            numerador = 0;
            contador = 0;
        } else {
            resultados[i] = probabilidadesBayes[i];
        }
    }
    escribirArchivoMerge(resultados);
    delete []resultados;

}

void mergeKNNBayes(){
    ifstream resultadosBayes;
    ifstream resultadosKNN;
    string delitoKNN, delitoBayes, descarte;
    float *probabilidadesBayes = new float[40];
    float *probabilidadesKNN = new float[40];

    resultadosBayes.open("../archivos/resultadosBayes.csv");
    if(resultadosBayes.fail())
    {
        cout << "Error al abrir el archivo resultadosBayes.csv" << endl;
    }
    resultadosKNN.open("../archivos/resultadosKNN.csv");
    if(resultadosKNN.fail())
    {
        cout << "Error al abrir el archivo resultadosKNN.csv" << endl;
    }

    getline(resultadosBayes, descarte, '\n');
    getline(resultadosKNN, descarte, '\n');
    while (true) {
        if (resultadosBayes.eof() || resultadosKNN.eof()) break;
        getline(resultadosBayes, delitoBayes, '\n');
        getline(resultadosKNN, delitoKNN, '\n');
        probabilidadesBayes = convertirLineaEnVector(delitoBayes);
        probabilidadesKNN = convertirLineaEnVector(delitoKNN);
        compararProbabilidades(probabilidadesBayes, probabilidadesKNN);

    }
    resultadosBayes.close();
    resultadosKNN.close();
}

int main()
{
   prepararArchivoResultados();
   mergeKNNBayes();
}
