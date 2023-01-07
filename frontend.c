#include"header.h"

int fd_serv, fd_cli;

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

int login(user utilizador){
    int res;
    int saldo;
    fd_serv = open(PIPE_FRONT_BACK, O_WRONLY);
    int value = FLAG_NEW_USER;
    res = write(fd_serv, &value, sizeof(int));
    res = write(fd_serv, &utilizador, sizeof(utilizador));
    
    res = read(fd_cli, &saldo, sizeof(saldo));
    if(saldo != -1){
        return saldo;

    }
    return -1;
}

int main(int argc, char *argv[]){
    char comando[50], arg[50];
    user utilizador;
    int numItens = 0, res, valido = 0;
    item items[MAXITEMS];
    fd_set fontes;
    struct timeval t;
    
    
    if(access(PIPE_FRONT_BACK, F_OK) != 0){
        printf("[ERROR] Nao existe backend em execucao\n");
        return 0;
    }

    if(argc != 3){
        printf("Insira username e password\n");
        return 0;
    }
    strcpy(utilizador.username, argv[1]);
    strcpy(utilizador.password, argv[2]);

    sprintf(utilizador.pipe_name, PIPE_BACK_FRONT, getpid());
    if(mkfifo(utilizador.pipe_name, 0600) == -1){
        printf("[ERROR] Ao criar o pipe\n");
        return 0;
    }
    fd_cli = open(utilizador.pipe_name,O_RDWR);

    utilizador.saldo = login(utilizador);
    if(utilizador.saldo == -1)
        return 0;
    printf("\n\n *** Bem Vindo %s ***\n\n", utilizador.username);

    if (getenv("HEARTBEAT") != NULL)
        nmaxalive = atoi(getenv("HEARTBEAT"));


    comandos();
    do{
        fflush(stdout);
        printf("Introduza um comando: ");
        fflush(stdout);

        FD_ZERO(&fontes);
        FD_SET(0, &fontes);
        FD_SET(fd_cli, &fontes);
        t.tv_sec =20;
        t.tv_usec=0;
        res = select(fd_cli + 1, &fontes, NULL, NULL, &t);

        if(res > 0 && FD_ISSET(0, &fontes)){        //VEIO DO TECLADO
            valido = 0;
            fgets(comando,50,stdin);
            comando[strlen(comando) - 1] = '\0';
            if(strncmp(comando, "sell", 4) == 0){
                if(contaWords(comando) == 6 && numItens < MAXITEMS){
                    strcpy(arg, strtok(comando, " "));
                    strcpy(arg, strtok(NULL, " "));
                    strcpy(items[numItens].name, arg);
                    strcpy(arg, strtok(NULL, " "));
                    strcpy(items[numItens].category, arg);
                    strcpy(arg, strtok(NULL, " "));
                    items[numItens].value = atoi(arg);
                    strcpy(arg, strtok(NULL, " "));
                    items[numItens].current_value = atoi(arg);
                    strcpy(arg, strtok(NULL, " "));
                    items[numItens].duration = atoi(arg);
                    strcpy(items[numItens].user_buyer, "");
                    strcpy(items[numItens].user_sell, utilizador.username);
                    printf("\n*Item colocado a leilao\n");
                    
                    int value = FLAG_NEW_ITEM;
                    res = write(fd_serv, &value, sizeof(int));
                    res = write(fd_serv, &items[numItens], sizeof(items[numItens]));
                    res = read(fd_serv, &items[numItens], sizeof(items[numItens]));

                    numItens++;
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
                int value = FLAG_TIME;
                write(fd_serv, &value, sizeof(int));
                write(fd_serv, &utilizador, sizeof(utilizador));
                int segundos;
                res = read(fd_cli, &segundos, sizeof(segundos));
                printf("Hora: %d \n", segundos); 
            }
            if(strncmp(comando, "buy", 3) == 0){
                if(contaWords(comando)==3){
                    strcpy(arg, strtok(comando, " "));
                    strcpy(arg, strtok(NULL, " "));
                    int id = atoi(arg);
                    strcpy(arg, strtok(NULL, " "));
                    int valor = atoi(arg);
                    if(utilizador.saldo > valor){
                        for(int i = 0; i<numItens; i++){
                            if(items[i].IDitem == id){
                                if(items[i].current_value < valor){
                                    printf("Licitou valor para item %d \n", id);
                                    items[i].current_value = valor;
                                    int value = FLAG_LICITACAO;
                                    write(fd_serv, &value, sizeof(int));
                                    write(fd_serv, &items[i], sizeof(items[i]));
                                    read(fd_cli, &items[i], sizeof(items[i]));
                                }
                                else{
                                    printf("Impossivel licitar porque o valor atual e de %d! \n", items[i].current_value);
                                }
                            }
                        }
                    }
                    printf("Impossivel licitar!\n");
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
                    utilizador.saldo = utilizador.saldo + atoi(arg);
                    printf("\n*Saldo atual: %d€ \n", utilizador.saldo);
                    int value = FLAG_CARREGAMENTO;
                    write(fd_serv, &value, sizeof(int));
                    write(fd_serv, &utilizador, sizeof(utilizador));
                }
                else{
                    printf("E necessario definir o valor que deseja carregar\n"); // add <value>
                }
            }
            if(strcmp(comando, "exit\0") == 0){
                printf("\n*A sair...\n"); //exit
                int value = FLAG_EXIT_USER;
                res = write(fd_serv, &value, sizeof(int));
                res = write(fd_serv, &utilizador, sizeof(utilizador));
            }
        }else if(res > 0 && FD_ISSET(fd_cli, &fontes)){        //VEIO DO PIPE DO SERVIDOR
            printf("recebeu do pipe\n");
        }

    }while(strcmp(comando, "exit"));
    remove(utilizador.pipe_name);
    close(fd_cli);
    unlink(utilizador.pipe_name);
    close(fd_serv);
}