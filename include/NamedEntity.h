/*
 * NamedEntity.h
 *
 */
#ifndef NAMED_ENTITY_H_
#define NAMED_ENTITY_H_
#include <string>

class NamedEntity {

public:
	NamedEntity();
	NamedEntity(std::string n, int f);
	int getFrequency() const;
	std::string getNamedEntity() const;
	void setFrequency(int const f);
	void setNamedEntity(std::string const en);
	bool equals(const NamedEntity& en) const;
	std::string toString() const;

private:
	int m_frequency;
	std::string m_named_entity;
};

#endif /* NAMED_ENTITY_H_ */
