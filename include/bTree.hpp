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
	int number; 					// Quantidade de valores que tem no nó

	// Construtor do node
    Node() : data(), filhos() {}
};

class bTree {
	private:
		Node *raiz;
		int order;
	public:

		bTree(int ordem){
			this->order = ordem;
		}

			~bTree(){
			delete raiz;
		}

		/**
		 * Busca um valor na árvore B
		 * 
		 * @return true caso o valor esteja na árvore, e false caso não esteja
		 */ 
		bool search(int key){
			if (raiz == nullptr) return false;
			return search_recursive(raiz, key);
		}

		bool search_recursive(Node* tree, int key){
			auto it = tree->data.begin();
			int i = 0;

			// Caso a árvore seja vazia
			if(tree == nullptr){
				cout << "Chave não encontrada\n";
				return false;
			}
		
			// Percorro a árvore procurando a chave
			for(; i < tree->data.size(); i++){
				// Chave encontrada
				if(tree->data[i] == key)
					return true;
				
				// Busco a chave na proxima posicao da pagina
				if(tree->data[i] > key){
					return search_recursive(tree->filhos[i], key);
				}
			}

			// Caso ele busque por toda a pagina e nao ache, busca na proxima pagina
			return search_recursive(*(tree->filhos.end()), key);
		}

		/**
		 * Insere um valor na árvore B
		 */ 
		void insert(int key){
			// Caso o valor já esteja na árvore
			if(search(key)){
				cout << "erro-insert: Valor " << key << "já está na árvore!";
				return;
			}

			// Se a árvore estiver vazia, insiro o valor na raiz
			if(raiz == nullptr){
				raiz = new Node;
				raiz->data.push_back(key);
				return;
			}

			insert_recursive(raiz, key);
		}

		void insert_recursive(Node* tree, int key){
			// Se a pagina tiver espaco, adiciono a chave
			if(tree->number < this->order*2){
				insertion_sort(tree, key);
				return;
			}
			
			// Se a pagina estiver cheia, faço a cisao
			if(tree->number == this->order*2){
				Node* new_raiz = new Node();

				// Novo raiz recebe a raiz antiga como filho
				new_raiz->filhos[0] = raiz;

				// Divide a raiz antiga e 
				cisao(raiz, 0);

				// Nova raiz possui novo filho, decido qual dos filhos terão nova chave
				int i = 0; 
				if(new_raiz->data[0] < key) 
					i++; 
				
				insertion_sort(new_raiz->filhos[i], key);
				tree = new_raiz; 
			}
		}

		void insertion_sort(Node* node, int key){
			// Inicializo com o ultimo elemento 
			int i = node->number-1; 
		
			if(node->data.size() == this->order){ 
				// Encontra o local para colocar a nova chave, e move todas as chaves maiores para um lugar à frente 
				while(i >= 0 && node->data[i] > this->order){ 
					node->data[i+1] = node->data[i]; 
					i--; 
				} 
				
				// Insere a nova chave no local encontrado
				node->data[i+1] = key; 
				node->number = node->number+1; 
			} else { 
				// Encontra o filho que terá a nova chave
				while(i >= 0 && node->data[i] > this->order) 
					i--; 
		
				// Confere se o filho está cheio e faz cisao
				if(node->filhos[i+1]->number == 2*this->order){  
					cisao(node->filhos[i+1], i+1); 
		
					// A chave do meio sobe, e os filhos são divididos em duas paginas 
					if(node->data[i+1] < this->order) 
						i++; 
				} 

				insertion_sort(node->filhos[i+1], key); 
			} 
		}

		/**
		 * Remove um valor da árvore B
		 */
		void remove(int key){
			// TODO
			remove_recursive();
		}

		void remove_recursive(){
			// TODO
		}

		/**
		 * Funcao que realiza cisão de uma pagina ao ter que inserir um valor em uma pagina cheia
		 */ 
		void cisao(Node* tree, int i){
			// Criando uma nova pagina que guarda (order-1) chaves
			Node* new_pagina = new Node();
			new_pagina->number = this->order - 1;

			// Copia as ultimas (order-1) chaves de tree para new_pagina
			for(int j=0; j<this->order-1; j++)
				new_pagina->data[j] = tree->data[j+this->order];

			// Copio o ultimo filho de tree para new_pagina
			if(tree->data.size() == this->order){
				for(int j=0; j<this->order; j++)
					new_pagina->filhos[j] = tree->filhos[j+this->order];
			}

			// Diminuo o numero de chaves de new_pagina
			new_pagina->number = this->order-1;

			// Como esse novo nó terá um novo filho, crio um espaco para ele
			for(int j=this->order; j>=i+1; j--)
				new_pagina->filhos[j+1] = new_pagina->filhos[j];

			// Conecto o novo nó à new_pagina
			new_pagina->filhos[i+1] = new_pagina;

			// Uma nova chave foi inserida, entao encontro a posicao para a nova chave e movo todas as outras chaves para frente
			for(int j=this->order-1; j>= i; j--)
				new_pagina->data[j+1] = new_pagina->data[j];

			// Copio a chave mediana para esse novo nó
			new_pagina->data[i] = new_pagina->data[this->order-1];

			new_pagina->number = new_pagina->number + 1;
		}

		void concatenacao(){
			// TODO
		}

		void redistribuicao(){
			// TODO
		}

		/**
		 * Função auxiliar para imprimir a árvore
		 */ 
		void print(){
			print_recursive(raiz);
		}

	   void print_recursive(Node* raiz){
		   if (raiz == nullptr) return;
		   int i = 0;
		   for(; i< raiz->data.size(); ++i){
               print_recursive(raiz->filhos[i]);
			   cout << raiz->data[i] << " ";
		   }
           print_recursive(raiz->filhos[i]);
	   }
};
#endif
