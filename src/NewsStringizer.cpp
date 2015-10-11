/*
 * NewsStringizer.cpp
 */
#include "NewsStringizer.h"

std::string NewsStringizer::titlesToString(const std::list<New*>& news_list)
{
  std::string output = "";
  std::list<New*>::const_iterator it;
  for (it = news_list.begin(); it != news_list.end(); it++) {
    output = output + "Titulo: " + (**it).getTitle() + "\n\n";
  }
  return output;
}

std::string NewsStringizer::titlesAndBodiesToString(const std::list<New*>& news_list)
{
  std::string output = "";
  std::list<New*>::const_iterator it;
  for (it = news_list.begin(); it != news_list.end(); it++) {
    output = output + "Titulo: " + (**it).getTitle() + "\n\n";
    output = output + "Cuerpo: " + (**it).getBody() + "\n\n";
  }
  return output;
}

