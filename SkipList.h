#pragma once
#include"nodes.h"
#include<mutex>
#include <fstream>
#include<cmath>
#include <cstdlib>
#include <cstring>
using namespace std;
template<typename K, typename V>
class SkipList//跳表
{
public:
	SkipList(int max_level);
	~SkipList();
	bool insert_element(K,V);//增
	bool delete_element(K);//删
	bool update_element(K,V);//改
	V search_element(K);//查
	nodes<K, V>* create_elemenmt(K, V, int level);//创建跳表节点
	int size();
	void display();//显示跳表
	int get_rand_level();
	void dump_file();//写入磁盘
	void load_file();//从磁盘加载
	void getKV(string& s,string* key,string*  value);//解析从磁盘获取的数据
private:
	static std::mutex mux;//锁，确保线程同步 
	int max_level;//允许的最高级索引
	int skiplist_current_level;//跳表当前的最高索引
	nodes<K, V>* header;//连表的头节点
	int nodes_element;//跳表的元素个数
	// file operator
	std::ofstream _file_writer;
	std::ifstream _file_reader;
};

