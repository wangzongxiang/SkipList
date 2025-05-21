#include "SkipList.h"
#include<iostream>
#include<cstring>
using namespace std;
template<typename K, typename V>
SkipList<K, V>::SkipList(int max_level) {//���캯��
	this->max_level = max_level;
	this->nodes_element = 0;
	this->skiplist_current_level = 0;
	K k;
	V v;
	this->header = new nodes<K,V>(k,v,this->max_level);//ÿ�ζ���ͷ�ڵ�
}

template<typename K, typename V>
SkipList<K, V>::~SkipList() {//��������


}

template<typename K, typename V>
bool SkipList<K, V>::insert_element(const K k,const V v)//��
{
	
	this->mux.lock();//��������
	nodes<K, V>* current = this->header;
	nodes<K, V>* update[this->max_level+1];
	memset(update, 0, sizeof(nodes<K, V>*) * (this->max_level + 1));//��ʼ����������
	for (int i = this->skiplist_current_level; i >= 0; i--) {
		while (current->next[i] != NULL && current->next[i]->get_key() < k) {//ͬ���������ҵ���һ����v��Ľڵ�
			current = current->next[i];
		}
		update[i] = current;//i�������п����ڴ˽ڵ�����
	}
	current = current->next[0];//�������һ��Ԫ��
	if (current != NULL && current->get_key() == k) {//������ͬ�ļ�ֵ��,,û�취����
		cout << "the K-V have been exited" << endl;
		this->mux.unlock();//��������
		return false;
		
	}
	//�����������ļ�ֵ�ԣ����Բ���
	int ran = this->get_rand_level();
	if (ran > this->skiplist_current_level) {//�������µ������㼶
		for (int i = this->skiplist_current_level + 1; i <= ran; i++) {
			update[i] = this->header;//ÿһ���������Ȼ��header��ʼ
		}
		this->skiplist_current_level = ran;//���������㼶
	}
	nodes<K, V>* nodes = this.create_elemenmt(k,v,ran);
	for (int i = 0; i <= ran; i++) {
		nodes->next[i] = update[i]->next[i];
		update[i].next[i] = nodes;
	}
	cout << "element insert successful" << endl;
	this->nodes_element++;//�ִ�ڵ�����+1
	this->mux.unlock();//��������
	delete current;
	return true;
}

template<typename K, typename V>
bool SkipList<K, V>::delete_element(const K k)//ɾ
{
	this->mux.lock();//��������
	nodes<K, V>* current = this->header;
	nodes<K, V>* update[this->skiplist_current_level+1];//��Ҫ���µı�
	for (int i = this->skiplist_current_level; i >= 0; i--) {
		while (current->next[i] != NULL && current->next[i].get_value() < k) {
			current = current->next[i];
		}
		update[i] = current;
		
	}
	current = current->next[0];
	if (current != NULL && current->get_key() == k) {//���ڼ�ֵ��
		for (int i = 0; i <= this->skiplist_current_level; i++) {
			if (update[i].next[i].get_Key() == k)  update[i].next[i] = current->next[i];//�����ڸü�ֵ�Ե������㼶�����޸�
			else break;
		}
		while (this->skiplist_current_level >= 0 && this->header[this->skiplist_current_level] == NULL) {//��߲㼶�в�����ʵ���Ե�����
			this->skiplist_current_level--;
		}
		cout << "element has been delete" << endl;
		this->nodes_element--;//����Ԫ��-1
		this->mux.unlock();//��������
		delete current;
		return true;
	}
	this->mux.unlock();//��������
	delete current;
	return false;
}

template<typename K, typename V>
bool SkipList<K, V>::update_element(const K k,const V v)//��
{
	this->mux.lock();//��������
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
		this->mux.unlock();//��������
		return true;
	}
	cout << "can't uopdate the K-V" << endl;
	this->mux.unlock();//��������
	return false;
}

template<typename K, typename V>
V SkipList<K, V>::search_element(const K k)//��
{
	nodes<K, V>* current = this->header;
	this->mux.lock();//��������
	for (int i = this->skiplist_current_level; i >= 0; i--){
		while (current->next[i] != NULL && current->next[i].get_key() < k) {
			current = current->next[i];
		}
	}
	current = current->next[0];
	if (current->get_key() == k) {
		cout << "find the K-V" << endl;
		this->mux.unlock();//��������
		return current->get_value();
	}
	cout << "unfind the K-V" << endl;
	this->mux.unlock();//��������
	return NULL;
}
template<typename K, typename V>
nodes<K, V>* SkipList<K, V>::create_elemenmt(const K k, const V v, const int level)//��������ڵ�
{
	nodes<K, V>* t = new nodes<K, V>(k, v, level);
	return  t;
}

template<typename K, typename V>
int SkipList<K, V>::size() {
	return this->nodes_element;
}

template<typename K, typename V>
void SkipList<K, V>::display()//��ʾ����
{
	for (int i = this->skiplist_current_level; i >= 0; i--) {
		nodes<K, V>* current = this->header;
		while (current->next[i] != NULL) cout << current->next[i].get_value() << "->";
		cout << endl;
	}
}

template<typename K, typename V>
int SkipList<K, V>::get_rand_level()//�����½ڵ����������㼶
{
	int k = 0;
	while (rand() % 2) k++;
	k = k < this->max_level ? k : this->max_level;
	return k;
}

template<typename K, typename V>
void SkipList<K, V>::dump_file()//����ǰ�洢���ڴ������д�����
{
	cout << "ready writing the data into the table1";
	this->_file_writer.open("table1");
	nodes<K, V>* node = this->header->next[0];//�����ĵ�һ����Ч�ڵ�
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
void SkipList<K, V>::load_file()//���洢�ڴ��̵�����д���ڴ����¹�������
{
	cout << "read reading the data from the table1" << endl;
	this->_file_reader.open("table1");
	string line;//��ȡһ������
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



