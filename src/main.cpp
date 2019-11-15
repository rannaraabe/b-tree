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
    bTree arvore(3); // Crio uma arvore com ordem 3
    int no;

    cin >> no; // Lendo o primeiro nó (considerando o primeiro nó como a raiz)
    arvore.insert(no);

    cout << "Árvore inicial: " << endl;
    arvore.print();
    // Inserindo na árvore todos os valores passados no arquivo
    while (cin >> no)
        arvore.insert(no);

    // Printando a árvore inicial apenas para teste, para o usuário ver ela sem nenhuma modificação
    cout << "Árvore inicial: " << endl;
    arvore.print();
    cout << endl << endl;

    // Lendo arquivo de comandos
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
				arvore.search(parametro);
				break;
			case INSIRA:
				ler >> parametro;
				cout << ">> Inserindo elemento " << parametro << endl;
				arvore.insert(parametro);
				break;
			case REMOVA:
				ler >> parametro;
				cout << ">> Removendo elemento " << parametro << endl;
				arvore.remove(parametro);
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
    arvore.print();
    cout << endl;

    return 0;
}
