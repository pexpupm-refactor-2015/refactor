/*
 * Tuit.cpp
 */
#include "Tuit.h"

void Tuit::setEntities()
{
  std::string aux = "";
  
  for (unsigned int i = 0; i <= m_title.size(); i++) {
    if (m_title[i] != ' ') {
      if (isLetter(m_title[i])) {
        aux += m_title[i];
      }
    }
    else {
      addEntity(aux);
        aux = "";
    }
  }
}
