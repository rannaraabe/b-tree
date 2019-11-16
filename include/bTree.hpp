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
	int order;						// Ordem da pag
	bool folha;						// Bool para saber se a pagina eh folha
	// Construtor do node
	Node(int _order, bool _folha) : order{_order}, folha{_folha}
	{}
};

bool search(Node* tree, int key);
void insert(Node* raiz, int k);
void insert_naocheia(Node* node, int k);
void cisao(Node* s, int i, Node *y);
void ordenar(vector<int> vector);
void remove(Node* tree, int key);
int encontrar_chave(Node *node, int key);
int get_predecessor(Node *tree, int idx);
int get_sucessor(Node *tree, int idx);
void concatenacao(Node* tree, int index_pag);
void redistribuicao(Node* tree, int index_pag);

bool search(Node* tree, int key){
	if(tree == nullptr)
		return false;

    int i = 0; 
    while(i < tree->data.size() && key > tree->data[i]) i++; 
  
	if (tree->data.empty())
		return false;

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

void insert(Node* raiz, int k) { 
    if(raiz == nullptr) { 
        raiz = new Node(raiz->order, true); 
        raiz->data.push_back(k);  
		raiz->folha = true;
    } 
    else { 
        if(raiz->data.size() == 2*raiz->order-1){ 
            Node *node = new Node(raiz->order, false); 
  
            node->filhos.push_back(raiz); 
            cisao(node, 0, raiz); 
  
            int i = 0; 
            if(node->data[0] < k) 
                i++; 
          
		    insert_naocheia(node->filhos[i],k); 
            raiz = node; 
        } else 
            insert_naocheia(raiz, k); 
    } 
} 
  
void insert_naocheia(Node* node, int k){ 
    int i = node->data.size() - 1; 
  
    if(node->folha == true){ 
        while(i >= 0 && node->data[i] > k){ 
            node->data[i+1] = node->data[i]; 
            i--; 
        } 
  
        node->data.insert(node->data.begin() + i + 1, k);
    } else { 
        while(i >= 0 && node->data[i] > k) 
            i--; 
  
        if(node->filhos[i+1]->data.size() == 2*node->order-1){ 
            cisao(node, i+1, node->filhos[i+1]); 
  
            if(node->data[i+1] < k) 
                i++; 
        } 

        insert_naocheia(node->filhos[i+1], k); 
    } 
} 
  
void cisao(Node* s, int i, Node *y){ 
    Node *z = new Node(y->order, y->folha); 
    for(int j = 0; j < y->order-1; j++) {
        z->data.push_back(y->data[j+y->order]); 
	}
	y->data.erase(y->data.begin() + y->order,y->data.end());

    if(y->folha == false){ 
        for (int j = 0; j < s->order; j++) 
            z->filhos.push_back(y->filhos[j+y->order]); 
    } 
  
    for(int j = s->data.size(); j >= i+1; j--) 
        s->filhos[j+1] = s->filhos[j]; 
  
    s->filhos[i+1] = z; 
  
    for(int j = s->data.size()-1; j >= i; j--) 
        s->data[j+1] = s->data[j]; 
  
	if(s->data.empty())
		s->data.push_back(y->data[s->order-1]);
	else 
		s->data[i] = y->data[s->order-1]; 
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
	int idx = encontrar_chave(tree, key); 

    if (idx < tree->order && tree->data[idx] == key){
        if (tree->folha) {
			for (int i=idx+1; i<tree->data.size(); ++i) 
			tree->data[i-1] = tree->data[i]; 
		} 
        else{
			int k = tree->data[idx]; 
			if (tree->filhos[idx]->order >= tree->order) {
				int pred = get_predecessor(tree, idx); 
				tree->data[idx] = pred; 
				remove(tree->filhos[idx], pred); 
			}
			else if(tree->filhos[idx+1]->order >= tree->order) { 
				int succ = get_sucessor(tree, idx); 
				tree->data[idx] = succ; 
				remove(tree->filhos[idx+1], succ); 
			} 
			else { 
				concatenacao(tree, idx); 
				remove(tree->filhos[idx], k); 
			} 
		}
    } else { 
        if(tree->folha) { 
            cout << "Chave não encontrada na arvore! \n"; 
            return; 
        } 

        bool flag = ((idx==tree->order) ? true : false ); 
  
        if (tree->filhos[idx]->order < tree->order) 
            redistribuicao(tree, idx); 
        if (flag && idx > tree->order) 
        	remove(tree->filhos[idx-1], key); 
        else
            remove(tree->filhos[idx], key); 
    } 
    return; 

	/*
	if(paginas_vizinhas < 2*tree->order)
		concatenacao();
	if(paginas_vizinhas > 2*tree->order)
		redistribuicao();
	*/
}

int encontrar_chave(Node *node, int key) {  
    int idx=0; 
    
	while (idx<node->order && node->data[idx] < key) 
        ++idx; 

    return idx; 
} 

int get_predecessor(Node *tree, int idx) {
    Node *cur = tree->filhos[idx]; 

    while (!cur->folha) 
        cur = cur->filhos[cur->order]; 
  
    return cur->data[cur->order-1]; 
} 
  
int get_sucessor(Node *tree, int idx) {
    Node *cur = tree->filhos[idx+1]; 
    
	while (!cur->folha) 
        cur = cur->filhos[0]; 
  
     
    return cur->data[0]; 
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
	cisao(pag_filha, 0, pag_vizinha);
}

void print(Node* tree){
	if(tree != nullptr){
		for(int i = 0; i < tree->order; i++){ 
			if(tree->folha == false) 
				print(tree->filhos[i]); 
			cout << " " << tree->data[i]; 
    	}
	}
}
#endif
