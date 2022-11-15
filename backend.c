#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"
//#include"users_lib.h"

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

int main(int argc, char *argv[]){
    char comando[50], arg[20];

    if (getenv("FPROMOTERS") != NULL)
        strcpy(fileFP, getenv("FPROMOTERS"));
    if (getenv("FUSERS") != NULL)
        strcpy(fileFU, getenv("FUSERS"));
    if (getenv("FITEMS") != NULL)
        strcpy(fileFI, getenv("FITEMS"));


    //if (isUserValid("paulo", "paulo2") == -1)
    //    printf("Funciona");
    //if (isUserValid("paulo", "paulo1") == 0)
    //    printf("Funciona");


    comandos();
    do{
        printf("Introduza um comando: ");
        fgets(comando,50,stdin);
        comando[strlen(comando) - 1] = '\0';
        //strcpy(arg, strtok(comando," "));
        if(strcmp(comando, "help\0") == 0){
            comandos();
        }
        if(strcmp(comando, "users\0") == 0){
            printf("comando valido \n");
        }
        if(strcmp(comando, "list\0") == 0){
            printf("comando valido \n");
        }
        if(strcmp(comando, "kick") == 0){
            if(strcmp(comando, "kick\0")!=0){   //Validar 2 argumento
            strcpy(arg, strtok(NULL," "));
            printf("\ncomando validado com arg = %s \n", arg);
            }
            printf("comando valido \n");
        }
        if(strcmp(comando, "prom\0") == 0){
            printf("comando valido \n");
        }
        if(strcmp(comando, "reprom\0") == 0){
            printf("comando valido \n");
        }
        if(strcmp(comando, "cancel") == 0){  //2 arg
            printf("comando valido \n");
        }
        if(strcmp(comando, "close\0") == 0){
            printf("\n A sair...\n");
        }

    }while(strcmp(comando, "close"));
}