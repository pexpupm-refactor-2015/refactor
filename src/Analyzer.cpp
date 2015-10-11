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
#include "Tuit.h"
#include "RawTextNewsParser.h"
#include "JsonTuitParser.h"
#include "NewsStringizer.h"
#include<json/writer.h>

Analyzer::Analyzer() :
m_news_list(), m_path()
{
	;
}

Analyzer::Analyzer(std::string path) :
  		m_path(path)
{
	setNews(path);
	setTuits(path);
}

void Analyzer::setNews(const std::string& path)
{
	RawTextNewsParser::parseAllFilesInPath(path, m_news_list);
}

void Analyzer::setTuits(const std::string& path)
{
	std::vector<Tuit> tuit_list;
	if(JsonTuitParser::parseFromPath(path, tuit_list)) {
		std::vector<Tuit>::const_iterator tuit_it = tuit_list.begin();
		for (tuit_it = tuit_list.begin(); tuit_it != tuit_list.end(); tuit_it++) {
			m_news_list.push_back(*tuit_it);
		}
	}
}

std::string Analyzer::groupNews()
{
	sortNews();

	std::string output = "";
	std::string entity = "";
	std::list<New>::iterator it;
	for (it = m_news_list.begin(); it != m_news_list.end(); it++) {
		New new1 = *it;
		if (entity.compare(new1.getMoreFrequent().getNamedEntity()) == 0) {
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
	std::cout << "IPM: groupToString" << std::endl;

	for (unsigned int c = 0; c < processed_news_list.size(); c++) {
		for (std::list<NamedEntity>::const_iterator it4 = group[c].begin();
				it4 != group[c].end(); it4++)
		{
			const NamedEntity& entity3 = *it4;

			std::list<New>::const_iterator news_it;
			for (news_it = original_news_list.begin();
					news_it != original_news_list.end();
					news_it ++) {
				const New& n = *news_it;
				if (n.getMoreFrequent().equals(entity3)) {
					if (groups == "") {
						std::cout << "IPM: new group [" << n.getTitle() << "]" << std::endl;
						groups = groups + "[" + n.getTitle()
                  		+ "]\n";
					}
					else {
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

std::string
Analyzer::groupToStringJson(const std::list<NamedEntity> group[],
		const std::list<New>& processed_news_list,
		const std::list<New>& original_news_list) const
{
	std::string output;
	std::string groups;

	Json::Value jRoot;
	Json::Value jGroups(Json::arrayValue);

	for (unsigned int c = 0; c < processed_news_list.size(); c++)
	{
		Json::Value jGroup;
		bool jGroupEmpty = true;
		for (std::list<NamedEntity>::const_iterator it4 = group[c].begin();
				it4 != group[c].end(); it4++)
		{
			const NamedEntity& entity3 = *it4;

			std::list<New>::const_iterator news_it;
			for (news_it = original_news_list.begin();
					news_it != original_news_list.end();
					news_it ++) {
				const New& n = *news_it;
				if (n.getMoreFrequent().equals(entity3)) {

					jGroup["entidades"].append(n.getMoreFrequent().getNamedEntity());
					if (jGroupEmpty)
					{
						jGroup["titulo"] = n.getTitle();
						jGroupEmpty = false;
						std::cout << "IPM: new group [" << n.getTitle() << "]" << std::endl;
					}
					else
					{
						if (n.getBody().compare("") == 0)
						{
							std::cout << "IPM: new element Tuit [" << n.getTitle() << "]" << std::endl;
							jGroup["elementos"].append((static_cast<const Tuit*>(&n))->toJsonNode());
						}
						else
						{
							std::cout << "IPM: new element Txt[" << n.getTitle() << "]" << std::endl;
					   	jGroup["elementos"].append(n.toJsonNode());
						}
					}
				}
			}
		}
		jGroups.append(jGroup);
		std::cout << "IPM: jGroups.append(jGroup)" << std::endl;
		output = output + groups + "\n";
		groups = "";
	}

	jRoot["grupos"] = jGroups;
	std::cout << jRoot << std::endl;

			//
			//	Json::Value group;
			//	group["titulo"] = "myTitulo";
			//	group["entidades"] = "myEnt";
			//
			//  std::list<New>::const_iterator it;
			//  for (it = m_news_list.begin(); it != m_news_list.end(); it++) {
			////    output = output + "Titulo: " + (*it).getTitle() + "\n\n";
			////    output = output + "Cuerpo: " + (*it).getBody() + "\n\n";
			//  }
			//  for (auto &myNew : m_news_list)
			//  {
			//  	Json::Value group;
			//  	group["titulo"] = myNew.getTitle();
			//
			//  	std::list<NamedEntity> entitiesList = myNew.getEntities();
			//  	Json::Value entities(Json::arrayValue);
			//  	for (auto &entity : entitiesList)
			//  	{
			//  		entities.append(entity.getNamedEntity());
			//  	}
			//  	group["entidades"] = entities;
			//
			//  	Json::Value elements(Json::arrayValue);
			//
			//
			//  	root["grupos"].append(group);
			//  }
			//
			//  std::cout << root << std::endl;

			return output;
}

void Analyzer::cleanDuplicatedEntities(std::list<NamedEntity>& list) const
{
	for (std::list<NamedEntity>::iterator it3 = list.begin();
			it3 != list.end(); it3++) {
		NamedEntity entity = *it3;
		for (std::list<NamedEntity>::iterator it4 = list.begin();
				it4 != list.end(); it4++) {
			NamedEntity entity2 = *it4;
			if ((entity.equals(entity2)) && (distance(it3, it4) != 0)) {
				it4 = list.erase(it4);
			}
		}
	}
}

bool Analyzer::groupPerNew(const New& the_new,
		std::list<NamedEntity>& group,
		std::list<New>& processed_news_list) const
{
	bool alone = true;
	std::list<New>::iterator news_it2;
	for (news_it2 = processed_news_list.begin();
			news_it2 != processed_news_list.end();
			news_it2++) {
		New& n2 = *news_it2;

		if ((the_new != n2)) {
			if ((the_new.canBeGrouped(n2)) || (n2.canBeGrouped(the_new))) {
				group.push_back(the_new.getMoreFrequent());
				group.push_back(n2.getMoreFrequent());
				news_it2 = processed_news_list.erase(news_it2);
				alone = false;
			}
		}
	}
	cleanDuplicatedEntities(group);
	if (alone) {
		group.push_back(the_new.getMoreFrequent());
	}
	return alone;
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
			news_it++) {
		if(groupPerNew(*news_it, group[c], processed_news_list)) {
			news_it = processed_news_list.erase(news_it);
		}
		c++;
	}
	groupToString(group, processed_news_list, original_news_list);
	groupToStringJson(group, processed_news_list, original_news_list);
	return groupToString(group, processed_news_list, original_news_list);
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
	for (int i = 1; i < news_list_size; i++) {
		for (int j = 0; j < news_list_size - 1; j++) {
			if (aux[j].getMoreFrequent().getNamedEntity()
					> aux[j + 1].getMoreFrequent().getNamedEntity()) {
				temp = aux[j];
				aux[j] = aux[j + 1];
				aux[j + 1] = temp;
			}
		}
	}

	m_news_list.clear();

	for (int i = 0; i < news_list_size; i++) {
		m_news_list.push_back(aux[i]);
	}
}

bool Analyzer::exists(std::list<NamedEntity> es, NamedEntity e) const
{
	bool output = false;
	NamedEntity aux;
	for (std::list<NamedEntity>::iterator it = es.begin(); it != es.end(); it++) {
		aux = *it;
		if (aux.getNamedEntity().compare(e.getNamedEntity()) == 0) {
			output = true;
		}
	}
	return output;
}

std::string Analyzer::toString() const
{
	std::string output;
	output = "Ruta del directorio: " + m_path + "\n\n";
	output += NewsStringizer::titlesToString(m_news_list);
	return output;
}

std::string Analyzer::toWideString() const
{
	std::string output;
	output = "Ruta del directorio: " + m_path + "\n\n";
	output += NewsStringizer::titlesAndBodiesToString(m_news_list);
	return output;
}

std::string Analyzer::toJsonString() const
{
	std::string output;

	Json::Value root;
	Json::Value group;
	group["titulo"] = "myTitulo";
	group["entidades"] = "myEnt";

	std::list<New>::const_iterator it;
	for (it = m_news_list.begin(); it != m_news_list.end(); it++) {
		//    output = output + "Titulo: " + (*it).getTitle() + "\n\n";
		//    output = output + "Cuerpo: " + (*it).getBody() + "\n\n";
	}
	for (auto &myNew : m_news_list)
	{
		Json::Value group;
		group["titulo"] = myNew.getTitle();

		std::list<NamedEntity> entitiesList = myNew.getEntities();
		Json::Value entities(Json::arrayValue);
		for (auto &entity : entitiesList)
		{
			entities.append(entity.getNamedEntity());
		}
		group["entidades"] = entities;

		Json::Value elements(Json::arrayValue);


		root["grupos"].append(group);
	}

	std::cout << root << std::endl;

	return output;
}
