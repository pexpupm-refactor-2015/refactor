#include <fstream>
#include <sstream>
#include "Tuit.h"
#include "JsonTuitParser.h"

const std::string TUITS_TAG = "tuits";
const std::string ID_TAG = "id";
const std::string USER_TAG = "usuario";
const std::string TUIT_TAG = "tuit";

const std::string JSON_TUITS_FILE = "tuits.json";

bool JsonTuitParser::parseFromPath(const char* tuit_dir,
                                   std::vector<Tuit>& tuit_list)
{
  return parseFromPath(std::string(tuit_dir), tuit_list);
}


bool JsonTuitParser::parseFromPath(const std::string& tuit_dir,
                                   std::vector<Tuit>& tuit_list)
{
  std::string json_file = tuit_dir + "/" + JSON_TUITS_FILE;
  return parseFile(json_file, tuit_list);
}

bool JsonTuitParser::parseFile(const std::string& json_file,
                               std::vector<Tuit>& tuit_list)
{
  std::ifstream t(json_file.c_str());
  std::stringstream buffer;
  buffer << t.rdbuf();
  return parseString(buffer.str(), tuit_list, json_file);
}

bool JsonTuitParser::parseString(const std::string& tuits_json_string,
                                 std::vector<Tuit>& tuit_list,
                                 const std::string& tuit_file_path)
{
  Json::Value json_root;
  Json::Reader json_reader;

  if(!json_reader.parse(tuits_json_string, json_root, false)) {
    return false;
  }

  const Json::Value array = json_root[TUITS_TAG];
 
  for(unsigned int index = 0; index < array.size(); ++index) {
    const Json::Value id = array[index][ID_TAG];
    const Json::Value user = array[index][USER_TAG];
    const Json::Value title = array[index][TUIT_TAG];
    Tuit tuit(id.asString(), user.asString(), " " + title.asString() + " ",
              tuit_file_path);
    tuit_list.push_back(tuit);
  }

  return true;
}
