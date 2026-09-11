#include <stdio.h>

int main () {
    
    int livros[], i, codLivro;
    
    for(i = 0; i <=3; i++){
    printf("Digite o cod dos 3 livros: ");
    scanf("%d", &codLivro);
    
    livros[i] = codLivro;

    }
    
    return 0;
}
