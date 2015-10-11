/*
 * Analyzer.h
 */
#ifndef _ANALYZER_H_
#define _ANALYZER_H_

#include <string>
#include <list>
#include "New.h"

class Analyzer
{
public:
  Analyzer();
  Analyzer(std::string path);
  void setNews(const std::string& path);
  void setTuits(const std::string& path);
  std::string groupNews();
  std::string groupGeneralNews(bool outJson = false);
  std::string toString() const;
  std::string toWideString() const;

 private:
  void sortNews();
  bool exists(std::list<NamedEntity> es, NamedEntity e) const;
  std::string groupToString(const std::list<NamedEntity> group[],
                            const std::list<New*>& processed_news_list,
                            const std::list<New*>& original_news_list) const;
  std::string groupToStringJson(const std::list<NamedEntity> group[],
                              const std::list<New*>& processed_news_list,
                              const std::list<New*>& original_news_list) const;
  void cleanDuplicatedEntities(std::list<NamedEntity>& list) const;
  bool groupPerNew(const New& the_new, std::list<NamedEntity>& group,
                   std::list<New*>& processed_news_list) const;
  std::list<New*> m_news_list;
  std::string m_path;
};

#endif /* _ANALYZER_H_ */
