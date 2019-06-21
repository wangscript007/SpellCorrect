#include "MyConf.h"
#include <iostream>

using namespace wd;

int main()
{
    Dictionary * p = Dictionary::createInstance();
    p->init("/home/wj/C++/project/data/dict.dat", "/home/wj/C++/project/data/index.dat");
    
    vector<pair<string, int> > x = p->getDict();

    map<string, set<int> > y = p->getIndexTable();

    for(auto &iter : y)
    {
        for(auto it = iter.second.begin(); it != iter.second.end(); ++it)
        {
            std::cout << *it << " ";
        }
        cout << endl;
    }

    

    return 0;
}
