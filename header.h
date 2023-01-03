#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>

char fileFP[20]="promoter.txt";
char fileFU[20]="user.txt";
char fileFI[20]="item.txt";
int nmaxalive = 60;

#define FPROMOTERS fileFP
#define FUSERS fileFU
#define FITEMS fileFI
#define HEARTBEAT nmaxalive
#define MAXUSERS 20
#define MAXPROMOTERS 10
#define MAXITEMS 30
#define TAM 50

#define PIPE_FRONT_BACK "SERV"
#define PIPE_BACK_FRONT "CLI%d"

typedef struct utilizador{
    char username[TAM];
    char password[TAM];
    char pipe_name[TAM];
    int saldo;
}user;

typedef struct items{
    int IDitem;
    char name[TAM];
    char category[TAM];
    int current_value;
    int value;
    int duration;
    char user_sell[TAM];
    char user_buyer[TAM];
}item;

typedef struct promocoes{
    char category[TAM];
    int descont;
    int duration;
}promocao;

typedef struct promotores{
    char name[TAM];
    int pid;
}promotor;

typedef struct {
    promotor promotor[MAXPROMOTERS];
}backend;