/*
 * NamedEntity.h
 *
 */
#ifndef NAMED_ENTITY_H_
#define NAMED_ENTITY_H_
#include <string>

class NamedEntity {

	int frecuencia;
	std::string entidadNombrada;

public:

	NamedEntity();
	NamedEntity( std::string n, int f);
	int getFrecuencia() const;
	std::string getNamedEntity() const;
	void setFrecuencia(int const f);
	void setNamedEntity(std::string const en);
	bool esIgual(const NamedEntity& en) const;
	std::string toString() const;

};

#endif /* NAMED_ENTITY_H_ */
