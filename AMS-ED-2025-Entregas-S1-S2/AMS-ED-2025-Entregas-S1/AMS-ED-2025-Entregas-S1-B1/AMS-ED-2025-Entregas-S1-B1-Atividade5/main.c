/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-5                          */
/*             Objetivo: Sistema de Gerenciamento de Pedidos para um Restaurante    */
/*                                                                                  */
/*                  Autores: Bianca, Gabriella, Giovanna e Guilherme Santos         */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pedido{
    int num;
    char nomeCliente[30];
    char prato[30];
    int quant;
    char status[10];
    struct Pedido *prox;
};

void push(struct Pedido **topo, int num, char nomeCliente[], char prato[], int quant, char status[]){
    struct Pedido *novoPedido = (struct Pedido*)malloc(sizeof(struct Pedido));
    if(novoPedido == NULL){
        printf("Erro ao alocar memoria!\n");
        return;
    }
    novoPedido->num = num;
    strcpy(novoPedido->nomeCliente, nomeCliente);
    strcpy(novoPedido->prato, prato);
    novoPedido->quant = quant;
    strcpy(novoPedido->status, status);
    novoPedido->prox = *topo;
    *topo = novoPedido;
}

void pop(struct Pedido **topo){
    if (*topo == NULL){
        printf("Pilha vazia, nada para remover.\n");
        return;
    }
    struct Pedido *removido = *topo;
    *topo = (*topo)->prox;
    free(removido);
    printf("Pedido removido com sucesso!\n");
}

void obterTopo(struct Pedido *topo){
    if (topo == NULL){
        printf("Pilha vazia!\n");
        return;
    }
    printf("==================================\n");
    printf("          Pedido #%d \n", topo->num);
    printf("==================================\n");
    printf("Número do Pedido: %d\nNome do Cliente: %s\nDescrição do prato: %s\nQuantidade: %d\nStatus: %s\n", 
        topo->num, topo->nomeCliente, topo->prato, topo->quant, topo->status);
}

void atualizarStatus(struct Pedido *topo){
    if (topo == NULL){
        printf("Pilha vazia!\n");
        return;
    }
    printf("===============================\n");
    printf("Status atual do Pedido: %s\n", topo->status);
    printf("Atualize o Status do Pedido (pendente, em preparo, pronto, entregue): ");
    getchar();
    scanf("%9[^\n]", topo->status);
    printf("Status do pedido atualizado com sucesso!\n");
}

void liberarPilha(struct Pedido **topo){
    while (*topo != NULL){
        pop(topo);
    }
    printf("Pilha de pedidos liberada com sucesso!\n");
}

int main(){
    int opcao=0;
    struct Pedido *topo = NULL;
    
    while(opcao != 5){
        printf("==================================\n");
        printf("     Gerenciamento de Pedidos  \n");
        printf("==================================\n");
        printf("1- Inserir Pedido na Pilha\n");
        printf("2- Obter Pedido no Topo\n");
        printf("3- Atualizar status do pedido no topo\n");
        printf("4- Remover Pedido do Topo\n");
        printf("5- Encerrar\n");
        printf("==================================\n");
        printf("Insira o número da opção desejada: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                {
                    int num, quant;
                    char nomeCliente[30], prato[30], status[10];
                    printf("Número do Pedido: ");
                    scanf("%d", &num);
                    printf("Nome do Cliente: ");
                    getchar(); 
                    scanf(" %[^\n]", nomeCliente);
                    printf("Descrição do Prato: ");
                    scanf(" %[^\n]", prato); 
                    printf("Quantidade: ");
                    scanf("%d", &quant);
                    printf("Status do Pedido: ");
                    scanf(" %[^\n]", status);
                    push(&topo, num, nomeCliente, prato, quant, status);
                    printf("Pedido inserido na pilha com sucesso!\n");
                }
                break;
            case 2:
                obterTopo(topo);
                break;
            case 3:
                atualizarStatus(topo);
                break;
            case 4:
                pop(&topo);
                break;
            case 5:
                liberarPilha(&topo);
                printf("Programa encerrado com sucesso!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
    
    return 0;
}
