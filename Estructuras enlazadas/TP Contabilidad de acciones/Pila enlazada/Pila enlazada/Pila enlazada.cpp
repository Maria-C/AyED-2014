/*IMPLEMENTACION ENLAZADA DE PILAS EN LA CONTABILIDAD DE ACCIONES
Córdoba María
K1051
Diciembre 2014*/

#include "stdafx.h"
#include <iostream>
#include <array>
#include <string>
#include <ciso646>
using namespace std;

//Declaraciones de tipos de datos:

struct Accion {    //Cada conjunto de acciones se va a considerar como una 2-upla de enteros
	int cantidad;
	int precio;
};

struct Nodo {
	Accion data;
	Nodo *next;
};

typedef Nodo* Stack;  //La pila es un puntero a un nodo.


//Prototipos funciones:

void Push(Stack &stack, Accion accion);
Accion Pop(Stack& stack);
bool IsEmpty(const Stack &stack);
//No consideraremos una función IsFull ya que conceptualmente las estructuras enlazadas no tienen 
//límite de elementos y tampoco definiremos uno nosotros para este ejercicio.

void Mostrarpreciomes(int preciopormes, string mes);
void ComprarAcciones(Accion &accion, int preciomes, Stack &stack);
void VenderAcciones(Stack &stack, int preciopormes, int ganancia, int perdida, int &gananciatotal, int &perdidatotal);
void CalcularGananciaOPerdida(int preciopormes, int precioaccion, int cantidadaccion, int ganancia, int perdida, int &gananciatotal, int &perdidatotal);
void MostrarResultados(int gt, int pt);

//Cuerpo del main
int main() {

	//Declaración de variables:
	Stack stack = nullptr;  //Inicializamos la variable stack de tipo Stack 

	Accion accionesenero;
	Accion accionesabril;
	Accion accionesseptiembre;

	string mes;
	int preciopormes;
	int perdida = 0;
	int ganancia = 0;
	int gananciatotal=0;
	int perdidatotal=0;

	cout << "==========================================================================\n ";
	cout << "        IMPLEMENTACION ENLAZADA DE PILAS - CONTABILIDAD DE ACCIONES \n";
	cout << "==========================================================================\n\n ";

	//En enero:
	preciopormes = 10;  Mostrarpreciomes(preciopormes, "enero");
	ComprarAcciones(accionesenero, preciopormes, stack); //Se compran 100 acciones
	
	//En abril:
	preciopormes = 30; Mostrarpreciomes(preciopormes, "abril");
	ComprarAcciones(accionesabril, preciopormes, stack); //Se compran otras 100 acciones
	
	//En junio:
	preciopormes = 20; Mostrarpreciomes(preciopormes, "junio");
	VenderAcciones(stack, preciopormes, ganancia, perdida, gananciatotal, perdidatotal); //Se venden 100 acciones 

	//En septiembre:
	preciopormes = 50; Mostrarpreciomes(preciopormes, "septiembre");
	ComprarAcciones(accionesseptiembre, preciopormes, stack); //Se compran otras 100 acciones:
	
	//En noviembre:
	preciopormes = 30; Mostrarpreciomes(preciopormes, "noviembre");
	VenderAcciones(stack, preciopormes, ganancia, perdida, gananciatotal, perdidatotal); //Se venden 100 acciones

	MostrarResultados(gananciatotal, perdidatotal);

}//Cierre del main


//Definiciones funciones y procedimientos

//Funciones específicas del ejercicio:

void Mostrarpreciomes(int preciopormes, string mes) {
	cout << "El precio de las acciones de " << mes << " es de $ " << preciopormes << ".\n";
}

void ComprarAcciones(Accion &accion, int preciomes, Stack &stack) {
	Push(stack, accion);
	(*stack).data.precio = preciomes;
	(*stack).data.cantidad = 100;  //La cantidad de acciones que se compran y venden es constante, no es necesario un ingreso por pantalla.
	cout << "Se compraron " << (*stack).data.cantidad << " acciones. \n\n";
}

void VenderAcciones(Stack &stack, int preciopormes, int ganancia, int perdida, int &gananciatotal, int &perdidatotal){
	Accion accionaux = Pop(stack);   //Guardamos el pop de la pila en una variable auxiliar para no perderla y utilizarla a continuación.
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
		else cout << "No hubo ganancia ni perdida en esta transaccion.";
	}
	gananciatotal += ganancia;
	perdidatotal += perdida;
	cout << "Ganancia total hasta ahora: $" << gananciatotal << ". \n";
	cout << "Perdida total hasta ahora: $" << perdidatotal << ". \n\n";
}

void MostrarResultados(int gt, int pt){
	cout << "Utilizando contabilidad LIFO, los resultados fueron: \nGanancia total: $" << gt << "\nPerdida total: $" << pt << "\n";
}

//Funciones de la implementación enlazada de pilas:

void Push(Stack &stack, Accion accion){
	Stack punteroaux = new Nodo;	//Reservamos el espacio en memoria para crear un nuevo nodo.
	(*punteroaux).data = accion;	//Llenamos el campo "data" del nuevo nodo.
	(*punteroaux).next = stack;		//El campo "next" del nuevo nodo apuntará adonde apuntaba el primer puntero de la pila
	stack = punteroaux;				//El primer puntero de la pila ahora apunta al nuevo nodo.
}

Accion Pop(Stack &stack){			         //El pop de la pila retorna lo que se encuentra en el campo "data" del nodo.
	if (!IsEmpty(stack)){

		//Creamos variables auxiliares:
		Stack punteroaux;
		Accion accionaux;

		punteroaux = stack;				//El puntero auxiliar recibe la direccion del primer nodo de la pila.
		accionaux = (*punteroaux).data;	 //La variable auxiliar recibe el elemento del campo "data" del primer nodo de la pila
		stack = (*punteroaux).next;      //El puntero a pila ahora apunta al siguiente nodo.
		delete punteroaux;				//Liberamos el espacio en memoria del nodo.
		return accionaux;
	}
}

bool IsEmpty(const Stack &stack){
	if (stack == nullptr)
		return true;
	else
		return false;
}