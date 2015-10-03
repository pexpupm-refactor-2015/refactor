#include <iostream>
#include "json/json.h"

int main()
{
  std::string json_example = "{\"cities\": \
[\"Madrid\",                                  \
\"Barcelona\"],                               \
\"country\":                                  \
\"Spain\"}";
  
  Json::Value root;
  Json::Reader reader;
  bool parsedSuccess = reader.parse(json_example, root, false);
 
  if(!parsedSuccess) {
    std::cout<<"Failed to parse JSON"<< std::endl <<reader.getFormattedErrorMessages()
        <<std::endl;
    return 1;
  }
 
  const Json::Value array = root["cities"];
 
  for(unsigned int index = 0; index < array.size(); ++index) { 
    std::cout<<"Element " <<index <<" in array: " <<array[index].asString() <<std::endl;
  }

  const Json::Value notAnArray = root["country"];
 
  if(!notAnArray.isNull()) {
    std::cout<<"Country: " <<notAnArray.asString() <<std::endl;
  }
 
  std::cout << "Json Example pretty print: " <<std::endl << 
    root.toStyledString()<<std::endl;

  return 0;
}
