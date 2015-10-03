/*
 * Tuit.h
 */
#ifndef _TUIT_H_
#define _TUIT_H_

#include "NamedEntity.h"
#include "New.h"

class Tuit : public New
{
public:
  Tuit() {};
  Tuit(const std::string& id,
       const std::string& user,
       const std::string& tuit_content,
       const std::string& path);
  ~Tuit() {};
  const std::string getId() const { return m_id; }
  const std::string getUser() const { return m_user; }
  virtual void setEntities();
 private:
  std::string m_id;
  std::string m_user;
};

#endif /* _TUIT_H_ */
