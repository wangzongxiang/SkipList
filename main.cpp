#include <cstdio>
#include"SkipList.h"
#include<iostream>
#include<sstream>
#include<cstring>
using namespace std;
int main()
{
    SkipList<int, string>* skipList = new  SkipList<int,string>(6);
    skipList->insert_element(1, "这是");
    skipList->insert_element(3, "一个");
    skipList->insert_element(7, "跳表项目");
    skipList->insert_element(8, "从代码随想录git下来");
    skipList->insert_element(9, "并自己学习和理解");
    skipList->insert_element(19, "收获很多");
    skipList->insert_element(19, "赶快关注吧你会发现详见很晚！");
    cout << "skipList size:" << skipList->size() << std::endl;
    skipList->dump_file();
    skipList->search_element(9);
    skipList->search_element(18);
    skipList->display();
    skipList->delete_element(3);
    skipList->delete_element(7);
    std::cout << "skipList size:" << skipList->size() << std::endl;
    skipList->display();
    return 0;
}