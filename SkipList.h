#pragma once
#include"nodes.h"
#include<mutex>
#include <fstream>
#include<cmath>
#include <cstdlib>
#include <cstring>
using namespace std;
template<typename K, typename V>
class SkipList//����
{
public:
	SkipList(int max_level);
	~SkipList();
	bool insert_element(K,V);//��
	bool delete_element(K);//ɾ
	bool update_element(K,V);//��
	V search_element(K);//��
	nodes<K, V>* create_elemenmt(K, V, int level);//��������ڵ�
	int size();
	void display();//��ʾ����
	int get_rand_level();
	void dump_file();//д�����
	void load_file();//�Ӵ��̼���
	void getKV(string& s,string* key,string*  value);//�����Ӵ��̻�ȡ������
private:
	static std::mutex mux;//����ȷ���߳�ͬ�� 
	int max_level;//�������߼�����
	int skiplist_current_level;//����ǰ���������
	nodes<K, V>* header;//�����ͷ�ڵ�
	int nodes_element;//�����Ԫ�ظ���
	// file operator
	std::ofstream _file_writer;
	std::ifstream _file_reader;
};

