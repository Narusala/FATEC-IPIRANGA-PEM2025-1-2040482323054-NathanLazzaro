#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUAS 3
#define GONDOLAS 10

typedef struct {
    char codigo[10];
} Produto;

void inicializarEstoque(Produto (*estoque)[GONDOLAS]) {
    for (int i = 0; i < RUAS; i++) {
        for (int j = 0; j < GONDOLAS; j++) {
            estoque[i][j].codigo[0] = '\0';
        }
    }
}

void estocarProduto(Produto (*estoque)[GONDOLAS], char *codigo, int rua, int gondola) {
    if (rua >= 0 && rua < RUAS && gondola >= 0 && gondola < GONDOLAS) {
        if (strlen(estoque[rua][gondola].codigo) == 0) {
            strcpy(estoque[rua][gondola].codigo, codigo);
            printf("Produto %s estocado na Rua %c, Gôndola %d.\n", codigo, 'A' + rua, gondola + 1);
        } else {
            printf("Gôndola já ocupada por %s.\n", estoque[rua][gondola].codigo);
        }
    } else {
        printf("Localização inválida!\n");
    }
}

void retirarProduto(Produto (*estoque)[GONDOLAS], char *codigo) {
    for (int i = 0; i < RUAS; i++) {
        for (int j = 0; j < GONDOLAS; j++) {
            if (strcmp(estoque[i][j].codigo, codigo) == 0) {
                printf("Produto %s retirado da Rua %c, Gôndola %d.\n", codigo, 'A' + i, j + 1);
                estoque[i][j].codigo[0] = '\0';
                return;
            }
        }
    }
    printf("Produto %s não encontrado no estoque.\n", codigo);
}

void visualizarEstoque(Produto (*estoque)[GONDOLAS]) {
    printf("\nEstado atual do estoque:\n");
    for (int i = 0; i < RUAS; i++) {
        for (int j = 0; j < GONDOLAS; j++) {
            printf("Rua %c, Gôndola %d: %s\n", 'A' + i, j + 1, strlen(estoque[i][j].codigo) > 0 ? estoque[i][j].codigo : "Vazio");
        }
    }
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Estocar produto\n");
    printf("2. Retirar produto\n");
    printf("3. Visualizar estoque\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Produto estoque[RUAS][GONDOLAS];
    inicializarEstoque(estoque);

    int opcao;
    char codigo[10];
    int rua, gondola;
    
    while (1) {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o código do produto: ");
                scanf("%s", codigo);
                printf("Digite a Rua (0=A, 1=B, 2=C): ");
                scanf("%d", &rua);
                printf("Digite a Gôndola (1-10): ");
                scanf("%d", &gondola);
                estocarProduto(estoque, codigo, rua, gondola - 1);
                break;
            case 2:
                printf("Digite o código do produto: ");
                scanf("%s", codigo);
                retirarProduto(estoque, codigo);
                break;
            case 3:
                visualizarEstoque(estoque);
                break;
            case 4:
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}