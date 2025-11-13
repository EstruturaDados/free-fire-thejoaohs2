#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ===============================
// Definição da estrutura de dados
// ===============================

// A struct Item representa um objeto dentro da mochila do jogador.
typedef struct {
    char nome[30];     // Nome do item (ex: "AK-47", "Bandagem")
    char tipo[20];     // Tipo do item (ex: "arma", "munição", "cura")
    int quantidade;    // Quantidade disponível do item
} Item;

// ===============================
// Protótipos das funções
// ===============================

void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);

// ===============================
// Função principal
// ===============================

int main() {
    Item mochila[10];   // Vetor que armazena até 10 itens
    int qtd = 0;        // Quantidade atual de itens na mochila
    int opcao;          // Opção do menu

    printf("=== SISTEMA DE INVENTÁRIO - DESAFIO NOVATO ===\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        switch(opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\nSaindo do sistema... Ate mais, sobrevivente!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);

    return 0;
}

// ===============================
// Função: inserirItem
// ===============================
// Cadastra um novo item na mochila, se houver espaço disponível.
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= 10) {
        printf("\nMochila cheia! Remova um item antes de adicionar outro.\n");
        return;
    }

    Item novo;
    printf("\n--- CADASTRO DE ITEM ---\n");

    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove o '\n'

    printf("Tipo do item (arma, municao, cura...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpa o buffer

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);
    listarItens(mochila, *qtd);
}

// ===============================
// Função: removerItem
// ===============================
// Remove um item da mochila com base no nome.
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nNome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem '%s' nao encontrado!\n", nomeRemover);
    } else {
        // desloca os itens à esquerda
        for (int j = encontrado; j < *qtd - 1; j++) {
            mochila[j] = mochila[j + 1];
        }
        (*qtd)--;
        printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
    }

    listarItens(mochila, *qtd);
}

// ===============================
// Função: listarItens
// ===============================
// Exibe todos os itens cadastrados na mochila.
void listarItens(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\n[Mochila vazia]\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// ===============================
// Função: buscarItem
// ===============================
// Busca sequencial de um item pelo nome e exibe seus dados.
void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item a buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        printf("\nItem encontrado!\n");
        printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
               mochila[encontrado].nome,
               mochila[encontrado].tipo,
               mochila[encontrado].quantidade);
    } else {
        printf("\nItem '%s' nao encontrado.\n", nomeBusca);
    }
}