#include <stdio.h>

#define MAX_LIVROS 3

int main() {

    int codigos[MAX_LIVROS];
    int estoques[MAX_LIVROS];
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

        qtdLivros++;
    }

    printf("\nLivros:\n");
    for (i = 0; i < qtdLivros; i++) {
        printf("%d - estoque %d\n", codigos[i], estoques[i]);
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
        if (estoques[posBusca] == 0) {
            printf("Livro indisponivel\n");
        } else {
            printf("Livro disponivel, estoque: %d\n", estoques[posBusca]);
        }
    }

    return 0;
}
