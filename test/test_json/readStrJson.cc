#include <iostream>
#include <json/json.h>

using namespace std;

const char* str =   
"{\"praenomen\":\"Gaius\",\"nomen\":\"Julius\",\"cognomen\":\"Caezar\","  
"\"born\":-100,\"died\":-44}";  

int main()
{
    Json::Reader reader;
    Json::Value root;

    if(reader.parse(str, root))
    {
        string praenomen = root["praenomen"].asString();
    }


    return 0;
}






