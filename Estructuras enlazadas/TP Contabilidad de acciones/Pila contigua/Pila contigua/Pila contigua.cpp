
/*IMPLEMENTACION CONTIGUA DE PILAS EN LA CONTABILIDAD DE ACCIONES
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

struct Stack {
	array <Accion, 10> secuencia;
	unsigned tope = 0;
};



//Prototipos funciones:
void Push(Stack& stack, Accion accion);
Accion Pop(Stack& stack);
bool IsEmpty(const Stack& stack);
bool IsFull(const Stack& stack);

void Mostrarpreciomes(int preciopormes, string mes);
void ComprarAcciones(Accion &accion, int preciomes, Stack &stack);
void VenderAcciones(Stack stack, int preciopormes, int ganancia, int perdida, int &gananciatotal, int &perdidatotal);
void CalcularGananciaOPerdida(int preciopormes, int precioaccion, int cantidadaccion, int ganancia, int perdida, int &gananciatotal, int &perdidatotal);
void MostrarResultados(int gt, int pt);

int main(){

	//Declaraciones de variables
	Stack stack;

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
	cout << "        IMPLEMENTACION CONTIGUA DE PILAS - CONTABILIDAD DE ACCIONES \n";
	cout << "==========================================================================\n\n";

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

void Mostrarpreciomes(int preciopormes, string mes){
	cout << "El precio de las acciones de " << mes << " es de $ " << preciopormes << ".\n";
}

void ComprarAcciones(Accion &accion, int preciomes, Stack &stack){
	accion.precio = preciomes;
	accion.cantidad = 100;  //La cantidad de acciones que se compran y venden es constante, no es necesario un ingreso por pantalla.
	Push(stack, accion);
	cout << "Se compraron " << accion.cantidad << " acciones. \n\n";
}

void VenderAcciones(Stack stack, int preciopormes, int ganancia, int perdida, int &gananciatotal, int &perdidatotal){
	Accion accionaux;
	accionaux = Pop(stack); //guardamos el pop de la stack en una variable local para no perderlo
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
		else cout << "No hubo ganancia ni perdida en esta transaccion. \n";
	}
	gananciatotal += ganancia;
	perdidatotal += perdida;
	cout << "Ganancia total hasta ahora: $" << gananciatotal << ". \n";
	cout << "Perdida total hasta ahora: $" << perdidatotal << ". \n\n";
}

void MostrarResultados(int gt, int pt){
	cout << "Utilizando contabilidad LIFO, los resultados fueron: \nGanancia total: $" << gt << "\nPerdida total: $" << pt;
}


//Funciones de la implementación contigua de stacks:
void Push(Stack& stack, Accion accion){
	if (!(IsFull(stack))){
		stack.secuencia.at(stack.tope) = accion;
		++stack.tope;
	}
}

Accion Pop(Stack& stack){
	if (!(IsEmpty(stack))){
		--stack.tope;
		return stack.secuencia.at(stack.tope);
	}
}

bool IsEmpty(const Stack& stack){
	return (stack.tope == 0);
}

bool IsFull(const Stack& stack){
	return (stack.secuencia.size()) == stack.tope;
}





