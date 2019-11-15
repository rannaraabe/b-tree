/**
 * @file bTree.hpp
 * @author Ranna Raabe e Douglas Lima
 */

#ifndef BTREE
#define BTREE

#include <iostream> 
#include <vector>

using namespace std;

// Struct que define uma pagina
struct Node {
	std::vector<int> data;			// Valores dos nós
	std::vector<Node*> filhos;		// Ponteiros de cada nós
	int order;
	bool folha;
	// Construtor do node
    Node() : data(), filhos() {}
	Node(int _order, bool _folha) : order{_order}, folha{_folha}
	{}
};


void cisao(Node* s, int i, Node *y);

void insertNonFull(Node* s, int k);

void insert(Node* root, int k) 
{ 
    
    if (root == NULL) 
    { 
        root = new Node(root->order, true); 
        root->data.push_back(k);  
		root->folha = true;
    } 
    else
    { 
        if (root->data.size() == 2*root->order-1) 
        { 
            Node *s = new Node(root->order, false); 
  
            s->filhos.push_back(root); 
  
            cisao(s, 0, root); 
  
            int i = 0; 
            if (s->data[0] < k) 
                i++; 
            insertNonFull(s->filhos[i],k); 
  
            root = s; 
        } 
        else 
            insertNonFull(root, k); 
    } 
} 
  
void insertNonFull(Node* s, int k) 
{ 
    int i = s->data.size() - 1; 
  
    if (s->folha == true) 
    { 
        while (i >= 0 && s->data[i] > k) 
        { 
            s->data[i+1] = s->data[i]; 
            i--; 
        } 
  
        s->data.insert(s->data.begin() + i + 1, k);
    } 
    else 
    { 
        
        while (i >= 0 && s->data[i] > k) 
            i--; 
  
        if (s->filhos[i+1]->data.size() == 2*s->order-1) 
        { 
            cisao(s, i+1, s->filhos[i+1]); 
  
            if (s->data[i+1] < k) 
                i++; 
        } 
        insertNonFull(s->filhos[i+1], k); 
    } 
} 
  
void cisao(Node* s, int i, Node *y) 
{ 
    Node *z = new Node(y->order, y->folha); 
    for (int j = 0; j < y->order-1; j++) {
        z->data.push_back(y->data[j+y->order]); 
	}
	y->data.erase(y->data.begin() + y->order,y->data.end());
  
    if (y->folha == false) 
    { 
        for (int j = 0; j < s->order; j++) 
            z->filhos.push_back(y->filhos[j+y->order]); 
    } 
  
  
    for (int j = s->data.size(); j >= i+1; j--) 
        s->filhos[j+1] = s->filhos[j]; 
  
    s->filhos[i+1] = z; 
  
    for (int j = s->data.size()-1; j >= i; j--) 
        s->data[j+1] = s->data[j]; 
  
    s->data[i] = y->data[s->order-1]; 
} 
bool search(Node* tree, int key){
	if(tree == nullptr)
		return false;

    int i = 0; 
    while(i < tree->data.size() && key > tree->data[i]) i++; 
  
    if(tree->data[i] == key) 
        return true; 

    if(tree->folha == true){
		for(int j = 0; j < tree->data.size(); j++){
			if(tree->data[j] == key) 
        		return true; 

			return false;
		}	
	} 
    
	return search(tree->filhos[i], key); 
}

void ordenar(vector<int> vector){
	for(int i = 0; i<vector.size(); ++i)
		for (int j = 0; j <vector.size() - i - 1; j++){
			int tem = vector[j];
			vector[j] = vector[j+1];
			vector[j+1] = tem;
		}	
}

void remove(Node* tree, int key){
	// TODO

	/*
	if(paginas_vizinhas < 2*tree->order)
		concatenacao();
	if(paginas_vizinhas > 2*tree->order)
		redistribuicao();
	*/
}

void concatenacao(Node* tree, int index_pag){	// eh propagavel
	Node* pag_filha = tree->filhos[index_pag];
	Node* pag_vizinha = tree->filhos[index_pag+1];
	
	int quantidade = pag_filha->data.size();
	
	int index_vizinha = 0;
	for(int i = quantidade+1; i<pag_vizinha->data.size(); i++){
		pag_filha->data[i] = pag_vizinha->data[index_vizinha];
		index_vizinha++;
	}

	if(!pag_filha->folha){
		index_vizinha = 0;

		for(int i = quantidade+1; i<pag_vizinha->data.size(); i++){
			pag_filha->filhos[i] = pag_vizinha->filhos[index_vizinha];
			index_vizinha++;
		}
	}

	ordenar(pag_filha->data); // Ordeno pq eh provavel q ele insira valores nos lugares errados
	delete(pag_vizinha);
}

void redistribuicao(Node* tree, int index_pag){		// nao eh propagavel
	Node* pag_filha = tree->filhos[index_pag];
	Node* pag_vizinha = tree->filhos[index_pag+1];
	
	int quantidade = pag_filha->data.size();
	
	int index_vizinha = 0;
	for(int i = quantidade+1; i<pag_vizinha->data.size(); i++){
		pag_filha->data[i] = pag_vizinha->data[index_vizinha];
		index_vizinha++;
	}

	if(!pag_filha->folha){
		index_vizinha = 0;

		for(int i = quantidade+1; i<pag_vizinha->data.size(); i++){
			pag_filha->filhos[i] = pag_vizinha->filhos[index_vizinha];
			index_vizinha++;
		}
	}

	ordenar(pag_filha->data); // Ordeno pq eh provavel q ele insira valores nos lugares errados
	cisao(pag_filha, pag_vizinha);
}

#endif
v