/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                       Id da Atividade: Atividade B2-2                            */
/*                             Objetivo: Bubblesort                                 */
/*                                                                                  */
/*                                  Autora: Bianca Nicolli Celso dos Santos         */
/*                                                                  Data:06/05/2025 */
/*----------------------------------------------------------------------------------*/







#include <stdio.h>

int main() {
    int n, i, j, temp;

   
    printf("Digite a quantidade de numeros: ");
    scanf("%d", &n);

    int vet[n];

   
    for (i = 0; i < n; i++) {
        printf("Digite o numero %d: ", i + 1);
        scanf("%d", &vet[i]);
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (vet[j] > vet[j + 1]) {
                // Troca os elementos
                temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }

    // Exibe o vetor ordenado
    printf("Vetor ordenado em ordem crescente:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", vet[i]);
    }

    printf("\n");
    return 0;
}
