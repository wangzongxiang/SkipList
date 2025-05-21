#include "SkipList.h"
#include<iostream>
#include<cstring>
using namespace std;
template<typename K, typename V>
SkipList<K, V>::SkipList(int max_level) {//构造函数
	this->max_level = max_level;
	this->nodes_element = 0;
	this->skiplist_current_level = 0;
	K k;
	V v;
	this->header = new nodes<K,V>(k,v,this->max_level);//每次都是头节点
}

template<typename K, typename V>
SkipList<K, V>::~SkipList() {//析构函数


}

template<typename K, typename V>
bool SkipList<K, V>::insert_element(const K k,const V v)//增
{
	
	this->mux.lock();//上锁操作
	nodes<K, V>* current = this->header;
	nodes<K, V>* update[this->max_level+1];
	memset(update, 0, sizeof(nodes<K, V>*) * (this->max_level + 1));//初始化更新数组
	for (int i = this->skiplist_current_level; i >= 0; i--) {
		while (current->next[i] != NULL && current->next[i]->get_key() < k) {//同级索引中找到第一个比v大的节点
			current = current->next[i];
		}
		update[i] = current;//i级索引中可以在此节点后更新
	}
	current = current->next[0];//链表的下一个元素
	if (current != NULL && current->get_key() == k) {//存在相同的键值对,,没办法插入
		cout << "the K-V have been exited" << endl;
		this->mux.unlock();//解锁操作
		return false;
		
	}
	//不存在这样的键值对，可以插入
	int ran = this->get_rand_level();
	if (ran > this->skiplist_current_level) {//产生了新的索引层级
		for (int i = this->skiplist_current_level + 1; i <= ran; i++) {
			update[i] = this->header;//每一层的索引必然由header开始
		}
		this->skiplist_current_level = ran;//更新索引层级
	}
	nodes<K, V>* nodes = this.create_elemenmt(k,v,ran);
	for (int i = 0; i <= ran; i++) {
		nodes->next[i] = update[i]->next[i];
		update[i].next[i] = nodes;
	}
	cout << "element insert successful" << endl;
	this->nodes_element++;//现存节点数量+1
	this->mux.unlock();//解锁操作
	delete current;
	return true;
}

template<typename K, typename V>
bool SkipList<K, V>::delete_element(const K k)//删
{
	this->mux.lock();//上锁操作
	nodes<K, V>* current = this->header;
	nodes<K, V>* update[this->skiplist_current_level+1];//需要更新的标
	for (int i = this->skiplist_current_level; i >= 0; i--) {
		while (current->next[i] != NULL && current->next[i].get_value() < k) {
			current = current->next[i];
		}
		update[i] = current;
		
	}
	current = current->next[0];
	if (current != NULL && current->get_key() == k) {//存在键值对
		for (int i = 0; i <= this->skiplist_current_level; i++) {
			if (update[i].next[i].get_Key() == k)  update[i].next[i] = current->next[i];//将存在该键值对的索引层级进行修改
			else break;
		}
		while (this->skiplist_current_level >= 0 && this->header[this->skiplist_current_level] == NULL) {//最高层级中不包含实质性的索引
			this->skiplist_current_level--;
		}
		cout << "element has been delete" << endl;
		this->nodes_element--;//跳表元素-1
		this->mux.unlock();//解锁操作
		delete current;
		return true;
	}
	this->mux.unlock();//解锁操作
	delete current;
	return false;
}

template<typename K, typename V>
bool SkipList<K, V>::update_element(const K k,const V v)//改
{
	this->mux.lock();//上锁操作
	nodes<K, V>* current = this->header;
	for (int i = this->skiplist_current_level; i >= 0; i--) {
		while (current->next[i] != NULL && current->next[i].get_key() < k) {
			current = current->next[i];
		}
	}
	current = current->next[0];
	if (current->get_key() == k) {
		current->set_value(v);
		cout << "uopdate the K-V" << endl;
		this->mux.unlock();//解锁操作
		return true;
	}
	cout << "can't uopdate the K-V" << endl;
	this->mux.unlock();//解锁操作
	return false;
}

template<typename K, typename V>
V SkipList<K, V>::search_element(const K k)//查
{
	nodes<K, V>* current = this->header;
	this->mux.lock();//上锁操作
	for (int i = this->skiplist_current_level; i >= 0; i--){
		while (current->next[i] != NULL && current->next[i].get_key() < k) {
			current = current->next[i];
		}
	}
	current = current->next[0];
	if (current->get_key() == k) {
		cout << "find the K-V" << endl;
		this->mux.unlock();//解锁操作
		return current->get_value();
	}
	cout << "unfind the K-V" << endl;
	this->mux.unlock();//解锁操作
	return NULL;
}
template<typename K, typename V>
nodes<K, V>* SkipList<K, V>::create_elemenmt(const K k, const V v, const int level)//创建跳表节点
{
	nodes<K, V>* t = new nodes<K, V>(k, v, level);
	return  t;
}

template<typename K, typename V>
int SkipList<K, V>::size() {
	return this->nodes_element;
}

template<typename K, typename V>
void SkipList<K, V>::display()//显示跳表
{
	for (int i = this->skiplist_current_level; i >= 0; i--) {
		nodes<K, V>* current = this->header;
		while (current->next[i] != NULL) cout << current->next[i].get_value() << "->";
		cout << endl;
	}
}

template<typename K, typename V>
int SkipList<K, V>::get_rand_level()//产生新节点的随机索引层级
{
	int k = 0;
	while (rand() % 2) k++;
	k = k < this->max_level ? k : this->max_level;
	return k;
}

template<typename K, typename V>
void SkipList<K, V>::dump_file()//将当前存储在内存的数据写入磁盘
{
	cout << "ready writing the data into the table1";
	this->_file_writer.open("table1");
	nodes<K, V>* node = this->header->next[0];//真正的第一个有效节点
	while (node != NULL) {
		this->_file_writer << node->get_key() << ":" << node->get_value() << "\n";
		cout << node->get_key() << ":" << node->get_value << ";\n";
		node = node->next[0];
	}
	this->_file_writer.flush();
	this->_file_writer.close();
	return;
}

template<typename K, typename V>
void SkipList<K, V>::load_file()//将存储在磁盘的数据写入内存重新构建跳表
{
	cout << "read reading the data from the table1" << endl;
	this->_file_reader.open("table1");
	string line;//获取一行数据
	string* key = new string();
	string* value = new string();
	while (getline(this->_file_reader,line)) {
		this->getKV(line, key, value);
		if (key == NULL || value == NULL) continue;
		this->insert_element(stoi(*key),*value);
	}
	this->_file_reader.close();
	delete key;
	delete value;
	return;
}


template<typename K, typename V>
void SkipList<K, V>::getKV(string& s, string* key, string* value)
{
	if (s.empty()) {
		return;
	}
	if (s.find(":") == string::npos) {
		return;
	}
	*key = s.substr(0, s.find(":"));
	*value = s.substr(s.find(":") + 1, s.length());
	return;
}



