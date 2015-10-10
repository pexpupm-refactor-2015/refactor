/*
 * RawTextNewsParser.cpp
 */
#include <string>
#include <fstream>
#include <sstream>
#include "RawTextNewsParser.h"
#include "New.h"

#include <dirent.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "JsonTuitParser.h"

const std::string NEWS_FILE_PREFIX = "/newC";
const std::string NEWS_FILE_SUFFIX = ".ES.txt";
const std::string NEWS_PATH = "/news";
const std::string RESTRICTED_WORDS = "/ES_stopList.txt";

static const std::string JSON_TITLE_TAG = "titulo";
static const std::string JSON_BODY_TAG = "parrafos";

bool RawTextNewsParser::parseAllFilesInPath(const std::string& all_news_path,
                                            std::list<New>& news_list)
{
  bool something_parsed = false;
  std::string restriction_path = all_news_path + RESTRICTED_WORDS;
  std::string news_path = all_news_path + NEWS_PATH;
  
  std::vector<std::string> newsFiles = getFilesFromDir(news_path);

  for (auto file : newsFiles)
  {
  	std::string final_path = news_path + "/" + file;
  	if (final_path.find(".txt") != std::string::npos)
  	{
  		parseNewsFromTxtFile(final_path, restriction_path, news_list);
  	}
  	else if (final_path.find(".json") != std::string::npos)
  	{
  		parseNewsFromJsonFile(final_path, restriction_path, news_list);
  	}
  }

  if (!news_list.empty())
  {
  	something_parsed = true;
  }

  return something_parsed;
}

void RawTextNewsParser::parseNewsFromTxtFile(std::string &file,
                      const std::string& restriction_path,
                      std::list<New>& news_list)
{
	std::ifstream news_file;
	news_file.open(file.c_str(), std::ofstream::in);
  std::string collector = "";
  std::string title = "";
  std::string body = "";
  if (news_file.is_open()) {
    while (!news_file.eof()) {
        getline(news_file, collector, '\n');
        if (title == "") {
          title = title + " " + collector;
        } else {
          body = body + " " + collector;
        }
    }
    New added_new(title, body, restriction_path);
    news_list.push_front(added_new);
  }
  news_file.close();
}

void RawTextNewsParser::parseNewsFromJsonFile(std::string &file,
                        const std::string& restriction_path,
                        std::list<New>& news_list)
{
  std::ifstream t(file.c_str());
  std::stringstream buffer;
  buffer << t.rdbuf();

  Json::Value json_root;
  Json::Reader json_reader;

  if(!json_reader.parse(buffer.str(), json_root, false)) {
    return;
  }

  std::string title;
  std::string body;

  const Json::Value jTitle = json_root[JSON_TITLE_TAG];
  const Json::Value jBodyArray = json_root[JSON_BODY_TAG];

  title = " " + jTitle.asString() + " ";
  for (unsigned int index = 0; index < jBodyArray.size(); ++index)
  {
    body += jBodyArray[index].asString();
  }

  New added_new(title, body, restriction_path);
  news_list.push_front(added_new);

  t.close();
}

std::vector<std::string> RawTextNewsParser::getFilesFromDir(const std::string &path)
{
	std::vector<std::string> newsFiles;
	DIR *d;
	struct dirent *dir;
	d = opendir(path.c_str());
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			std::string file(dir->d_name);
			if (file.compare(".") !=0 && file.compare("..") != 0)
			{
				newsFiles.push_back(file);
			}
		}
	}
	std::sort(newsFiles.begin(), newsFiles.end());
	return newsFiles;
}
