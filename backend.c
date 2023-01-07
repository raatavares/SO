#include"header.h"
#include"users_lib.h"
#include <pthread.h>

backend info;


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

void *increment_seconds(void *arg){
    
    while(info.FLAG_TERMINOU == 0){
        sleep(1);
        info.seconds++;
        for(int i = 0; i < info.numItens; i++){
            info.items[i].duration--;
        }
        for(int i = 0; i < info.numPromocao; i++){
            info.promocoes[i].duration--;
        }
        //verificaExpiracao();
    }
    return NULL;
}

void* LaunchPromotores(void * dados){

    promotor* data = (promotor *)dados;

    pthread_t t[20];
    int pl[2];
    pipe(pl);
    char promotor1[20], aux[20]="";
    char path[100];
    int id = -1;

            id=fork();

    if(id == 0){
        close(1);//fechar acesso ao monitor
        dup(pl[1]);//duplicar p[1] na primeira posição do pipe
        close(pl[0]);//fechar extremidade de leitura do pipe
        close(pl[1]);//fechar extremidade de escrita do pipe

        sprintf(path,"Promotores/%s",data->name);

        execl(path, data->name, NULL);

        printf("Promotor nao lançado\n");
        exit(1);
    }
    else
    {
        data->pid=id;
        printf("\n\n->%d\n\n",data->pid);
        close(pl[1]);

    while(1)
    {
        read(pl[0],&promotor1,sizeof(promotor1));

        if(strcmp(promotor1,aux)!=0)
        {
            printf("\nPromotor: %s",promotor1);
            strcpy(aux,promotor1);
            strcpy(promotor1,"");
        }
    }

    close(pl[0]);
    }

    pthread_exit(NULL);
}

void verificaExpiracao(){
    for(int i = 0; i < info.numItens; i++){
        if(info.items[i].duration == 0){
            if(strcmp(info.items[i].user_buyer , "") == 0)
                printf("<Tempo expirou> Item %d - %s foi vendido: (categoria)%s (preco atual)%d (comprador)%s \n", info.items[i].IDitem, info.items[i].name, info.items[i].category, info.items[i].current_value, info.items[i].user_buyer);
            else
                printf("<Tempo expirou> Item: %d nao foi vendido!\n", info.items[i].IDitem);
        }
    }
    for(int i = 0; i < info.numPromocao; i++){
        if(info.promocoes[i].duration == 0){
                printf("<Tempo expirou> Promocao de %d na categoria %s expirou! \n", info.promocoes[i].descont, info.promocoes[i].category);
        }
    }
    return;
}

void Promotores(backend* data){

    int pd[MAXPROMOTERS];
    char prom[20];
    int error,i=0;
    pthread_t promotorThread[MAXPROMOTERS];

    FILE *filedesc;
    filedesc = fopen("promoter.txt","r");

    while (fscanf(filedesc,"%s %d",prom,&error) == 1 && i < 10 ){

        strcpy( data->listaProm[i].name,prom);

        if(pthread_create(&promotorThread[i],NULL,&LaunchPromotores,&data->listaProm[i]) != 0) return;
        ++i;
    }

    i=0;
    while (i<10){
        pd[i] = data->listaProm[i].pid;
        ++i;
    }
}

void CancelPromotor (backend* dados, char* nome_prom){
    backend * data=(backend *)dados;
    int i=0;

    do {
        printf("\n\n");
        if(strcmp(data->listaProm[i].name,nome_prom) ==0 )
        {

            union sigval val;
            sigqueue(data->listaProm[i].pid, SIGUSR1 , val);

            strcpy(data->listaProm[i].name,"--");
        }
        ++i;
    } while (i<10);

    for (int j=0; j<10 ; j++)
    {
        printf("--[%s(%d(]",data->listaProm[j].name,j);
    }
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
    int res, fd_cli;
    fd_set fontes;
    struct timeval t;
    backend data;
    pthread_t thread;


    
    if(access(PIPE_FRONT_BACK, F_OK) == 0){
        printf("[ERROR] Backend ja esta em execucao\n");
        return 0;
    }
    if(mkfifo(PIPE_FRONT_BACK, 0666) != 0){
        printf("[ERROR] Ao criar o pipe\n");
        return 0;
    }
    int fd_serv = open(PIPE_FRONT_BACK, O_RDWR);
    info.seconds = 0;
    info.numItens = 0;
    info.numPromocao = 0;
    info.numProm = 0;
    info.numUsers = 0;
    info.FLAG_TERMINOU = 0;
    

    user aux;
    

    if (getenv("FPROMOTERS") != NULL)
        strcpy(fileFP, getenv("FPROMOTERS"));
    if (getenv("FUSERS") != NULL)
        strcpy(fileFU, getenv("FUSERS"));
    if (getenv("FITEMS") != NULL)
        strcpy(fileFI, getenv("FITEMS"));

    //cria thread
    pthread_create(&thread, NULL, increment_seconds, NULL);

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
                if( info.numUsers == 0)
                    printf("Nao existem users!\n");
                for(int i = 0; i < info.numUsers ; i++){
                    printf("Users: %s \n", info.listaUsers[i].username);
                }
            }
            if(strcmp(comando, "list\0") == 0){
                if( info.numItens == 0)
                    printf("Nao existem itens!\n");
                for(int i = 0; i < info.numItens ; i++){
                    printf("Item %d - %s: (categoria)%s (preco atual)%d (preco base)%d (vendedor)%s (comprador)%s \n", info.items[i].IDitem, info.items[i].name, info.items[i].category, info.items[i].current_value, info.items[i].value, info.items[i].user_sell, info.items[i].user_buyer);
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
                if( info.numProm == 0)
                    printf("Nao existem promocoes!\n");
                for(int i = 0; i < info.numProm ; i++){
                    printf("Promotor: %s \n", info.listaProm[i].name);
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
                info.FLAG_TERMINOU = 1;
            }
            if(strncmp(comando, "atualiza", 8) == 0){
                if(strcmp(comando, "atualiza\0") != 0){ 
                    strcpy(arg, strtok(comando, " "));
                    strcpy(arg, strtok(NULL, " "));
                    if((info.numUsers = atualizaLista(info.numUsers, info.listaUsers, arg)) != -1)
                        printf("%s foi atualizado\n", arg);
                }else
                    printf("E necessario definir o nome a ser atualizado \n");
            }
            if(strcmp(comando, "leitura\0") == 0){
                info.numItens = le_itens(info.numItens, info.items);
                info.numUsers = le_users(info.numUsers, info.listaUsers);
            }
            if(strcmp(comando, "promotor\0") == 0){
                Promotores(&data);
            }
        }else if(res > 0 && FD_ISSET(fd_serv, &fontes)){        //VEIO DO PIPE DO SERVIDOR
            int flag;
            res = read(fd_serv, &flag, sizeof(flag));
            if (flag == FLAG_NEW_USER){
                res = read(fd_serv, &aux, sizeof(aux));
                fd_cli = open(aux.pipe_name, O_WRONLY);
                printf("\nNew User : %s  -  ", aux.username);
                if (isUserValid(aux.username, aux.password) == 1 && info.numUsers < MAXUSERS){
                    adicionaUsers(aux, info.listaUsers, info.numUsers); 
                    strcpy(mensagem, "ACEITE");
                }else {
                    strcpy(mensagem, "RECUSADO");
                }
                printf("%s\n", mensagem);
                res = write(fd_cli, &mensagem, sizeof(mensagem));
            }/*else if(flag == FLAG_NEW_ITEM){

            }else if(flag == FLAG_TIME){

            }else if(flag == FLAG_LICITACAO){

            }else if(flag == FLAG_CARREGAMENTO){

            } */           
        }

        

    }while(strcmp(comando, "close"));
    remove(PIPE_FRONT_BACK);
    close(fd_serv);
    unlink(PIPE_FRONT_BACK);
}
