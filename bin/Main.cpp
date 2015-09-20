/*
 * Main.cpp
 *
 *  Created on: 27-dic-2012
 *      Author: Alvaro
 */

#include "iostream"
#include "NamedEntity.h"
#include "cstdio"
#include "New.h"
#include "Analyzer.h"
#include <iterator>

int main() {

	Analyzer a1("data");

	std::cout << "T�tulo noticias\n\n";
	std::cout << a1.toString();
	std::cout << "\n\n";
	std::cout << "Agrupaci�n 1\n\n";
	std::cout << a1.groupNews();
	std::cout << "\n\n";
	std::cout << "Agrupaci�n 2\n\n";
	std::cout << a1.groupGeneralNews();

	return 0;
}
