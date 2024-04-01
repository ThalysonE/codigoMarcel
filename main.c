#include <stdio.h>
#include <stdlib.h>

typedef struct voo{
    int numVoo;
    char origem[30];
    char destino[30];
    char data[10];
    int horario; // numero de quatro digitos
    int numAssentos;
    struct voo *esquerda,*direita
    short altura;
} Voo;
