#include "nodes.h"
template<typename K, typename V>
nodes<K,V>::nodes() {

}

template<typename K, typename V>
nodes<K, V>::~nodes()
{
	
}

template<typename K, typename V>
nodes<K, V>::nodes(const K k, const V v, const int level) {
	this->k = k;
	this->v = v;
	this->nodes_level = level;
	this->next = new nodes<K, V>* [level + 1];
	memset(this->next, 0, sizeof(nodes<K,V>*)*(level+1));//让数组元素指向空
}

template<typename K, typename V>
const K nodes<K, V>::get_key() {
	return this->k;
}

template<typename K, typename V>
const V nodes<K, V>::get_value() {
	return this->v;
}

template<typename K, typename V>
void nodes<K, V>::set_value(const V v) {
	this->v = v;
}