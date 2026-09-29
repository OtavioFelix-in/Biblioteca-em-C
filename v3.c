#include <stdio.h>
#include <string.h>

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

int main() {

    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};
    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];
    int qtdTitulos = 0, qtdExemplares = 0, codigoBuscado, posBusca, disponivel;

    while (qtdTitulos < MAX_TITULOS) {
        qtdTitulos = cadastrarTitulo(
            codigos,
            estoques,
            descricao1,
            descricao2,
            descricao3,
            qtdTitulos
        );
    }

    listarTitulos(
        codigos,
        estoques,
        descricao1,
        descricao2,
        descricao3,
        qtdTitulos
    );

    printf("\nDigite o codigo do titulo que deseja buscar: ");
    scanf("%d", &codigoBuscado);

    posBusca = buscarTitulo(
        codigos,
        qtdTitulos,
        codigoBuscado
    );

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

        disponivel = disponibilidadeTitulo(
            estoques[posBusca]
        );

        if (disponivel == 1) {
            printf("Titulo disponivel! Quantidade em estoque: %d\n", estoques[posBusca]);
        } else {
            printf("Titulo temporariamente indisponivel.\n");
        }
    }

    qtdExemplares = calcularQtdExemplares(
        estoques,
        qtdTitulos
    );

    printf("\nTotal de exemplares no acervo: %d\n", qtdExemplares);

    return 0;
}

int cadastrarTitulo(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
) {
    int codigoTemp, estoqueTemp;

    printf("Digite o codigo do titulo %d: ", qtdTitulos + 1);
    scanf("%d", &codigoTemp);

    while (codigoTemp < 0 || buscarTitulo(codigos, qtdTitulos, codigoTemp) != -1) {
        if (codigoTemp < 0) {
            printf("Codigo invalido (nao pode ser negativo). Digite novamente: ");
        } else {
            printf("Codigo ja cadastrado. Digite outro codigo: ");
        }
        scanf("%d", &codigoTemp);
    }

    printf("Digite a quantidade em estoque para o codigo %d: ", codigoTemp);
    scanf("%d", &estoqueTemp);

    while (estoqueTemp < 0) {
        printf("Estoque invalido (nao pode ser negativo). Digite novamente: ");
        scanf("%d", &estoqueTemp);
    }

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

    codigos[qtdTitulos] = codigoTemp;
    estoques[qtdTitulos] = estoqueTemp;

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

    printf("\n--- Acervo cadastrado ---\n");
    for (i = 0; i < qtdTitulos; i++) {
        if (i == 0) {
            printf("Codigo: %d | %s | Estoque: %d\n", codigos[i], descricao1, estoques[i]);
        } else if (i == 1) {
            printf("Codigo: %d | %s | Estoque: %d\n", codigos[i], descricao2, estoques[i]);
        } else {
            printf("Codigo: %d | %s | Estoque: %d\n", codigos[i], descricao3, estoques[i]);
        }
    }
}

int buscarTitulo(
    int codigos[],
    int qtdTitulos,
    int codigoBuscado
) {
    int i;

    for (i = 0; i < qtdTitulos; i++) {
        if (codigos[i] == codigoBuscado) {
            return i;
        }
    }

    return -1;
}

int calcularQtdExemplares(
    int estoques[],
    int qtdTitulos
) {
    int i, qtdExemplares = 0;

    for (i = 0; i < qtdTitulos; i++) {
        qtdExemplares += estoques[i];
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
