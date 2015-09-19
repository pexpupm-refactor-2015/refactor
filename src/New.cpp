/*
 * New.cpp
 *
 */
#include <assert.h>
#include <list>
#include <iostream>
#include <fstream>
#include "New.h"
#include "NamedEntity.h"

New::New() {
	this->m_title = "";
	this->m_body = "";
	std::list<NamedEntity> l;
	this->m_entities = l;
	std::list<std::string> p;
	this->m_entities_r = p;
	NamedEntity e;
	this->m_more_frequent = e;
}

New::New(std::string title, std::string body, std::string path) {
	this->m_title = title;
	this->m_body = body;
	this->setReservedWords(path);
	this->setEntities();
	this->setMoreFrequent();
}

void New::setTitle(std::string title) {
	this->m_title = title;
}

void New::setBody(std::string body) {
	this->m_body = body;
}

void New::setReservedWords(std::string path) {
	std::ifstream f;
	f.open(path.c_str(), std::ofstream::in);
	assert(f.good());
	std::string aux;
	while (!f.eof()) {
		f >> aux;
		this->m_entities_r.push_back(aux);
	}
}

void New::update() {
	this->setEntities();
	this->setMoreFrequent();
}

std::string New::getTitle() const {
	return this->m_title;
}

std::string New::getBody() const {
	return this->m_body;
}

NamedEntity New::getMoreFrequent() const {
	return this->m_more_frequent;
}

std::list<NamedEntity> New::getEntities() const {
	return this->m_entities;
}

std::list<std::string> New::getReservedWords() const {
	return this->m_entities_r;
}

std::list<NamedEntity> New::getRelevantEntities() const {

	std::string aux = this->m_body;
	std::list<NamedEntity> relevant_entities;

	NamedEntity en;
	aux = aux.substr(0, (aux.size() / 3));
  std::list<NamedEntity>::const_iterator it;
	for (it = m_entities.begin(); it != m_entities.end(); it++) {
		en = *it;
		if (aux.find(en.getNamedEntity()) != std::string::npos) {
			relevant_entities.push_back(en);
		}
	}

	return relevant_entities;
}

bool New::canBeGrouped(New n) const {

	bool output = false;

	if (this->m_title.find(n.getMoreFrequent().getNamedEntity())
			!= std::string::npos) {
		output = true;
	}

	std::list<NamedEntity> first = this->getRelevantEntities();
	std::list<NamedEntity> second = n.getRelevantEntities();
	std::list<NamedEntity> final;
	NamedEntity en1;
	NamedEntity en2;

	for (std::list<NamedEntity>::iterator it1 = first.begin();
			it1 != first.end(); it1++) {

		en1 = *it1;
		for (std::list<NamedEntity>::iterator it2 = second.begin();
				it2 != second.end(); it2++) {

			en2 = *it2;
			if (en1.equals(en2)) {
				final.push_back(en2);
			}
		}
	}

	if (final.size() >= (second.size() / 3)) {
		output = true;
	}
	return output;
}

std::string New::toString() const {

	std::string output;
	output = "TITLE: " + this->m_title + "\n" + "BODY: " + this->m_body + "\n"
			+ "ENTITIES: ";

	std::list<NamedEntity> entities_list = this->getEntities();

	for (std::list<NamedEntity>::iterator i = entities_list.begin();
			i != entities_list.end(); i++) {
		output += i->toString();
		output += " ";
	}

	output = output + "\n" + "MAS FRECUENTE: "
			+ getMoreFrequent().toString();

	return output;
}

void New::setEntities() {
	std::string aux = "";

	for (unsigned int i = 0; i <= this->m_body.size(); i++) {
		if (this->m_body[i] != ' ') {
			if (this->isLetter(this->m_body[i])) {
				aux += this->m_body[i];
			}
		} else {
			this->addEntity(aux);
			aux = "";
		}
	}
}

void New::setMoreFrequent() {
	NamedEntity aux;
	NamedEntity aux2;
	for (std::list<NamedEntity>::iterator i = this->m_entities.begin();
			i != this->m_entities.end(); ++i) { // Iterate through 'items'
		aux2 = *i;
		if (aux.getFrequency() < aux2.getFrequency()) {
			aux.setNamedEntity(aux2.getNamedEntity());
			aux.setFrequency(aux2.getFrequency());
		}
	}
	this->m_more_frequent = aux;
}

void New::addEntity(std::string nombre) {
	bool must_start = true;
	for (std::list<std::string>::iterator i = this->m_entities_r.begin();
			i != this->m_entities_r.end(); i++) {
		std::string aux = nombre;
		int ascii = static_cast<int>(aux[0]);
		if ((ascii >= 65) && (ascii <= 90)) {
			aux[0] = static_cast<char>(aux[0] + 32);
		}
		if (i->compare(aux) == 0) {
			must_start = false;
		}
	}
	if (must_start) {
		bool add = true;
		for (std::list<NamedEntity>::iterator it = this->m_entities.begin();
				it != this->m_entities.end(); it++) {
			if (it->getNamedEntity().compare(nombre) == 0) {
				it->setFrequency(it->getFrequency() + 1);
				add = false;
			}
		}
		if (add) {
			int aux = static_cast<int>(nombre[0]);
			if ((aux >= 65) && (aux <= 90)) {
				NamedEntity aux(nombre, 1);
				this->m_entities.push_back(aux);
			}
		}
	}
}

bool New::isLetter(char c) const {
	bool output = false;
	int ascii = static_cast<int>(c);
	if ((ascii >= 65) && (ascii <= 90)) {
		output = true;
	}
	if ((ascii >= 97) && (ascii <= 122)) {
		output = true;
	}
	if (ascii < 0) {
		output = true;
	}
	if ((ascii >= 48) && (ascii <= 57)) {
		output = true;
	}
	return output;
}
