#include <stdio.h>

#define MAX_LIVROS 3
#define TAM_TEXTO 120

int main() {

    int codigos[MAX_LIVROS];
    int estoques[MAX_LIVROS];
    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];
    int qtdLivros = 0, codTemporario, estoTemporario, repetido, i, qtdExemplares = 0, codigoBusca, posBusca;

    while (qtdLivros < MAX_LIVROS) {

        repetido = 0;

        printf("Codigo do livro: ");
        scanf("%d", &codTemporario);

        for (i = 0; i < qtdLivros; i++) {
            if (codigos[i] == codTemporario) {
                repetido = 1;
            }
        }

        while (codTemporario <= 0 || repetido == 1) {
            if (codTemporario <= 0) {
                printf("Codigo invalido, digite de novo: ");
            } else {
                printf("Esse codigo ja existe, digite outro: ");
            }
            scanf("%d", &codTemporario);

            repetido = 0;
            for (i = 0; i < qtdLivros; i++) {
                if (codigos[i] == codTemporario) {
                    repetido = 1;
                }
            }
        }

        codigos[qtdLivros] = codTemporario;

        printf("Estoque: ");
        scanf("%d", &estoTemporario);

        while (estoTemporario < 0) {
            printf("Estoque invalido, digite de novo: ");
            scanf("%d", &estoTemporario);
        }

        estoques[qtdLivros] = estoTemporario;

        // pesquisei e achei melhor usar o getchar pra tirar o enter que sobra do scanf antes do fgets
        getchar();

        printf("Descricao (titulo; autor; ano; tema): ");
        if (qtdLivros == 0) {
            fgets(descricao1, TAM_TEXTO, stdin);
        } else if (qtdLivros == 1) {
            fgets(descricao2, TAM_TEXTO, stdin);
        } else {
            fgets(descricao3, TAM_TEXTO, stdin);
        }

        qtdLivros++;
    }

    printf("\nLivros:\n");
    for (i = 0; i < qtdLivros; i++) {
        if (i == 0) {
            printf("%d - estoque %d - %s", codigos[i], estoques[i], descricao1);
        } else if (i == 1) {
            printf("%d - estoque %d - %s", codigos[i], estoques[i], descricao2);
        } else {
            printf("%d - estoque %d - %s", codigos[i], estoques[i], descricao3);
        }
        qtdExemplares = qtdExemplares + estoques[i];
    }

    printf("Total: %d\n", qtdExemplares);

    printf("\nCodigo para buscar: ");
    scanf("%d", &codigoBusca);

    posBusca = -1;
    for (i = 0; i < qtdLivros; i++) {
        if (codigos[i] == codigoBusca) {
            posBusca = i;
        }
    }

    if (posBusca == -1) {
        printf("Livro nao encontrado\n");
    } else {
        if (posBusca == 0) {
            printf("Livro: %s", descricao1);
        } else if (posBusca == 1) {
            printf("Livro: %s", descricao2);
        } else {
            printf("Livro: %s", descricao3);
        }

        if (estoques[posBusca] == 0) {
            printf("Livro indisponivel\n");
        } else {
            printf("Livro disponivel, estoque: %d\n", estoques[posBusca]);
        }
    }

    return 0;
}
