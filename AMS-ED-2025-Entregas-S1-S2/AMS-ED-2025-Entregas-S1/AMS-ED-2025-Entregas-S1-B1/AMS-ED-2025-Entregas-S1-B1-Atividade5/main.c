#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 4

typedef struct {
    int Numero;
    char Nome[30];
    char Descricao[50];
    int Quantidade;
    char Status[20];
} Pedido;

typedef struct {
    Pedido Data[max];
    int Top;
} Pilha;

char TipoStatus[4][20] = {"Pendente", "Em Preparo", "Pronto", "Entregue"};

Pilha* CriarPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->Top = -1;
    return p;
}

int Vazia(Pilha* p) {
    return p->Top == -1;
}

int Cheia(Pilha* p) {
    return p->Top == max - 1;
}

void PushPedido(Pilha* p) {
    if (Cheia(p)) {
        printf("Erro: Pilha cheia! Não é possível adicionar mais pedidos.\n");
        return;
    }

    Pedido novoPedido;
    printf("Insira o número do pedido: ");
    scanf("%d", &novoPedido.Numero);
    printf("Insira o seu nome: ");
    scanf("%s", novoPedido.Nome);
    printf("Insira a descrição do pedido: ");
    scanf("%s", novoPedido.Descricao);
    printf("Insira a quantidade: ");
    scanf("%d", &novoPedido.Quantidade);
    strcpy(novoPedido.Status, TipoStatus[0]);

    p->Top++;
    p->Data[p->Top] = novoPedido;
}

void PopPedido(Pilha* p) {
    if (Vazia(p)) {
        printf("Erro: Nenhum pedido para remover!\n");
        return;
    }

    Pedido pedido = p->Data[p->Top];
    p->Top--;
    printf("Pedido removido: %d - %s - %s\n", pedido.Numero, pedido.Nome, pedido.Status);
}

void AtualizarStatusPedido(Pilha* p) {
    if (Vazia(p)) {
        printf("Erro: Nenhum pedido para atualizar!\n");
        return;
    }

    Pedido* pedido = &p->Data[p->Top];
    for (int i = 0; i < 3; i++) {
        if (strcmp(pedido->Status, TipoStatus[i]) == 0) {
            strcpy(pedido->Status, TipoStatus[i + 1]);
            printf("O status do pedido foi atualizado para: %s\n", pedido->Status);
            if (strcmp(pedido->Status, "Entregue") == 0) {
                PopPedido(p);
            }
            return;
        }
    }
}

void ExibirPedidoAtual(Pilha* p) {
    if (Vazia(p)) {
        printf("Erro: Nenhum pedido disponível!\n");
        return;
    }

    Pedido pedido = p->Data[p->Top];
    printf("\nPedido Atual:\nNúmero: %d\nCliente: %s\nDescrição: %s\nQuantidade: %d\nStatus: %s\n", 
           pedido.Numero, pedido.Nome, pedido.Descricao, pedido.Quantidade, pedido.Status);
}

int main() {
    Pilha* pilha = CriarPilha();
    int escolha;
    while (1) {
        printf("\n\nRestaurante - Pilha de Pedidos\n");
        printf("1 - Inserir pedido\n");
        printf("2 - Obter pedido atual\n");
        printf("3 - Atualizar status do pedido\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 0:
                free(pilha);
                return 0;
            case 1:
                PushPedido(pilha);
                break;
            case 2:
                ExibirPedidoAtual(pilha);
                break;
            case 3:
                AtualizarStatusPedido(pilha);
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    }
}
