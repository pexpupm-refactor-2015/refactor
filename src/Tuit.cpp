/*
 * Tuit.cpp
 */
#include "Tuit.h"
#include <stdio.h>
#include <iostream>

Tuit::Tuit(const std::string& id,
           const std::string& user,
           const std::string& tuit_content,
           const std::string& path) : 
  m_id(id), m_user(user),
  New(tuit_content, "", path)
{
  setEntities();
  setMoreFrequent();
}

void Tuit::setEntities()
{
  std::string aux = "";
  
  for (unsigned int i = 0; i <= m_title.size(); i++) {
    if (m_title[i] != ' ' && m_title[i] != '\n' && m_title[i] != '\r') {
      if (isLetter(m_title[i])) {
        aux += m_title[i];
      }
    }
    else {
      addEntity(aux);
      aux = "";
    }
  }
  if(aux != "") {
    addEntity(aux);
  }
}

Json::Value Tuit::toJsonNode() const
{
	Json::Value jNew;
	jNew["tuit"] = this->m_title;
	jNew["usuario"] = this->m_user;
	jNew["id"] = this->m_id;
	return jNew;
}
