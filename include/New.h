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

public:
	New();
	New(std::string titulo, std::string cuerpo, std::string ruta);
	void setTitle(std::string title);
	void setBody(std::string body);
	void setReservedWords(std::string path);
	void update();
	std::string getTitle()const;
	std::string getBody()const;
	NamedEntity getMoreFrequent()const;
	std::list<NamedEntity> getEntities()const;
	std::list<std::string> getReservedWords()const;
	std::list<NamedEntity> getRelevantEntities()const;
	bool canBeGrouped(New n)const;
	std::string toString()const;

private:
	void setEntities();
	void setMoreFrequent();
	void addEntity(std::string nombre);
	bool isLetter(char c) const;
	std::string m_title;
	std::string m_body;
	std::list<NamedEntity> m_entities;
	std::list<std::string> m_entities_r;
	NamedEntity m_more_frequent;
};

#endif /* NOTICIA_H_ */
