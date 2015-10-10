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
  
  std::vector<std::string> newsFiles = getFilesFromDir(news_path);

  for (auto file : newsFiles)
  {
  	std::string final_path = news_path + "/" + file;
  	if (final_path.find(".txt"))
  	{
  		parseNewsFromTxtFile(final_path, restriction_path, news_list);
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
