/*
 * RawTextNewsParser.h
 */
#ifndef _RAW_TEXT_NEWS_PARSER_H_
#define _RAW_TEXT_NEWS_PARSER_H_

#include <list>
#include "New.h"
#include <vector>
#include <string>

class RawTextNewsParser
{
public:
  static bool parseAllFilesInPath(const std::string& all_news_path,
                                  std::list<New>& news_list);

private:

  static void parseNewsFromTxtFile(std::string &file,
                        const std::string& news_path,
                        std::list<New>& news_list);

  static std::vector<std::string> getFilesFromDir(const std::string &path);
};

#endif /* _RAW_TEXT_NEWS_PARSER_H_ */
