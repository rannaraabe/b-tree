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

void insert(Node* tree, int key){
	// Se a pagina tiver espaco, adiciono a chave
	if(tree->filhos.empty())
		insert(tree, key);

	
	if(tree->data.size() < tree->order*2){
		for (int i = 0; i< tree->data.size(); ++i){
			if (key < tree->data[i]){
				insert(tree->filhos[i], key);
				break;
			}
		}			
	}
	printf("oi amiguinho \n");
	
	
	// Se a pagina estiver cheia, faço a cisao
	if(tree->data.size() >= tree->order*2){
		Node* new_raiz = new Node();
		
		// Novo raiz recebe a raiz antiga como filho
		new_raiz->filhos[0] = tree;
		
		// Divide a raiz antiga e 
		
		// Nova raiz possui novo filho, decido qual dos filhos terão nova chave
		int i = 0; 
		if(new_raiz->data[0] < key) 
			i++; 
		
		insert(new_raiz->filhos[i], key);
		tree = new_raiz; 
	}
}

void search(Node* tree, int key){

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
}

void concatenacao(Node* tree, int index_pag){
	Node* pag_filha = tree->filhos[index_pag];
	Node* pag_vizinha = tree->filhos[index_pag+1];
	
	if(pag_filha->data.size()+pag_vizinha->filhos.size() < 2*tree->order){
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
}

void redistribuicao(){
	// TODO
}

#endif
