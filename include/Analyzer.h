#ifndef ANALYZER_H_
#define ANALYZER_H_
#include "string"
#include <list>
#include "New.h"

class Analyzer {
public:
	Analyzer();
	Analyzer(std::string ruta);
	std::list<New> getNoticias() const;
	void setNews(const std::string& ruta);
	std::string groupNews();
	std::string groupGeneralNews();
	std::string toString()const;
private:
	std::string zeroPadding(int n, int size) const;
	void sortNews();
	void parseNews(std::ifstream& f,
				   const std::string& news_path);
	const std::string getFinalPath(const std::string& ruta_noticias,
								   const int& xshift,
								   const int& yshift) const;
	bool exists(std::list<NamedEntity> es, NamedEntity e)const;
	std::list<New> m_news_list;
	std::string m_path;
};

#endif /* ANALYZER_H_ */
