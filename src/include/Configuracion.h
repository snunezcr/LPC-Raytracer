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

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <fstream>
#include <map>
#include <set>
#include <Punto.h>
#include <Vector.h>
#include <String.h>

using namespace std;

typedef std::map<String,String> ConjuntoVariables;
typedef std::set<String> ConjuntoStrings;

class Configuracion {
private:
	void *vars;
	void *secs;
	const String nombreArchivo;
	String seccionLocal;
	bool cargado;
	String preprocesar(fstream &input);
	bool precargar(fstream &input);
public:
	Configuracion();
	Configuracion(const String &archivo);
	~Configuracion();
	bool cargarPorNombreBool(const String &nombre, bool defval) const;
	double cargarPorNombreFloat(const String &nombre, double defval) const;
	const String &cargarPorNombreString(const String &nombre, const String &defval) const;
	long cargarPorNombreInt(const String &nombre, long defval) const;
	Vector obtenerPorNombreVector(const String &nombre, const Vector &defval) const;
	Punto obtenerPorNombrePunto(const String &nombre, const Punto &defval) const;
	int establecerSeccion(const String &s);
};

#endif /* CONFIGURACION_H_ */
