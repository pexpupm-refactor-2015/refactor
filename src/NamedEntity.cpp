/*
 * NamedEntity.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */
#include <sstream>

#include "NamedEntity.h"

NamedEntity::NamedEntity() :
		frecuencia(0), entidadNombrada("") {
}

NamedEntity::NamedEntity(std::string n, int f) :
		frecuencia(f), entidadNombrada(n) {
}

int NamedEntity::getFrecuencia() const {
	return this->frecuencia;
}

std::string NamedEntity::getNamedEntity() const {
	return this->entidadNombrada;
}

void NamedEntity::setFrecuencia(int const f) {
	this->frecuencia = f;
}

void NamedEntity::setNamedEntity(std::string const en) {
	this->entidadNombrada = en;
}

bool NamedEntity::esIgual(const NamedEntity& en) const {
	bool salida = false;
	if ((this->entidadNombrada.compare(en.entidadNombrada) == 0)) {
		salida = true;
	}
	return salida;
}

std::string NamedEntity::toString() const {
	std::stringstream s;
	s << this->entidadNombrada << " [" << this->frecuencia << "]";
	return s.str();
}
