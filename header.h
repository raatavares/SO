char fileFP[20]="promoter.txt";
char fileFU[20]="user.txt";
char fileFI[20]="item.txt";
#define FPROMOTERS fileFP
#define FUSERS fileFU
#define FITEMS fileFI
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
