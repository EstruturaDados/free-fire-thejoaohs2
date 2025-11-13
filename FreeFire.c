#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ======================================================
// ESTRUTURA PRINCIPAL
// ======================================================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ======================================================
// VARIÁVEIS GLOBAIS
// ======================================================

int comparacoes = 0;

// ======================================================
// FUNÇÕES DE APOIO
// ======================================================

// Exibe os componentes formatados
void mostrarComponentes(Componente comp[], int n) {
    printf("\n--- COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("%2d. Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
}

// Copia vetor auxiliar (para medir tempo sem destruir o original)
void copiarComponentes(Componente origem[], Componente destino[], int n) {
    for (int i = 0; i < n; i++)
        destino[i] = origem[i];
}

// ======================================================
// ALGORITMOS DE ORDENAÇÃO
// ======================================================

// Bubble Sort - ordena por NOME
void bubbleSortNome(Componente comp[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                Componente temp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort - ordena por TIPO
void insertionSortTipo(Componente comp[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = comp[i];
        int j = i - 1;
        while (j >= 0 && strcmp(comp[j].tipo, chave.tipo) > 0) {
            comp[j + 1] = comp[j];
            j--;
            comparacoes++;
        }
        comp[j + 1] = chave;
        comparacoes++;
    }
}

// Selection Sort - ordena por PRIORIDADE (int)
void selectionSortPrioridade(Componente comp[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (comp[j].prioridade < comp[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = comp[i];
            comp[i] = comp[min];
            comp[min] = temp;
        }
    }
}

// ======================================================
// BUSCA BINÁRIA (apenas após ordenação por nome)
// ======================================================

int buscaBinariaPorNome(Componente comp[], int n, char nome[]) {
    int inicio = 0, fim = n - 1, meio;
    int compBinaria = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        compBinaria++;
        int cmp = strcmp(comp[meio].nome, nome);

        if (cmp == 0) {
            printf("\n✅ Componente encontrado na posição %d\n", meio + 1);
            printf("Comparações na busca: %d\n", compBinaria);
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\n❌ Componente '%s' não encontrado!\n", nome);
    printf("Comparações na busca: %d\n", compBinaria);
    return -1;
}

// ======================================================
// FUNÇÃO PARA MEDIR TEMPO DE EXECUÇÃO
// ======================================================

void medirTempo(void (*func)(Componente[], int), Componente comp[], int n, const char *nomeAlg) {
    Componente copia[MAX];
    copiarComponentes(comp, copia, n);

    clock_t inicio = clock();
    func(copia, n);
    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n--- RESULTADOS (%s) ---\n", nomeAlg);
    mostrarComponentes(copia, n);
    printf("Comparações: %d\n", comparacoes);
    printf("Tempo de execução: %.6f segundos\n", tempo);
}

// ======================================================
// FUNÇÃO PRINCIPAL
// ======================================================

int main() {
    Componente componentes[MAX];
    int qtd = 0;
    int opcao;
    char nomeBusca[30];

    printf("=== DESAFIO MESTRE: TORRE DE RESGATE ===\n");

    // Cadastro de componentes
    printf("\nQuantos componentes deseja cadastrar (até 20)? ");
    scanf("%d", &qtd);
    getchar();

    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do componente %d ---\n", i + 1);
        printf("Nome: ");
        fgets(componentes[i].nome, sizeof(componentes[i].nome), stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(componentes[i].tipo, sizeof(componentes[i].tipo), stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    // Menu de opções
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Ordenar por NOME (Bubble Sort)\n");
        printf("2. Ordenar por TIPO (Insertion Sort)\n");
        printf("3. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("4. Busca Binária por Nome (após Bubble Sort)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                medirTempo(bubbleSortNome, componentes, qtd, "Bubble Sort (Nome)");
                break;

            case 2:
                medirTempo(insertionSortTipo, componentes, qtd, "Insertion Sort (Tipo)");
                break;

            case 3:
                medirTempo(selectionSortPrioridade, componentes, qtd, "Selection Sort (Prioridade)");
                break;

            case 4:
                printf("\nDigite o nome do componente-chave: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                buscaBinariaPorNome(componentes, qtd, nomeBusca);
                break;
        }

    } while (opcao != 0);

    printf("\n🏁 Fase concluída! Torre de resgate pronta para ativação!\n");
    return 0;
}
