#ifndef BTREE
#define BTREE

struct Node {
	unsigned int order;
	int* data;
	Node* filhos; 

};


bool search (Node* tree, T key){
	
	for(int cont = 0; cont < tree->order; ++cont){
		if ( tree->data[cont] == key)
			return true;
		if ( tree->data[cont] > key)
			return search(tree->filhos[cont], data);
	}
	return false;
};


bool insert(Node* tree, T data){

	return false;
}


bool remove (Node* tree, T data){

	return false
}
#endif
