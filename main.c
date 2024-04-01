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



No* remover(No *raiz, int chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raiz->valor == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerdo == NULL && raiz->direito == NULL) {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    No *aux = raiz->esquerdo;
                    while(aux->direito != NULL)
                        aux = aux->direito;
                    raiz->valor = aux->valor;
                    aux->valor = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    No *aux;
                    if(raiz->esquerdo != NULL)
                        aux = raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->valor)
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}
