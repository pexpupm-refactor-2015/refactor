#include<iostream>
#include<json/writer.h>

int main(void)
{
    Json::Value event;   
    Json::Value vec(Json::arrayValue);
    vec.append(Json::Value(1));
    vec.append(Json::Value(2));
    vec.append(Json::Value(3));

    event["competitors"]["home"]["name"] = "Liverpool";
    event["competitors"]["away"]["code"] = 89223;
    event["competitors"]["away"]["name"] = "Aston Villa";
    event["competitors"]["away"]["code"] = vec;

    std::cout << event << std::endl;

    Json::Value animals;
    Json::Value dogs(Json::arrayValue);
    dogs.append("Cocker");
    dogs.append("Pitbull");
    animals["animals"]["mammals"]["dog"]["race"] = dogs;

    std::cout << animals << std::endl;

    return 0;
}
