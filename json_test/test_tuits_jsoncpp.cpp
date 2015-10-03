#include <iostream>
#include "json/json.h"

int main()
{
  std::string json_example = "{\
\"tuits\": [                   \
   {                           \
      \"id\": 34343,                              \
      \"usuario\": \"@pepe_perez\",                                         \
      \"tuit\": \"Las Fuerzas Armadas Revolucionarias de Colombia ( FARC ) \
pretenden intercambiar a 45 personas cautivas por medio millar de rebeldes \
presos en Colombia.\"\
   },\
   {                           \
      \"id\": 34344,                              \
      \"usuario\": \"@juan_garcia\",                                         \
      \"tuit\": \"Las Fuerzas Armadas Revolucionarias de Colombia ( FARC ) \
plantean un alto el fuego provisional.\"\
   }\
]\
}";
  
  Json::Value root;
  Json::Reader reader;
  bool parsedSuccess = reader.parse(json_example, root, false);
 
  if(!parsedSuccess) {
    std::cout<<"Failed to parse JSON"<< std::endl <<reader.getFormattedErrorMessages()
        <<std::endl;
    return 1;
  }
 
  const Json::Value array = root["tuits"];
 
  for(unsigned int index = 0; index < array.size(); ++index) { 
    std::cout<<"Element " <<index <<" in array: " <<array[index] <<std::endl;
  }

  std::cout << "Json Example pretty print: " <<std::endl << 
    root.toStyledString()<<std::endl;

  return 0;
}
