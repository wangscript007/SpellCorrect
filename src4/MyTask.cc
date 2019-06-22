#include "MyTask.h"
#include "EditDistance.h"

namespace wd
{

void MyTask::execute()
{
    queryIndexTable();
    insertQueue();
    response();
}

void MyTask::queryIndexTable()
{
    auto indexTable = dic_.getIndexTable();
    
    //去除重复字母 
    set<string> wordChars;
    for(size_t idx = 0; idx != queryWord_.size(); ++idx)
    {
        string ch = string(1, queryWord_[idx]);
        wordChars.insert(ch);
    }

    for(auto ch : wordChars)
    {
        statistic(indexTable[ch]);
    }
    
}

void MyTask::statistic(set<int> & iset)
{
    auto dicTable = dic_.getDict();
    //防止单词重复push，先将位置插入set中过滤一遍
    for(auto &location : iset)
    {
        if(distance(dicTable[location].first) <= 3)
            words_.insert(location);
    }

}

int MyTask::distance(const string & rhs)
{
    EditDistance editdis(queryWord_, rhs);
    return editdis.work();
}

void MyTask::insertQueue()
{
    MyResult tmp;
    auto dicTable = dic_.getDict();
    
    for(auto &it : words_)
    {
        tmp.word_ = dicTable[it].first;
        tmp.iFreq_= dicTable[it].second; 
        tmp.iDist_ = distance(dicTable[it].first);
        resultQue_.push(tmp);
    }
}

void MyTask::response()
{
    Json::Value root;
    root["word1"] = Json::Value(resultQue_.top().word_);
    resultQue_.pop();
    root["word2"] = Json::Value(resultQue_.top().word_);
    resultQue_.pop();
    root["word3"] = Json::Value(resultQue_.top().word_);
 
    Json::FastWriter fw;
    stringstream ss;
    ss << fw.write(root);
    string ans;
    ss >> ans;

    conn_->sendInLoop(ans);
    
    priority_queue<MyResult, vector<MyResult>, MyCompare> temp;
    resultQue_.swap(temp); //清空队列
}

}
