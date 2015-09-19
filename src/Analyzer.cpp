/*
 * Analyzer.cpp
 *
 */
#include "Analyzer.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string.h>
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
	this->setNews(path);
}

const std::string Analyzer::getFinalPath(const std::string& news_path,
										   const int& xshift,
										   const int& yshift) const
{
  std::string file_name = NEWS_FILE_PREFIX + this->zeroPadding(xshift, 5)
     + "_" + this->zeroPadding(yshift, 3) + NEWS_FILE_SUFFIX;
  return news_path + file_name;
}

void Analyzer::parseNews(std::ifstream& f,
						   const std::string& restricted_words_path)
{
	std::string colector = "";
	std::string titulo = "";
	std::string cuerpo = "";
	if (f.is_open()) {
		while (!f.eof()) {
			getline(f, colector, '\n');
			if (titulo == "") {
				titulo = titulo + " " + colector;
			} else {
				cuerpo = cuerpo + " " + colector;
			}
		}
		New n(titulo, cuerpo, restricted_words_path);
		titulo = "";
		cuerpo = "";
		m_news_list.push_front(n);
	}
}

void Analyzer::setNews(const std::string& ruta) {

	std::string rutaRestricciones = ruta + RESTRICTED_WORDS;
	std::string rutaNews = ruta + NEWS_PATH;

	int x = 1;
	int y = 1;
	bool continue_parsing = true;
	bool more_files = false;
	std::ifstream f;

	do {
		std::string rutaFinal = getFinalPath(rutaNews, x, y);
		std::ifstream f;
		f.open(rutaFinal.c_str(), std::ofstream::in);
		parseNews(f, rutaRestricciones);
		y++;
		if (y >= 999) {
			if (!more_files) {
				continue_parsing = false;
			} else {
				x++;
				y = 0;
				more_files = false;
			}
		}
		if (f.is_open()) {
			more_files = true;
		}
		if (x >= 99999) {
			continue_parsing = false;
		}
		f.close();
	} while (continue_parsing);
}

std::string Analyzer::groupNews() {

	this->sortNews();

	std::string output = "";
	std::string entity = "";
	std::list<New>::iterator it;
	for (it = m_news_list.begin(); it != m_news_list.end(); it++) {

		New n = *it;
		if (entity.compare(n.getMasFrecuente().getNamedEntity()) == 0) {
			output = output + "*[" + n.getTitulo() + "]\n";
		} else {
			entity = n.getMasFrecuente().getNamedEntity();
			output = output + "\n" + entity + "\n" + "*[" + n.getTitulo()
					+ "]\n";
		}
	}

	return output;
}

std::string Analyzer::groupGeneralNews() {

	std::list<NamedEntity> agrupacion[m_news_list.size()];

	this->sortNews();

	std::list<New> ln1 = this->m_news_list;
	std::list<New> ln2 = this->m_news_list;

	std::string salida = "";
	std::string agrupaciones = "";
	New n2;
	NamedEntity en;
	NamedEntity en2;
	NamedEntity en3;

	unsigned int c = 0;
	for (std::list<New>::iterator it1 = ln1.begin(); it1 != ln1.end();
			it1++) {

		bool sola = true;
		New& n = *it1;
		for (std::list<New>::iterator it2 = ln1.begin(); it2 != ln1.end();
				it2++) {
			New& n2 = *it2;

			if ((distance(it1, it2) != 0)) {
				if ((n.esAgrupable(n2)) || (n2.esAgrupable(n))) {
					agrupacion[c].push_back(n.getMasFrecuente());
					agrupacion[c].push_back(n2.getMasFrecuente());
					it2 = ln1.erase(it2);
					sola = false;
				}
			}
		}

		for (std::list<NamedEntity>::iterator it3 = agrupacion[c].begin();
				it3 != agrupacion[c].end(); it3++) {
			en2 = *it3;
			for (std::list<NamedEntity>::iterator it4 =
					agrupacion[c].begin(); it4 != agrupacion[c].end(); it4++) {
				en3 = *it4;
				if ((en2.esIgual(en3)) && (distance(it3, it4) != 0)) {
					it4 = agrupacion[c].erase(it4);
				}
			}
		}
		if (sola) {
			agrupacion[c].push_back(n.getMasFrecuente());
			it1 = ln1.erase(it1);
		}

		c++;
	}

	for (unsigned int c = 0; c < ln1.size(); c++) {
		for (std::list<NamedEntity>::iterator it4 = agrupacion[c].begin();
				it4 != agrupacion[c].end(); it4++) {

			NamedEntity& en3 = *it4;

			for (std::list<New>::iterator it5 = ln2.begin();
					it5 != ln2.end(); it5++) {
				New& n = *it5;

				if (n.getMasFrecuente().esIgual(en3)) {
					if (agrupaciones == "") {
						agrupaciones = agrupaciones + "[" + n.getTitulo()
								+ "]\n";
					} else {
						agrupaciones = agrupaciones + "   *[" + n.getTitulo()
								+ "]\n";
					}
				}
			}
		}
		salida = salida + agrupaciones + "\n";
		agrupaciones = "";
	}

	return salida;
}

std::string Analyzer::zeroPadding(int n, int size) const {
	std::stringstream ss;
	ss << n;
	std::string aux = ss.str();
	for (int i = aux.size(); i < size; i++) {
		aux = "0" + aux;
	}
	return aux;
}

void Analyzer::sortNews() {

	New aux[this->m_news_list.size()];
	int c = 0;
	for (std::list<New>::iterator it = m_news_list.begin();
			it != m_news_list.end(); it++) {
		New n = *it;
		aux[c] = n;
		c++;
	}

	int tam = m_news_list.size();
	New temp;
	for (int i = 1; i < tam; i++) {
		for (int j = 0; j < tam - 1; j++) {
			if (aux[j].getMasFrecuente().getNamedEntity()
					> aux[j + 1].getMasFrecuente().getNamedEntity()) {
				temp = aux[j];
				aux[j] = aux[j + 1];
				aux[j + 1] = temp;
			}
		}
	}

	m_news_list.clear();
	for (int i = 0; i < tam; i++) {
		m_news_list.push_back(aux[i]);
	}
}

bool Analyzer::exists(std::list<NamedEntity> es,
		NamedEntity e) const {
	bool salida = false;
	NamedEntity aux;
	for (std::list<NamedEntity>::iterator it = es.begin(); it != es.end();
			it++) {
		aux = *it;
		if (aux.getNamedEntity().compare(e.getNamedEntity()) == 0) {
			salida = true;
		}
	}
	return salida;
}

std::string Analyzer::toString() const {
	std::string salida = "";
	New aux;
 std::list<New>::const_iterator it;
	for (it = m_news_list.begin(); it != m_news_list.end(); it++) {
		aux = *it;
		if (salida == "") {
			salida = salida + "Ruta del directorio: " + this->m_path + "\n\n";
		}
		salida = salida + "Titulo: " + aux.getTitulo() + "\n\n";
	}
	return salida;
}

