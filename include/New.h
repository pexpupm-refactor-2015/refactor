/*
 * New.h
 *
 */
#ifndef NEW_H_
#define NEW_H_
#include "string"
#include <list>
#include "NamedEntity.h"

class New {

	std::string titulo;
	std::string cuerpo;
	std::list<NamedEntity> entidades;
	std::list<std::string> entidadesR;
	NamedEntity masFrecuente;

public:
	New();
	New(std::string titulo, std::string cuerpo, std::string ruta);

	void setTitulo(std::string titulo);
	void setCuerpo(std::string cuerpo);
	void setPalabrasReservadas(std::string ruta);
	void actualizar();

	std::string getTitulo()const;
	std::string getCuerpo()const;
	NamedEntity getMasFrecuente()const;
	std::list<NamedEntity> getEntidades()const;
	std::list<std::string> getPalabrasReservadas()const;
	std::list<NamedEntity> getEntidadesRelevantes()const;
	bool esAgrupable(New n)const;
	std::string toString()const;


private:
	void setEntidades();
	void setMasFrecuente();
	void agregarEntidad(std::string nombre);
	bool esletra(char c) const;
};

#endif /* NOTICIA_H_ */
