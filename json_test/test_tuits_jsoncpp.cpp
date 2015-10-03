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
    std::cout<< "----------------------------------------------" <<std::endl;
    std::cout<<"Element " <<index <<" in array: " <<array[index] <<std::endl;
    const Json::Value id = array[index]["id"];
    const Json::Value tuit = array[index]["tuit"];
    const Json::Value user = array[index]["usuario"];
    std::cout<<" * Element [" << index <<"] id " << id << std::endl;
    std::cout<<" * Element [" << index <<"] usuario " << user << std::endl;
    std::cout<<" * Element [" << index <<"] tuit " << tuit << std::endl;
    std::cout<< "----------------------------------------------" <<std::endl;
  }

  std::cout << "Json Example pretty print: " <<std::endl << 
    root.toStyledString()<<std::endl;

  return 0;
}
