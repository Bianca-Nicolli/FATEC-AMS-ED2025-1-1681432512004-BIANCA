/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                       Id da Atividade: Atividade B1-3                            */
/*             Objetivo: Sistema De Gerenciamento de Pedidos para um Restaurante    */
/*                                                                                  */
/*                                  Autora: Bianca Nicolli Celso dos Santos         */
/*                                                                  Data:20/03/2025 */
/*----------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
   int numero;
   char cliente[50];
   char prato[50];
   int quantidade;
   char status[20];
   struct Pedido* proximo;
} Pedido;

const char* STATUS_VALIDOS[] = {"pendente", "em preparo", "pronto", "entregue"};
const int STATUS_COUNT = 4;

Pedido* criarLista() {
   return NULL;
}

int isStatusValido(const char* status) {
   for (int i = 0; i < STATUS_COUNT; i++) {
       if (strcmp(status, STATUS_VALIDOS[i]) == 0) {
           return 1;
       }
   }
   return 0;
}

void lerString(char* buffer, int tamanho, const char* mensagem) {
   printf("%s", mensagem);
   if (fgets(buffer, tamanho, stdin)) {
       size_t len = strlen(buffer);
       if (len > 0 && buffer[len - 1] == '\n') {
           buffer[len - 1] = '\0';
       }
   }
}

int lerInteiro(const char* mensagem) {
   int valor;
   char buffer[50];  
   while (1) {
       printf("%s", mensagem);
       if (fgets(buffer, sizeof(buffer), stdin)) {
           if (sscanf(buffer, "%d", &valor) == 1) {
               return valor;
           }
       }
       printf("Entrada inválida. Tente novamente.\n");
   }
}

void inserirPedido(Pedido** lista) {
   Pedido* novo = (Pedido*)malloc(sizeof(Pedido));
   if (!novo) {
       printf("Erro: Falha ao alocar memória.\n");
       return;
   }
   novo->numero = lerInteiro("Número do pedido: ");
   lerString(novo->cliente, 50, "Nome do cliente: ");
   lerString(novo->prato, 50, "Nome do prato: ");
   novo->quantidade = lerInteiro("Quantidade: ");
   while (1) {
       lerString(novo->status, 20, "Status (pendente, em preparo, pronto, entregue): ");
       if (isStatusValido(novo->status)) {
           break;
       }
       printf("Erro: Status inválido.\n");
   }
   novo->proximo = *lista;
   *lista = novo;
   printf("Pedido %d inserido com sucesso!\n", novo->numero);
}

void buscarPedido(Pedido* lista) {
   int numero = lerInteiro("Número do pedido a buscar: ");
   Pedido* atual = lista;
   while (atual) {
       if (atual->numero == numero) {
           printf("\n--- Pedido Encontrado ---\n");
           printf("Número: %d\n", atual->numero);
           printf("Cliente: %s\n", atual->cliente);
           printf("Prato: %s\n", atual->prato);
           printf("Quantidade: %d\n", atual->quantidade);
           printf("Status: %s\n\n", atual->status);
           return;
       }
       atual = atual->proximo;
   }
   printf("Erro: Pedido %d não encontrado.\n", numero);
}

void atualizarStatus(Pedido* lista) {
   int numero = lerInteiro("Número do pedido a atualizar: ");
   Pedido* atual = lista;
   while (atual) {
       if (atual->numero == numero) {
           while (1) {
               char novoStatus[20];
               lerString(novoStatus, 20, "Novo status (pendente, em preparo, pronto, entregue): ");
               if (isStatusValido(novoStatus)) {
                   strcpy(atual->status, novoStatus);
                   printf("Status do pedido %d atualizado para '%s'.\n", numero, novoStatus);
                   return;
               }
               printf("Erro: Status inválido.\n");
           }
       }
       atual = atual->proximo;
   }
   printf("Erro: Pedido %d não encontrado.\n", numero);
}

void removerPedido(Pedido** lista) {
   int numero = lerInteiro("Número do pedido a remover: ");
   Pedido *atual = *lista, *anterior = NULL;
   while (atual && atual->numero != numero) {
       anterior = atual;
       atual = atual->proximo;
   }
   if (!atual) {
       printf("Erro: Pedido %d não encontrado.\n", numero);
       return;
   }
   if (!anterior) {  
       *lista = atual->proximo;
   } else {
       anterior->proximo = atual->proximo;
   }
   free(atual);
   printf("Pedido %d removido com sucesso.\n", numero);
}

void liberarLista(Pedido* lista) {
   Pedido* atual = lista;
   while (atual) {
       Pedido* temp = atual;
       atual = atual->proximo;
       free(temp);
   }
}

void exibirMenu() {
   printf("\n-- Sistema de Gerenciamento de Pedidos --\n");
   printf("1. Criar Lista de Pedidos\n");
   printf("2. Inserir Pedido\n");
   printf("3. Buscar Pedido\n");
   printf("4. Atualizar Status\n");
   printf("5. Remover Pedido\n");
   printf("6. Sair\n");
}

int main() {
   Pedido* lista = NULL;
   int opcao;
   int listaCriada = 0;  
   do {
       exibirMenu();
       opcao = lerInteiro("Escolha uma opção: ");
       switch (opcao) {
           case 1:
               if (listaCriada) {
                   printf("Erro: A lista já foi criada. Não é possível criar uma nova lista.\n");
               } else {
                   lista = criarLista();
                   listaCriada = 1;
                   printf("Lista de pedidos criada com sucesso!\n");
               }
               break;
           case 2:
               if (!listaCriada) {
                   printf("Erro: Crie a lista antes de inserir um pedido.\n");
               } else {
                   inserirPedido(&lista);
               }
               break;
           case 3:
               if (!listaCriada) {
                   printf("Erro: Crie a lista antes de buscar um pedido.\n");
               } else {
                   buscarPedido(lista);
               }
               break;
           case 4:
               if (!listaCriada) {
                   printf("Erro: Crie a lista antes de atualizar um pedido.\n");
               } else {
                   atualizarStatus(lista);
               }
               break;
           case 5:
               if (!listaCriada) {
                   printf("Erro: Crie a lista antes de remover um pedido.\n");
               } else {
                   removerPedido(&lista);
               }
               break;
           case 6:
               if (listaCriada) {
                   liberarLista(lista);
               }
               printf("Encerrando o programa.\n");
               break;
           default:
               printf("Opção inválida. Tente novamente.\n");
       }
   } while (opcao != 6);
   return 0;
}
