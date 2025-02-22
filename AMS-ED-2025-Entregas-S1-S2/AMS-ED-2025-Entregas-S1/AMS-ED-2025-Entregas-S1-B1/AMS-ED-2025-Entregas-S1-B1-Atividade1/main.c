#include <stdio.h>

float calcularDesconto(float *ptrPreco, float *ptrDesconto, int *ptrDecisaoD) { 
    if((*ptrDecisaoD == 1)) {
        float pFinal = (*ptrPreco) - ((*ptrPreco) * ((*ptrDesconto) / 100 ));
        
        printf("\n");
        printf("O seu produto, de preço original $%2.f e desconto de %2.f%c ficou com o preço final de: $%.2f\n", *ptrPreco, *ptrDesconto, 37, pFinal);
    }
    
    else {
        float pFinal = (*ptrPreco) - (*ptrDesconto);
        
        printf("\n");
        printf("O seu produto, de preço original $%2.f e desconto de $%2.f reais ficou com o preço final de: $%.2f\n", *ptrPreco, *ptrDesconto, pFinal);
    }
    
    return 0;
}

 void main() {
    int decisaoSN, decisaoD;
    float preco, desconto, pFinal;
    
    printf("Bem vindo à Loja de Eletrônicos XuxuBeleza!! \n");
    printf("\n");
    
    printf("Insira o preco do seu produto: ");
    scanf("%f", &preco);
    printf("\n");
    
    printf("Você gostaria de adicionar um desconto? \n");
    printf("Use 1 para SIM e 0 para NÃO: ");
    scanf("%i", &decisaoSN);
    
    switch (decisaoSN) {
        case 0:
            printf("\n");
            printf("O seu produto, sem desconto, possui o preço de: $%2.f\n", preco);
            break;
        
        case 1:
            printf("\n");
            printf("O seu desconto seria em porcentagem ou reais? \n");
            printf("Use 1 para porcentagem e 0 para REAIS: ");
            scanf("%i", &decisaoD);
            
            printf("\n");
            printf("Insira o desconto: ");
            scanf("%f", &desconto); 
            
            pFinal = calcularDesconto(&preco, &desconto, &decisaoD); 
            break;
        
        default:
            printf("\n");
            printf("Opção inválida, tente novamente\n");
    }
}