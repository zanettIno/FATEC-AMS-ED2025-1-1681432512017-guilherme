/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-4                                 */
/*             Objetivo: << Manipulação de Pilha >>                                 */
/*                                                                                  */
/*                                  Autor: Guilherme Xavier Zanetti                 */
/*                                                                  Data:30/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define max 4

typedef struct {
    double conteudo[max];
    char expressao[max][50];
    int topo;
} Pilha;

int opcao;

void ExibirMenu() {
    printf("Bem Vindo à Calculadora RPN!!\n\n");
    printf("Escolha uma opção: \n");
    printf("0 - Sair \n");
    printf("1 - Calcular expressão RPN \n");
}

Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    p->topo = -1;
    return p;
}

int Vazia(Pilha* p) {
    return p->topo == -1;
}

int Cheia(Pilha* p) {
    return p->topo == max - 1;
}

void Push(Pilha* p, double valor, const char* expr) {
    if (Cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->topo++;
    p->conteudo[p->topo] = valor;
    strcpy(p->expressao[p->topo], expr);
}

double Pop(Pilha* p, char* expr) {
    if (Vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    strcpy(expr, p->expressao[p->topo]);
    return p->conteudo[p->topo--];
}

int Top(Pilha* pilha) {
    if (Vazia(pilha)) {
        printf("Erro: a pilha está vazia\n");
        return -1;
    }
    return pilha->conteudo[pilha->topo];
}


void calcular_RPN(char* expressao) {
    Pilha* pilha = criar_pilha();
    char* token = strtok(expressao, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            double num = atof(token);
            char temp[20];
            sprintf(temp, "%.2f", num);
            Push(pilha, num, temp);
        } else {
            if (pilha->topo < 1) {
                printf("Erro: Expressão inválida!\n");
                free(pilha);
                return;
            }
            char exprA[50], exprB[50];
            double X = Pop(pilha, exprB);
            double Y = Pop(pilha, exprA);
            double T;
            char Z = token[0];
            char novaExpr[150];
            
            switch (Z) {
                case '+': T = Y + X; break;
                case '-': T = Y - X; break;
                case '*': T = Y * X; break;
                case '/':
                    if (X == 0) {
                        printf("Erro: Divisão por zero!\n");
                        free(pilha);
                        return;
                    }
                    T = Y / X;
                    break;
                default:
                    printf("Erro: Operador inválido!\n");
                    free(pilha);
                    return;
            }
            
            snprintf(novaExpr, sizeof(novaExpr), "(%s %c %s)", exprA, Z, exprB);
            Push(pilha, T, novaExpr);
        }
        token = strtok(NULL, " ");
    }
    
    if (pilha->topo != 0) {
        printf("Erro: Expressão inválida!\n");
        free(pilha);
        return;
    }
    
    char resultadoExpr[100];
    double resultadoFinal = Pop(pilha, resultadoExpr);
    printf("\nResultado: %s = %.2f \n", resultadoExpr, resultadoFinal);
    free(pilha);
}

int main() {
    Pilha* pilha = criar_pilha();
    char expressao[100];
    
    ExibirMenu();
    scanf("%d", &opcao);
    
    switch (opcao) {
        case 0:
            free(pilha);
            return 0;
        
        case 1:
            printf("\nDigite a expressão em RPN:\n");
            getchar(); 
            fgets(expressao, sizeof(expressao), stdin);
            expressao[strcspn(expressao, "\n")] = 0;  
            calcular_RPN(expressao);
            break;
        
        default:
            printf("\nNão há esta opção no menu!\n");
    }

    free(pilha);
    return 0;
}
