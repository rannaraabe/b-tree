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
	std::vector<int> data;	// Valores dos nós
	std::vector<Node*> filhos;		// Ponteiros de cada nós
};

class bTree
{
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
			return search_recursive(raiz, key);
		}

		bool search_recursive(Node* tree, int key){
			auto it = tree->data.begin();
			int i = 0;
		
			if(tree == nullptr){
				cout << "Chave não encontrada\n";
				return false;
			}
		
			for(; i < tree->data.size(); i++)
			{
				if(tree->data[i] == key)
					return true;
				
				if(tree->data[i] > key){
					return search_recursive(tree->filhos[i], key);
				}
			}
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
			// Se a pagina ainda estiver espaco, adiciono
			if (tree->data.size() < 2*this->order){
				insertion_sort(tree, key);
				return;
			}
			
			// Se a pagina estiver cheia
			if(tree->data.size() == order*2){
				// desço pelo ponteiro
			}
		}

		void insertion_sort(Node* node, int key){

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
		 * Funcoes auxiliares para insercao e remocao
		 */ 
		void cisao(){
			// TODO
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
			cout << "";
		}
};
#endif
