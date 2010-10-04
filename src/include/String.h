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

#ifndef __STRING_H_
#define __STRING_H_

static unsigned int tamanoPreferido = 1 << 8;

typedef char * iterador;
typedef const char * iterador_const;

class String {
private:
	char *buffer;
	int tamanoReservado;
	int tamano;
	void crecer(int nuevoTamano);
public:
	String();
	String(const String &s);
	String(const char * s);
	String(const char *s, int largo);
	String(iterador_const inicial, iterador_const final);
	~String();
	String & operator=(const String &s);
	String & asignar(const String &s);
	String & asignar(const char * s);
	String & asignar(const char * s, int largo);
	String & asignar(iterador_const inicial, iterador_const final);
	String & pegar(const String &s);
	String & pegar(const char * s);
	String & pegar(const char * s, int largo);
	String & pegar(iterador_const inicial, iterador_const final);
	String & pegar(char c);
	String & pegar(int i);
	String & pegar(unsigned int ui);
	String & pegar(long l);
	String & pegar(unsigned long ul);
	char * cString() const;
	int tamanoStr() const;
	bool vacia() const;
	int comparar(const String &s) const;
	int comparar(const char *s) const;
	void redimensionar(int nuevoTamano);
	iterador inicio();
	iterador final();
	String substring(int pos, int n) const;
	int encontrarUltimo(char c) const;
	bool operator<(String &s);
	bool operator<(String s);
};

#endif /* __STRING_H_ */
