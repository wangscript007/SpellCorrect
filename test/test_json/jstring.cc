#include <iostream>
#include <string>
#include <json/json.h>
#include <sstream>

using namespace std;


int main()
{
    Json::Value root;

    root["word1"] = Json::Value("word");
    root["word2"] = Json::Value("world");
    root["word3"] = Json::Value("work");

    Json::FastWriter fw;
    stringstream res;
    res << fw.write(root);
    string ans;
    res >> ans;
    cout << ans << endl;
    return 0;
}
