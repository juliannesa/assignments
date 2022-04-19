#include <stdio.h>

void torreDeHanoi(int num, int hasteori, int hasteaux, int hastedes) {
    if (num == 1) printf("Peca %d que esta na haste %d vai para a haste %d\n", num, hasteori, hastedes);
    else{
        torreDeHanoi(num - 1, hasteori, hastedes, hasteaux);
        printf("Peca %d que esta na haste %d vai para a haste %d\n", num, hasteori, hastedes);
        torreDeHanoi(num - 1, hasteaux, hasteori,hastedes);
    }
}

int main() {
    int numero;
    scanf("%d", &numero);
    torreDeHanoi(numero, 1, 2, 3);
    return 0;
}
