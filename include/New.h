/*
 * New.h
 */
#ifndef _NEW_H_
#define _NEW_H_

#include <string>
#include <list>
#include "NamedEntity.h"

class New
{
public:
  New();
  New(const std::string& title,
      const std::string& body,
      const std::string& path);
  void setTitle(const std::string& title);
  void setBody(const std::string& body);
  void setReservedWords(const std::string& path);
  void update();
  std::string getTitle() const;
  std::string getBody() const;
  NamedEntity getMoreFrequent() const;
  std::list<NamedEntity> getEntities() const;
  std::list<std::string> getReservedWords() const;
  std::list<NamedEntity> getRelevantEntities() const;
  bool canBeGrouped(const New& analyzed_new) const;
  std::string toString() const;
  const bool operator==(const New& the_new) const; 
  const bool operator!=(const New& the_new) const; 
 private:
  void setEntities();
  void setMoreFrequent();
  void mergeNamedEntities(const std::list<NamedEntity> first,
                          const std::list<NamedEntity> second,
                          std::list<NamedEntity>& merged) const;
  void addEntity(const std::string& nombre);
  bool isLetter(const char& c) const;
  std::string m_title;
  std::string m_body;
  std::list<NamedEntity> m_entities;
  std::list<std::string> m_entities_reserved;
  NamedEntity m_more_frequent;
};

#endif /* NOTICIA_H_ */
