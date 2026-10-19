#include <stdio.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 120

int cadastrarTitulo(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
);

void listarTitulos(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
);

int buscarTitulo(
    int codigos[],
    int qtdTitulos,
    int codigoBuscado
);

int calcularQtdExemplares(
    int estoques[],
    int qtdTitulos
);

int disponibilidadeTitulo(
    int qtdEstoque
);

int cadastrarTitulo(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
) {
    int codTemporario, estoTemporario;

    printf("Codigo do titulo: ");
    scanf("%d", &codTemporario);

    while (codTemporario <= 0 || buscarTitulo(codigos, qtdTitulos, codTemporario) != -1) {
        if (codTemporario <= 0) {
            printf("Codigo invalido, digite de novo: ");
        } else {
            printf("Esse codigo ja existe, digite outro: ");
        }
        scanf("%d", &codTemporario);
    }

    printf("Estoque: ");
    scanf("%d", &estoTemporario);

    while (estoTemporario < 0) {
        printf("Estoque invalido, digite de novo: ");
        scanf("%d", &estoTemporario);
    }

    // pesquisei e achei melhor usar o getchar pra tirar o enter que sobra do scanf antes do fgets
    getchar();

    printf("Descricao (titulo; autor; ano; tema): ");
    if (qtdTitulos == 0) {
        fgets(descricao1, TAM_TEXTO, stdin);
    } else if (qtdTitulos == 1) {
        fgets(descricao2, TAM_TEXTO, stdin);
    } else {
        fgets(descricao3, TAM_TEXTO, stdin);
    }

    codigos[qtdTitulos] = codTemporario;
    estoques[qtdTitulos] = estoTemporario;

    qtdTitulos++;

    return qtdTitulos;
}

void listarTitulos(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
) {
    int i;

    printf("\nTitulos:\n");
    for (i = 0; i < qtdTitulos; i++) {
        if (i == 0) {
            printf("%d - estoque %d - %s", codigos[i], estoques[i], descricao1);
        } else if (i == 1) {
            printf("%d - estoque %d - %s", codigos[i], estoques[i], descricao2);
        } else {
            printf("%d - estoque %d - %s", codigos[i], estoques[i], descricao3);
        }
    }
}

int buscarTitulo(
    int codigos[],
    int qtdTitulos,
    int codigoBuscado
) {
    int i, posicao;

    posicao = -1;
    for (i = 0; i < qtdTitulos; i++) {
        if (codigos[i] == codigoBuscado) {
            posicao = i;
        }
    }

    return posicao;
}

int calcularQtdExemplares(
    int estoques[],
    int qtdTitulos
) {
    int i, qtdExemplares = 0;

    for (i = 0; i < qtdTitulos; i++) {
        qtdExemplares = qtdExemplares + estoques[i];
    }

    return qtdExemplares;
}

int disponibilidadeTitulo(
    int qtdEstoque
) {
    if (qtdEstoque > 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {

    int codigos[MAX_TITULOS];
    int estoques[MAX_TITULOS];
    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];
    int qtdTitulos = 0, qtdExemplares, codigoBuscado, posBusca, disponivel;

    while (qtdTitulos < MAX_TITULOS) {
        qtdTitulos = cadastrarTitulo(codigos, estoques, descricao1, descricao2, descricao3, qtdTitulos);
    }

    listarTitulos(codigos, estoques, descricao1, descricao2, descricao3, qtdTitulos);

    printf("\nCodigo para buscar: ");
    scanf("%d", &codigoBuscado);

    posBusca = buscarTitulo(codigos, qtdTitulos, codigoBuscado);

    if (posBusca == -1) {
        printf("Titulo nao encontrado\n");
    } else {
        if (posBusca == 0) {
            printf("Titulo: %s", descricao1);
        } else if (posBusca == 1) {
            printf("Titulo: %s", descricao2);
        } else {
            printf("Titulo: %s", descricao3);
        }

        disponivel = disponibilidadeTitulo(estoques[posBusca]);

        if (disponivel == 1) {
            printf("Titulo disponivel, estoque: %d\n", estoques[posBusca]);
        } else {
            printf("Titulo temporariamente indisponivel\n");
        }
    }

    qtdExemplares = calcularQtdExemplares(estoques, qtdTitulos);

    printf("\nTotal: %d\n", qtdExemplares);

    return 0;
}
