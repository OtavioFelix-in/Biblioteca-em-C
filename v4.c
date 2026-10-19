#include <stdio.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 120

struct Livro {
    int codigo;
    int estoque;
    char descricao[TAM_TEXTO];
};

int cadastrarTitulo(
    struct Livro livros[],
    int qtdTitulos
);

void listarTitulos(
    struct Livro livros[],
    int qtdTitulos
);

int buscarTitulo(
    struct Livro livros[],
    int qtdTitulos,
    int codigoBuscado
);

int calcularQtdExemplares(
    struct Livro livros[],
    int qtdTitulos
);

int disponibilidadeTitulo(
    int qtdEstoque
);

int cadastrarTitulo(
    struct Livro livros[],
    int qtdTitulos
) {
    int codTemporario, estoTemporario;

    printf("Codigo do titulo: ");
    scanf("%d", &codTemporario);

    while (codTemporario <= 0 || buscarTitulo(livros, qtdTitulos, codTemporario) != -1) {
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
    fgets(livros[qtdTitulos].descricao, TAM_TEXTO, stdin);

    livros[qtdTitulos].codigo = codTemporario;
    livros[qtdTitulos].estoque = estoTemporario;

    qtdTitulos++;

    return qtdTitulos;
}

void listarTitulos(
    struct Livro livros[],
    int qtdTitulos
) {
    int i;

    printf("\nTitulos:\n");
    for (i = 0; i < qtdTitulos; i++) {
        printf("%d - estoque %d - %s", livros[i].codigo, livros[i].estoque, livros[i].descricao);
    }
}

int buscarTitulo(
    struct Livro livros[],
    int qtdTitulos,
    int codigoBuscado
) {
    int i, posicao;

    posicao = -1;
    for (i = 0; i < qtdTitulos; i++) {
        if (livros[i].codigo == codigoBuscado) {
            posicao = i;
        }
    }

    return posicao;
}

int calcularQtdExemplares(
    struct Livro livros[],
    int qtdTitulos
) {
    int i, qtdExemplares = 0;

    for (i = 0; i < qtdTitulos; i++) {
        qtdExemplares = qtdExemplares + livros[i].estoque;
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

    struct Livro livros[MAX_TITULOS];
    int qtdTitulos = 0, qtdExemplares, codigoBuscado, posBusca, disponivel;

    while (qtdTitulos < MAX_TITULOS) {
        qtdTitulos = cadastrarTitulo(livros, qtdTitulos);
    }

    listarTitulos(livros, qtdTitulos);

    printf("\nCodigo para buscar: ");
    scanf("%d", &codigoBuscado);

    posBusca = buscarTitulo(livros, qtdTitulos, codigoBuscado);

    if (posBusca == -1) {
        printf("Titulo nao encontrado\n");
    } else {
        printf("Titulo: %s", livros[posBusca].descricao);

        disponivel = disponibilidadeTitulo(livros[posBusca].estoque);

        if (disponivel == 1) {
            printf("Titulo disponivel, estoque: %d\n", livros[posBusca].estoque);
        } else {
            printf("Titulo temporariamente indisponivel\n");
        }
    }

    qtdExemplares = calcularQtdExemplares(livros, qtdTitulos);

    printf("\nTotal: %d\n", qtdExemplares);

    return 0;
}
