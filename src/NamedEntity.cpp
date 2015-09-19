/*
 * NamedEntity.cpp
 */
#include <sstream>
#include "NamedEntity.h"

NamedEntity::NamedEntity() :
		m_frequency(0), m_named_entity("") {
}

NamedEntity::NamedEntity(std::string n, int f) :
		m_frequency(f), m_named_entity(n) {
}

int NamedEntity::getFrequency() const {
	return this->m_frequency;
}

std::string NamedEntity::getNamedEntity() const {
	return this->m_named_entity;
}

void NamedEntity::setFrequency(int const f) {
	m_frequency = f;
}

void NamedEntity::setNamedEntity(std::string const en) {
	m_named_entity = en;
}

bool NamedEntity::equals(const NamedEntity& en) const {
	bool output = false;
	if ((this->m_named_entity.compare(en.m_named_entity) == 0)) {
		output = true;
	}
	return output;
}

std::string NamedEntity::toString() const {
	std::stringstream s;
	s << m_named_entity << " [" << m_frequency << "]";
	return s.str();
}
