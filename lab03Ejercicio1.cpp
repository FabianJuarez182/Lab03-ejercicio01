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
using namespace std;
//Creacion de variables que se utilizaran de manera global
void *subtotal1(void *ptr);
void *subtotal2(void *ptr);
int total = 0;
int valMax = 0;
int numThread = 0;
int n = 0;
//Se creara el estructure para cada persona que posee un DPI
struct hilo{
  int limitInf , limitMax , subtotal;
  string nameThread;
};

int main()
{
    printf("------------------------------------------\n");
    cout << "Ingrese el valor máximo: "; //Se pide el valor maximo a ingresar
    cin >> valMax; // variable en la que se guardara el valor
  
    cout << "Ingrese el numero de threads para realizar el calculo : "; //Se pide el num de threads a ingresar
    cin >> numThread; // variable en la que se guardara el valor
    
    n = valMax/numThread;
    int r = valMax%numThread;
    printf("Cantidad de valores a evaluar por thread: %d y residuo: %d\n", n,r);
    printf("Buscando primos entre 0 y %d . . .\n", valMax);
    printf("------------------------------------------\n\n");
    for (int i = 0; i < numThread; i++){
        struct hilo hilon;
        hilon.nameThread = "THREAD " + i;
        pthread_t Threadn;
        if (i == 0){
            hilon.limitInf = 0;
            hilon.limitMax = n - 1;
        }
        if(i!=0 & i+1!=numThread){
            hilon.limitInf = n * i;
            hilon.limitMax = n * (i+1);
        }
        if (i+1==numThread){
            int diferencia = valMax - (n * (i+1));
            hilon.limitInf = n * i;
            hilon.limitMax = (n * (i+1)) + diferencia;
        }
        printf("lim inf: %d\n lim sup: %d\n",hilon.limitInf, hilon.limitMax);
    }
}