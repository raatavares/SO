#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"

void comandos(){
    printf("========== Comando ========== \n");
    printf("sell - Colocar um item a leilao(nome categoria preco_base preco_compre_ja duracao) \n");
    printf("list - Lista de todos os itens \n");
    printf(" licat - Lista de Itens por categoria \n");
    printf(" lisel - Lista de Itens por vendedor \n");
    printf(" lival - Lista de Itens por valor \n");
    printf(" litime - Lista de Itens por prazo \n");
    printf("time - Obter a hora atual \n");
    printf("buy - Licitar um item \n");
    printf("cash - Consultar saldo \n");
    printf("add - Carregar saldo \n");
    printf("exit - Sair \n");
}

int main(int argc, char *argv[]){


    comandos();

}