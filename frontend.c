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
    user utilizador;
    int numItens = 0;
    item items[MAXITEMS];
    int valido = 0;
    

    if(argc != 3){
        printf("Insira username e password\n");
        return 0;
    }
    strcpy(utilizador.username, argv[1]);
    strcpy(utilizador.password, argv[2]);
    printf("\n\n *** Bem Vindo %s ***\n\n", utilizador.username);


    if (getenv("HEARTBEAT") != NULL)
        nmaxalive = atoi(getenv("HEARTBEAT"));


    comandos();
    do{
        valido = 0;
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
                printf("E necessario definir o nome, categoria, preco_base, preco_compre_ja, duracao \n"); // sell <name> <category> <value> <current_value> <duration>
            }
        }
        if(strcmp(comando, "list\0") == 0){
            if( numItens == 0)
                printf("Nao existem itens!\n");
            for(int i = 0; i < numItens ; i++){
                printf("Item %d - %s: (categoria)%s (preco atual)%d (preco base)%d (vendedor)%s \n", items[i].IDitem, items[i].name, items[i].category, items[i].current_value, items[i].value, items[i].user_sell);
            }
        }
        if(strncmp(comando, "licat", 5) == 0){
            if(strcmp(comando, "licat\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                for(int i = 0; i < numItens ; i++){
                    if(strcmp(items[i].category, arg) == 0){
                        printf("Item %d - %s: (preco atual)%d (preco base)%d \n", items[i].IDitem, items[i].name, items[i].current_value, items[i].value);
                        valido = 1;
                    }
                }
                if(valido == 0)
                    printf("Nao existem itens na categoria %s", arg);
            }
            else{
                printf("E necessario definir a categoria \n");
            }
        }
        if(strncmp(comando, "lisel", 5) == 0){
            if(strcmp(comando, "lisel\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                for(int i = 0; i < numItens ; i++){
                    if(strcmp(items[i].user_sell, arg) == 0){
                        printf("Item %d - %s: (categoria)%s (preco atual)%d (preco base)%d \n", items[i].IDitem, items[i].name, items[i].category, items[i].current_value, items[i].value);
                        valido = 1;
                    }
                }
                if(valido == 0)
                    printf("Nao existem itens vendidos por %s", arg);
            }
            else{
                printf("E necessario definir o vendedor \n"); 
            }
        }
        if(strncmp(comando, "lival", 5) == 0){
            if(strcmp(comando, "lival\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                for(int i = 0; i < numItens ; i++){
                    if(items[i].value <= atoi(arg)){
                        printf("Item %d - %s: (categoria)%s (preco atual)%d (preco base)%d \n", items[i].IDitem, items[i].name, items[i].category, items[i].current_value, items[i].value);
                        valido = 1;
                    }
                }
                if(valido == 0)
                    printf("Nao existem itens ate %d€", atoi(arg));
            }
            else{
                printf("E necessario definir o valor \n"); 
            }
        }
        if(strncmp(comando, "litime", 6) == 0){
            if(strcmp(comando, "litime\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                for(int i = 0; i < numItens ; i++){
                    if(items[i].duration <= atoi(arg)){
                        printf("Item %d - %s: (categoria)%s (preco atual)%d (preco base)%d \n", items[i].IDitem, items[i].name, items[i].category, items[i].current_value, items[i].value);
                        valido = 1;
                    }
                }
                if(valido == 0)
                    printf("Nao existem itens ate %d segundos", atoi(arg));
            }
            else{
                printf("E necessario definir um prazo(em segundos) \n"); // litime <hora-em-segundos>
            }
        }
        if(strcmp(comando, "time\0") == 0){
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
                printf("E necessario definir o id e o valor \n"); // buy <IDitem> <value>
            }
        }
        if(strcmp(comando, "cash\0") == 0){
            printf("Saldo: %d \n", utilizador.saldo);
        }
        if(strncmp(comando, "add", 3) == 0){
            if(strcmp(comando, "add\0") != 0){
                strcpy(arg, strtok(comando, " "));
                strcpy(arg, strtok(NULL, " "));
                printf("\n*Carregado: %s€ \n", arg);
            }
            else{
                printf("E necessario definir o valor que deseja carregar\n"); // add <value>
            }
        }
        if(strcmp(comando, "exit\0") == 0){
            printf("\n*A sair...\n"); //exit
        }

    }while(strcmp(comando, "exit"));

}