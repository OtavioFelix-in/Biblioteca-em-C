#include <stdio.h>
#include <string.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 120

int main() {

    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};
    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];
    int qtdTitulos = 0, codigoTemp, estoqueTemp, repetido, i, qtdExemplares = 0, codigoBusca, posBusca;

    while (qtdTitulos < MAX_TITULOS) {

        repetido = 0;

        printf("Digite o codigo do titulo %d: ", qtdTitulos + 1);
        scanf("%d", &codigoTemp);

        for (i = 0; i < qtdTitulos; i++) {
            if (codigos[i] == codigoTemp) {
                repetido = 1;
            }
        }

        while (codigoTemp < 0 || repetido == 1) {
            if (codigoTemp < 0) {
                printf("Codigo invalido (nao pode ser negativo). Digite novamente: ");
            } else {
                printf("Codigo ja cadastrado. Digite outro codigo: ");
            }
            scanf("%d", &codigoTemp);

            repetido = 0;
            for (i = 0; i < qtdTitulos; i++) {
                if (codigos[i] == codigoTemp) {
                    repetido = 1;
                }
            }
        }

        codigos[qtdTitulos] = codigoTemp;

        printf("Digite a quantidade em estoque para o codigo %d: ", codigoTemp);
        scanf("%d", &estoqueTemp);

        while (estoqueTemp < 0) {
            printf("Estoque invalido (nao pode ser negativo). Digite novamente: ");
            scanf("%d", &estoqueTemp);
        }

        estoques[qtdTitulos] = estoqueTemp;

        while (getchar() != '\n');

        printf("Digite a descricao do titulo (Titulo; Autor; Ano; Tema): ");
        if (qtdTitulos == 0) {
            fgets(descricao1, TAM_TEXTO, stdin);
            descricao1[strcspn(descricao1, "\n")] = '\0';
        } else if (qtdTitulos == 1) {
            fgets(descricao2, TAM_TEXTO, stdin);
            descricao2[strcspn(descricao2, "\n")] = '\0';
        } else {
            fgets(descricao3, TAM_TEXTO, stdin);
            descricao3[strcspn(descricao3, "\n")] = '\0';
        }

        qtdTitulos++;
    }

    printf("\n--- Acervo cadastrado ---\n");
    for (i = 0; i < qtdTitulos; i++) {
        if (i == 0) {
            printf("Codigo: %d | %s | Estoque: %d\n", codigos[i], descricao1, estoques[i]);
        } else if (i == 1) {
            printf("Codigo: %d | %s | Estoque: %d\n", codigos[i], descricao2, estoques[i]);
        } else {
            printf("Codigo: %d | %s | Estoque: %d\n", codigos[i], descricao3, estoques[i]);
        }
        qtdExemplares += estoques[i];
    }

    printf("Total de exemplares no acervo: %d\n", qtdExemplares);

    printf("\nDigite o codigo do titulo que deseja buscar: ");
    scanf("%d", &codigoBusca);

    posBusca = -1;
    for (i = 0; i < qtdTitulos; i++) {
        if (codigos[i] == codigoBusca) {
            posBusca = i;
        }
    }

    if (posBusca == -1) {
        printf("Titulo nao encontrado no acervo.\n");
    } else {
        if (posBusca == 0) {
            printf("Titulo encontrado: %s\n", descricao1);
        } else if (posBusca == 1) {
            printf("Titulo encontrado: %s\n", descricao2);
        } else {
            printf("Titulo encontrado: %s\n", descricao3);
        }

        if (estoques[posBusca] == 0) {
            printf("Titulo temporariamente indisponivel.\n");
        } else {
            printf("Titulo disponivel! Quantidade em estoque: %d\n", estoques[posBusca]);
        }
    }

    return 0;
}
