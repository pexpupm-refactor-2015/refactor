/*
 * Analyzer.h
 */
#ifndef _NEWS_STRINGIZER_H_
#define _NEWS_STRINGIZER_H_

#include <string>
#include <list>
#include "New.h"

class NewsStringizer
{
public:
  // Dump news titles to string
  static std::string titlesToString(const std::list<New*>& news_list);

  // Dump news titles and bodies to string
  static std::string titlesAndBodiesToString(const std::list<New*>& news_list);
};

#endif /* _NEWS_STRINGIZER_H_ */
