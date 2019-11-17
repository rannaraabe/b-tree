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
#include <deque>
#include <algorithm>

using namespace std;

// Struct que define uma pagina
struct Node {
	std::deque<int> data;			// Valores dos nós
	std::deque<Node*> filhos;		// Ponteiros de cada nós
	int order;						// Ordem da pag
	Node *father;
	// Construtor do node
	Node(int _order) : order{_order}
	{}
};

class BTree{
private:
	Node* root;

	bool is_leaf(Node* node){
		if(node == nullptr) return false;
		if(node->filhos[0] == nullptr) return true;
		return false;
	}

	bool search_recursive(Node* tree, int key){
		if(tree == nullptr) return false;
		int i = 0;
		while(i < tree->data.size() && tree->data[i] < key) i++;
		if(i < tree->data.size() && key == tree->data[i]) return true;
		search_recursive(tree->filhos[i], key);
	}

	void insert_recursive(Node* tree, int key, Node *page_l, Node *page_r){
		if(tree == nullptr){
			tree = new Node(page_l->order, true);
			tree->data.push_back(key);
			tree->filhos.push_back(page_l);
			tree->filhos.push_back(page_r);
			page_l->father = tree;
			page_r->father = tree;
			root = tree;
		}
		
		else{
			int pos = lower_bound(tree->data.begin(), tree->data.end(), key)-tree->data.begin();
			tree->data.insert(pos+tree->data.begin(), key);
			
			if(tree->filhos.size()) tree->filhos.erase(pos+tree->filhos.begin());
			
			tree->filhos.insert(pos+tree->filhos.begin(), page_l);
			tree->filhos.insert(pos+1+tree->filhos.begin(), page_r);
			if(tree->data.size() > 2*tree->order){
				//cisao
				Node *new_page_l = new Node(tree->order);
				Node *new_page_r = new Node(tree->order);
				int median = tree->data[tree->data.size()/2];
				
				for(int i = 0; i < tree->data.size(); i++){
					if(i < tree->data.size()/2)
						new_page_l->data.push_back(tree->data[i]);
					if(i > tree->data.size()/2)
						new_page_r->data.push_back(tree->data[i]);
				}
				for(int i = 0; i < tree->filhos.size(); i++){
					if(i < tree->filhos.size()/2) 
						new_page_l->filhos.push_back(tree->filhos[i]);
					else
						new_page_r->filhos.push_back(tree->filhos[i]);
				}
				
				insert_recursive(tree->father, median, new_page_l, new_page_r);
				if(tree->father != nullptr){
					new_page_l->father = tree->father;
					new_page_r->father = tree->father;
				}
			}
		}
	}
	
	Node* find_page_to_insert(Node* tree, int key){
		if(is_leaf(tree)) return tree;
		int i = 0;
		while(i < tree->data.size() && tree->data[i] < key) i++;
		find_page_to_insert(tree->filhos[i], key);
	}

	Node* find_page_to_delete(Node* tree, int key){

	}


public:
	BTree(int order) : root(new Node(order, true)){ }

	bool search(int key){
		return search_recursive(root, key);
	}

	void insert(int key){
		if(search(key)){
			cout << "erro-insert: O elemento já está na árvore!" << endl;
			return;
		}
		insert_recursive(find_page_to_insert(root, key), key, nullptr, nullptr);
	}

	void print(){
		queue<Node*> q;
		q.push(root);
		while(!q.empty()){
			Node* u = q.front(); q.pop();
			if(u == nullptr) continue;
			for(auto d : u->data){
				cout << d << " ";
			}
			cout << "| ";
			for(auto f : u->filhos){
				q.push(f);
			}
		}
	}

	void remove(int key){
		if(!search(key)){
			cout << "erro-remove: O elemento não está na árvore!" << endl;
		}
		Node* page = find_page_to_remove(root, key);
		if(is_leaf(page)){
			page->filhos.pop_back();
			page->data.erase(find(page->data.begin(), page->data.end(), key));
		}
		else{
			
		}
	}

};
#endif
