/**
 * @file main.cpp
 * @author Ranna Raabe e Douglas Lima
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "../include/bTree.hpp"

using namespace std;

// Guardando um inteiro para cada operação
enum cod_funcoes {
    BUSCA,
    INSIRA,
    REMOVA
};

// Uso um mapa para conferir a operação e seu código
map<string, cod_funcoes> map_funcoes;

int main(){
    Node* arvore; // Crio uma arvore com ordem 3
	arvore->order = 3;
    int no;

    fstream arquivo;
    arquivo.open("./data/comandos.txt");

    string comando_linha; // Para salvar o comando da linha do arquivo

    // Inicializando o map
    map_funcoes["BUSCA"] = BUSCA;
    map_funcoes["INSIRA"] = INSIRA;
    map_funcoes["REMOVA"] = REMOVA;

    // Enquanto tiver comandos para ler
    while (getline(arquivo, comando_linha)){
        stringstream ler(comando_linha);

        string funcao; // Para salvar a funcao que está na linha de comando
        int parametro; // Para salvar o valor que está na linha de comando

        ler >> funcao;

        // Chamando a função para cada uma das funções
        switch (map_funcoes[funcao]){
			case BUSCA:
				ler >> parametro;
                cout << ">> Buscando elemento " << parametro << endl;
				search(arvore, parametro);
				break;
			case INSIRA:
				ler >> parametro;
				cout << ">> Inserindo elemento " << parametro << endl;
				insert(arvore, parametro);
				break;
			case REMOVA:
				ler >> parametro;
				cout << ">> Removendo elemento " << parametro << endl;
				remove(arvore, parametro);
				break;
			default:
				cout << "" << endl;
				cout << ">> Comando não encontrado! " << endl;
				break;
        }
    }

    arquivo.close();

    // Só pra testar mesmo, para o usuário ver a árvore após todas as alterações
    cout << endl;
    cout << "Árvore final: " << endl;
    cout << endl;

    return 0;
}
