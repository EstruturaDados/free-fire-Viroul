#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>  
/*Sua missão é construir um
sistema de inventário que simule a
mochila de loot inicial do jogador.
Para isso, você criará uma struct
chamada Item, que armazenará
informações essenciais de cada
objeto coletado. O sistema permitirá
que o jogador cadastre, remova,
liste e busque por itens dentro da
mochila.*/
// Definição de constantes para o tamanho das strings
#define TAM_NOME 30
#define TAM_TIPO 20
#define TAM_MAX 10

// Estrutura item
typedef struct {
    char nome[TAM_NOME];       // Nome do território
    char tipo[TAM_TIPO];    // Cor do exército que domina o território
    int quantidade;          // Quantidade de tropas presentes
} item;


// Estrutura mochila
typedef struct {
    item itens[TAM_MAX];
    int quantidade;
} mochila;

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void inicializar_mochila(mochila *mochila_jogador){
    mochila_jogador->quantidade = 0;
}

void inserir_Item(mochila *mochila_jogador, const char *nome, const char *tipo, int quantidade){
    if(mochila_jogador->quantidade == TAM_MAX){
    printf("Erro: mochila cheia!\n");
    return;
    }
    
    strcpy(mochila_jogador->itens[mochila_jogador->quantidade].nome, nome);
    strcpy(mochila_jogador->itens[mochila_jogador->quantidade].tipo, tipo);
    mochila_jogador->quantidade++;
    printf("Item \"%s\" inserido com sucesso.\n", nome);

};

void remover_Item(mochila *mochila_jogador, const char *nome){
    int pos = -1;
    for (int i = 0; i < mochila_jogador->quantidade; i++){
        if (strcmp(mochila_jogador->itens[i].nome, nome) == 0){
            pos = i;
            break;
        }
    }
    
    //tratando erro
    if (pos == -1){
        printf("Erro: item\"%s\" não encontrado.\n", nome);
        return;
    }
    /// fechar a lacuna:
    for (int i = pos; i < mochila_jogador->quantidade - 1; i++){
        mochila_jogador->itens[i] = mochila_jogador->itens[i + 1];
    mochila_jogador->quantidade--;
    printf("item \"%s\" removido com sucesso.\n", nome);
}}

void listar_Itens(mochila *mochila_jogador){
    if(mochila_jogador->quantidade == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }
    printf("Itens da mochila:\n");
    for (int i = 0; i < mochila_jogador->quantidade; i++){
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
            i+1,
            mochila_jogador->itens[i].nome,
            mochila_jogador->itens[i].tipo,
            mochila_jogador->itens[i].quantidade
        );
    }
}

void buscar_item(mochila *mochila_jogador, const char *nome) {
    for (int i = 0; i < mochila_jogador->quantidade; i++) {
        if (strcmp(mochila_jogador->itens[i].nome, nome) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                mochila_jogador->itens[i].nome,
                mochila_jogador->itens[i].tipo,
                mochila_jogador->itens[i].quantidade
            );
            return;
        }
    }
    printf("Item \"%s\" não encontrado.\n", nome);
}

void menu_inserir(mochila *mochila_jogador) {
    char nome[TAM_NOME], tipo[TAM_TIPO];
    int quantidade;

    printf("Nome do item: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Tipo do item: ");
    fgets(tipo, TAM_TIPO, stdin);
    tipo[strcspn(tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &quantidade);
    limparBufferEntrada(); // limpa o \n deixado pelo scanf

    inserir_Item(mochila_jogador, nome, tipo, quantidade);
}

void menu_remover(mochila *mochila_jogador) {
    char nome[TAM_NOME];
    printf("Nome do item a remover: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;

    remover_Item(mochila_jogador, nome);
}

void menu_listar(mochila *mochila_jogador) {
    listar_Itens(mochila_jogador);
}

void menu_buscar(mochila *mochila_jogador) {
    char nome[TAM_NOME];
    printf("Nome do item a buscar: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;

    buscar_item(mochila_jogador, nome);
}

int main(){
    mochila mochila_jogador;
    inicializar_mochila(&mochila_jogador);

    int opcao, quantidade;
    char nome[TAM_NOME], tipo[TAM_TIPO];

    do {
        printf("===== MENU =====\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Ler\n");
        printf("4 - Buscar\n");
        printf("0 - Sair\n");
        printf("================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBufferEntrada(); // limpa o buffer antes de chamar o menu

        switch(opcao) {
            case 1: menu_inserir(&mochila_jogador); break;
            case 2: menu_remover(&mochila_jogador); break;
            case 3: menu_listar(&mochila_jogador); break;
            case 4: menu_buscar(&mochila_jogador); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida! Tente novamente.\n");
        }

        printf("\n");

    } while(opcao != 0);
}