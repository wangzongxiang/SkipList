#pragma once
template<typename K, typename V>
class nodes
{
public:
	nodes();
	~nodes();
	nodes(const K k,const V v,const int level);
	nodes<K, V>** next;//next����,�洢node���͵�ָ��
	const K get_key();
	const V get_value();
	void set_value(V);
	int nodes_level;
private:
	K k;
	V v;
};

