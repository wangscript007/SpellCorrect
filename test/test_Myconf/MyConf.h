#pragma once
#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace wd
{

class Dictionary
{
public:
    static Dictionary * createInstance()
    {
        if(nullptr == pInstance_){
            pInstance_ = new Dictionary();       
        }   
        return pInstance_;
    }

    static void destroy()
    {
        if(pInstance_){
            delete pInstance_;
        }
    }

    void init(const char * dictEnPath, const char * indexEnPath)
    {
        ifstream ifsDict(dictEnPath);
        string word;
        int wordFreq;
        while(ifsDict >> word >> wordFreq){
            dict_.push_back(make_pair(word, wordFreq));
        }
        ifsDict.close();

        ifstream ifsIndex(indexEnPath);
        string ch;
        while(ifsIndex >> ch)
        {
            string line;
            getline(ifsIndex, line);    //读取字母后面的换行符
            getline(ifsIndex, line);
            stringstream ss(line);
            int num;
            while(ss >> num)
            {
                indexTable_[ch].insert(num);
            }
        }
        ifsIndex.close();
    }

    vector<pair<string, int> > & getDict()
    {
        return dict_;
    }

    map<string, set<int> > & getIndexTable()
    {
        return indexTable_;
    }

private:
    Dictionary() {}
    ~Dictionary() {}

private:
    static Dictionary* pInstance_;
    vector<pair<string, int> > dict_;       //词典
    map<string, set<int> > indexTable_;     //索引表
};

Dictionary* Dictionary::pInstance_ = new Dictionary();  //饱汉模式

}
