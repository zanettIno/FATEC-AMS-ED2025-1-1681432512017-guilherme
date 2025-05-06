/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B2-2                                 */
/*             Objetivo: <<  bubbleSort  >>                                         */
/*                                                                                  */
/*                                  Autor: Carolina Souza, Guilherme Zanetti,       */
/*                                       Heloísa Souza e Nuno Yokoji                */
/*                                                                   Data:06/05/2025*/
/*----------------------------------------------------------------------------------*/


#include <stdio.h>

#define MAX 100

int menu() {
    int decisao;
    printf("Deseja inserir mais um número? (1 - Sim | 0 - Não): ");
    scanf("%d", &decisao);
    return decisao;
}

void bubbleSort(int num[], int tamanho) {
    int i, j, temp;
    for(i = 0; i < tamanho; i++) {
        for(j = 0; j < tamanho - 1; j++) {
            if(num[j] > num[j + 1]) {
                temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }
}

void exibir(int num[], int tamanho) {
    printf("Numeros em ordem crescente:\n");
    for(int i = 0; i < tamanho; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
}

int main() {
    int num[MAX];
    int i = 0;
    int decisao = 1;

    while(decisao == 1 && i < MAX) {
        printf("Insira um número: ");
        scanf("%d", &num[i]);
        i++;

        if(i < MAX) {
            decisao = menu();
        }
    }

    bubbleSort(num, i);
    exibir(num, i);

    return 0;
}
