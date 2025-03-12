/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2                                 */
/*             Objetivo: << Manipulacao de Array com ponteiro >>                    */
/*                                                                                  */
/*                                  Autor: Guilherme Xavier Zanetti                 */
/*                                                                  Data:06/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Candidato {
    char nome[50];
    float PE[4];
    float AC[5];
    float PP[10];
    float EB[3];
    float NF;
    struct Candidato *prox; 
};

float mediaCentral(float *ptrNotas, int tamanho) { 
    float soma = 0, maior = ptrNotas[0], menor = ptrNotas[0];
    int i;
    
    for (i = 0; i < tamanho; i++) {
        soma += ptrNotas[i];
        if (ptrNotas[i] > maior) maior = ptrNotas[i];
        if (ptrNotas[i] < menor) menor = ptrNotas[i];
    }

    return (soma - maior - menor); 
}

void inserirCandidato(struct Candidato **inicio, char nome[], float PE[], float AC[], float PP[], float EB[]) {
    struct Candidato *novoCandidato = (struct Candidato*)malloc(sizeof(struct Candidato));
    
    if (novoCandidato == NULL) {
        printf("Erro ao alocar memoria! \n");
        return;
    }

    strcpy(novoCandidato->nome, nome);
    memcpy(novoCandidato->PE, PE, 4 * sizeof(float));
    memcpy(novoCandidato->AC, AC, 5 * sizeof(float));
    memcpy(novoCandidato->PP, PP, 10 * sizeof(float));
    memcpy(novoCandidato->EB, EB, 3 * sizeof(float));

    float media_PE = mediaCentral(PE, 4); 
    float media_AC = mediaCentral(AC, 5);  
    float media_PP = mediaCentral(PP, 10); 
    float media_EB = mediaCentral(EB, 3);  

    novoCandidato->NF = (media_PE * 0.3f) + (media_AC * 0.1f) +
                        (media_PP * 0.4f) + (media_EB * 0.2f);
    
    novoCandidato->prox = *inicio;
    *inicio = novoCandidato;
}

void classificarCandidatos(struct Candidato **inicio) {
    struct Candidato *i, *j;
    float tempNF;
    char tempNome[50];

    for (i = *inicio; i != NULL; i = i->prox) {
        for (j = i->prox; j != NULL; j = j->prox) {
            if (i->NF < j->NF) {
                tempNF = i->NF;
                i->NF = j->NF;
                j->NF = tempNF;

                strcpy(tempNome, i->nome);
                strcpy(i->nome, j->nome);
                strcpy(j->nome, tempNome);
            }
        }
    }
}

void exibirClassificacao(struct Candidato *inicio) {
    struct Candidato *ptr = inicio;
    printf("Classificação dos melhores candidatos: \n");
    for (int i = 0; i < 5 && ptr != NULL; i++) {
        printf("%dº %s - Nota Final: %.2f \n", i + 1, ptr->nome, ptr->NF);
        ptr = ptr->prox;
    }
}

int main() {
    struct Candidato *inicio = NULL;

    int num_candidatos = 0;
    int continuar = 1;  

    printf("Bem-vindo ao sistema de classificação para residência médica: \n\n");

    while (continuar == 1) {
        char nome[50];
        float PE[4], AC[5], PP[10], EB[3];
        
        printf("Você já cadastrou %i candidato(os) \n", num_candidatos);
        printf("Digite o nome do candidato: ");
        scanf("%s", nome);

        printf("Digite as 4 notas para Prova Escrita(PE):\n");
        for (int qtde = 0; qtde < 4; qtde++) {
            scanf("%f", &PE[qtde]);
        }

        printf("Digite as 5 notas para Análise Curricular(AC):\n");
        for (int qtde = 0; qtde < 5; qtde++) {
            scanf("%f", &AC[qtde]);
        }

        printf("Digite as 10 notas para Prova Prática(PP):\n");
        for (int qtde = 0; qtde < 10; qtde++) {
            scanf("%f", &PP[qtde]);
        }

        printf("Digite as 3 notas para Entrevista em Banca(EB):\n");
        for (int qtde = 0; qtde < 3; qtde++) {
            scanf("%f", &EB[qtde]);
        }

        inserirCandidato(&inicio, nome, PE, AC, PP, EB);
        num_candidatos++;

        if (num_candidatos >= 50) {
            printf("Limite de 50 candidatos atingido. \n");
            break;
        }

        printf("\nVocê deseja adicionar mais um candidato? (1 para SIM, 0 para NÃO): ");
        scanf("%d", &continuar);
    }

    classificarCandidatos(&inicio);
    exibirClassificacao(inicio);

    return 0;
}
