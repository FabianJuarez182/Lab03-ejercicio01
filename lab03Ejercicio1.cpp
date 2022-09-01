/*
*------------------------------------------
* Laboratorio 3.cpp
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
* CC3086 - Programacion de Microprocesadores
* Fabian Juárez 21440
*------------------------------------------
* Descripción: Desarrollar un programa que permita calcular
* los números primos entre 0 y un valor máximo, el cual debe ser
* ingresado por el usuario, también deberá ingresar la cantidad de hilos
* a utilizar. Se calculará e imprimirá el valor de la suma total
* de los primos encontrados.
*------------------------------------------
*/ 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sstream>  // for string streams
#include <string>  // for string
using namespace std;
//Creacion de variables que se utilizaran de manera global
void *process(void *ptr);
int total = 0;
int valMax = 0;
int numThread = 0;
int n = 0;
int subtotal = 0;
int diferencia = 0;
//Se creara el estructure para cada persona que posee un DPI
struct hilo{
  int limitInf , limitMax , subtotal;
  pthread_t Threadn;
};
//Funcion para determinar si el numero es primo o no
bool esPrimo(int numero) {
    // Casos especiales
    if (numero == 0 || numero == 1 || numero == 4) return false;
    for (int x = 2; x < numero / 2; x++) {
        if (numero % x == 0) return false;
    }
    // Si no se pudo dividir por ninguno de los de arriba, sí es primo
    return true;
}
// Funcion para el thread el cual se encarga de encontrar los numeros primos 
// al final sumarlos y tener un subtotal y sumarlo al total completo
void *process(void *ptr){
    hilo *soloHilo;
    soloHilo = (hilo *) ptr;
    printf("lim inf: %d\nlim sup: %d\n", soloHilo->limitInf, soloHilo->limitMax);
    for(int i = soloHilo->limitInf; i <= soloHilo->limitMax; i++){
        // Casos especiales
        if (esPrimo(i)){
            printf("%d\n",i);
            subtotal = subtotal + i;
        }
    }
    printf("Suma hilo: %d\n",subtotal);
    total = total + subtotal;
    subtotal = 0;
    printf("------------------------------------------\n");
    pthread_exit(NULL);
}

int main()
{
    printf("------------------------------------------\n");
    cout << "Ingrese el valor maximo: "; //Se pide el valor maximo a ingresar
    cin >> valMax; // variable en la que se guardara el valor
  
    cout << "Ingrese el numero de threads para realizar el calculo : "; //Se pide el num de threads a ingresar
    cin >> numThread; // variable en la que se guardara el valor
    hilo hilon[numThread];
    n = valMax/numThread;
    int r = valMax%numThread;
    printf("Cantidad de valores a evaluar por thread: %d y residuo: %d\n", n,r);
    printf("Buscando primos entre 0 y %d . . .\n", valMax);
    printf("------------------------------------------\n");
    for (int i = 0; i < numThread; i++){
        if (i == 0){
            hilon[i].limitInf = 0;
            hilon[i].limitMax = n - 1;
        }
        if(i!=0 && i+1!=numThread){
            hilon[i].limitInf = n * i;
            hilon[i].limitMax = n * (i+1);
        }
        if (i+1==numThread){
            diferencia = valMax - (n * (i+1));
            hilon[i].limitInf = (n * i);
            hilon[i].limitMax = (n * (i+1)) + diferencia;
        }
    }
    for(int k = 0; k < numThread; k++){
        cout<<"Thread:" ;
        printf("%d\n", k);
        // Se crean los hilos de manera independiente el cual ejecutara la misma funcion
        pthread_create( &hilon[k].Threadn, NULL, process, (void*) &hilon[k]);
        // Esperar a que cada thread termine en orden
        pthread_join(hilon[k].Threadn, NULL);
    }
    printf("Suma Total: %d\n",total);
    pthread_exit(NULL);
    exit(0);
}