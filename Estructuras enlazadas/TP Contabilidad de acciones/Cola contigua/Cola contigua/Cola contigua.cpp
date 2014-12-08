/*IMPLEMENTACION CONTIGUA DE COLAS EN LA CONTABILIDAD DE ACCIONES
Córdoba María
K1051
Diciembre 2014*/

#include "stdafx.h"
#include <iostream>
#include <array>
#include <string>
#include <ciso646>
using namespace std;


// Declaraciones de tipos de datos:

struct Accion {    //Cada conjunto de acciones se va a considerar como una 2-upla de enteros
	int cantidad;
	int precio;
};

struct Queue {
	array <Accion, 10> secuencia;
	unsigned front = 0;
	unsigned rear = 0;
};


//Prototipos funciones:
void Enqueue(Queue& queue, Accion accion);
Accion Dequeue(Queue& queue);
bool IsEmpty(const Queue&);
bool IsFull(const Queue&queue);

void Mostrarpreciomes(int preciopormes, string mes);
void ComprarAcciones(Accion &accion, int preciomes, Queue &queue);
void VenderAcciones(Queue &queue, int preciopormes, int ganancia, int perdida, int &gananciatotal, int &perdidatotal);
void CalcularGananciaOPerdida(int preciopormes, int precioaccion, int cantidadaccion, int ganancia, int perdida, int &gananciatotal, int &perdidatotal);
void MostrarResultados(int gt, int pt);

//Cuerpo del main:
int main() {

	//Declaraciones de variables:
	Queue queue; //Variable "queue" de tipo Queue

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
	cout << "        IMPLEMENTACION CONTIGUA DE COLAS - CONTABILIDAD DE ACCIONES \n";
	cout << "==========================================================================\n\n";

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
	preciopormes = 30; Mostrarpreciomes(preciopormes, "noviembre");
	VenderAcciones(queue, preciopormes, ganancia, perdida, gananciatotal, perdidatotal); //Se venden 100 acciones

	MostrarResultados(gananciatotal, perdidatotal);

}//Cierre del main


//Definiciones funciones y procedimientos

//Funciones específicas del ejercicio:

void Mostrarpreciomes(int preciopormes, string mes){
	cout << "El precio de las acciones de " << mes << " es de $ " << preciopormes << ".\n";
}

void ComprarAcciones(Accion &accion, int preciomes, Queue &queue){
	accion.precio = preciomes;
	accion.cantidad = 100;  //La cantidad de acciones que se compran y venden es constante, no es necesario un ingreso por pantalla.
	Enqueue(queue, accion);
	cout << "Se compraron " << accion.cantidad << " acciones. \n\n";
}

void VenderAcciones(Queue &queue, int preciopormes, int ganancia, int perdida, int &gananciatotal, int &perdidatotal){
	Accion accionaux;
	accionaux = Dequeue(queue); //guardamos el dequeue de la queue en una variable local para no perderlo
	cout << "Se vendieron " << accionaux.cantidad << " acciones que costaban $ " << accionaux.precio << " a $ " << preciopormes << ". \n";
	CalcularGananciaOPerdida(preciopormes, accionaux.precio, accionaux.cantidad, ganancia, perdida, gananciatotal, perdidatotal);
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
		else cout << "No hubo ganancia ni perdida en esta transaccion.\n";
	}
	gananciatotal += ganancia;
	perdidatotal += perdida;
	cout << "Ganancia total hasta ahora: $" << gananciatotal << ". \n";
	cout << "Perdida total hasta ahora: $" << perdidatotal << ". \n\n";
}

void MostrarResultados(int gt, int pt){
	cout << "Utilizando contabilidad FIFO, los resultados fueron: \nGanancia total: $" << gt << "\nPerdida total: $" << pt;
}


//Funciones de la implementación contigua de queues:

void Enqueue(Queue& queue, Accion accion){
	if (!IsFull(queue)){
		queue.secuencia.at(queue.rear) = accion;
		++queue.rear;
	}
}

Accion Dequeue(Queue& queue){
	if (!IsEmpty(queue))
		return queue.secuencia.at(queue.front++); //necesitamos retornar lo que hay en la posicion front y luego incrementarlo
}                                      //tiene que ser un post incremento pero no lo podemos poner despues de "return"

bool IsEmpty(const Queue& queue){
	if (queue.front == queue.rear)
		return true;
	else
		return false;
}

bool IsFull(const Queue&queue){
	return queue.secuencia.size() == queue.rear;
}


