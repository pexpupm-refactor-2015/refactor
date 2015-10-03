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
  static bool parseFile(const std::string& tuit_file_path,
                        std::vector<Tuit>& tuit_list);
  static bool parseFromPath(const char* tuit_file_path,
                            std::vector<Tuit>& tuit_list);
  static bool parseFromPath(const std::string& tuit_file_path,
                            std::vector<Tuit>& tuit_list);
  static bool parseString(const std::string& tuit_json_string,
                          std::vector<Tuit>& tuit_list,
                          const std::string& tuit_file_path);
};

#endif /* _TUIT_H_ */
