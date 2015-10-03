/*
 * JSON_TUIT_PARSER.h
 */
#ifndef _JSON_TUIT_PARSER_H_
#define _JSON_TUIT_PARSER_H_

#include <vector>
#include "Tuit.h"

#include "json/json.h"

class JsonTuitParser
{
public:
  JsonTuitParser();
  ~JsonTuitParser();
  bool parseFile(const char* tuit_file_path, std::vector<Tuit>& tuit_list);
  bool parseFile(const std::string& tuit_file_path, std::vector<Tuit>& tuit_list);
  bool parseString(const std::string& tuit_json_string, std::vector<Tuit>& tuit_list,
                   const std::string& tuit_file_path);
 private:
  Json::Value m_json_root;
  Json::Reader m_json_reader;
};

#endif /* _TUIT_H_ */
