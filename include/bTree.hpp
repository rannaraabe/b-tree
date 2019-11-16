/**
 * @file bTree.hpp
 * @author Ranna Raabe e Douglas Lima
 */

#ifndef BTREE
#define BTREE

#include <iostream> 
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// Struct que define uma pagina
struct Node {
	std::vector<int> data;			// Valores dos nós
	std::vector<Node*> filhos;		// Ponteiros de cada nós
	int order;						// Ordem da pag
	bool folha;						// Boolean para saber se a pagina é folha ou nao

	// Construtor do node
	Node(int _order, bool _folha) : order{_order}, folha{_folha}
	{}
};

// Declarando as funcoes
bool search(Node* tree, int key);
void insert(Node* raiz, int k);
void insert_naocheia(Node* node, int k);
void cisao(Node* s, int i, Node *y);
void ordenar(vector<int> vector);
void remove(Node* tree, int key);
int encontrar_chave(Node *node, int key);
int get_predecessor(Node *tree, int i);
int get_sucessor(Node *tree, int i);
void concatenacao(Node* tree, int index_pag);
void redistribuicao(Node* tree, int index_pag);

////////////////////////////////////////////// SEARCH //////////////////////////////////////////////

/**
 * Funcao busca um valor na arvore
 * 
 * @return true caso o elemento esteja na árvore, false caso contrário
 */ 
bool search(Node* tree, int key){
	// Caso a arvore seja vazia
	if(tree == nullptr)
		return false;

	// Condicao para salvar o i enquanto a chave for maior dos que os valores da pagina
    int i = 0; 
    while(i < tree->data.size() && key > tree->data[i]) i++; 
  
	// Caso a pagina esteja vazia, sem valor nenhum
	if(tree->data.empty())
		return false;

	// Caso a chave esteja na posicao atual
    if(tree->data[i] == key) 
        return true; 

	// Caso esteja numa folha percorro procurando a chave em cada posicao da folha
    if(tree->folha){
		for(int j = 0; j < tree->data.size(); j++){
			if(tree->data[j] == key) 
        		return true; 

			return false;
		}	
	}

	// Chamo a funcao para buscar o valor no proximo filho (no proximo ponteiro) 
	return search(tree->filhos[i], key); 
}

////////////////////////////////////////////// INSERT //////////////////////////////////////////////

/**
 * Funcao insere um valor na arvore
 */
void insert(Node* tree, int key) { 
	// Verifico se o valor já está na árvore
	if(search(tree, key)){
		cout << "erro-insert: O elemento já está na árvore!" << endl;
		return;
	}

	// Se a árvore for vazia, aloco um espaco para o primeiro valor
    if(tree == nullptr) { 
        tree = new Node(tree->order, true); 
        tree->data.push_back(key);  
		tree->folha = true;
    } else { 
		// Verifico se a pagina está cheia
        if(tree->data.size() == 2*tree->order-1){ 
			// Crio um novo nó não-folha e faço a cisao
            Node *node = new Node(tree->order, false); 
            node->filhos.push_back(tree); 
            cisao(node, 0, tree); 

			// Se a chave que quero inserir for maior do que a posicao no novo nó
            int i = 0; 
            if(key > node->data[0]) 
                i++; 

			// Depois da cisao chamo a funcao para inserir na pagina atual (que nao esta cheia)
		    insert_naocheia(node->filhos[i], key); 
            tree = node; 
        } else 
			// Caso a pagina nao esteja cheia, eu nao preciso fazer cisao, entao so chamo a funcao de inserir na pagina nao cheia
            insert_naocheia(tree, key); 
    } 
} 

/**
 * Funcao auxiliar para inserir um valor em uma pagina que nao está cheia na arvore 
 */
void insert_naocheia(Node* node, int key){ 
	// Inicializo o i
    int i = node->data.size() - 1; 
  
	// Se for folha
    if(node->folha){ 
		// Enquanto a chave for menor no que a valor da posicao atual, vou "empurrando" os valores para a direita (para colocar o valor na esquerda)
        while(i >= 0 && node->data[i] > key){ 
            node->data[i+1] = node->data[i]; 
            i--; 
        } 

		// Depois de ter "empurrado" todo mundo que queria, insiro o valor na posicao certa
        node->data.insert(node->data.begin() + i + 1, key);
    } else { 
        while(i >= 0 && node->data[i] > key) 
            i--; 

		// Se a pagina estiver cheia, faco a cisao 
        if(node->filhos[i+1]->data.size() == 2*node->order-1){ 
            cisao(node, i+1, node->filhos[i+1]); 
  
            if(key >node->data[i+1]) 
                i++; 
        } 
		// Depois de fazer a cisao, insiro o elemento na pagina
        insert_naocheia(node->filhos[i+1], key); 
    } 
} 

/**
 * Funcao que realiza a cisao de paginas na arvore
 */
void cisao(Node* pagina_pai, int i, Node* pagina){ 		// a variavel i guarda o i na pag 
	// Crio uma nova pagina
	Node* new_pagina = new Node(pagina->order, pagina->folha); 
    
	// Guardo na nova pagina os ultimos valores da pagina que estou fazendo cisao
	for(int j = 0; j < pagina->order-1; j++)
        new_pagina->data.push_back(pagina->data[j + pagina->order]); 
	
	pagina->data.erase(pagina->data.begin() + pagina->order, pagina->data.end());

	// Guardo na nova pagina os ultimos filhos da pagina que estou fazendo cisao (se for folha, nao preciso copiar os filhos)
    if(!pagina->folha){ 
        for (int j = 0; j < pagina_pai->order; j++) 
            new_pagina->filhos.push_back(pagina->filhos[j + pagina->order]); 
    } 
  
	// Crio um novo espaco na pagina pai para o novo filho que vai entrar
    for(int j = pagina_pai->data.size(); j >= i+1; j--) 
        pagina_pai->filhos[j+1] = pagina_pai->filhos[j]; 
  
	// Coloco na pagina pai o novo filho
    pagina_pai->filhos[i+1] = new_pagina; 
  
	// Procuro onde colocar a nova chave, "empurrando" todos os valores maiores do que ela para frente
    for(int j = pagina_pai->data.size()-1; j >= i; j--) 
        pagina_pai->data[j+1] = pagina_pai->data[j]; 
  
	if(pagina_pai->data.empty())
		pagina_pai->data.push_back(pagina->data[pagina_pai->order-1]);
	else 
		// Copio a chave mediana para a pagina pai
		pagina_pai->data[i] = pagina->data[pagina_pai->order-1]; 
} 

////////////////////////////////////////////// REMOVE //////////////////////////////////////////////

/**
 * Funcao remove um valor na arvore
 */
void remove(Node* tree, int key){
	int i = encontrar_chave(tree, key); 

    if (i < tree->order && tree->data[i] == key){
        if (tree->folha) {
			for (int i=i+1; i<tree->data.size(); ++i) 
				tree->data[i-1] = tree->data[i]; 
		} 
        else{
			int k = tree->data[i]; 
			if (tree->filhos[i]->order >= tree->order) {
				int pred = get_predecessor(tree, i); 
				tree->data[i] = pred; 
				
				remove(tree->filhos[i], pred); 
			}
			else if(tree->filhos[i+1]->order >= tree->order) { 
				int succ = get_sucessor(tree, i); 
				tree->data[i] = succ; 
				
				remove(tree->filhos[i+1], succ); 
			} 
			else { 
				// Entao as paginas vizinhas somadas sao menores do que 2*ordem, faco a concatenacao e depois removo o valor
				concatenacao(tree, i); 
				remove(tree->filhos[i], k); 
			} 
		}
    } else { 
        if(tree->folha) { 
            cout << "erro-remove: Chave não encontrada na arvore! \n"; 
            return; 
        } 

        bool flag = ((i==tree->order) ? true : false ); 
  
		// Se as paginas vizinhas somadas sao maiores do que 2*ordem, faco a redistribuicao
        if (tree->filhos[i]->order < tree->order) 
            redistribuicao(tree, i); 
        if (flag && i > tree->order) 
        	remove(tree->filhos[i-1], key); 
        else
            remove(tree->filhos[i], key); 
    } 
    return;
}

/**
 * Funcao auxiliar que encontra o i de um valor na arvore
 */
int encontrar_chave(Node *node, int key) {  
    int i = 0; 
    
	while (i<node->order && node->data[i] < key) 
        ++i; 

    return i; 
} 

/**
 * Funcao auxiliar que retorna o predecessor um valor na arvore
 */
int get_predecessor(Node *tree, int i) {
    Node *cur = tree->filhos[i]; 

    while (!cur->folha) 
        cur = cur->filhos[cur->order]; 
  
    return cur->data[cur->order-1]; 
} 

/**
 * Funcao auxiliar que retorna o sucessor um valor na arvore
 */
int get_sucessor(Node *tree, int i) {
    Node *cur = tree->filhos[i+1]; 
    
	while (!cur->folha) 
        cur = cur->filhos[0]; 
  
     
    return cur->data[0]; 
} 

/**
 * Funcao auxiliar que realiza a concatenacao de paginas na arvore
 */
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

/**
 * Funcao auxiliar que realiza a redistribuicao de valores nas paginas de uma arvore
 */
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

/**
 * Funcao auxiliar que ordena os valores na arvore
 */
void ordenar(vector<int> vector){
	// Bubble sort para ordenar uma pagina
	for(int i = 0; i<vector.size(); ++i)
		for (int j = 0; j <vector.size() - i - 1; j++){
			int temp = vector[j];
			vector[j] = vector[j+1];
			vector[j+1] = temp;
		}	
}

////////////////////////////////////////////// PLUS //////////////////////////////////////////////

/**
 * Funcao auxiliar que pinta a arvore
 */
void print(Node* tree){
	if(tree != nullptr){
		for(int i = 0; i < tree->order*2; i++){ 
			// Caso a pagina seja uma folha, imprimo suas chaves guardadas
			if(tree->folha) 
				cout << " " << tree->data[i];
			else	
				// Caso n seja, desço para imprimir os filhos
				print(tree->filhos[i]); 
    	}
	}
	return;

	// stack<Node*> stack;
    // stack.push(tree);
    // while (!stack.empty()){
    //     Node* raiz = stack.top();
    //     stack.pop();
    //     int i;
    //     for(i = 0; i < tree->order*2; i++){
    //         if(tree->folha == false)
    //             stack.push(raiz->filhos[i]); 
    //         cout << " " << raiz->data[i];
    //     }
    //     if (tree->folha == false)
    //         stack.push(raiz->filhos[i]);
    // }
}
#endif
