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
    if(argc != 3){
        printf("Insira username e password\n");
        return 0;
    }
    char username[TAM];
    char password[TAM];
    strcpy(username, argv[1]);
    strcpy(password, argv[2]);
    printf("\n\n *** Bem Vindo %s ***\n\n", username);


    if (getenv("HEARTBEAT") != NULL)
        nmaxalive = atoi(getenv("HEARTBEAT"));


    comandos();
    do{
        printf("Introduza um comando: ");
        fgets(comando,50,stdin);
        comando[strlen(comando) - 1] = '\0';
        if(strcmp(comando, "sell\0") == 0){
            printf("comando valido \n"); // sell <name> <category> <value> <current_value> <duration>
        }
        if(strcmp(comando, "list\0") == 0){
            printf("comando valido \n"); // list
        }
        if(strcmp(comando, "licat\0") == 0){
            printf("comando valido \n"); // licat <category>
        }
        if(strcmp(comando, "lisel\0") == 0){
            printf("comando valido \n"); // lisel <user_sell>
        }
        if(strcmp(comando, "lival\0") == 0){
            printf("comando valido \n"); // lival <
        }
        if(strcmp(comando, "litime\0") == 0){
            printf("comando valido \n"); // litime <
        }
        if(strcmp(comando, "timet\0") == 0){
            printf("comando valido \n"); // time
        }
        if(strcmp(comando, "buy\0") == 0){
            printf("comando valido \n"); // buy <IDitem> <value>
        }
        if(strcmp(comando, "cash\0") == 0){
            printf("comando valido \n"); // cash
        }
        if(strcmp(comando, "add\0") == 0){
            printf("comando valido \n"); // add value
        }
        if(strcmp(comando, "exit\0") == 0){
            printf("\n A sair...\n"); //exit
        }

    }while(strcmp(comando, "exit"));

}