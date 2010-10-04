/*
 * Instituto Tecnologico de Costa Rica
 * Sede Cartago
 *
 * Ingenieria en Computacion
 * Lenguajes de Programacion
 *
 * Orientacion a Objetos: el LPC-RayTracer
 * Instructor: Santiago Nunez Corrales
 *
 * Objetivo del proyecto: el estudiante debe agregar nuevos tipos de objetos geometricos
 * para generar imagenes mas complejas utilizando Geometria Constructiva de Solidos
 */

#include <iostream>
#include <Raytracer.h>

using namespace std;

int main (int argc, char *argv[]) {
	if (argc != 3) {
		cout << "Uso: " << argv[0] << " <entrada> <salida en TGA>" << endl;
		return -1;
	}

	Raytracer rt(argv[1], argv[2]);

	if (! rt.init()) {
		cout << "Archivo de escena no valido." << endl;
		return -1;
	}

	if (! rt.dibujar()) {
		cout << "No fue posible crear el archivo de salida." << endl;
		return -1;
	}

	return 0;
}
