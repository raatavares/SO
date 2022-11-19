#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
#include"users_lib.h"



void comandos(){
    printf("========== Comando ========== \n");
    printf("help - Lista de Comandos \n");
    printf("users - Lista de Utilizadores \n");
    printf("list - Lista de Itens a Venda \n");
    printf("kick - Banir um cliente \n");
    printf("prom - Lista de Promotores \n");
    printf("reprom - Atualizar promotores \n");
    printf("cancel - Cancelar um Promotor \n");
    printf("close - Encerrar um Programa \n");
    printf("atualiza - Teste -> Atualizar utilizadores \n");
    printf("leitura - Teste -> Leitura de Itens \n");
    printf("promotor - Teste -> Conexão com promotores \n");

}

void promotores(){
    
}

int atualizaLista(int numUsers, user user[]) {
    int nlidos, saldo;
    nlidos = loadUsersFile(FUSERS);
    printf("\nHa %d utilizadores no sistema\n", nlidos);
    numUsers = numUsers + nlidos;
    saldo = getUserBalance("Paulo");
    updateUserBalance("Paulo", saldo-1);
    saveUsersFile(FUSERS);
    return numUsers;
}

int le_itens(int numItens, item items[]) {
    if(numItens == MAXITEMS){
        printf("Nao e possivel ler mais itens\n");
        return numItens;
    }
    
    FILE *file;
    file = fopen(fileFI, "rt");
    if(file == NULL){
        printf("\nNao foi possivel abrir o ficheiro dos itens\n");
        return numItens;
    }
    while(numItens < MAXITEMS && fscanf(file, "%d %s %s %d %d %d %s %s", items[numItens-1].IDitem, items[numItens-1].name, items[numItens-1].category, items[numItens-1].current_value, items[numItens-1].value, items[numItens-1].duration, items[numItens-1].user_sell, items[numItens-1].user_buyer)){
        printf("lido item: %s", items[numItens-1].name);
        numItens++;
    }
    fclose(file);
    return numItens;
}

int main(int argc, char *argv[]){
    char comando[50], arg[50];
    int numUsers = 0, numItens = 0;

    user listaUsers[MAXUSERS];
    item items[MAXITEMS];

    if (getenv("FPROMOTERS") != NULL)
        strcpy(fileFP, getenv("FPROMOTERS"));
    if (getenv("FUSERS") != NULL)
        strcpy(fileFU, getenv("FUSERS"));
    if (getenv("FITEMS") != NULL)
        strcpy(fileFI, getenv("FITEMS"));


    comandos();
    do{
        printf("Introduza um comando: ");
        fgets(comando,50,stdin);
        comando[strlen(comando) - 1] = '\0';
        if(strcmp(comando, "help\0") == 0){
            comandos();
        }
        if(strcmp(comando, "users\0") == 0){
            printf("comando valido \n");
            for(int i = 0; i < numUsers ; i++){
                printf("\n %s \n", listaUsers[i].username);
            }
        }
        if(strcmp(comando, "list\0") == 0){
            printf("comando valido \n");
        }
        if(strncmp(comando, "kick", 4) == 0){
            if(strcmp(comando, "kick\0") != 0){ 
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n Kick do user %s \n", arg);
            }
            printf("E necessario definir o user a ser expulso \n");
        }
        if(strcmp(comando, "prom\0") == 0){
            printf("comando valido \n");
        }
        if(strcmp(comando, "reprom\0") == 0){
            printf("comando valido \n");
        }
        if(strncmp(comando, "cancel", 6) == 0){
            if(strcmp(comando, "cancel\0") != 0){ 
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n cancel do user %s \n", arg);
            }
            printf("E necessario definir o promotor a ser cancelado \n");
        }
        if(strcmp(comando, "close\0") == 0){
            printf("\n A sair...\n");
        }
        if(strcmp(comando, "atualiza\0") == 0){
            numUsers = atualizaLista(numUsers, listaUsers);
        }
        if(strcmp(comando, "leitura\0") == 0){
            numItens = le_itens(numItens, items);
        }
        if(strcmp(comando, "promotor\0") == 0){
            promotores();
        }

    }while(strcmp(comando, "close"));
}