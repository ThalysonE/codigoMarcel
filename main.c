#include <stdio.h>
#include <stdlib.h>

// 1 - Cada nó da árvore deve representar um voo, contendo os seguintes campos: número do voo, origem, destino, data, horário, número de assentos disponíveis.
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

// 3 - Implemente uma função para remover um voo da árvore, atualizando a estrutura para manter a propriedade da árvore binária.
Voo* remover(Voo *raiz, int chave) {
    if(raiz == NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    } else { // procura o nó a remover
        if(raiz->numero == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerda == NULL && raiz->direita == NULL) {
                printf("Removendo o Voo: Numero: %d, Origem: %s, Destino: %s",raiz->numero, raiz->origem, raiz->destino);
                free(raiz);
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->esquerdA != NULL && raiz->direita != NULL){
                    Voo *aux = raiz->esquerda;
                    while(aux->direito != NULL)
                        aux = aux->direita;
                    raiz->numero = aux->numero;
                    strcpy(raiz->origem,aux->origem); //atualiza a string
                    strcpy(raiz->destino,aux->destino);
                    raiz->data = aux->data // falta mudar pra nova forma
                    raiz->horario = aux->horario;
                    raiz->numeroAssentos = aux->numeroAssentos;
                    aux->numero = chave;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    Voo *aux;
                    if(raiz->esquerdo != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;

                    free(raiz);
                    printf("Voo de numero %d removido!\n", chave);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->numero)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direita = remover(raiz->direita, chave);
            return  raiz;
        }
    }
}
// 6 - Implemente uma função para listar todos os voos com menos de 10 assentos disponíveis.
void imprimirVoos(Voo *raiz) {
    if (raiz != NULL) {
        if (raiz->numeroAssentos < 10)
            printf("Numero: %d, Origem: %s, Destino: %s, Data: %s, Horario: %d", raiz->numero, raiz->origem,raiz->destino, raiz->data, raiz->horario); //aqui tbm precisa mudar a forma da data
        imprimirVoos(raiz->esquerda);
        imprimirVoos(raiz->direita);
    }
}
//10 - O código deve implementar uma maneira de exibir a árvore de maneira intuitiva no console.
void imprimirArvore(Voo* raiz, int espacos) {
    if (raiz == NULL) {
        return;
    }

    espacos += 10;

    imprimirArvore(raiz->direita, espacos);

    printf("\n");
    for (int i = 10; i < espacos; i++) {
        printf(" ");
    }
    printf("%d - Destino: %s\n", raiz->numero, raiz->destino);

    imprimirArvore(raiz->esquerda, espacos);
}
