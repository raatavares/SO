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
}

void promotores(){  //falta ficheiro do prof

}

void atualizaUtilizadores(){    //Falta biblioteca
    //loadUsersFile();
    //saveUsersFile();
}

void leituraItens(){

}

int atualizaLista(int numUsers, user users[]) {
    int nlidos;
    nlidos = loadUsersFile(FUSERS);
    for(int i = 0; i < nlidos; i++){
        users[i].saldo = users[i].saldo - 1;
    }
    numUsers = numUsers + nlidos;
    printf("\nForam lidos: %d \n", nlidos);
    return numUsers;
}

int main(int argc, char *argv[]){
    char comando[50], arg[50];
    int numUsers = 0;

    user listaUsers[MAXUSERS];

    if (getenv("FPROMOTERS") != NULL)
        strcpy(fileFP, getenv("FPROMOTERS"));
    if (getenv("FUSERS") != NULL)
        strcpy(fileFU, getenv("FUSERS"));
    if (getenv("FITEMS") != NULL)
        strcpy(fileFI, getenv("FITEMS"));


    numUsers = atualizaLista(numUsers, listaUsers);

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

    }while(strcmp(comando, "close"));
}