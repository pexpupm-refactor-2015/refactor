/*
 * RawTextNewsParser.cpp
 */
#include <string>
#include <fstream>
#include <sstream>
#include "RawTextNewsParser.h"
#include "New.h"

const std::string NEWS_FILE_PREFIX = "/newC";
const std::string NEWS_FILE_SUFFIX = ".ES.txt";
const std::string NEWS_PATH = "/news";
const std::string RESTRICTED_WORDS = "/ES_stopList.txt";

bool RawTextNewsParser::parseAllFilesInPath(const std::string& all_news_path,
                                            std::list<New>& news_list)
{
  bool something_parsed = false;
  std::string restriction_path = all_news_path + RESTRICTED_WORDS;
  std::string news_path = all_news_path + NEWS_PATH;
  
  int group_desc = 1;
  int new_desc = 1;
  bool continue_parsing = true;
  bool more_files = false;
  std::ifstream news_file;
  do {
    std::string final_path =
      getFinalPath(news_path, group_desc, new_desc);

    std::ifstream news_file;
    news_file.open(final_path.c_str(), std::ofstream::in);
    RawTextNewsParser::parseNews(news_file, restriction_path, news_list);
    if(!something_parsed) {
      something_parsed = true;
    }
    new_desc++;
    continue_parsing = mustContinueParsing(news_file, group_desc, new_desc,
                                           more_files);
    news_file.close();
  }
  while (continue_parsing);
  return something_parsed;
}

void RawTextNewsParser::parseNews(std::ifstream& f,
                                  const std::string& restricted_words_path,
                                  std::list<New>& news_list)
{
  std::string collector = "";
  std::string title = "";
  std::string body = "";
  if (f.is_open()) {
    while (!f.eof()) {
        getline(f, collector, '\n');
        if (title == "") {
          title = title + " " + collector;
        } else {
          body = body + " " + collector;
        }
    }
    New added_new(title, body, restricted_words_path);
    news_list.push_front(added_new);
  }
}

bool RawTextNewsParser::mustContinueParsing(const std::ifstream& file,
                                            int& group_desc,
                                            int& new_desc,
                                            bool& more_files)
{
 bool continue_parsing = true;
 if (new_desc >= 999) {
   if (!more_files) {
     continue_parsing = false;
   }
   else {
     group_desc++;
     new_desc = 0;
     more_files = false;
   }
 }
 if (file.is_open()) {
   more_files = true;
 }
 if (group_desc >= 99999) {
   continue_parsing = false;
 }
 return continue_parsing;
}

std::string RawTextNewsParser::getFinalPath(const std::string& news_path,
                                            const int& xshift,
                                            const int& yshift)
{
  std::string file_name = NEWS_FILE_PREFIX + zeroPadding(xshift, 5)
    + "_" + zeroPadding(yshift, 3) + NEWS_FILE_SUFFIX;
  return news_path + file_name;
}

std::string RawTextNewsParser::zeroPadding(const int& number, const int& size)
{
  std::stringstream ss;
  ss << number;
  std::string aux = ss.str();
  for (int i = aux.size(); i < size; i++) {
    aux = "0" + aux;
  }
  return aux;
}


