#ifndef ANALIZADOR_H_
#define ANALIZADOR_H_
#include "string"
#include <list>
#include "Noticia.h"

class Analizador {
public:
	Analizador();
	Analizador(std::string ruta);
	std::list<Noticia> getNoticias() const;
	void setNoticias(const std::string& ruta);
	std::string agruparNoticias();
	std::string agruparNoticiasGeneral();
	std::string toString()const;
private:
	std::string rellenarCeros(int n, int size)const;
	void ordenarNoticias();
	void parseNews(std::ifstream& f,
				   const std::string& news_path);
	const std::string getRutaFinal(const std::string& ruta_noticias,
								   const int& xshift,
								   const int& yshift) const;
	bool existe(std::list<EntidadNombrada> es, EntidadNombrada e)const;
	std::list<Noticia> noticias;
	std::string ruta;
};

#endif /* ANALIZADOR_H_ */
