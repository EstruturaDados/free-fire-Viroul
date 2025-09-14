#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>
#include <time.h>

// Definição de constantes
#define TAM_NOME 30
#define TAM_TIPO 20
#define MAX_COMPONENTES 20

typedef struct {
    char nome[TAM_NOME];   // Nome do Componente
    char tipo[TAM_TIPO];   // Tipo do Componente
    int prioridade;        // Prioridade do Componente (1 a 10)
} Componente;

// Função para trocar componentes
void trocarComponente(Componente* a, Componente* b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// Função para cadastrar um componente
void cadastro_componentes(Componente *lista, int *total) {
    if (*total >= MAX_COMPONENTES) {
        printf("Não é possível cadastrar mais.\n");
        return;
    }

    printf("Nome do item: ");
    fgets(lista[*total].nome, TAM_NOME, stdin);
    lista[*total].nome[strcspn(lista[*total].nome, "\n")] = 0;

    printf("Tipo do item: ");
    fgets(lista[*total].tipo, TAM_TIPO, stdin);
    lista[*total].tipo[strcspn(lista[*total].tipo, "\n")] = 0;

    // validação da prioridade
    do {
        printf("Prioridade do item (1-10): ");
        scanf("%d", &lista[*total].prioridade);
        getchar();
    } while (lista[*total].prioridade < 1 || lista[*total].prioridade > 10);

    (*total)++; // incrementa o contador de componentes cadastrados
}

// Função para listar os componentes
void listar_componentes(Componente lista[], int total) {
    if (total == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Componentes ---\n");
    for (int i = 0; i < total; i++) {
        printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
               lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

// Bubble Sort por nome
void bubbleSortNome(Componente componentes[], int tamanho, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - 1 - i; j++) {
            (*comparacoes)++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                trocarComponente(&componentes[j], &componentes[j + 1]);
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente componentes[], int tamanho, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < tamanho; i++) {
        Componente chave = componentes[i];

        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente componentes[], int tamanho, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        
        int indiceMenor = i;
        for (int j = i + 1; j < tamanho; j++) {
            (*comparacoes)++;
            if (componentes[j].prioridade < componentes[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        if (indiceMenor != i) {
            trocarComponente(&componentes[i], &componentes[indiceMenor]);
        }
    }
}

// Busca binaria por nome
int buscaBinariaPorNome(Componente *componentes, int tamanho, const char *nome, int *comparacoes) {
    int inicio = 0, fim = tamanho - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(componentes[meio].nome, nome);

        if (cmp == 0) {
            return meio; // encontrou
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1; // não encontrou
}

// funcao para medir o tempo
void medirDesempenho(void (*algoritmo)(Componente*, int, int*),
                     Componente *lista, int tamanho, const char *nomeAlg) {
    int comparacoes;
    Componente copia[MAX_COMPONENTES];
    memcpy(copia, lista, sizeof(Componente) * tamanho); // não altera a lista original

    clock_t inicio = clock();
    algoritmo(copia, tamanho, &comparacoes);
    clock_t fim = clock();

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\n=== %s ===\n", nomeAlg);
    printf("Tempo de execução: %.6f segundos\n", tempo);
    printf("Número de comparações: %d\n", comparacoes);

    // Exibir lista ordenada
    listar_componentes(copia, tamanho);
}


int main() {
    Componente pecas[MAX_COMPONENTES];
    int total_cadastrado = 0;
    int opcao;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar por Nome (Bubble Sort)\n");
        printf("4 - Ordenar por Tipo (Insertion Sort)\n");
        printf("5 - Ordenar por Prioridade (Selection Sort)\n");
        printf("6 - Buscar por Nome (Busca Binária)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar \n do buffer

        switch(opcao) {
            case 1:
                cadastro_componentes(pecas, &total_cadastrado);
                break;

            case 2:
                listar_componentes(pecas, total_cadastrado);
                break;

            case 3:
                medirDesempenho(bubbleSortNome, pecas, total_cadastrado, "Bubble Sort por Nome");
                break;

            case 4:
                medirDesempenho(insertionSortTipo, pecas, total_cadastrado, "Insertion Sort por Tipo");
                break;

            case 5:
                medirDesempenho(selectionSortPrioridade, pecas, total_cadastrado, "Selection Sort por Prioridade");
                break;

            case 6: {
                char busca[TAM_NOME];
                int comparacoes;
                printf("Digite o nome do componente para buscar: ");
                fgets(busca, TAM_NOME, stdin);
                busca[strcspn(busca, "\n")] = 0;

                // garante que está ordenado por nome antes da busca
                bubbleSortNome(pecas, total_cadastrado, &comparacoes);

                int pos = buscaBinariaPorNome(pecas, total_cadastrado, busca, &comparacoes);
                if (pos != -1) {
                    printf("Encontrado! Nome: %s | Tipo: %s | Prioridade: %d (Comparações: %d)\n",
                           pecas[pos].nome, pecas[pos].tipo, pecas[pos].prioridade, comparacoes);
                } else {
                    printf("Componente não encontrado.\n");
                }
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
