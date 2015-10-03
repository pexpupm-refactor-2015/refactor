#include <fstream>
#include <sstream>
#include "Tuit.h"
#include "JsonTuitParser.h"

const std::string TUITS_TAG = "tuits";
const std::string ID_TAG = "id";
const std::string USER_TAG = "usuario";
const std::string TUIT_TAG = "tuit";

JsonTuitParser::JsonTuitParser() : m_json_root(), m_json_reader()
{
  ;
}

JsonTuitParser::~JsonTuitParser()
{
  ;
}

bool JsonTuitParser::parseFile(const char* tuit_file_path, std::vector<Tuit>& tuit_list)
{
  return parseFile(std::string(tuit_file_path), tuit_list);
}


bool JsonTuitParser::parseFile(const std::string& tuit_file_path,
                               std::vector<Tuit>& tuit_list)
{
  std::ifstream t(tuit_file_path.c_str());
  std::stringstream buffer;
  buffer << t.rdbuf();
  return parseString(buffer.str(), tuit_list, tuit_file_path);
}

bool JsonTuitParser::parseString(const std::string& tuits_json_string,
                                 std::vector<Tuit>& tuit_list,
                                 const std::string& tuit_file_path)
{
  if(!m_json_reader.parse(tuits_json_string, m_json_root, false)) {
    return false;
  }
 
  const Json::Value array = m_json_root[TUITS_TAG];
 
  for(unsigned int index = 0; index < array.size(); ++index) {
    const Json::Value id = array[index][ID_TAG];
    const Json::Value user = array[index][USER_TAG];
    const Json::Value body = array[index][TUIT_TAG];
    Tuit tuit(id.asString(), user.asString(), body.asString(), tuit_file_path);
    tuit_list.push_back(tuit);
  }

  return true;
}