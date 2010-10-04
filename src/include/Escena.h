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

#ifndef ESCENA_H_
#define ESCENA_H_

#include <vector>
#include <Configuracion.h>
#include <Raytracer.h>

/*
 * Una escena esta compuesta de los siguientes elementos
 *
 * - Una lista de materiales que dan las texturas a los objetos
 * - Una lista de objetos (en este caso esferas) que contiene los elementos
 * de la escena
 * - Una lista de fuentes de luz que iluminan la escena generando fotones
 * - Un tamanno del frame en ancho y alto
 */

class Material {
public:
	float reflexion;
	float rojo;
	float verde;
	float azul;

	Material();
	Material(float rf, float rj, float vd, float az);
	~Material();
};

class Esfera {
public:
	Punto posicion;
	float tamano;
	int idMaterial;

	Esfera();
	Esfera (Punto &p, float t, int id);
	~Esfera();
};

class Luz {
public:
	Punto posicion;
	float rojo;
	float verde;
	float azul;

	Luz();
	Luz(Punto &p, float rj, float vd, float az);
	~Luz();
};

class Rayo {
public:
	Punto inicio;
	Vector direccion;

	Rayo();
	Rayo(Punto &i, Vector &d);
	~Rayo();
};

class Escena {
public:
	std::vector<Material> listaMateriales;
	std::vector<Esfera> listaEsferas;
	std::vector<Luz> listaLuces;
	int tamX;
	int tamY;
	Escena();
	~Escena();
	bool init(char *archivo);
private:
	void obtenerMaterial(const Configuracion &archivo, Material &material);
	void obtenerEsfera(const Configuracion &archivo, Esfera &esfera);
	void obtenerLuz(const Configuracion &archivo, Luz &luz);
};

#endif /* ESCENA_H_ */
