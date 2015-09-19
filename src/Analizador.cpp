/*
 * Analizador.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Analizador.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string.h>
#include "Noticia.h"

const std::string NEWS_FILE_PREFIX = "/newC";
const std::string NEWS_FILE_SUFFIX = ".ES.txt";
const std::string NEWS_PATH = "/news";
const std::string RESTRICTED_WORDS = "/ES_stopList.txt";

Analizador::Analizador() :
		noticias(), ruta()
{
	;
}

Analizador::Analizador(std::string ruta) :
		ruta(ruta)
{
	this->setNoticias(ruta);
}

const std::string Analizador::getRutaFinal(const std::string& ruta_noticias,
										   const int& xshift,
										   const int& yshift) const {
	std::string nombreArchivo = NEWS_FILE_PREFIX + this->rellenarCeros(xshift, 5) + "_"
			+ this->rellenarCeros(yshift, 3) + NEWS_FILE_SUFFIX;
    return ruta_noticias + nombreArchivo;
}

void Analizador::parseNews(std::ifstream& f,
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
		Noticia n(titulo, cuerpo, restricted_words_path);
		titulo = "";
		cuerpo = "";
		this->noticias.push_front(n);
	}
}

void Analizador::setNoticias(const std::string& ruta) {

	std::string rutaRestricciones = ruta + RESTRICTED_WORDS;
	std::string rutaNoticias = ruta + NEWS_PATH;

	int x = 1;
	int y = 1;
	bool continue_parsing = true;
	bool more_files = false;
	std::ifstream f;

	do {
		std::string rutaFinal = getRutaFinal(rutaNoticias, x, y);
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

std::string Analizador::agruparNoticias() {

	this->ordenarNoticias();

	std::list<Noticia> lista = this->noticias;
	std::string salida = "";
	std::string entidad = "";
	for (std::list<Noticia>::iterator it = lista.begin(); it != lista.end();
			it++) {

		Noticia n = *it;
		if (entidad.compare(n.getMasFrecuente().getEntidadNombrada()) == 0) {
			salida = salida + "*[" + n.getTitulo() + "]\n";
		} else {
			entidad = n.getMasFrecuente().getEntidadNombrada();
			salida = salida + "\n" + entidad + "\n" + "*[" + n.getTitulo()
					+ "]\n";
		}
	}

	return salida;
}

std::string Analizador::agruparNoticiasGeneral() {

	std::list<EntidadNombrada> agrupacion[this->noticias.size()];

	this->ordenarNoticias();

	std::list<Noticia> ln1 = this->noticias;
	std::list<Noticia> ln2 = this->noticias;

	std::string salida = "";
	std::string agrupaciones = "";
	Noticia n2;
	EntidadNombrada en;
	EntidadNombrada en2;
	EntidadNombrada en3;

	unsigned int c = 0;
	for (std::list<Noticia>::iterator it1 = ln1.begin(); it1 != ln1.end();
			it1++) {

		bool sola = true;
		Noticia& n = *it1;
		for (std::list<Noticia>::iterator it2 = ln1.begin(); it2 != ln1.end();
				it2++) {
			Noticia& n2 = *it2;

			if ((distance(it1, it2) != 0)) {
				if ((n.esAgrupable(n2)) || (n2.esAgrupable(n))) {
					agrupacion[c].push_back(n.getMasFrecuente());
					agrupacion[c].push_back(n2.getMasFrecuente());
					it2 = ln1.erase(it2);
					sola = false;
				}
			}
		}

		for (std::list<EntidadNombrada>::iterator it3 = agrupacion[c].begin();
				it3 != agrupacion[c].end(); it3++) {
			en2 = *it3;
			for (std::list<EntidadNombrada>::iterator it4 =
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
		for (std::list<EntidadNombrada>::iterator it4 = agrupacion[c].begin();
				it4 != agrupacion[c].end(); it4++) {

			EntidadNombrada& en3 = *it4;

			for (std::list<Noticia>::iterator it5 = ln2.begin();
					it5 != ln2.end(); it5++) {
				Noticia& n = *it5;

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

std::string Analizador::rellenarCeros(int n, int size) const {
	std::stringstream ss;
	ss << n;
	std::string aux = ss.str();
	for (int i = aux.size(); i < size; i++) {
		aux = "0" + aux;
	}
	return aux;
}

void Analizador::ordenarNoticias() {

	Noticia aux[this->noticias.size()];
	int c = 0;
	for (std::list<Noticia>::iterator it = this->noticias.begin();
			it != this->noticias.end(); it++) {
		Noticia n = *it;
		aux[c] = n;
		c++;
	}

	int tam = this->noticias.size();
	Noticia temp;
	for (int i = 1; i < tam; i++) {
		for (int j = 0; j < tam - 1; j++) {
			if (aux[j].getMasFrecuente().getEntidadNombrada()
					> aux[j + 1].getMasFrecuente().getEntidadNombrada()) {
				temp = aux[j];
				aux[j] = aux[j + 1];
				aux[j + 1] = temp;
			}
		}
	}

	this->noticias.clear();
	for (int i = 0; i < tam; i++) {
		this->noticias.push_back(aux[i]);
	}
}

bool Analizador::existe(std::list<EntidadNombrada> es,
		EntidadNombrada e) const {
	bool salida = false;
	EntidadNombrada aux;
	for (std::list<EntidadNombrada>::iterator it = es.begin(); it != es.end();
			it++) {
		aux = *it;
		if (aux.getEntidadNombrada().compare(e.getEntidadNombrada()) == 0) {
			salida = true;
		}
	}
	return salida;
}

std::string Analizador::toString() const {
	std::list<Noticia> lista = this->noticias;
	std::string salida = "";
	Noticia aux;
	for (std::list<Noticia>::iterator it = lista.begin(); it != lista.end();
			it++) {
		aux = *it;
		if (salida == "") {
			salida = salida + "Ruta del directorio: " + this->ruta + "\n\n";
		}
		salida = salida + "Titulo: " + aux.getTitulo() + "\n\n";
	}
	return salida;
}

