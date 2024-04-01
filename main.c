#include <stdio.h>
#include <stdlib.h>

struct data{
    int dia;
    int mes;
    int ano;
};

typedef struct voo{
    int numVoo;
    char origem[20];
    char destino[20];
    struct data dtVoo; // pode utilizar uma biblioteca
    int horario; // numero de quatro digitos
    int numAssentosDisp;
} Voo;

Voo inserirDados(){
    Voo novo;
    printf("\nDigite o número do voo: ");
    scanf("%d", &novo.numVoo);
    printf("\nDigite o nome da origem do voo: ");
    scanf(" %19[^\n]", novo.origem); 
    printf("\nDigite o destino do Voo: ");
    scanf(" %19[^\n]", novo.destino); 
    printf("\nDigite o horario do voo: ");
    scanf("%d", &novo.horario);
    printf("Digite o dia do Voo no formato (dd/mm/aa)");
    scanf("%d/%d/%d", &novo.dtVoo.dia, &novo.dtVoo.mes, &novo.dtVoo.ano);
    printf("\nDigite o número de assentos disponiveis no voo: ");
    scanf("%d", &novo.numAssentosDisp);
    return novo;
}
