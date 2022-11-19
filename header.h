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
#define MAXITEMS 30             //maximo de itens á venda
#define TAM 50

typedef struct utilizador{
    char username[TAM];
    char password[TAM];
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
}promotor;