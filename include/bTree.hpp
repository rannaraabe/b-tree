/**
 * @file bTree.hpp
 * @author Ranna Raabe e Douglas Lima
 */

#ifndef BTREE
#define BTREE

#include <iostream>
#include <forward_list> 
#include <vector>

using namespace std;

struct Node {
	unsigned int order;				// Ordem d da árvore
	std::forward_list<int> data;	// Valores dos nós
	std::vector<Node*> filhos;		// Ponteiros de cada nós
};

class bTree
{
	private:
		Node *raiz;
	public:

		bTree(){ }

		~bTree(){
			delete raiz;
		}

		/**
		 * Busca um valor na árvore B
		 * 
		 * @return true caso o valor esteja na árvore, e false caso não esteja
		 */ 
		bool search(int key){
			int index = 0;

			return search_recursive(raiz, key, index);
		}

		bool search_recursive(Node* tree, int key, int index){
			auto it = tree->data.begin();

			while(it != tree->data.end()){
				// Caso árvore seja vazia
				if(*it == NULL){
					cout << "Árvore vazia! \n";
					return false;
				}

				// Caso o valor seja a posicao atual
				if(*it == key)
					return true;

				// Caso o valor seja maior do que o atual, avança na lista procurando o mesmo
				if(key > *it)
					return search_recursive(it.operator++, key, index++);
				else{
					// Caso o valor seja maior do que o atual e menor do que o próximo da lista, sigo para a pagina apontada e busco o valor na lista dos filhos
					if(key > *it && key < *it+1)
						return search_recursive(tree->filhos[index++], key, index);
				}

				it++;
			}
			
			return false;
		}

		/**
		 * Insere um valor na árvore B
		 */ 
		void insert(int key){
			// TODO
			insert_recursive();
		}

		void insert_recursive(){
			// TODO
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
		 * Função auxiliar para imprimir a árvore
		 */ 
		void print(){
			cout << "";
		}
};
#endif
