/*
 * NamedEntity.h
 */
#ifndef _NAMED_ENTITY_H_
#define _NAMED_ENTITY_H_

#include <string>

class NamedEntity
{
public:
	NamedEntity();
	NamedEntity(std::string n, int f);
	int getFrequency() const;
	std::string getNamedEntity() const;
	void setFrequency(const int& frequency);
	void setNamedEntity(const std::string& entity);
	bool equals(const NamedEntity& entity) const;
	std::string toString() const;

private:
	int m_frequency;
	std::string m_named_entity;
};

#endif /* _NAMED_ENTITY_H_ */
