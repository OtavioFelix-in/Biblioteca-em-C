# Biblioteca em C

Projeto feito durante as aulas de Sistemas de Informação na PUC-Campinas para praticar lógica de programação em C, simulando o cadastro de livros em uma biblioteca.

O mesmo sistema é desenvolvido em várias versões. Cada versão acrescenta um conteúdo novo da disciplina e reaproveita o que já funcionava na anterior. O roteiro completo está no arquivo `Sistema de Biblioteca - Aulas Proramacao v1-3.pdf`.

## Versões

| Versão | Arquivo | Conteúdo | O que o sistema passa a fazer |
|--------|---------|----------|-------------------------------|
| 1 | `v1.c` | Vetores e repetições | Cadastra códigos e estoques, lista o acervo, calcula o total de exemplares e busca um livro pelo código |
| 2 | `v2.c` | Strings | Guarda e mostra uma descrição para cada livro (título, autor, ano e tema) |
| 3 | `v3.c` | Funções | Separa cadastro, listagem, busca, total de exemplares e disponibilidade em funções |

## Regras do sistema

- No máximo 3 títulos cadastrados, cada um podendo ter vários exemplares.
- O código de cada livro deve ser um número inteiro, positivo e único.
- O estoque não pode ser negativo.
- A descrição do livro é informada em uma única linha de até 120 caracteres, separando as informações por ponto e vírgula. Exemplo: `O Hobbit; J. R. R. Tolkien; 1937; Fantasia`
- Um livro com estoque maior que zero está disponível; com estoque igual a zero, está indisponível.

## Tecnologias

- C

## Como rodar

É preciso ter um compilador C instalado, como o `gcc`. Troque `v3.c` pelo arquivo da versão que quiser executar:

```bash
gcc v3.c -o biblioteca
./biblioteca
```

No Windows, o executável gerado é `biblioteca.exe`:

```bash
gcc v3.c -o biblioteca.exe
biblioteca.exe
```

## Exemplo de uso

Cadastrando os livros abaixo:

| Código | Estoque | Descrição |
|--------|---------|-----------|
| 101 | 2 | O Hobbit; J. R. R. Tolkien; 1937; Fantasia |
| 205 | 0 | Dom Casmurro; Machado de Assis; 1899; Romance |
| 310 | 5 | Memórias Póstumas de Brás Cubas; Machado de Assis; 1881; Romance |

O total de exemplares no acervo é 7. Buscando o código 205, o livro é encontrado, mas aparece como indisponível. Buscando um código que não existe, como 999, o sistema informa que o título não foi encontrado.
