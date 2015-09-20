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

New::New() : 
  m_title(), m_body(),
  m_entities(), m_entities_r(),
  m_more_frequent()
{
  ;
}

New::New(const std::string& title, const std::string& body,
         const std::string& path) :
  m_title(title), m_body(body)
{
	setReservedWords(path);
	setEntities();
	setMoreFrequent();
}

void New::setTitle(const std::string& title)
{
	m_title = title;
}

void New::setBody(const std::string& body)
{
	m_body = body;
}

void New::setReservedWords(const std::string& path)
{
	std::ifstream f;
	f.open(path.c_str(), std::ofstream::in);
	assert(f.good());
	std::string aux;
	while (!f.eof()) {
		f >> aux;
		m_entities_r.push_back(aux);
	}
}

void New::update()
{
	setEntities();
	setMoreFrequent();
}

std::string New::getTitle() const
{
	return m_title;
}

std::string New::getBody() const
{
	return m_body;
}

NamedEntity New::getMoreFrequent() const
{
	return m_more_frequent;
}

std::list<NamedEntity> New::getEntities() const
{
	return m_entities;
}

std::list<std::string> New::getReservedWords() const
{
	return m_entities_r;
}

std::list<NamedEntity> New::getRelevantEntities() const
{
	std::string aux = m_body;
	std::list<NamedEntity> relevant_entities;

	NamedEntity en;
	aux = aux.substr(0, (aux.size() / 3));
 std::list<NamedEntity>::const_iterator it;
	for (it = m_entities.begin(); it != m_entities.end(); it++)
	{
		en = *it;
		if (aux.find(en.getNamedEntity()) != std::string::npos)
		{
			relevant_entities.push_back(en);
		}
	}
	return relevant_entities;
}

void New::mergeNamedEntities(const std::list<NamedEntity> first,
                            const std::list<NamedEntity> second,
                            std::list<NamedEntity>& merged) const
{
	NamedEntity en1;
	NamedEntity en2;

	for (std::list<NamedEntity>::const_iterator it1 = first.begin();
			it1 != first.end(); it1++) {

		en1 = *it1;
		for (std::list<NamedEntity>::const_iterator it2 = second.begin();
				it2 != second.end(); it2++) {

			en2 = *it2;
			if (en1.equals(en2)) {
				merged.push_back(en2);
			}
		}
	}
}


bool New::canBeGrouped(const New& analyzed_new) const
{
	bool groupable = false;

	if (m_title.find(analyzed_new.getMoreFrequent().getNamedEntity())
			!= std::string::npos)
	{
		groupable = true;
	}

	std::list<NamedEntity> first = getRelevantEntities();
	std::list<NamedEntity> second = analyzed_new.getRelevantEntities();
	std::list<NamedEntity> final;

	mergeNamedEntities(first, second, final);

	if (final.size() >= (second.size() / 3))
 {
		groupable = true;
	}

	return groupable;
}

std::string New::toString() const
{
	std::string output;
	output = "TITLE: " + m_title + "\n" + "BODY: " + m_body + "\n" + "ENTITIES: ";

	std::list<NamedEntity> entities_list = getEntities();
  std::list<NamedEntity>::iterator entities_it;

	for (entities_it = entities_list.begin();
      entities_it != entities_list.end(); entities_it++) {
		output += (*entities_it).toString();
		output += " ";
	}

	output = output + "\n" + "MAS FRECUENTE: " + getMoreFrequent().toString();

	return output;
}

void New::setEntities()
{
	std::string aux = "";

	for (unsigned int i = 0; i <= m_body.size(); i++)
	{
		if (m_body[i] != ' ') {
			if (isLetter(m_body[i])) {
				aux += m_body[i];
			}
		}
		else {
			addEntity(aux);
			aux = "";
		}
	}
}

void New::setMoreFrequent()
{
	NamedEntity aux;
	NamedEntity aux2;
 std::list<NamedEntity>::iterator entities_it;
   for (entities_it = m_entities.begin(); entities_it != m_entities.end();
        ++entities_it) { 
		aux2 = *entities_it;
		if (aux.getFrequency() < aux2.getFrequency())
		{
			aux.setNamedEntity(aux2.getNamedEntity());
			aux.setFrequency(aux2.getFrequency());
		}
	}
	m_more_frequent = aux;
}

void New::addEntity(const std::string& entity_name)
{
	bool must_start = true;
	for (std::list<std::string>::iterator i = m_entities_r.begin();
			i != m_entities_r.end(); i++) {
		std::string aux = entity_name;
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
		for (std::list<NamedEntity>::iterator it = m_entities.begin();
				it != m_entities.end(); it++)
		{
			if (it->getNamedEntity().compare(entity_name) == 0) {
				it->setFrequency(it->getFrequency() + 1);
				add = false;
			}
		}
		if (add) {
			int aux = static_cast<int>(entity_name[0]);
			if ((aux >= 65) && (aux <= 90)) {
				NamedEntity aux(entity_name, 1);
				m_entities.push_back(aux);
			}
		}
	}
}

bool New::isLetter(const char& c) const
{
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
	if ((ascii >= 48) && (ascii <= 57))
	{
		output = true;
	}
	return output;
}

const bool New::operator==(const New& the_new) const
{
	return ((m_title == the_new.m_title) && (m_body == the_new.m_body));
}

const bool New::operator!=(const New& the_new) const
{
	return !(*this == the_new);
}
