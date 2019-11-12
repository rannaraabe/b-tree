#ifndef BTREE
#define BTREE
#include <forward_list> 

struct Node {
	unsigned int order;
	std::forward_list<int> data;
	std::vector<Node*>filhos;
};


bool search (Node* tree, int key){
	int cont = 0;
	auto it = data.begin();
	while(it != data.end()){
		if ( *it == key)
			return true;
		if ( *it > key)
			return search(tree->filhos[cont], data);
		cont++;
		it++;
	}
	return false;
};


bool insert(Node* tree, T data){

	return false;
};


bool remove (Node* tree, T data){

	return false;
};
#endif
