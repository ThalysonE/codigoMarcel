#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1 - Cada nó da árvore deve representar um voo, contendo os seguintes campos: número do voo, origem, destino, data, horário, número de assentos disponíveis.
typedef struct voo{
    int numero;
    char origem[30];
    char destino[30];
    char data[10];
    int horario; // numero de quatro digitos
    int numeroAssentos;
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
                if(raiz->esquerda != NULL && raiz->direita != NULL){
                    Voo *aux = raiz->esquerda;
                    while(aux->direita != NULL)
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
                    if(raiz->esquerda != NULL)
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
            printf("\nNumero: %d, Origem: %s, Destino: %s, Data: %s, Horario: %d\n", raiz->numero, raiz->origem,raiz->destino, raiz->data, raiz->horario); //aqui tbm precisa mudar a forma da data
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

int main(){
    Voo *raiz=NULL;
    int op,chave;
    char origem[20],destino[20];
    
    
    //Menu do codigo
    do{
        printf("\n0 - Sair\n1 - Inserir\n2 - Remover\n3 -Buscar Voo\n4 - Listar todos voos com assentos disponiveis\n5 - Listar todsos os voos com menos de 10 assentos\n6 - Numero total de voos disponiveis\n7 - Geração de uma arvore balanceada aleatória\n8 - Exibicao da arvore\n");
        scanf("%d",&op);
        switch (op) {
            case 0:
                printf("\nSaindo...\n");
                break;
            case 1:
                //incluir os dados da funcao inserir
                break;
            case 2:
                printf("\nDigite o numero do voo a ser apagado: ");
                scanf("%d",&chave);
                remover(raiz,chave);
                break;
            case 3:
                printf("\nDigite o a origem da viagem: ");
                scanf("%s",origem);
                printf("\nDigite o destino da viagem: ");
                scanf("%s",destino);
                printf("\nDigite a data da viajem: "); //alterar pra nova forma da data e adicionar o scanf
                break;
            case 4:
            // falta implementar
                break;
            case 5:
                if(raiz != NULL)
                    imprimirVoos(raiz);
                else
                    printf("\n A raiz não possui nenhum valor");
                break;
            case 6:
                //falta inserir
                break;
            case 7:
                imprimirArvore(raiz,5);
                break;
            default:
                printf("\nOpcao invalida!");
                break;
        }
    }while(op != 0);
}
