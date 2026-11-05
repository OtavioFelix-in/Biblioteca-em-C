#include <stdio.h>

#define MAX_TITULOS 3
#define MAX_USUARIOS 3
#define TAM_TEXTO 120
#define SEM_EMPRESTIMO -1

struct Livro {
    int codigo;
    char descricao[TAM_TEXTO];
    int estoque;
};

struct Usuario {
    int codigo;
    char dados[TAM_TEXTO];
    int codigoLivroEmprestado;
};


int cadastrarTitulo(
    struct Livro livros[],
    int qtdTitulos
);

void listarTitulos(
    struct Livro livros[],
    int qtdTitulos
);

int buscarLivro(
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

int cadastrarUsuario(
    struct Usuario usuarios[],
    int qtdUsuarios
);

void listarUsuarios(
    struct Usuario usuarios[],
    int qtdUsuarios
);

int buscarUsuario(
    struct Usuario usuarios[],
    int qtdUsuarios,
    int codigoBuscado
);


void alterarEstoque(
    struct Livro *livro,
    int valor
);

void registrarEmprestimo(
    struct Usuario *usuario,
    int codigoLivro
);

void encerrarEmprestimo(
    struct Usuario *usuario
);


int cadastrarTitulo(
    struct Livro livros[],
    int qtdTitulos
) {
    int codTemporario, estoTemporario;

    printf("Codigo do titulo: ");
    scanf("%d", &codTemporario);

    while (codTemporario <= 0 || buscarLivro(livros, qtdTitulos, codTemporario) != -1) {
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

    // tira o enter que sobra do scanf antes do fgets
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

int buscarLivro(
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


int cadastrarUsuario(
    struct Usuario usuarios[],
    int qtdUsuarios
) {
    int codTemporario;

    printf("Codigo do usuario: ");
    scanf("%d", &codTemporario);

    while (codTemporario <= 0 || buscarUsuario(usuarios, qtdUsuarios, codTemporario) != -1) {
        if (codTemporario <= 0) {
            printf("Codigo invalido, digite de novo: ");
        } else {
            printf("Esse codigo ja existe, digite outro: ");
        }
        scanf("%d", &codTemporario);
    }

    // tira o enter que sobra do scanf antes do fgets
    getchar();

    printf("Dados do usuario (nome; telefone; ...): ");
    fgets(usuarios[qtdUsuarios].dados, TAM_TEXTO, stdin);

    usuarios[qtdUsuarios].codigo = codTemporario;
    usuarios[qtdUsuarios].codigoLivroEmprestado = SEM_EMPRESTIMO;

    qtdUsuarios++;

    return qtdUsuarios;
}

void listarUsuarios(
    struct Usuario usuarios[],
    int qtdUsuarios
) {
    int i;

    printf("\nUsuarios:\n");
    for (i = 0; i < qtdUsuarios; i++) {
        printf("%d - livro emprestado %d - %s", usuarios[i].codigo, usuarios[i].codigoLivroEmprestado, usuarios[i].dados);
    }
}

int buscarUsuario(
    struct Usuario usuarios[],
    int qtdUsuarios,
    int codigoBuscado
) {
    int i, posicao;

    posicao = -1;
    for (i = 0; i < qtdUsuarios; i++) {
        if (usuarios[i].codigo == codigoBuscado) {
            posicao = i;
        }
    }

    return posicao;
}


void alterarEstoque(
    struct Livro *livro,
    int valor
) {
    livro->estoque = valor;
}

void registrarEmprestimo(
    struct Usuario *usuario,
    int codigoLivro
) {
    usuario->codigoLivroEmprestado = codigoLivro;
}

void encerrarEmprestimo(
    struct Usuario *usuario
) {
    usuario->codigoLivroEmprestado = SEM_EMPRESTIMO;
}

int main() {

    struct Livro livros[MAX_TITULOS];
    struct Usuario usuarios[MAX_USUARIOS];
    int qtdTitulos = 0, qtdUsuarios = 0;
    int codigoBuscado, posBusca, disponivel;

    while (qtdTitulos < MAX_TITULOS) {
        qtdTitulos = cadastrarTitulo(livros, qtdTitulos);
    }

    printf("\n");

    while (qtdUsuarios < MAX_USUARIOS) {
        qtdUsuarios = cadastrarUsuario(usuarios, qtdUsuarios);
    }

    listarTitulos(livros, qtdTitulos);
    listarUsuarios(usuarios, qtdUsuarios);

    printf("\nTotal: %d\n", calcularQtdExemplares(livros, qtdTitulos));

    printf("\nCodigo do titulo para buscar: ");
    scanf("%d", &codigoBuscado);

    posBusca = buscarLivro(livros, qtdTitulos, codigoBuscado);

    if (posBusca == -1) {
        printf("Titulo nao encontrado\n");
        return 0;
    }

    printf("Titulo: %s", livros[posBusca].descricao);

    disponivel = disponibilidadeTitulo(livros[posBusca].estoque);

    if (disponivel == 1) {
        printf("Titulo disponivel, estoque: %d\n", livros[posBusca].estoque);
    } else {
        printf("Titulo temporariamente indisponivel\n");
    }

    /* ---------- Testes da v5 com o livro buscado e o primeiro usuario ---------- */

    printf("\n--- Teste 1: alterar estoque ---\n");
    printf("Antes: %d\n", livros[posBusca].estoque);
    alterarEstoque(&livros[posBusca], 1);
    printf("Depois: %d\n", livros[posBusca].estoque);

    printf("\n--- Teste 2: duas alteracoes seguidas ---\n");
    alterarEstoque(&livros[posBusca], livros[posBusca].estoque + 1);
    alterarEstoque(&livros[posBusca], livros[posBusca].estoque + 1);
    printf("Estoque (esperado 3): %d\n", livros[posBusca].estoque);

    printf("\n--- Teste 3: registrar emprestimo ---\n");
    printf("Antes: %d\n", usuarios[0].codigoLivroEmprestado);
    registrarEmprestimo(&usuarios[0], livros[posBusca].codigo);
    printf("Depois: %d\n", usuarios[0].codigoLivroEmprestado);

    printf("\n--- Teste 4: encerrar emprestimo ---\n");
    encerrarEmprestimo(&usuarios[0]);
    printf("Depois: %d (esperado %d)\n", usuarios[0].codigoLivroEmprestado, SEM_EMPRESTIMO);

    listarTitulos(livros, qtdTitulos);
    listarUsuarios(usuarios, qtdUsuarios);

    return 0;
}
