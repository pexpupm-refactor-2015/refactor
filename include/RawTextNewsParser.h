/*
 * RawTextNewsParser.h
 */
#ifndef _RAW_TEXT_NEWS_PARSER_H_
#define _RAW_TEXT_NEWS_PARSER_H_

#include <list>
#include "New.h"

class RawTextNewsParser
{
public:
  static bool parseAllFilesInPath(const std::string& all_news_path,
                                  std::list<New>& news_list);
  static bool parseFile(const char* raw_text_file_path,
                        std::list<New>& news_list);
  static bool parseFile(const std::string& news_file_path,
                        std::list<New>& news_list);
private:
  static void parseNews(std::ifstream& f,
                        const std::string& news_path,
                        std::list<New>& news_list);
  static bool mustContinueParsing(const std::ifstream& file,
                                  int& group_desc,
                                  int& new_desc,
                                  bool& more_files);
  static bool continueParsing();
  static std::string getFinalPath(const std::string& path_news,
                                  const int& xshift,
                                  const int& yshift);
  static std::string zeroPadding(const int& nunber, const int& size);
};

#endif /* _RAW_TEXT_NEWS_PARSER_H_ */
