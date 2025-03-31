/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                       Id da Atividade: Atividade B1-4                            */
/*                             Objetivo: Manipulação de Pilha                       */
/*                                                                                  */
/*                                  Autora: Bianca Nicolli Celso dos Santos         */
/*                                                                  Data:31/03/2025 */
/*----------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    double data[MAX_SIZE];
    char exp[MAX_SIZE][300];  
    int top;
} Pilha;

Pilha* criar_pilha() {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    pilha->top = -1;
    return pilha;
}


int pilha_vazia(Pilha* pilha) {
    return pilha->top == -1;
}


int pilha_cheia(Pilha* pilha) {
    return pilha->top == MAX_SIZE - 1;
}


void push(Pilha* pilha, double valor, const char* exp) {
    if (pilha_cheia(pilha)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    pilha->top++;
    pilha->data[pilha->top] = valor;
    strncpy(pilha->exp[pilha->top], exp, sizeof(pilha->exp[pilha->top]) - 1);
    pilha->exp[pilha->top][sizeof(pilha->exp[pilha->top]) - 1] = '\0';  
}


double pop(Pilha* pilha, char* exp) {
    if (pilha_vazia(pilha)) {
        printf("Erro: Pilha vazia!\n");
        return 0;
    }
    strcpy(exp, pilha->exp[pilha->top]);  
    return pilha->data[pilha->top--];
}


void calcular_rpn(char* expressao) {
    Pilha* pilha = criar_pilha();
    char* token = strtok(expressao, " ");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            
            push(pilha, atof(token), token);
        } else {
           
            if (pilha->top < 1) {
                printf("Erro: Expressão inválida!\n");
                free(pilha);
                return;
            }

            char a_exp[300], b_exp[300];
            double b = pop(pilha, b_exp);
            double a = pop(pilha, a_exp);
            double resultado = 0;
            char operador = token[0];

            switch (operador) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Erro: Divisão por zero!\n");
                        free(pilha);
                        return;
                    }
                    resultado = a / b;
                    break;
                default:
                    printf("Erro: Operador inválido!\n");
                    free(pilha);
                    return;
            }

           
            int tamanho = snprintf(NULL, 0, "(%s %c %s)", a_exp, operador, b_exp) + 1;
            char* resultado_exp = malloc(tamanho);
            snprintf(resultado_exp, tamanho, "(%s %c %s)", a_exp, operador, b_exp);

            
            push(pilha, resultado, resultado_exp);
            free(resultado_exp);
        }
        token = strtok(NULL, " ");
    }

    if (pilha->top != 0) {
        printf("Erro: Expressão inválida!\n");
    } else {
        char resultado_exp[300];
        double resultado = pop(pilha, resultado_exp);
        printf("Resultado: %.2f\n", resultado);
        printf("Expressão: %s\n", resultado_exp);
    }

    free(pilha);
}

int main() {
    char expressao[100];

    printf("Digite a expressão em RPN: ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = 0;  

    calcular_rpn(expressao);

    return 0;
}