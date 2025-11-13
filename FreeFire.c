#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// =======================================================
// Estruturas de dados
// =======================================================

// Estrutura básica do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// =======================================================
// Variáveis globais para contadores
// =======================================================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// =======================================================
// Funções para vetor
// =======================================================

void inserirItemVetor(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\n[Mochila cheia!]\n");
        return;
    }

    Item novo;
    printf("\n--- Inserir Item (Vetor) ---\n");
    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtd] = novo;
    (*qtd)++;
    printf("Item '%s' adicionado ao vetor!\n", novo.nome);
}

void removerItemVetor(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\n[Mochila vazia!]\n");
        return;
    }

    char nome[30];
    printf("\n--- Remover Item (Vetor) ---\n");
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++)
                mochila[j] = mochila[j + 1];
            (*qtd)--;
            printf("Item '%s' removido!\n", nome);
            return;
        }
    }

    printf("Item '%s' nao encontrado!\n", nome);
}

void listarItensVetor(Item mochila[], int qtd) {
    printf("\n--- Itens no Vetor ---\n");
    if (qtd == 0) {
        printf("[Mochila vazia]\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int buscarSequencialVetor(Item mochila[], int qtd, char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < qtd; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

// Ordenação (Bubble Sort)
void ordenarVetor(Item mochila[], int qtd) {
    Item temp;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome!\n");
}

// Busca binária
int buscarBinariaVetor(Item mochila[], int qtd, char nome[]) {
    int inicio = 0, fim = qtd - 1;
    comparacoesBinaria = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(nome, mochila[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

// =======================================================
// Funções para lista encadeada
// =======================================================

No* inserirItemLista(No* inicio) {
    No* novo = (No*) malloc(sizeof(No));

    printf("\n--- Inserir Item (Lista Encadeada) ---\n");
    printf("Nome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicio;
    printf("Item '%s' adicionado na lista!\n", novo->dados.nome);
    return novo;
}

No* removerItemLista(No* inicio) {
    if (inicio == NULL) {
        printf("\n[Lista vazia!]\n");
        return NULL;
    }

    char nome[30];
    printf("\n--- Remover Item (Lista Encadeada) ---\n");
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = inicio, *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item '%s' nao encontrado!\n", nome);
        return inicio;
    }

    if (anterior == NULL)
        inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Item '%s' removido!\n", nome);
    return inicio;
}

void listarItensLista(No* inicio) {
    printf("\n--- Itens na Lista Encadeada ---\n");
    if (inicio == NULL) {
        printf("[Mochila vazia]\n");
        return;
    }

    No* aux = inicio;
    int i = 1;
    while (aux != NULL) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i, aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
        i++;
    }
}

void buscarSequencialLista(No* inicio, char nome[]) {
    comparacoesSequencial = 0;
    No* aux = inicio;
    while (aux != NULL) {
        comparacoesSequencial++;
        if (strcmp(aux->dados.nome, nome) == 0) {
            printf("\nItem encontrado na lista!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
            printf("Comparacoes: %d\n", comparacoesSequencial);
            return;
        }
        aux = aux->proximo;
    }
    printf("\nItem '%s' nao encontrado!\n", nome);
    printf("Comparacoes: %d\n", comparacoesSequencial);
}

// =======================================================
// Função principal
// =======================================================

int main() {
    Item mochilaVetor[MAX_ITENS];
    int qtdVetor = 0;
    No* mochilaLista = NULL;

    int escolhaEstrutura, opcao;
    char nomeBusca[30];

    printf("=== DESAFIO: NIVEL AVENTUREIRO ===\n");

    do {
        printf("\nEscolha a estrutura de dados:\n");
        printf("1. Mochila com Vetor\n");
        printf("2. Mochila com Lista Encadeada\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &escolhaEstrutura);
        getchar();

        if (escolhaEstrutura == 0) break;

        do {
            printf("\n--- MENU DE OPERACOES ---\n");
            printf("1. Inserir Item\n");
            printf("2. Remover Item\n");
            printf("3. Listar Itens\n");
            printf("4. Buscar Item (Sequencial)\n");
            if (escolhaEstrutura == 1)
                printf("5. Ordenar Vetor e Buscar Binaria\n");
            printf("0. Voltar\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            getchar();

            switch(opcao) {
                case 1:
                    if (escolhaEstrutura == 1)
                        inserirItemVetor(mochilaVetor, &qtdVetor);
                    else
                        mochilaLista = inserirItemLista(mochilaLista);
                    break;

                case 2:
                    if (escolhaEstrutura == 1)
                        removerItemVetor(mochilaVetor, &qtdVetor);
                    else
                        mochilaLista = removerItemLista(mochilaLista);
                    break;

                case 3:
                    if (escolhaEstrutura == 1)
                        listarItensVetor(mochilaVetor, qtdVetor);
                    else
                        listarItensLista(mochilaLista);
                    break;

                case 4:
                    printf("Nome do item para buscar: ");
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                    if (escolhaEstrutura == 1) {
                        int pos = buscarSequencialVetor(mochilaVetor, qtdVetor, nomeBusca);
                        if (pos != -1)
                            printf("\nItem encontrado: %s | Tipo: %s | Quantidade: %d\n", 
                                   mochilaVetor[pos].nome, mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                        else
                            printf("\nItem nao encontrado!\n");
                        printf("Comparacoes: %d\n", comparacoesSequencial);
                    } else {
                        buscarSequencialLista(mochilaLista, nomeBusca);
                    }
                    break;

                case 5:
                    if (escolhaEstrutura == 1) {
                        ordenarVetor(mochilaVetor, qtdVetor);
                        printf("\nNome do item para busca binaria: ");
                        fgets(nomeBusca, sizeof(nomeBusca), stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                        int pos = buscarBinariaVetor(mochilaVetor, qtdVetor, nomeBusca);
                        if (pos != -1)
                            printf("\nItem encontrado: %s | Tipo: %s | Quantidade: %d\n", 
                                   mochilaVetor[pos].nome, mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                        else
                            printf("\nItem nao encontrado!\n");
                        printf("Comparacoes (busca binaria): %d\n", comparacoesBinaria);
                    }
                    break;
            }

        } while (opcao != 0);

    } while (escolhaEstrutura != 0);

    printf("\nFim da simulacao! Boa sorte na zona de perigo!\n");
    return 0;
}
