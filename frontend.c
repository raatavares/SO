#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"

void comandos(){
    printf("========== Comando ========== \n");
    printf("sell - Colocar um item a leilao\n");
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

int contaWords(char str[]){
    int i = 0, nword = 1;

    while(str[i] != '\0'){
        if(str[i] == ' '){
            nword++;
        }
        i++;
    }
    return nword;
}

int main(int argc, char *argv[]){
    char comando[50], arg[50];
    

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
        printf("\nIntroduza um comando: ");
        fgets(comando,50,stdin);
        comando[strlen(comando) - 1] = '\0';
        if(strncmp(comando, "sell", 4) == 0){
            if(contaWords(comando) == 6){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                strcpy(arg, strtok(NULL, " "));
                strcpy(arg, strtok(NULL, " "));
                strcpy(arg, strtok(NULL, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n*Item colocado a leilao\n");
            }
            else{
                printf("E necessario defenir o nome, categoria, preco_base, preco_compre_ja, duracao \n"); // sell <name> <category> <value> <current_value> <duration>
            }
        }
        if(strcmp(comando, "list\0") == 0){
            printf("*comando valido \n"); // list
        }
        if(strncmp(comando, "licat", 5) == 0){
            if(strcmp(comando, "licat\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n*Lista selecionada por categoria\n");
            }
            else{
                printf("E necessario defenir a categoria \n"); // licat <category>
            }
        }
        if(strncmp(comando, "lisel", 5) == 0){
            if(strcmp(comando, "lisel\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n*Lista selecionada por vendedor\n");
            }
            else{
                printf("E necessario defenir o vendedor \n"); // lisel <user_sell>
            }
        }
        if(strncmp(comando, "lival", 5) == 0){
            if(strcmp(comando, "lival\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n*Lista selecionada ate ao valor: %s€\n", arg);
            }
            else{
                printf("E necessario defenir o valor \n"); // lival <preco-maximo>
            }
        }
        if(strncmp(comando, "litime", 6) == 0){
            if(strcmp(comando, "litime\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n*Lista selecionada ate ao prazo: %s\n", arg);
            }
            else{
                printf("E necessario defenir um prazo(em segundos) \n"); // litime <hora-em-segundos>
            }
        }
        if(strcmp(comando, "timet\0") == 0){
            printf("comando valido \n"); // time
        }
        if(strncmp(comando, "buy", 3) == 0){
            if(contaWords(comando)==3){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n*Item licitado %s\n", arg);
            }
            else{
                printf("E necessario defenir o id e o valor \n"); // buy <IDitem> <value>
            }
        }
        if(strcmp(comando, "cash\0") == 0){
            printf("*comando valido \n"); // cash
        }
        if(strncmp(comando, "add", 3) == 0){
            if(strcmp(comando, "add\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n*Carregado: %s€ \n", arg);
            }
            else{
                printf("E necessario defenir o valor que deseja carregar\n"); // add <value>
            }
        }
        if(strcmp(comando, "exit\0") == 0){
            printf("\n*A sair...\n"); //exit
        }

    }while(strcmp(comando, "exit"));

}