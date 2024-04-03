#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 1 - Cada nó da árvore deve representar um voo, contendo os seguintes campos: número do voo, origem, destino, data, horário, número de assentos disponíveis.
typedef struct voo{
    int numero;
    char origem[20];
    char destino[20];
    char data[11];
    char horario[9];
    long int dataValor; // usando a biblioteca podemos chegar no valor da data e hora em segundos baseado no tempo unix
    int numeroAssentos;
    struct voo *esquerda,*direita;
    short altura;
} Voo;

Voo* novoNo(int x, char *origem, char *destino, char *data,char *horario, long int dataValor, int numeroAssentos){
    Voo *novo = malloc(sizeof(Voo));

    if(novo){
        novo->numero = x;
        strcpy(novo->origem,origem);
        strcpy(novo->destino, destino);
        strcpy(novo->data,data);
        strcpy(novo->horario,horario);
        novo->dataValor = dataValor;
        novo->numeroAssentos = numeroAssentos;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
    }
    else
        printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
short maior(short a, short b){
    return (a > b)? a: b;
}


//  Retorna a altura de um nó ou -1 caso ele seja null
short alturaDoNo(Voo *voo){
    if(voo == NULL)
        return -1;
    else
        return voo->altura;
}

//   Calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(Voo *voo){
    if(voo)
        return (alturaDoNo(voo->esquerda) - alturaDoNo(voo->direita));
    else
        return 0;
}

// --------- ROTAÇÕES ---------------------------

// função para a rotação à esquerda
Voo* rotacaoEsquerda(Voo *r){
    Voo *y, *f;

    y = r->direita;
    f = y->esquerda;

    y->esquerda = r;
    r->direita = f;

    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

// função para a rotação à direita
Voo* rotacaoDireita(Voo *r){
    Voo *y, *f;

    y = r->esquerda;
    f = y->direita;

    y->direita = r;
    r->esquerda = f;

    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

Voo* rotacaoEsquerdaDireita(Voo *r){
    r->esquerda = rotacaoEsquerda(r->esquerda);
    return rotacaoDireita(r);
}

Voo* rotacaoDireitaEsquerda(Voo *r){
    r->direita = rotacaoDireita(r->direita);
    return rotacaoEsquerda(r);
}

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
Voo* balancear(Voo *raiz){
    short fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direita) <= 0)
        raiz = rotacaoEsquerda(raiz);

        // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) >= 0)
        raiz = rotacaoDireita(raiz);

        // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

        // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->direita) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

/*
    Insere um novo nó na árvore
    raiz -> raiz da árvore
    x -> numero a ser inserido
    Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
Voo* inserir(Voo *raiz, int x, char *origem, char *destino,char *data, char *horario, long int dataValor, int numeroAssentos){
    if(raiz == NULL) // árvore vazia
        return novoNo(x, origem, destino, data, horario, dataValor, numeroAssentos);
    else{ // inserção será à esquerda ou à direita
        if (numeroAssentos < 0)
            printf("\nInsercao nao realizada!\nO numero de assentos eh menor que zero!\n");
        else if(x < raiz->numero)
            raiz->esquerda = inserir(raiz->esquerda, x, origem, destino,data, horario, dataValor, numeroAssentos);
        else if(x > raiz->numero)
            raiz->direita = inserir(raiz->direita, x, origem, destino,data, horario, dataValor, numeroAssentos);
        else
            printf("\nInsercao nao realizada!\nO elemento %d ja existe!\n", x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
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
                    strcpy(raiz->data, aux->data);
                    strcpy(raiz->horario,aux->horario);
                    raiz->dataValor = aux->dataValor;
                    raiz->numeroAssentos = aux->numeroAssentos;
                    aux->numero = chave;
                    printf("Elemento trocados!\n");
                    raiz->esquerda = remover(raiz->esquerda, chave); //remove o no da folha
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
            printf("\nNumero: %d, Origem: %s, Destino: %s, Data: %s, Horario: %s, Numero de Assentos: %d\n", raiz->numero, raiz->origem,raiz->destino, raiz->data, raiz->horario, raiz->numeroAssentos); //aqui tbm precisa mudar a forma da data
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
    printf("%d - Origem: %s -> Destino: %s\n", raiz->numero, raiz->origem, raiz->destino);

    imprimirArvore(raiz->esquerda, espacos);
}
int tamanho(Voo *raiz){
    if(raiz == NULL)
        return 0;
    else
        return  1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
}

void limparArvore(Voo *raiz) {
    if (raiz != NULL) {
        limparArvore(raiz->esquerda);
        limparArvore(raiz->direita);
        free(raiz);
    }
}

// 9 - Implementar uma maneira de criar uma arvore aleatória com 7 elementos
void gerarArvoreAleatoria(Voo **raiz) {
    // Excluir árvore anterior, se existir
    if (*raiz != NULL) {
        printf("Excluindo arvore anterior...\n");
        limparArvore(*raiz);
        *raiz = NULL;
    }
    // Aqui predefino alguns valores para os atributos de Voo
    int numeros[50] = {1, 2, 3, 4, 5, 6, 7};
    char origens[7][30] = {"Sao Paulo", "Rio de Janeiro", "Salvador", "Brasilia", "Fortaleza","Belo Horizonte", "Manaus"};
    char destinos[7][20] = {"Curitiba", "Recife", "Goiania","Belem", "Porto Alegre", "Sao Luis", "Campinas"};
    char datas[7][11] = {"2024-04-01", "2024-04-02", "2024-04-03", "2024-04-04", "2024-04-05", "2024-04-06", "2024-04-07"};
    char horarios[7][9] = {"08:00:00", "09:00:00", "10:00:00", "11:00:00", "12:00:00", "13:00:00", "14:00:00"};
    int assentos[7] = {150, 200, 100, 120, 180, 220, 170};

    // Inicializar a semente para a função rand()
    srand(time(NULL));

    // Inserir os elementos aleatórios na árvore
    for (int i = 0; i < 7; i++) {
        // Gerar números de voo aleatórios entre 1 e 1000
        int numero = numeros[i] + rand() % 100;
        int origemIndex = rand() % 7;
        int destinoIndex = rand() % 7;
        int dataIndex = rand() % 7;
        int horarioIndex = rand() % 7;
        int assentos = 50 + rand() % 251;

        // Inserir o voo na árvore
        *raiz = inserir(*raiz, numero, origens[origemIndex], destinos[destinoIndex], datas[dataIndex], horarios[horarioIndex], 0, assentos);
    }

    printf("Arvore binaria aleatoria gerada com sucesso!\n");
}

// Função temporária de buscar voos com assentos disponiveis
void listarVoosComAssentosDisponiveis(Voo *raiz) {
    if (raiz != NULL) {
        listarVoosComAssentosDisponiveis(raiz->esquerda);

        if (raiz->numeroAssentos > 0) {
            printf("Numero: %d, Origem: %s, Destino: %s, Data: %s, Horario: %s, Numero de Assentos: %d\n", raiz->numero, raiz->origem, raiz->destino, raiz->data, raiz->horario, raiz->numeroAssentos);
        }

        listarVoosComAssentosDisponiveis(raiz->direita);
    }
}

// 4- Buscar voos com base na origem, destino e data
void buscarVoosDisponiveis(Voo *raiz, char *origem, char *destino, char *data) {
    if (raiz != NULL) {
        // Verifica se o voo tem origem, destino e data correspondentes
        if (strcmp(raiz->origem, origem) == 0 && strcmp(raiz->destino, destino) == 0 && strcmp(raiz->data, data) == 0) {
            // Verifica se há assentos disponíveis
            if (raiz->numeroAssentos > 0) {
                printf("Numero: %d, Origem: %s, Destino: %s, Data: %s, Horario: %s, Numero de Assentos: %d\n", raiz->numero, raiz->origem, raiz->destino, raiz->data, raiz->horario, raiz->numeroAssentos);
            } else {
                printf("Voo encontrado, mas não há assentos disponíveis.\n");
            }
        }

        // Busca nos filhos da esquerda e direita
        buscarVoosDisponiveis(raiz->esquerda, origem, destino, data);
        buscarVoosDisponiveis(raiz->direita, origem, destino, data);
    }
}

// Função para converter a data e horário em um valor numérico
long int valorDataHora(char *data, char *horario) {
    struct tm tm_time;
    time_t timestamp;
    memset(&tm_time, 0, sizeof(struct tm));

    sscanf(data, "%d-%d-%d", &tm_time.tm_year, &tm_time.tm_mon, &tm_time.tm_mday);
    sscanf(horario, "%d:%d:%d", &tm_time.tm_hour, &tm_time.tm_min, &tm_time.tm_sec);
    tm_time.tm_year -= 1900;
    tm_time.tm_mon -= 1;
    tm_time.tm_isdst = -1;

    timestamp = mktime(&tm_time);
    return (long int)timestamp;
}

// Função auxiliar para criar e ordenar uma lista de voos disponíveis
void criarEOrdenarListaVoosDisponiveis(Voo *raiz, Voo *voosDisponiveis[], int *indice) {
    if (raiz != NULL) {
        if (raiz->numeroAssentos > 0) {
            voosDisponiveis[*indice] = raiz;
            (*indice)++;
        }
        criarEOrdenarListaVoosDisponiveis(raiz->esquerda, voosDisponiveis, indice);

        criarEOrdenarListaVoosDisponiveis(raiz->direita, voosDisponiveis, indice);
    }
}

// 5 - Função para listar todos os voos com assentos disponíveis e ordená-los em ordem crescente de data e hora
void listarVoosDisponiveisOrdenados(Voo *raiz) {
    if (raiz == NULL) {
        return;
    }

    Voo *voosDisponiveis[tamanho(raiz)];
    int indice = 0;
    criarEOrdenarListaVoosDisponiveis(raiz, voosDisponiveis, &indice);

    for (int i = 0; i < indice - 1; i++) {
        for (int j = i + 1; j < indice; j++) {
            long int valorDataHora1 = valorDataHora(voosDisponiveis[i]->data, voosDisponiveis[i]->horario);
            long int valorDataHora2 = valorDataHora(voosDisponiveis[j]->data, voosDisponiveis[j]->horario);
            if (valorDataHora1 > valorDataHora2) {
                Voo *temp = voosDisponiveis[i];
                voosDisponiveis[i] = voosDisponiveis[j];
                voosDisponiveis[j] = temp;
            }
        }
    }
    // Imprimir voos disponíveis ordenados
    for (int i = 0; i < indice; i++) {
        printf("Numero: %d, Origem: %s, Destino: %s, Data: %s, Horario: %s, Numero de Assentos: %d\n",
               voosDisponiveis[i]->numero, voosDisponiveis[i]->origem, voosDisponiveis[i]->destino,
               voosDisponiveis[i]->data, voosDisponiveis[i]->horario, voosDisponiveis[i]->numeroAssentos);
    }
}


int main(){
    Voo *raiz=NULL;
    int op,chave;
    int  numero, numeroAssentos;

    struct tm date; // cria uma estrutura para manipular a data e hora
    long int dataValor; // recebe o valor da data e hora em segundos

    char origem[20], destino[20], data[11], horario[9];


    //Menu do codigo
    do{
        printf("\n0 - Sair\n1 - Inserir\n2 - Remover\n3 - Buscar Voo\n4 - Exibir Voos com assentos disponiveis ordenados crescentemente com base na data e hora\n5 - Listar todos os voos com menos de 10 assentos\n6 - Quantidade total de voos disponiveis\n7 - Geracao de uma arvore balanceada aleatoria\n8 - Exibicao da arvore\n");
        scanf("%d",&op);
        switch (op) {
            case 0:
                printf("\nSaindo...\n");
                break;
            case 1:
                printf("\nDigite o numero a ser inserido: ");
                scanf("%d", &numero);
                printf("\nDigite o data a ser inserido(AAAA-MM-DD): ");
                scanf(" %s", data);
                printf("\nDigite o horario a ser inserido(HH:MM:SS): ");
                scanf(" %s", horario);
                printf("\nDigite o numero de assentos a ser inserido: ");
                scanf("%d", &numeroAssentos);
                printf("\nDigite o origem a ser inserido: ");
                scanf(" %[^\n]", origem);
                printf("\nDigite o destino a ser inserido: ");
                scanf(" %[^\n]", destino);

                // contateca data e horario em uma string
                printf("\nNumero: %d, Origem: %s, Destino: %s, Data: %s, Horario: %s\n",numero, origem,destino,data, horario);
                char temp[20]; // Defina uma string temporária para armazenar a concatenação de data e horário

                strcpy(temp, data);
                strcat(temp, " ");
                strcat(temp, horario);
                printf("\n%s",temp);
                //tranfoma a data e hora e inteiro
                sscanf(temp, "%d-%d-%d %d:%d:%d",
                       &date.tm_year, &date.tm_mon, &date.tm_mday,
                       &date.tm_hour, &date.tm_min, &date.tm_sec);

                date.tm_mon--; // Os meses em struct tm são de 0 a 11
                date.tm_year -= 1900; // tm_year conta os anos desde 1900

                time_t tempo = mktime(&date);
                dataValor = (long)tempo; 

                //realiza a ação de insersão
                raiz = inserir(raiz, numero, origem, destino,data, horario,dataValor,numeroAssentos);
                break;
            case 2:
                printf("\nDigite o numero do voo a ser apagado: ");
                scanf("%d",&chave);
                remover(raiz,chave);
                break;
           case 3:
                printf("\nDigite a origem da viagem: ");
                scanf("%s", origem);
                printf("\nDigite o destino da viagem: ");
                scanf("%s", destino);
                printf("\nDigite a data da viagem (AAAA-MM-DD): ");
                scanf("%s", data);
                printf("\nVoos disponiveis com base na origem, destino e data:\n");
                buscarVoosDisponiveis(raiz, origem, destino, data);
                break;
            case 4:
                listarVoosDisponiveisOrdenados(raiz);
                break;
            case 5:
                if(raiz != NULL)
                    imprimirVoos(raiz);
                else
                    printf("A raiz nao possui nenhum valor\n");
                break;
            case 6:
                printf("A quantidade de voos disponiveis: %d",tamanho(raiz));
                break;
            case 7:
                gerarArvoreAleatoria(&raiz);
                break;
            case 8:
                if(raiz != NULL)
                    imprimirArvore(raiz,8);
                else
                    printf("A raiz nao possui valor!\n");
                break;
            default:
                printf("\nOpcao invalida!");
        }
    }while(op != 0);
}
