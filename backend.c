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
    char frase[TAM];
    
    int pl[2], estado;
    pipe(pl);
    int res=fork();
    if(res == 0){
        close(1);//fechar acesso ao monitor
        dup(pl[1]);//duplicar p[1] na primeira posição do pipe
        close(pl[0]);//fechar extremidade de leitura do pipe
        close(pl[1]);//fechar extremidade de escrita do pipe
        execl("black_friday", "black_friday", NULL);
    }
    close(pl[1]);
    read(pl[0], &frase, TAM);
    close(pl[0]);
    wait(&estado);
    printf("Promocao: %s\n", frase);
}

int atualizaLista(int numUsers, user user[], char nome[]) {
    int nlidos, saldo;
    nlidos = loadUsersFile(FUSERS);
    numUsers = numUsers + nlidos;
    if(getUserBalance(nome) == -1){
        printf("Nao existe ninguem com esse nome!\n");
        return -1;

    }

    saldo = getUserBalance(nome);
    updateUserBalance(nome, saldo-1);
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
    while(numItens < MAXITEMS && fscanf(file, "%d %s %s %d %d %d %s %s\n", &items[numItens].IDitem, items[numItens].name, items[numItens].category, &items[numItens].current_value, &items[numItens].value, &items[numItens].duration, items[numItens].user_sell, items[numItens].user_buyer)!=EOF){
        printf("Lido item: %s\n", items[numItens].name);
        numItens++;
    }
    fclose(file);
    return numItens;
}

int le_users(int numUsers, user users[]) {
    if(numUsers == MAXUSERS){
        printf("Nao e possivel ler mais users\n");
        return numUsers;
    }
    
    FILE *file;
    file = fopen(fileFU, "rt");
    if(file == NULL){
        printf("\nNao foi possivel abrir o ficheiro dos users\n");
        return numUsers;
    }
    while(numUsers < MAXUSERS && fscanf(file, "%s %s %d\n", users[numUsers].username, users[numUsers].password, &users[numUsers].saldo)!=EOF){
        printf("Lido user: %s\n", users[numUsers].username);
        numUsers++;
    }
    fclose(file);
    return numUsers;
}

void adicionaUsers(user aux, user users[], int numUsers){
    printf("Novo utilizador: %s\n", aux.username);
    strcpy(users[numUsers].password,aux.password);
    strcpy(users[numUsers].username,aux.username);
    users[numUsers].saldo=aux.saldo;
    strcpy(users[numUsers].pipe_name,aux.pipe_name);
    numUsers++;
}

int main(int argc, char *argv[]){
    char comando[50], arg[50], mensagem[50];
    int numUsers = 0, numItens = 0, numProm = 0, res, fd_cli;
    fd_set fontes;
    struct timeval t;

    
    if(access(PIPE_FRONT_BACK, F_OK) == 0){
        printf("[ERROR] Backend ja esta em execucao\n");
        return 0;
    }
    if(mkfifo(PIPE_FRONT_BACK, 0666) != 0){
        printf("[ERROR] Ao criar o pipe\n");
        return 0;
    }
    int fd_serv = open(PIPE_FRONT_BACK, O_RDWR);
    
    

    user listaUsers[MAXUSERS], aux;
    item items[MAXITEMS];
    promotor listaProm[MAXPROMOTERS];

    if (getenv("FPROMOTERS") != NULL)
        strcpy(fileFP, getenv("FPROMOTERS"));
    if (getenv("FUSERS") != NULL)
        strcpy(fileFU, getenv("FUSERS"));
    if (getenv("FITEMS") != NULL)
        strcpy(fileFI, getenv("FITEMS"));


    comandos();
    do{
        fflush(stdout);
        printf("\nIntroduza um comando: ");
        fflush(stdout);

        FD_ZERO(&fontes);
        FD_SET(0, &fontes);
        FD_SET(fd_serv, &fontes);
        t.tv_sec =20;
        t.tv_usec=0;
        res = select(fd_serv + 1, &fontes, NULL, NULL, &t);

        if(res > 0 && FD_ISSET(0, &fontes)){        //VEIO DO TECLADO
            fgets(comando,50,stdin);
            comando[strlen(comando) - 1] = '\0';
            if(strcmp(comando, "help\0") == 0){
                comandos();
            }
            if(strcmp(comando, "users\0") == 0){
                if( numUsers == 0)
                    printf("Nao existem users!\n");
                for(int i = 0; i < numUsers ; i++){
                    printf("Users: %s \n", listaUsers[i].username);
                }
            }
            if(strcmp(comando, "list\0") == 0){
                if( numItens == 0)
                    printf("Nao existem itens!\n");
                for(int i = 0; i < numItens ; i++){
                    printf("Item %d - %s: (categoria)%s (preco atual)%d (preco base)%d (vendedor)%s (comprador)%s \n", items[i].IDitem, items[i].name, items[i].category, items[i].current_value, items[i].value, items[i].user_sell, items[i].user_buyer);
                }
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
                if( numProm == 0)
                    printf("Nao existem promocoes!\n");
                for(int i = 0; i < numProm ; i++){
                    printf("Promotor: %s \n", listaProm[i].name);
                }
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
            if(strncmp(comando, "atualiza", 8) == 0){
                if(strcmp(comando, "atualiza\0") != 0){ 
                    strcpy(arg, strtok(comando, " "));
                    strcpy(arg, strtok(NULL, " "));
                    if((numUsers = atualizaLista(numUsers, listaUsers, arg)) != -1)
                        printf("%s foi atualizado\n", arg);
                }else
                    printf("E necessario definir o nome a ser atualizado \n");
            }
            if(strcmp(comando, "leitura\0") == 0){
                numItens = le_itens(numItens, items);
                numUsers = le_users(numUsers, listaUsers);
            }
            if(strcmp(comando, "promotor\0") == 0){
                promotores();
            }
        }else if(res > 0 && FD_ISSET(fd_serv, &fontes)){        //VEIO DO PIPE DO SERVIDOR
            res = read(fd_serv, &aux, sizeof(aux));
            printf("User : %s", aux.username);
            if (isUserValid(aux.username, aux.password) == 1 && numUsers < MAXUSERS){
                adicionaUsers(aux, listaUsers, numUsers); 
                strcpy(mensagem, "ACEITE");
            }else {
                strcpy(mensagem, "RECUSADO");
            }
            printf("%s\n", mensagem);
            fd_cli = open(aux.pipe_name, O_WRONLY);
            res = write(fd_cli, &mensagem, sizeof(mensagem));
        }

        

    }while(strcmp(comando, "close"));
    remove(PIPE_FRONT_BACK);
    close(fd_serv);
    unlink(PIPE_FRONT_BACK);
}
