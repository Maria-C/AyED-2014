/*IMPLEMENTACION ENLAZADA DE COLAS EN LA CONTABILIDAD DE ACCIONES
Córdoba María
K1051
Diciembre 2014*/

#include "stdafx.h"
#include <iostream>
#include <array>
#include <string>
#include <ciso646>
using namespace std;

//Declaraciones de variables

struct Accion {    //Cada conjunto de acciones se va a considerar como una 2-upla de enteros
	int cantidad;
	int precio;
};

struct Nodo {
	Accion data;
	Nodo *next;
};

struct Queue {
	Nodo* front = nullptr;  //La cola son dos punteros a nodo.
	Nodo* rear = nullptr;
};

//Prototipos funciones
void Enqueue(Queue &queue, Accion accion);
Accion Dequeue(Queue &queue);
bool IsEmpty(const Queue &queue);

void Mostrarpreciomes(int preciopormes, string mes);
void ComprarAcciones(Accion &accion, int preciomes, Queue &queue);
void VenderAcciones(Queue &queue, int preciopormes, int ganancia, int perdida, int &gananciatotal, int &perdidatotal);
void CalcularGananciaOPerdida(int preciopormes, int precioaccion, int cantidadaccion, int ganancia, int perdida, int &gananciatotal, int &perdidatotal);
void MostrarResultados(int gt, int pt);


//Cuerpo del main
int main() {

	//Declaraciones de variables:
	Nodo firstnode;
	Queue queue;

	Accion accionesenero;
	Accion accionesabril;
	Accion accionesseptiembre;

	string mes;
	int preciopormes;
	int perdida = 0;
	int ganancia = 0;
	int gananciatotal = 0;
	int perdidatotal = 0;

	cout << "==========================================================================\n ";
	cout << "        IMPLEMENTACION ENLAZADA DE COLAS - CONTABILIDAD DE ACCIONES \n";
	cout << "==========================================================================\n\n" << " " << endl;
	
	//En enero:
	preciopormes = 10;  Mostrarpreciomes(preciopormes, "enero");
	ComprarAcciones(accionesenero, preciopormes, queue); //Se compran 100 acciones
	
	//En abril:
	preciopormes = 30; Mostrarpreciomes(preciopormes, "abril");
	ComprarAcciones(accionesabril, preciopormes, queue); //Se compran otras 100 acciones
	
	//En junio:
	preciopormes = 20; Mostrarpreciomes(preciopormes, "junio");
	VenderAcciones(queue, preciopormes, ganancia, perdida, gananciatotal, perdidatotal); //Se venden 100 acciones 
	
	//En septiembre:
	preciopormes = 50; Mostrarpreciomes(preciopormes, "septiembre");
	ComprarAcciones(accionesseptiembre, preciopormes, queue); //Se compran otras 100 acciones:
	
	//En noviembre:
	preciopormes = 30; Mostrarpreciomes(preciopormes,"noviembre");
	VenderAcciones(queue, preciopormes, ganancia, perdida, gananciatotal, perdidatotal); //Se venden 100 acciones
	
	MostrarResultados(gananciatotal, perdidatotal);

}//Cierre del main


//Definiciones funciones y procedimientos

//Funciones específicas del ejercicio:

void Mostrarpreciomes(int preciopormes, string mes) {
	cout << "El precio de las acciones de " << mes << " es de $ " << preciopormes << ".\n";
}

void ComprarAcciones(Accion &accion, int preciomes, Queue &queue){
	Enqueue(queue, accion);
	(*(queue.rear)).data.cantidad = 100;  //La cantidad de acciones que se compran y venden es constante, no es necesario un ingreso por pantalla.
	(*(queue.rear)).data.precio = preciomes;
	cout << "Se compraron " << (*(queue.rear)).data.cantidad << " acciones. \n\n";
}

void VenderAcciones(Queue &queue, int preciomes, int ganancia, int perdida, int &gananciatotal, int &perdidatotal){
	Accion accionaux = Dequeue(queue); //Guardamos el dequeue de la cola en una variable auxiliar para no perderla y utilizarla a continuación.
	cout << "Se vendieron " << accionaux.cantidad << " acciones que costaban $ " << accionaux.precio << " a $ " << preciomes << ". \n";
	CalcularGananciaOPerdida(preciomes, accionaux.precio, accionaux.cantidad, ganancia, perdida, gananciatotal, perdidatotal);
}

void CalcularGananciaOPerdida(int preciopormes, int precioaccion, int cantidadaccion, int ganancia, int perdida, int &gananciatotal, int &perdidatotal){
	if (preciopormes > precioaccion){  //Si el precio actual al que vendemos las acciones es mayor al precio que las compramos
		ganancia = (cantidadaccion * (preciopormes - precioaccion));
		cout << "En esta transaccion hubo ganancia de $" << ganancia << ". \n";
	}
	else {
		if (precioaccion > preciopormes){ //Si el precio al que compramos las acciones es mayor al precio actual al que vendemos
			perdida = (cantidadaccion * (precioaccion - preciopormes));
			cout << "En esta transaccion hubo perdida de $ " << perdida << ". \n";
		}
		else cout << "No hubo ganancia ni perdida en esta transaccion. \n";
	}
	gananciatotal += ganancia;
	perdidatotal += perdida;
	cout << "Ganancia total hasta ahora: $" << gananciatotal << ". \n";
	cout << "Perdida total hasta ahora: $" << perdidatotal << ". \n\n";
}

void MostrarResultados(int gt, int pt){
	cout << "Utilizando contabilidad FIFO, los resultados fueron: \nGanancia total: $" << gt << "\nPerdida total: $" << pt << "\n";
}

//Funciones de la implementación enlazada de colas:

void Enqueue(Queue &queue, Accion accion){
	Nodo *nuevonodo = new Nodo;     //reservo el espacio en memoria para crear un nuevo nodo
	(*nuevonodo).data = accion;     //Llenamos el campo data del nuevo nodo
	(*nuevonodo).next = nullptr;   //El puntero del nuevo nodo no apunta a nada

	if (IsEmpty(queue)) {      //Para encolar por primera vez
		queue.front = nuevonodo; //El nodo ya esta creado
		queue.rear = nuevonodo;
	}
	else {
		(*(queue.rear)).next = nuevonodo;   //El puntero del ultimo nodo de la cola ahora apunta al nuevo nodo
		queue.rear = nuevonodo;             //El rear de la cola ahora apunta al nuevo nodo
	}
}

Accion Dequeue(Queue &queue){
	if (!IsEmpty(queue)){

		//Creamos variables auxiliares:
		Accion accionaux;
		Nodo* punteroaux;
		
		accionaux = (*(queue.front)).data; 	//La variable auxiliar recibe el primer elemento de la cola, que está apuntado con el puntero "front".
		punteroaux = queue.front;           //El puntero auxiliar recibe la direccion del nodo "front" de la cola.
		queue.front = (*punteroaux).next;   //El puntero "front" de la cola ahora apunta al siguiente nodo.
		delete punteroaux;					//Liberamos el espacio en memoria del nodo.
		return accionaux;
	}
}

bool IsEmpty(const Queue &queue){
	if ((queue.front == nullptr) or(queue.rear == nullptr))
		return true;
	else
		return false;
}

