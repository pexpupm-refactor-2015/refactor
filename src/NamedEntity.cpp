/*
 * NamedEntity.cpp
 */
#include <sstream>
#include "NamedEntity.h"

NamedEntity::NamedEntity() :
		m_frequency(0), m_named_entity("")
{
	;
}

NamedEntity::NamedEntity(std::string n, int f) :
		m_frequency(f), m_named_entity(n)
{
	;
}

int NamedEntity::getFrequency() const 
{
	return m_frequency;
}

std::string NamedEntity::getNamedEntity() const
{
	return m_named_entity;
}

void NamedEntity::setFrequency(const int& frequency)
{
	m_frequency = frequency;
}

void NamedEntity::setNamedEntity(const std::string& entity)
{
	m_named_entity = entity;
}

bool NamedEntity::equals(const NamedEntity& entity) const
{
	bool output = false;
	if ((m_named_entity.compare(entity.m_named_entity) == 0))
	{
		output = true;
	}
	return output;
}

std::string NamedEntity::toString() const
{
	std::stringstream s;
	s << m_named_entity << " [" << m_frequency << "]";
	return s.str();
}
