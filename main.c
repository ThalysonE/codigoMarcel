#include <stdio.h>
#include <stdlib.h>


 //Cria uma estrutura para cada No que será utilizado na arvore

typedef struct no{
    int conteudo;
    struct no *esquerda, *direita;
}No;
//Insere um novo NO em uma arvore
No* inserirNovaVersao(No* raiz, int valor);
//Imprime todos os NOs da arvore
void imprimir(No *raiz);
//Remove um NO da arvore
No* remover(No* raiz, int valor);
//Dado um valor essa funcao realiza a busca desse valor na arvore
int buscar(No *raiz,int valor);
//Calcula a quantidade de Nos que a arvore possui
int tamanho(No *raiz);
//Calcula a altura da arvore. Que nada mais é do que a distancia do No folha mais longe até a raiz.
int alturaArv(No *raiz);


//Funcoes para o calculo da altura de uma subArvore
No* buscarNO(No *raiz,int valor);
int alturaSubArv(No *raiz, int chave);

No* inserirNovaVersao(No* raiz, int valor) {
    if (raiz == NULL) {
        No *novo = (No *) malloc(sizeof(No)); // cria um novo no para ser inserido e guarda o valor nele
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo; // quando chegar em NO nulo ele vai inserir esse valor e retorna para a recurção anterior
    } else {
        if (valor < raiz->conteudo)
            raiz->esquerda = inserirNovaVersao(raiz->esquerda, valor); // ultima recursão recebe o novo valor
        if (valor > raiz->conteudo)
            raiz->direita = inserirNovaVersao(raiz->direita, valor);
        return raiz; //todas as outras recursões recebem o mesmo valor que já se encontravam nela
    }
}
void imprimir(No *raiz){
    if(raiz != NULL){
        imprimir(raiz->esquerda); // imprime primeiramente todos os valores menor que a raiz
        printf("%d ", raiz->conteudo);//imprime a raiz
        imprimir(raiz->direita); // imprime todos os valore maiores que a raiz
    }
}
No* remover(No* raiz, int valor){
    if(raiz == NULL){
        printf("Valor nao encontrado");
        return NULL;
    }
    else{
        if(raiz->conteudo == valor) {
            //verifica se o No é uma folha
            if (raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                return NULL;
            } else {
                //verifica se um dos filhos é nulo
                if (raiz->esquerda == NULL || raiz->direita == NULL) {
                    No *aux;
                    if (raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux; //Usando a recursão esse valor vai retornar para substituir o No apagado
                }
                //entra nessa condicao caso todos os filhos possuem valores
                else{
                    /* Nesse pode-se utilizar dois casos para substituir o valor a ser apagado
                    1 - Percorre a subArvore a esquerda e pega o valor "mais a direita", ou seja, o valor que mais se aproxima do valor do No a ser apagado
                    2 - Percorre a SubArvore a direira e pega o valor "mais a esquerda" do conteúdo da raiz, ou seja o valor que chegue mais próximo do valor da raiz

                    Nesse caso é utilizado o primeiro caso então veja a resolução:
                    */

                    No *aux = raiz->esquerda; // cria uma variável auxiliar para percorrer a arvore
                    while(aux->direita != NULL)//repetição para encontrar o NO mais a direita da raiz
                        aux = aux->direita;
                    raiz->conteudo = aux->conteudo;// substitue o conteudo da raiz pelo o valor mais próximo da direita
                    aux->conteudo = valor;//O No encontrado recebe o valor a ser apagado
                    raiz->esquerda = remover(raiz->esquerda, valor); // remove o NO mais a direita juntamente com o seu valor
                    return raiz;
                }
            }
        }else{
            if(valor < raiz->conteudo)
                raiz->esquerda = remover(raiz->esquerda,valor);
            if(valor > raiz->conteudo)
                raiz->direita =  remover(raiz->direita,valor);
            return raiz;
        }
    }
}
int buscar(No *raiz,int valor){
    if(raiz == NULL){
        printf("\nValor nao encontrado!");
        return  -1;
    }else{
        if(raiz->conteudo == valor){
            return raiz->conteudo;
        }else{
            if(valor < raiz->conteudo){
                return buscar(raiz->esquerda,valor); // O valor é desempilhado até ser retornado na main
            }else
                return buscar(raiz->direita,valor);

        }
    }
}
int tamanho(No *raiz){
    if(raiz == NULL)
        return 0;
    else
        return  1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
}
No* buscarNO(No *raiz,int valor){
    if(raiz == NULL){
        printf("\nValor nao encontrado!");
        return  NULL;
    }else{
        if(raiz->conteudo == valor){
            return raiz;
        }else{
            if(valor < raiz->conteudo){
                return buscarNO(raiz->esquerda,valor);
            }else
                return buscarNO(raiz->direita,valor);

        }
    }
}
int alturaArv(No *raiz){
    //verifica se raiz é nula ou é uma folha
    if(raiz == NULL || raiz->direita == NULL && raiz->esquerda == NULL)
        return  0;
    else{
        int esq = 1 + alturaArv(raiz->esquerda);//
        int dir = 1 + alturaArv(raiz->direita);
        //retorna o maior
        if(esq > dir)
            return  esq;
        else
            return dir;
    }
}
int alturaSubArv(No *raiz, int chave){
    No *no = buscarNO(raiz, chave);
    if(no)
        return  alturaArv(no);
    else
        return -1;
}

int main(){
    int op, valor;
    No *raiz = NULL;
    do{

        printf("\n0 - sair\n1 - inserir\n2 - imprimir\n3 - remover\n4 - buscar\n5 - altura da arvore\n6 - altura de uma subArvore\n");
        scanf("%d", &op);


        switch (op) {
            case 0:
                printf("\nSaindo...\n");
                break;
            case 1:
                printf("digite um valor: ");
                scanf("%d", &valor);
                raiz = inserirNovaVersao(raiz,valor);
                //inserir(&arv, valor);
                break;
            case 2:
                printf("\nimpressao da arvore binaria:\n");
                imprimir(raiz);
                printf("\n");
                printf("Tamanho: %d\n", tamanho(raiz));
                break;
            case 3:
                printf("Digite um valor para remover: ");
                scanf("%d",&valor);
                raiz = remover(raiz,valor);
                break;
            case 4:
                printf("Digite um numero para buscar: ");
                scanf("%d",&valor);
                printf("Resultado da busca: %d\n", buscar(raiz,valor));
                break;
            case 5:
                printf("A altura da arvore eh: %d", alturaArv(raiz));
                break;
            case 6:
                printf("Digite um numero para buscar: ");
                scanf("%d",&valor);
                printf("\nA altura da subArvore eh: %d\n", alturaSubArv(raiz,valor));
                break;
            default:
                printf("\nOpcao invalida...\n");
        }
    }while(op!=0);
}