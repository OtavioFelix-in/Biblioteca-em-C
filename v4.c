#include <stdio.h>
#include <string.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 120

typedef struct {
    int codigo;
    int estoque;
    char descricao[TAM_TEXTO];
} Livro;

int cadastrarTitulo(
    Livro livros[],
    int qtdTitulos
);

void listarTitulos(
    Livro livros[],
    int qtdTitulos
);

int buscarTitulo(
    Livro livros[],
    int qtdTitulos,
    int codigoBuscado
);

int calcularQtdExemplares(
    Livro livros[],
    int qtdTitulos
);

int disponibilidadeTitulo(
    int qtdEstoque
);

int main() {

    Livro livros[MAX_TITULOS];
    int qtdTitulos = 0, qtdExemplares = 0, codigoBuscado, posBusca, disponivel;

    while (qtdTitulos < MAX_TITULOS) {
        qtdTitulos = cadastrarTitulo(
            livros,
            qtdTitulos
        );
    }

    listarTitulos(
        livros,
        qtdTitulos
    );

    printf("\nDigite o codigo do titulo que deseja buscar: ");
    scanf("%d", &codigoBuscado);

    posBusca = buscarTitulo(
        livros,
        qtdTitulos,
        codigoBuscado
    );

    if (posBusca == -1) {
        printf("Titulo nao encontrado no acervo.\n");
    } else {
        printf("Titulo encontrado: %s\n", livros[posBusca].descricao);

        disponivel = disponibilidadeTitulo(
            livros[posBusca].estoque
        );

        if (disponivel == 1) {
            printf("Titulo disponivel! Quantidade em estoque: %d\n", livros[posBusca].estoque);
        } else {
            printf("Titulo temporariamente indisponivel.\n");
        }
    }

    qtdExemplares = calcularQtdExemplares(
        livros,
        qtdTitulos
    );

    printf("\nTotal de exemplares no acervo: %d\n", qtdExemplares);

    return 0;
}

int cadastrarTitulo(
    Livro livros[],
    int qtdTitulos
) {
    Livro novo;

    printf("Digite o codigo do titulo %d: ", qtdTitulos + 1);
    scanf("%d", &novo.codigo);

    while (novo.codigo <= 0 || buscarTitulo(livros, qtdTitulos, novo.codigo) != -1) {
        if (novo.codigo <= 0) {
            printf("Codigo invalido (deve ser positivo). Digite novamente: ");
        } else {
            printf("Codigo ja cadastrado. Digite outro codigo: ");
        }
        scanf("%d", &novo.codigo);
    }

    printf("Digite a quantidade em estoque para o codigo %d: ", novo.codigo);
    scanf("%d", &novo.estoque);

    while (novo.estoque < 0) {
        printf("Estoque invalido (nao pode ser negativo). Digite novamente: ");
        scanf("%d", &novo.estoque);
    }

    while (getchar() != '\n');

    printf("Digite a descricao do titulo (Titulo; Autor; Ano; Tema): ");
    fgets(novo.descricao, TAM_TEXTO, stdin);
    novo.descricao[strcspn(novo.descricao, "\n")] = '\0';

    livros[qtdTitulos] = novo;

    qtdTitulos++;

    return qtdTitulos;
}

void listarTitulos(
    Livro livros[],
    int qtdTitulos
) {
    int i;

    printf("\n--- Acervo cadastrado ---\n");
    for (i = 0; i < qtdTitulos; i++) {
        printf("Codigo: %d | %s | Estoque: %d\n", livros[i].codigo, livros[i].descricao, livros[i].estoque);
    }
}

int buscarTitulo(
    Livro livros[],
    int qtdTitulos,
    int codigoBuscado
) {
    int i;

    for (i = 0; i < qtdTitulos; i++) {
        if (livros[i].codigo == codigoBuscado) {
            return i;
        }
    }

    return -1;
}

int calcularQtdExemplares(
    Livro livros[],
    int qtdTitulos
) {
    int i, qtdExemplares = 0;

    for (i = 0; i < qtdTitulos; i++) {
        qtdExemplares += livros[i].estoque;
    }

    return qtdExemplares;
}

int disponibilidadeTitulo(
    int qtdEstoque
) {
    if (qtdEstoque > 0) {
        return 1;
    }

    return 0;
}
