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

int cadastrarUsuario(
    struct Usuario usuarios[],
    int qtdUsuarios
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

int buscarUsuario(
    struct Usuario usuarios[],
    int qtdUsuarios,
    int codigoBuscado
);

int disponibilidadeTitulo(
    int qtdEstoque
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

int emprestarLivro(
    struct Livro *livro,
    struct Usuario *usuario
);

int devolverLivro(
    struct Livro *livro,
    struct Usuario *usuario
);

int cadastrarTitulo(
    struct Livro livros[],
    int qtdTitulos
) {
    int codTemporario, estoTemporario;

    if (qtdTitulos >= MAX_TITULOS) {
        printf("Limite de titulos atingido\n");
        return qtdTitulos;
    }

    printf("Codigo do titulo: ");
    scanf("%d", &codTemporario);

    if (codTemporario <= 0) {
        printf("Codigo invalido, o titulo nao foi cadastrado\n");
        return qtdTitulos;
    }

    if (buscarLivro(livros, qtdTitulos, codTemporario) != -1) {
        printf("Esse codigo ja existe, o titulo nao foi cadastrado\n");
        return qtdTitulos;
    }

    printf("Estoque: ");
    scanf("%d", &estoTemporario);

    if (estoTemporario < 0) {
        printf("Estoque invalido, o titulo nao foi cadastrado\n");
        return qtdTitulos;
    }

    // pesquisei e achei melhor usar o getchar pra tirar o enter que sobra do scanf antes do fgets
    getchar();

    printf("Descricao (titulo; autor; ano; tema): ");
    fgets(livros[qtdTitulos].descricao, TAM_TEXTO, stdin);

    livros[qtdTitulos].codigo = codTemporario;
    livros[qtdTitulos].estoque = estoTemporario;

    qtdTitulos++;

    printf("Titulo cadastrado\n");

    return qtdTitulos;
}

int cadastrarUsuario(
    struct Usuario usuarios[],
    int qtdUsuarios
) {
    int codTemporario;

    if (qtdUsuarios >= MAX_USUARIOS) {
        printf("Limite de usuarios atingido\n");
        return qtdUsuarios;
    }

    printf("Codigo do usuario: ");
    scanf("%d", &codTemporario);

    if (codTemporario <= 0) {
        printf("Codigo invalido, o usuario nao foi cadastrado\n");
        return qtdUsuarios;
    }

    if (buscarUsuario(usuarios, qtdUsuarios, codTemporario) != -1) {
        printf("Esse codigo ja existe, o usuario nao foi cadastrado\n");
        return qtdUsuarios;
    }

    getchar();

    printf("Dados do usuario: ");
    fgets(usuarios[qtdUsuarios].dados, TAM_TEXTO, stdin);

    usuarios[qtdUsuarios].codigo = codTemporario;
    usuarios[qtdUsuarios].codigoLivroEmprestado = SEM_EMPRESTIMO;

    qtdUsuarios++;

    printf("Usuario cadastrado\n");

    return qtdUsuarios;
}

void listarTitulos(
    struct Livro livros[],
    int qtdTitulos
) {
    int i;

    if (qtdTitulos == 0) {
        printf("Nenhum titulo cadastrado\n");
        return;
    }

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

int disponibilidadeTitulo(
    int qtdEstoque
) {
    if (qtdEstoque > 0) {
        return 1;
    } else {
        return 0;
    }
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

int emprestarLivro(
    struct Livro *livro,
    struct Usuario *usuario
) {
    // as duas mudancas so acontecem se todas as regras forem aprovadas
    if (disponibilidadeTitulo(livro->estoque) == 0) {
        return 0;
    }

    if (usuario->codigoLivroEmprestado != SEM_EMPRESTIMO) {
        return 0;
    }

    alterarEstoque(livro, livro->estoque - 1);
    registrarEmprestimo(usuario, livro->codigo);

    return 1;
}

int devolverLivro(
    struct Livro *livro,
    struct Usuario *usuario
) {
    if (usuario->codigoLivroEmprestado == SEM_EMPRESTIMO) {
        return 0;
    }

    if (usuario->codigoLivroEmprestado != livro->codigo) {
        return 0;
    }

    alterarEstoque(livro, livro->estoque + 1);
    encerrarEmprestimo(usuario);

    return 1;
}

int main() {

    struct Livro livros[MAX_TITULOS];
    struct Usuario usuarios[MAX_USUARIOS];
    int qtdTitulos = 0, qtdUsuarios = 0;
    int opcao = -1, codigoBuscado, codigoUsuario, indiceLivro, indiceUsuario;

    while (opcao != 0) {

        printf("\n--- Biblioteca ---\n");
        printf("1 - Cadastrar livro\n");
        printf("2 - Cadastrar usuario\n");
        printf("3 - Listar livros\n");
        printf("4 - Buscar livro\n");
        printf("5 - Emprestar livro\n");
        printf("6 - Devolver livro\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            qtdTitulos = cadastrarTitulo(livros, qtdTitulos);
        } else if (opcao == 2) {
            qtdUsuarios = cadastrarUsuario(usuarios, qtdUsuarios);
        } else if (opcao == 3) {
            listarTitulos(livros, qtdTitulos);
        } else if (opcao == 4) {
            printf("Codigo do titulo: ");
            scanf("%d", &codigoBuscado);

            indiceLivro = buscarLivro(livros, qtdTitulos, codigoBuscado);

            if (indiceLivro == -1) {
                printf("Titulo nao encontrado\n");
            } else {
                printf("Titulo: %s", livros[indiceLivro].descricao);

                if (disponibilidadeTitulo(livros[indiceLivro].estoque) == 1) {
                    printf("Titulo disponivel, estoque: %d\n", livros[indiceLivro].estoque);
                } else {
                    printf("Titulo temporariamente indisponivel\n");
                }
            }
        } else if (opcao == 5) {
            printf("Codigo do titulo: ");
            scanf("%d", &codigoBuscado);
            printf("Codigo do usuario: ");
            scanf("%d", &codigoUsuario);

            indiceLivro = buscarLivro(livros, qtdTitulos, codigoBuscado);
            indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);

            if (indiceLivro == -1) {
                printf("Titulo nao encontrado\n");
            } else if (indiceUsuario == -1) {
                printf("Usuario nao encontrado\n");
            } else if (emprestarLivro(&livros[indiceLivro], &usuarios[indiceUsuario])) {
                printf("Emprestimo realizado.\n");
            } else {
                printf("Nao foi possivel realizar o emprestimo.\n");
            }
        } else if (opcao == 6) {
            printf("Codigo do titulo: ");
            scanf("%d", &codigoBuscado);
            printf("Codigo do usuario: ");
            scanf("%d", &codigoUsuario);

            indiceLivro = buscarLivro(livros, qtdTitulos, codigoBuscado);
            indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);

            if (indiceLivro == -1) {
                printf("Titulo nao encontrado\n");
            } else if (indiceUsuario == -1) {
                printf("Usuario nao encontrado\n");
            } else if (devolverLivro(&livros[indiceLivro], &usuarios[indiceUsuario])) {
                printf("Devolucao realizada.\n");
            } else {
                printf("Nao foi possivel realizar a devolucao.\n");
            }
        } else if (opcao != 0) {
            printf("Opcao invalida\n");
        }
    }

    printf("Programa encerrado\n");

    return 0;
}
