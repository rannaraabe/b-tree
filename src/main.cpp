#include <iostream>
#include <fstream>
#include "bTree.h"


template<typename T>
void buildTree(Node<T>* tree, char* path){
	std::fstream espec;
	espec.open(path);
	T val;
	espec>>val;
	tree->key = val;
	tree->isRoot = true;
	while(espec>>val)
		binTreeInsertion(tree, val);
}


template<typename T>
void runTest(Node<T>* tree, std::string path){

	std::fstream test;
	test.open(path.c_str());
	std::string fcomand;
	while(test>>fcomand){
		int arg;
		T key;
		if (fcomand == "ENESIMO"){
			test >>arg;
			std::cout << "Elemento " << arg << " " << nthElement(tree, arg)->key << std::endl;
		}
		else if ( fcomand == "POSICAO"){
			test >> arg;
			std::cout << "Posição de " << arg << " " <<position(tree, arg) << std::endl;
		}
		else if ( fcomand == "MEDIANA"){
			std::cout<< "Mediana: " <<median(tree) <<std::endl;
		}
		else if ( fcomand == "CHEIA"){
			std::cout << "Eh cheia "<< isFull(tree) <<std::endl;
		}
		else if ( fcomand == "COMPLETA"){
			std::cout << "Eh completa "<< isComplete(tree, tree->nodesL + tree->nodesR + 1) <<std::endl;
		}
		else if ( fcomand == "INSIRA"){
			test >> key;
			binTreeInsertion(tree, key);
		}
		else if ( fcomand == "REMOVA"){
			test >> key;
			binTreeRemoval(tree, key);
		}
		else{ 
			printf("IMPRIMINDO MESMO EM\n");
			std::cout << toString(tree) << std::endl;
		}
	}

}

int main(int argc, char* argv[]){
    Node<int> *root = new Node<int>;
    buildTree(root,argv[1]);
    runTest(root, argv[2]);
    return 0;
}
