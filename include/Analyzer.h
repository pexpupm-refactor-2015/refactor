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
	Analyzer(std::string ruta);
	void setNews(const std::string& ruta);
	std::string groupNews();
	std::string groupGeneralNews();
	std::string toString()const;
private:
	bool mustContinueParsing(const std::ifstream& file,
                          int& group_desc,
                          int& new_desc,
                          bool& more_files) const;
	std::string zeroPadding(const int& nunber, const int& size) const;
	bool continueParsing() const;
	void sortNews();
	void parseNews(std::ifstream& f,
								const std::string& news_path);
	const std::string getFinalPath(const std::string& ruta_noticias,
																	const int& xshift,
																	const int& yshift) const;
	bool exists(std::list<NamedEntity> es, NamedEntity e) const;
	std::string groupToString(const std::list<NamedEntity> group[],
																											const std::list<New>& processed_news_list,
																											const std::list<New>& original_news_list) const;
	void cleanDuplicatedEntities(std::list<NamedEntity>& list);
	std::list<New> m_news_list;
	std::string m_path;
};

#endif /* _ANALYZER_H_ */
