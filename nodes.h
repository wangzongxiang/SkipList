#pragma once
template<typename K, typename V>
class nodes
{
public:
	nodes();
	~nodes();
	nodes(const K k,const V v,const int level);
	nodes<K, V>** next;//next数组,存储node类型的指针
	const K get_key();
	const V get_value();
	void set_value(V);
	int nodes_level;
private:
	K k;
	V v;
};

