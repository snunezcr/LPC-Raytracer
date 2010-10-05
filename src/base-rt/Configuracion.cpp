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

#include <cmath>
#include <stdlib.h>
#include <Configuracion.h>

Configuracion::Configuracion(const String &archivo) : vars(NULL), secs(NULL),
										nombreArchivo(archivo), cargado(false) {

}

Configuracion::~Configuracion() {
	if (vars != NULL)
		delete static_cast<ConjuntoVariables *>(vars);

	if (secs != NULL)
		delete static_cast<ConjuntoStrings *>(secs);
}

String Configuracion::preprocesar(fstream &input) {
	String tmp;
	string linea;

	while (getline(input, linea, '\n')) {
		linea = linea.substr(0, linea.find("//"));

		for (string::iterator i = linea.begin(); i != linea.end(); i++) {
			switch (*i) {
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				break;
			default:
				tmp.pegar(*i);
			}
		}
	}

	return tmp;
}

bool Configuracion::precargar(fstream &input) {
	static String buffer;
	String tmp;
	int scope = 0;
	tmp = preprocesar(input);
	iterador i = tmp.inicio();
	String nombreTemp;
	String valorTemp;
	String seccionActual;

encontrar_nombre:
	if (i == tmp.final())
		goto fin;

	switch (*i) {
	case '{':
		if ((static_cast<ConjuntoStrings *>(secs))->insert(nombreTemp).second == false) {
			(static_cast<ConjuntoStrings *>(secs))->clear();
			(static_cast<ConjuntoVariables *>(vars))->clear();
			return false;
		}
		seccionActual = nombreTemp;
		nombreTemp.redimensionar(0);
		goto en_seccion;
		break;
	default:
		nombreTemp.pegar(&*i, 1);
	}
	i++;
	goto encontrar_nombre;

en_seccion:
	if (i == tmp.final()) {
		(static_cast<ConjuntoStrings *>(secs))->clear();
		(static_cast<ConjuntoVariables *>(vars))->clear();
		return false;
	}
	switch(*i) {
	case '{':
		scope++;
		break;
	case '}':
		scope--;
		if (scope == 0) {
			i++;
			seccionActual.redimensionar(0);
			goto encontrar_nombre;
		}
		break;
	default:
		goto nombre_variable;
	}
	i++;
	goto en_seccion;
nombre_variable:
	if (i == tmp.final()) {
		(static_cast<ConjuntoStrings *>(secs))->clear();
		(static_cast<ConjuntoVariables *>(vars))->clear();
		return false;
	}
	switch(*i) {
	case '{':
		goto en_seccion;
	case '}':
		(static_cast<ConjuntoStrings *>(secs))->clear();
		(static_cast<ConjuntoVariables *>(vars))->clear();
		return false;
	case '=':
		if (nombreTemp.vacia()) {
			(static_cast<ConjuntoStrings *>(secs))->clear();
			(static_cast<ConjuntoVariables *>(vars))->clear();
			return false;
		}
		i++;
		goto valor_variable;
	default:
		nombreTemp.pegar(&*i, 1);
		break;
	}
	i++;
	goto nombre_variable;
valor_variable:
	if (i == tmp.final()) {
		(static_cast<ConjuntoStrings *>(secs))->clear();
		(static_cast<ConjuntoVariables *>(vars))->clear();
		return false;
	}
	switch(*i) {
	case '{':
		(static_cast<ConjuntoStrings *>(secs))->clear();
		(static_cast<ConjuntoVariables *>(vars))->clear();
		return false;
	case '}':
		(static_cast<ConjuntoStrings *>(secs))->clear();
		(static_cast<ConjuntoVariables *>(vars))->clear();
		return false;
	case ';':
		if (nombreTemp.vacia()) {
			(static_cast<ConjuntoStrings *>(secs))->clear();
			(static_cast<ConjuntoVariables *>(vars))->clear();
			return false;
		}
		buffer.asignar(seccionActual);
		buffer.pegar('/');
		buffer.pegar(nombreTemp);
		(static_cast<ConjuntoVariables *>(vars))->insert(ConjuntoVariables::value_type(buffer, valorTemp));
		nombreTemp.redimensionar(0);
		valorTemp.redimensionar(0);
		i++;
		goto en_seccion;
	default:
		valorTemp.pegar(i, 1);
		break;
	}
	i++;
	goto valor_variable;
fin:
	return true;
}

bool Configuracion::cargarPorNombreBool(const String &nombre, bool defval) const {
	static String nombreBool;
	nombreBool.asignar(seccionLocal).pegar(nombre);
	ConjuntoVariables::const_iterator i =
			static_cast<ConjuntoVariables *>((ConjuntoVariables *)vars)->find(nombreBool);
	if (i != ((ConjuntoVariables *)vars)->end())
		return (*i).second.comparar("true") == 0;
	else
		return defval;
}

double Configuracion::cargarPorNombreFloat(const String &nombre, double defval) const {
	static String nombreFloat;
	nombreFloat.asignar(seccionLocal).pegar(nombre);
	ConjuntoVariables::const_iterator i =
			static_cast<ConjuntoVariables *>((ConjuntoVariables *)vars)->find(nombreFloat);
	if (i != ((ConjuntoVariables *)vars)->end())
		return atof((*i).second.cString());
	else
		return defval;
}

const String & Configuracion::cargarPorNombreString(const String &nombre, const String &defval) const {
	static String nombreString;
	nombreString.asignar(seccionLocal).pegar(nombre);
	ConjuntoVariables::const_iterator i =
			static_cast<ConjuntoVariables *>((ConjuntoVariables *)vars)->find(nombreString);
	if (i != ((ConjuntoVariables *)vars)->end())
		return (*i).second;
	else
		return defval;
}

long Configuracion::cargarPorNombreInt(const String &nombre, long defval) const {
	static String nombreLong;
	nombreLong.asignar(seccionLocal).pegar(nombre);
	ConjuntoVariables::const_iterator i =
			static_cast<ConjuntoVariables *>((ConjuntoVariables *)vars)->find(nombreLong);
	if (i != ((ConjuntoVariables *)vars)->end())
		return atol((*i).second.cString());
	else
		return defval;
}

Vector Configuracion::obtenerPorNombreVector(const String &nombre, const Vector &defval) const {
	Vector v;
	static String nombreVector;
	nombreVector.asignar(seccionLocal).pegar(nombre);
	ConjuntoVariables::const_iterator i =
			static_cast<ConjuntoVariables *>((ConjuntoVariables *)vars)->find(nombreVector);
	if (i != ((ConjuntoVariables *)vars)->end()) {
		int leidos = sscanf(i->second.cString(), "%f, %f, %f", &v.x, &v.y, &v.z);

		if (leidos != 3)
			return defval;

		return v;
	} else {
		return defval;
	}
}

Punto Configuracion::obtenerPorNombrePunto(const String &nombre, const Punto &defval) const {
	Punto p;
	static String nombrePunto;
	nombrePunto.asignar(seccionLocal).pegar(nombre);
	ConjuntoVariables::const_iterator i =
			static_cast<ConjuntoVariables *>((ConjuntoVariables *)vars)->find(nombrePunto);
	if (i != ((ConjuntoVariables *)vars)->end()) {
		int leidos = sscanf(i->second.cString(), "%f, %f, %f", &p.x, &p.y, &p.z);

		if (leidos != 3)
			return defval;

		return p;
	} else {
		return defval;
	}
}

int Configuracion::establecerSeccion(const String &s) {
	if (! cargado) {
		cargado = true;
		vars = new ConjuntoVariables();
		secs = new ConjuntoStrings;
		fstream input;
		bool resultado;

		input.open(nombreArchivo.cString(), ios::in);

		if (input.is_open() == 0) {
			resultado = false;
		} else {
			resultado = precargar(input);
			input.close();
		}

		if (! resultado) {
			delete static_cast<ConjuntoVariables *>(vars);
			vars = NULL;

			delete static_cast<ConjuntoStrings *>(secs);
			secs = NULL;

			return -1;
		}
	}

	if (vars == NULL)
		return -1;

	ConjuntoStrings::const_iterator i = ((ConjuntoStrings *) secs)->find(s);

	if (i != ((ConjuntoStrings *) secs)->end()) {
		seccionLocal.asignar(s).pegar('/');
		return 0;
	} else {
		seccionLocal.redimensionar(0);
		return -1;
	}
}

