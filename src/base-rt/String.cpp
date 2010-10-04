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

#include <String.h>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdio>
#include <climits>

String::String() : buffer(NULL), tamanoReservado(0), tamano(0) {
	crecer(tamanoReservado);
}

String::String(const String &s) : buffer(NULL), tamanoReservado(0), tamano(0) {
	asignar(s);
}

String::String(const char * s) : buffer(NULL), tamanoReservado(0), tamano(0) {
	asignar(s);
}

String::String(const char *s, int largo) : buffer(NULL),
												tamanoReservado(0), tamano(0) {
	asignar(s, largo);
}

String::String(iterador_const inicial, iterador_const final) : buffer(NULL),
												tamanoReservado(0), tamano(0) {
	asignar(inicial, final);
}

String::~String() {
	delete [] buffer;
}

void String::crecer(int nuevoTamano) {
	if (tamanoReservado == 0) {
		tamanoReservado = tamanoPreferido;

		while (nuevoTamano > tamanoReservado)
			tamanoReservado *= 2;

		buffer = new char[size_t(tamanoReservado)];
		buffer[0] = '\0';
	} else {
		while (nuevoTamano > tamanoReservado)
					tamanoReservado *= 2;

		char *tmp = new char[size_t(tamanoReservado)];
		memcpy(tmp, buffer, size_t(tamano + 1));
		delete [] buffer;
		buffer = tmp;
	}

	return;
}

String & String::operator=(const String &s) {
	return asignar(s);
}

String & String::asignar(const String &s) {
	int largo = s.tamanoStr();

	if (largo + 1 > tamanoReservado)
		crecer(largo + 1);

	memcpy(buffer, s.cString(), largo + 1);
	tamano = largo;

	return *this;
}

String & String::asignar(const char * s) {
	int largo = int(strlen(s));

	if (largo + 1 > tamanoReservado)
		crecer(largo + 1);

	memcpy(buffer, s, largo + 1);
	tamano = largo;

	return *this;
}

String & String::asignar(const char * s, int largo) {

	if (largo + 1 > tamanoReservado)
		crecer(largo + 1);

	memcpy(buffer, s, largo + 1);
	tamano = largo;
	buffer[largo] = '\0';

	return *this;
}

String & String::asignar(iterador_const inicial, iterador_const final) {
	int largo = int(final - inicial);

	if (largo < 0)
		largo = 0;

	if (largo + 1 > tamanoReservado)
		crecer(largo + 1);

	memcpy(buffer, inicial, largo + 1);
	tamano = largo;
	buffer[largo] = '\0';

	return *this;
}

String & String::pegar(const String &s) {
	int largo = s.tamanoStr();

	if (largo + tamano + 1 > tamanoReservado)
		crecer(largo + tamano + 1);

	memcpy(buffer + tamano, s.cString(), size_t(largo + 1));
	tamano += largo;

	return *this;
}

String & String::pegar(const char * s) {
	int largo = int(strlen(s));

	if (largo + tamano + 1 > tamanoReservado)
		crecer(largo + tamano + 1);

	memcpy(buffer + tamano, s, size_t(largo + 1));
	tamano += largo;

	return *this;
}

String & String::pegar(const char * s, int largo) {
	if (largo + tamano + 1 > tamanoReservado)
		crecer(largo + tamano + 1);

	memcpy(buffer + tamano, s, size_t(largo + 1));
	tamano += largo;
	buffer[tamano] = '\0';

	return *this;
}

String & String::pegar(iterador_const inicial, iterador_const final) {
	int largo = int(final - inicial);

	if (largo + tamano + 1 > tamanoReservado)
		crecer(largo + tamano + 1);

	memcpy(buffer + tamano, inicial, size_t(largo + 1));
	tamano += largo;
	buffer[tamano] = '\0';

	return *this;
}

String & String::pegar(char c) {
	if (tamano + 2 > tamanoReservado)
		crecer(tamano + 2);

	buffer[tamano] = c;
	tamano++;
	buffer[tamano] = '\0';

	return *this;
}

String & String::pegar(int i) {
	return pegar(static_cast<long>(i));
}

String & String::pegar(unsigned int ui) {
	return pegar(static_cast<unsigned long>(ui));
}

String & String::pegar(long l) {
	char buf[40];
	sprintf(buf, "%ld", l);

	int largo = strlen(buf);

	if (largo + tamano + 1 > tamanoReservado)
		crecer(largo + tamano + 1);

	memcpy(buffer + tamano, buf, size_t(largo + 1));
	tamano += largo;
	buffer[tamano] = '\0';

	return *this;
}

String & String::pegar(unsigned long ul) {
	char buf[40];
	sprintf(buf, "%lu", ul);

	int largo = strlen(buf);

	if (largo + tamano + 1 > tamanoReservado)
		crecer(largo + tamano + 1);

	memcpy(buffer + tamano, buf, size_t(largo + 1));
	tamano += largo;
	buffer[tamano] = '\0';

	return *this;
}

char * String::cString() const {
	return buffer;
}

int String::tamanoStr() const {
	return tamano;
}

bool String::vacia() const {
	return tamano == 0;
}

int String::comparar(const String &s) const {
	return strcmp(buffer, s.cString());
}

int String::comparar(const char *s) const {
	return strcmp(buffer, s);
}

void String::redimensionar(int nuevoTamano) {
	if (nuevoTamano + 1 > tamanoReservado)
		crecer(nuevoTamano + 1);

	tamano = nuevoTamano;
	buffer[tamano] = '\0';
}

iterador String::inicio() {
	return buffer;
}

iterador String::final() {
	return buffer + tamano;
}

String String::substring(int pos, int n) const {
	return String(buffer + pos, buffer + pos + n);
}

int String::encontrarUltimo(char c) const {
	int i = int(tamano - 1);

	while (i >= 0) {
		if (c == buffer[i])
			return i;

		i--;
	}

	return -1;
}

bool String::operator<(String &s) {
	return strcmp(cString(), s.cString()) < 0;
}

bool String::operator<(String s) {
	return strcmp(cString(), s.cString()) < 0;
}

