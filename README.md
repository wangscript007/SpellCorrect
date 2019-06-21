# SpellCorrect  

## v1离线版

读取txt生成词典和索引文件。

## v2在线版

增加网络框架（用的v4版本）；

在基础上增加业务逻辑，主要在MyTask中实现（在statistic中有bug，在v3中修复）。

## v3在线版

修复statsitc中的只能查询一部分索引，未检索全部索引的bug；

将main函数中加入SpellCorrect类，解除threadpool全局变量，建立抽象层。

## v3.5在线版

以json数据格式传输，每次返回三个候选词；

主要修改SocketIO文件，修改协议为小火车协议；

修改客户端文件，使之与服务端匹配火车协议，并对json数据解包；

结果中会多次push同一个单词，修复bug，修改了MyTask.hpp；

删除重复字母的重复查询索引，见MyTask.cc