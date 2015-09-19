/*
 * New.cpp
 *
 */
#include "New.h"
#include "list"
#include "NamedEntity.h"
#include <iostream>
#include <fstream>
#include <assert.h>

New::New() {
	this->titulo = "";
	this->cuerpo = "";
	std::list<NamedEntity> l;
	this->entidades = l;
	std::list<std::string> p;
	this->entidadesR = p;
	NamedEntity e;
	this->masFrecuente = e;
}

New::New(std::string titulo, std::string cuerpo, std::string ruta) {
	this->titulo = titulo;
	this->cuerpo = cuerpo;
	this->setPalabrasReservadas(ruta);
	this->setEntidades();
	this->setMasFrecuente();
}

void New::setTitulo(std::string titulo) {
	this->titulo = titulo;
}

void New::setCuerpo(std::string cuerpo) {
	this->cuerpo = cuerpo;
}

void New::setPalabrasReservadas(std::string ruta) {
	std::ifstream f;
	f.open(ruta.c_str(), std::ofstream::in);
	assert(f.good());
	std::string aux;
	while (!f.eof()) {
		f >> aux;
		this->entidadesR.push_back(aux);
	}
}

void New::actualizar() {
	this->setEntidades();
	this->setMasFrecuente();
}

std::string New::getTitulo() const {
	return this->titulo;
}

std::string New::getCuerpo() const {
	return this->cuerpo;
}

NamedEntity New::getMasFrecuente() const {
	return this->masFrecuente;
}

std::list<NamedEntity> New::getEntidades() const {
	return this->entidades;
}

std::list<std::string> New::getPalabrasReservadas() const {
	return this->entidadesR;
}

std::list<NamedEntity> New::getEntidadesRelevantes() const {

	std::string aux = this->cuerpo;
	std::list<NamedEntity> lista;
	std::list<NamedEntity> misEntidades = this->entidades;

	NamedEntity en;
	aux = aux.substr(0, (aux.size() / 3));
	for (std::list<NamedEntity>::iterator it = misEntidades.begin();
			it != misEntidades.end(); it++) {
		en = *it;
		if (aux.find(en.getNamedEntity()) != std::string::npos) {
			lista.push_back(en);
		}
	}

	return lista;
}

bool New::esAgrupable(New n) const {

	bool salida = false;

	if (this->titulo.find(n.getMasFrecuente().getNamedEntity())
			!= std::string::npos) {
		salida = true;
	}

	std::list<NamedEntity> primero = this->getEntidadesRelevantes();
	std::list<NamedEntity> segundo = n.getEntidadesRelevantes();
	std::list<NamedEntity> final;
	NamedEntity en1;
	NamedEntity en2;

	for (std::list<NamedEntity>::iterator it1 = primero.begin();
			it1 != primero.end(); it1++) {

		en1 = *it1;
		for (std::list<NamedEntity>::iterator it2 = segundo.begin();
				it2 != segundo.end(); it2++) {

			en2 = *it2;
			if (en1.esIgual(en2)) {
				final.push_back(en2);
			}
		}
	}

	if (final.size() >= (segundo.size() / 3)) {
		salida = true;
	}
	return salida;
}

std::string New::toString() const {

	std::string salida;
	salida = "TITULO: " + this->titulo + "\n" + "CUERPO: " + this->cuerpo + "\n"
			+ "ENTIDADES: ";

	std::list<NamedEntity> lista = this->getEntidades();

	for (std::list<NamedEntity>::iterator i = lista.begin();
			i != lista.end(); i++) {
		salida += i->toString();
		salida += " ";
	}

	salida = salida + "\n" + "MAS FRECUENTE: "
			+ this->getMasFrecuente().toString();

	return salida;
}

void New::setEntidades() {
	std::string aux = "";
	std::list<NamedEntity> lista;

	for (unsigned int i = 0; i <= this->cuerpo.size(); i++) {
		if (this->cuerpo[i] != ' ') {
			if (this->esletra(this->cuerpo[i])) {
				aux += this->cuerpo[i];
			}
		} else {
			this->agregarEntidad(aux);
			aux = "";
		}
	}
}

void New::setMasFrecuente() {
	NamedEntity aux;
	NamedEntity aux2;
	for (std::list<NamedEntity>::iterator i = this->entidades.begin();
			i != this->entidades.end(); ++i) { // Iterate through 'items'
		aux2 = *i;
		if (aux.getFrecuencia() < aux2.getFrecuencia()) {
			aux.setNamedEntity(aux2.getNamedEntity());
			aux.setFrecuencia(aux2.getFrecuencia());
		}
	}
	this->masFrecuente = aux;
}

void New::agregarEntidad(std::string nombre) {
	bool empezar = true;
	for (std::list<std::string>::iterator i = this->entidadesR.begin();
			i != this->entidadesR.end(); i++) {
		std::string aux = nombre;
		int ascii = static_cast<int>(aux[0]);
		if ((ascii >= 65) && (ascii <= 90)) {
			aux[0] = static_cast<char>(aux[0] + 32);
		}
		if (i->compare(aux) == 0) {
			empezar = false;
		}
	}
	if (empezar) {
		bool add = true;
		for (std::list<NamedEntity>::iterator it = this->entidades.begin();
				it != this->entidades.end(); it++) {
			if (it->getNamedEntity().compare(nombre) == 0) {
				it->setFrecuencia(it->getFrecuencia() + 1);
				add = false;
			}
		}
		if (add) {
			int aux = static_cast<int>(nombre[0]);
			if ((aux >= 65) && (aux <= 90)) {
				NamedEntity aux(nombre, 1);
				this->entidades.push_back(aux);
			}
		}
	}
}

bool New::esletra(char c) const {
	bool salida = false;
	int ascii = static_cast<int>(c);
	if ((ascii >= 65) && (ascii <= 90)) {
		salida = true;
	}
	if ((ascii >= 97) && (ascii <= 122)) {
		salida = true;
	}
	if (ascii < 0) {
		salida = true;
	}
	if ((ascii >= 48) && (ascii <= 57)) {
		salida = true;
	}
	return salida;
}

