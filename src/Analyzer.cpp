/*
 * Analyzer.cpp
 */
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string.h>
#include "Analyzer.h"
#include "New.h"

const std::string NEWS_FILE_PREFIX = "/newC";
const std::string NEWS_FILE_SUFFIX = ".ES.txt";
const std::string NEWS_PATH = "/news";
const std::string RESTRICTED_WORDS = "/ES_stopList.txt";

Analyzer::Analyzer() :
		m_news_list(), m_path()
{
	;
}

Analyzer::Analyzer(std::string path) :
		m_path(path)
{
	setNews(path);
}

const std::string Analyzer::getFinalPath(const std::string& news_path,
                                         const int& xshift,
                                         const int& yshift) const
{
  std::string file_name = NEWS_FILE_PREFIX + zeroPadding(xshift, 5)
     + "_" + zeroPadding(yshift, 3) + NEWS_FILE_SUFFIX;
  return news_path + file_name;
}

void Analyzer::parseNews(std::ifstream& f,
                         const std::string& restricted_words_path)
{
	std::string collector = "";
	std::string title = "";
	std::string body = "";
	if (f.is_open())
	{
		while (!f.eof())
		{
			getline(f, collector, '\n');
			if (title == "") {
				title = title + " " + collector;
			} else {
				body = body + " " + collector;
			}
		}
		New added_new(title, body, restricted_words_path);
		m_news_list.push_front(added_new);
	}
}

bool Analyzer::mustContinueParsing(const std::ifstream& file,
                                   int& group_desc,
                                   int& new_desc,
                                   bool& more_files) const
{
 bool continue_parsing = true;
	if (new_desc >= 999)
	{
		if (!more_files)
		{
			continue_parsing = false;
		}
		else {
			group_desc++;
			new_desc = 0;
			more_files = false;
		}
	}
	if (file.is_open())
	{
		more_files = true;
	}
	if (group_desc >= 99999)
	{
		continue_parsing = false;
	}
	return continue_parsing;
}

void Analyzer::setNews(const std::string& path)
{
	std::string restriction_path = path + RESTRICTED_WORDS;
	std::string news_path = path + NEWS_PATH;

	int group_desc = 1;
	int new_desc = 1;
	bool continue_parsing = true;
	bool more_files = false;
	std::ifstream news_file;
	do
	{
		std::string final_path = getFinalPath(news_path, group_desc, new_desc);
		std::ifstream news_file;
		news_file.open(final_path.c_str(), std::ofstream::in);
		parseNews(news_file, restriction_path);
		new_desc++;
  continue_parsing = mustContinueParsing(news_file, group_desc, new_desc,
                                         more_files);
		news_file.close();
	}
	while (continue_parsing);
}

std::string Analyzer::groupNews()
{
	sortNews();

	std::string output = "";
	std::string entity = "";
	std::list<New>::iterator it;
	for (it = m_news_list.begin(); it != m_news_list.end(); it++)
 {
		New new1 = *it;
		if (entity.compare(new1.getMoreFrequent().getNamedEntity()) == 0)
  {
			output = output + "*[" + new1.getTitle() + "]\n";
		}
  else {
			entity = new1.getMoreFrequent().getNamedEntity();
			output = output + "\n" + entity + "\n" + "*[" + new1.getTitle() + "]\n";
		}
	}
	return output;
}

std::string 
Analyzer::groupToString(const std::list<NamedEntity> group[],
                        const std::list<New>& processed_news_list,
                        const std::list<New>& original_news_list) const
{
	std::string output;
	std::string groups;

	for (unsigned int c = 0; c < processed_news_list.size(); c++)
	{
		for (std::list<NamedEntity>::const_iterator it4 = group[c].begin();
				it4 != group[c].end(); it4++)
		{
			const NamedEntity& entity3 = *it4;

			std::list<New>::const_iterator news_it;
			for (news_it = original_news_list.begin();
									news_it != original_news_list.end();
									news_it ++)
			{
				const New& n = *news_it;
				if (n.getMoreFrequent().equals(entity3))
				{
					if (groups == "")
					{
						groups = groups + "[" + n.getTitle()
								+ "]\n";
					}
					else
					{
						groups = groups + "   *[" + n.getTitle()
								+ "]\n";
					}
				}
			}
		}
		output = output + groups + "\n";
		groups = "";
	}
 return output;
}

void Analyzer::cleanDuplicatedEntities(std::list<NamedEntity>& list)
{
	for (std::list<NamedEntity>::iterator it3 = list.begin();
      it3 != list.end(); it3++)
 {
		NamedEntity entity = *it3;
		for (std::list<NamedEntity>::iterator it4 =
				list.begin(); it4 != list.end(); it4++)
		{
			NamedEntity entity2 = *it4;
			if ((entity.equals(entity2)) && (distance(it3, it4) != 0))
			{
				it4 = list.erase(it4);
			}
		}
	}
}

std::string Analyzer::groupGeneralNews()
{
	sortNews();
	std::list<NamedEntity> group[m_news_list.size()];
	std::list<New> processed_news_list = m_news_list;
	std::list<New> original_news_list = m_news_list;
	unsigned int c = 0;

 std::list<New>::iterator news_it;
	for (news_it = processed_news_list.begin();
						news_it != processed_news_list.end(); 
						news_it++)
 {
		bool alone = true;
		New& n = *news_it;
  std::list<New>::iterator news_it2;
		for (news_it2 = processed_news_list.begin();
							news_it2 != processed_news_list.end(); 
							news_it2++)
  {
			New& n2 = *news_it2;

			if ((distance(news_it, news_it2) != 0))
   {
				if ((n.canBeGrouped(n2)) || (n2.canBeGrouped(n)))
    {
					group[c].push_back(n.getMoreFrequent());
					group[c].push_back(n2.getMoreFrequent());
					news_it2 = processed_news_list.erase(news_it2);
					alone = false;
				}
			}
		}
  cleanDuplicatedEntities(group[c]);
		if (alone)
		{
			group[c].push_back(n.getMoreFrequent());
			news_it = processed_news_list.erase(news_it);
		}
		c++;
	}
	return groupToString(group, processed_news_list, original_news_list);
}

std::string Analyzer::zeroPadding(const int& number, const int& size) const
{
	std::stringstream ss;
	ss << number;
	std::string aux = ss.str();
	for (int i = aux.size(); i < size; i++)
	{
		aux = "0" + aux;
	}
	return aux;
}

void Analyzer::sortNews()
{
	New aux[m_news_list.size()];
	int c = 0;
	for (std::list<New>::iterator it = m_news_list.begin();
			it != m_news_list.end(); it++) {
		New n = *it;
		aux[c] = n;
		c++;
	}

	int news_list_size = m_news_list.size();
	New temp;
	for (int i = 1; i < news_list_size; i++)
	{
		for (int j = 0; j < news_list_size - 1; j++)
		{
			if (aux[j].getMoreFrequent().getNamedEntity()
					> aux[j + 1].getMoreFrequent().getNamedEntity())
			{
				temp = aux[j];
				aux[j] = aux[j + 1];
				aux[j + 1] = temp;
			}
		}
	}

	m_news_list.clear();

	for (int i = 0; i < news_list_size; i++)
	{
		m_news_list.push_back(aux[i]);
	}
}

bool Analyzer::exists(std::list<NamedEntity> es, NamedEntity e) const
{
	bool output = false;
	NamedEntity aux;
	for (std::list<NamedEntity>::iterator it = es.begin(); it != es.end();
			it++)
	{
		aux = *it;
		if (aux.getNamedEntity().compare(e.getNamedEntity()) == 0)
		{
			output = true;
		}
	}
	return output;
}

std::string Analyzer::toString() const
{
	std::string output = "";
	New aux;
	std::list<New>::const_iterator it;
	for (it = m_news_list.begin(); it != m_news_list.end(); it++)
	{
		aux = *it;
		if (output == "") {
			output = output + "Ruta del directorio: " + m_path + "\n\n";
		}
		output = output + "Titulo: " + aux.getTitle() + "\n\n";
	}
	return output;
}
