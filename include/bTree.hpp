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
};

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

void insert(Node* tree, int key){
	// TODO
}

void cisao(Node* pagina1, Node* pagina2){
	// TODO
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
