#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

// Estrutura da peça
typedef struct {
    char tipo; // 'I', 'O', 'T', 'L'
    int id;    // Identificador único
} Peca;

// Fila circular
typedef struct {
    Peca fila[TAMANHO_FILA];
    int inicio;
    int fim;
    int quantidade;
    int contadorID; // Para gerar IDs únicos
} FilaPecas;

// Gera uma nova peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Inicializa a fila com peças automáticas
void inicializarFila(FilaPecas *fp) {
    fp->inicio = 0;
    fp->fim = 0;
    fp->quantidade = 0;
    fp->contadorID = 0;

    for (int i = 0; i < TAMANHO_FILA; i++) {
        fp->fila[fp->fim] = gerarPeca(fp->contadorID++);
        fp->fim = (fp->fim + 1) % TAMANHO_FILA;
        fp->quantidade++;
    }
}

// Exibe o estado atual da fila
void exibirFila(FilaPecas *fp) {
    printf("\nFila de Peças:\n");
    int i = fp->inicio;
    for (int count = 0; count < fp->quantidade; count++) {
        printf("[%c %d] ", fp->fila[i].tipo, fp->fila[i].id);
        i = (i + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

// Remove a peça da frente (dequeue)
void jogarPeca(FilaPecas *fp) {
    if (fp->quantidade == 0) {
        printf("Fila vazia. Nenhuma peça para jogar.\n");
        return;
    }
    printf("Jogou a peça [%c %d]\n", fp->fila[fp->inicio].tipo, fp->fila[fp->inicio].id);
    fp->inicio = (fp->inicio + 1) % TAMANHO_FILA;
    fp->quantidade--;
}

// Insere nova peça ao final (enqueue)
void inserirPeca(FilaPecas *fp) {
    if (fp->quantidade == TAMANHO_FILA) {
        printf("Fila cheia. Não é possível inserir nova peça.\n");
        return;
    }
    fp->fila[fp->fim] = gerarPeca(fp->contadorID++);
    fp->fim = (fp->fim + 1) % TAMANHO_FILA;
    fp->quantidade++;
    printf("Nova peça inserida com sucesso.\n");
}

// Menu principal
void menu(FilaPecas *fp) {
    int opcao;
    do {
        exibirFila(fp);
        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(fp);
                break;
            case 2:
                inserirPeca(fp);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios
    FilaPecas fila;
    inicializarFila(&fila);
    menu(&fila);
    return 0;
}
