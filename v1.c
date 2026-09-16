#include <stdio.h>

#define MAX_TITULOS 3

int main() {

    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};
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

        qtdTitulos++;
    }

    printf("\n--- Acervo cadastrado ---\n");
    for (i = 0; i < qtdTitulos; i++) {
        printf("Codigo: %d | Estoque: %d\n", codigos[i], estoques[i]);
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
        if (estoques[posBusca] == 0) {
            printf("Titulo encontrado, porem esta temporariamente indisponivel.\n");
        } else {
            printf("Titulo disponivel! Quantidade em estoque: %d\n", estoques[posBusca]);
        }
    }

    return 0;
}
