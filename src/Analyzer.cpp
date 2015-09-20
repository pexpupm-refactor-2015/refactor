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

std::string Analyzer::groupGeneralNews()
{
	std::list<NamedEntity> group[m_news_list.size()];
	sortNews();

	std::list<New> ln1 = m_news_list;
	std::list<New> ln2 = m_news_list;

	std::string output = "";
	std::string groups = "";
	NamedEntity entity2;
	NamedEntity entity3;

	unsigned int c = 0;
	for (std::list<New>::iterator it1 = ln1.begin(); it1 != ln1.end(); it1++)
 {
		bool alone = true;
		New& n = *it1;
		for (std::list<New>::iterator it2 = ln1.begin(); it2 != ln1.end(); it2++)
  {
			New& n2 = *it2;

			if ((distance(it1, it2) != 0))
   {
				if ((n.canBeGrouped(n2)) || (n2.canBeGrouped(n)))
    {
					group[c].push_back(n.getMoreFrequent());
					group[c].push_back(n2.getMoreFrequent());
					it2 = ln1.erase(it2);
					alone = false;
				}
			}
		}

		for (std::list<NamedEntity>::iterator it3 = group[c].begin();
				it3 != group[c].end(); it3++)
  {
			entity2 = *it3;
			for (std::list<NamedEntity>::iterator it4 =
					group[c].begin(); it4 != group[c].end(); it4++) {
				entity3 = *it4;
				if ((entity2.equals(entity3)) && (distance(it3, it4) != 0)) {
					it4 = group[c].erase(it4);
				}
			}
		}
		if (alone) {
			group[c].push_back(n.getMoreFrequent());
			it1 = ln1.erase(it1);
		}
		c++;
	}

	for (unsigned int c = 0; c < ln1.size(); c++)
	{
		for (std::list<NamedEntity>::iterator it4 = group[c].begin();
				it4 != group[c].end(); it4++) {

			NamedEntity& entity3 = *it4;

			for (std::list<New>::iterator it5 = ln2.begin();
					it5 != ln2.end(); it5++)
			{
				New& n = *it5;

				if (n.getMoreFrequent().equals(entity3)) {
					if (groups == "") {
						groups = groups + "[" + n.getTitle()
								+ "]\n";
					} else {
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
