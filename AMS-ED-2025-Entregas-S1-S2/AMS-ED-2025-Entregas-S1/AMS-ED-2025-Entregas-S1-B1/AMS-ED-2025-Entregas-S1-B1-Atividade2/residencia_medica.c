/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                       Id da Atividade: Atividade B1-2                            */
/*             Objetivo: Seleção para Residência Médica                             */
/*                                                                                  */
/*                                  Autora: Bianca Nicolli Celso dos Santos         */
/*                                                                   Data:05/03/2025*/
/*----------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50

typedef struct {
    char nome[70];
    float notasPE[4], notasAC[5], notasPP[10], notasEB[3];
    float notaFinal;
} Candidato;

float soma_notas_centrais(float *notas, int tamanho) {
    float maior = notas[0], menor = notas[0], soma = 0.0;
    int i, idxMaior = -1, idxMenor = -1;
    
    for (i = 0; i < tamanho; i++) {
        if (notas[i] > maior) {
            maior = notas[i];
            idxMaior = i;
        }
        if (notas[i] < menor) {
            menor = notas[i];
            idxMenor = i;
        }
    }

    int removidos = 0; 
    for (i = 0; i < tamanho; i++) {
        if ((notas[i] == maior || notas[i] == menor) && removidos < 2) {
            removidos++;
            continue; 
        }
        soma += notas[i];
    }
    return soma;
}

int compara(const void *a, const void *b) {
    float nf1 = ((Candidato*)a)->notaFinal;
    float nf2 = ((Candidato*)b)->notaFinal;
    return (nf2 > nf1) - (nf2 < nf1);
}

float lerNotaValida(const char* tipoNota) {
    float nota;
    char buffer[50];
    int validaInput;

    do {
        printf("%s (de 0.0 a 10.0): ", tipoNota);
        fgets(buffer, sizeof(buffer), stdin);
        validaInput = sscanf(buffer, "%f", &nota);
        
        if (strchr(buffer, ',') != NULL) {
            validaInput = 0;  
        }

        if (validaInput != 1 || nota < 0.0 || nota > 10.0) {
            printf("Nota inválida! A nota deve ser um número entre 0.0 e 10.0 (use ponto, não vírgula).\n");
        }
    } while (validaInput != 1 || nota < 0.0 || nota > 10.0);

    return nota;
}

int main() {
    Candidato candidatos[MAX_CANDIDATOS];
    int numCandidatos, i, j;
    
    do {
        printf("Digite o número de candidatos (máximo %d): ", MAX_CANDIDATOS);
        scanf("%d", &numCandidatos);
        getchar(); 
    } while (numCandidatos < 1 || numCandidatos > MAX_CANDIDATOS);
    
    for (i = 0; i < numCandidatos; i++) {
        Candidato *ptr = &candidatos[i];  
        
        printf("\nCandidato %d\n", i + 1);
        printf("Nome: ");
        fgets(ptr->nome, sizeof(ptr->nome), stdin);
        ptr->nome[strcspn(ptr->nome, "\n")] = 0; 
        
        printf("Digite as 4 notas da Prova Escrita:\n");
        for (j = 0; j < 4; j++) {
            ptr->notasPE[j] = lerNotaValida("Nota da Prova Escrita");
        }
        
        printf("Digite as 5 notas da Análise de Curricular:\n");
        for (j = 0; j < 5; j++) {
            ptr->notasAC[j] = lerNotaValida("Nota da Análise de Curricular");
        }
        
        printf("Digite as 10 notas da Prova Prática:\n");
        for (j = 0; j < 10; j++) {
            ptr->notasPP[j] = lerNotaValida("Nota da Prova Prática");
        }
        
        printf("Digite as 3 notas da Entrevista em Banca Avaliadora:\n");
        for (j = 0; j < 3; j++) {
            ptr->notasEB[j] = lerNotaValida("Nota da Entrevista em Banca Avaliadora");
        }

        float pe = soma_notas_centrais(ptr->notasPE, 4);
        float ac = soma_notas_centrais(ptr->notasAC, 5);
        float pp = soma_notas_centrais(ptr->notasPP, 10);
        float eb = soma_notas_centrais(ptr->notasEB, 3);

        ptr->notaFinal = (pe * 0.3) + (ac * 0.1) + (pp * 0.4) + (eb * 0.2);
    }
    
    qsort(candidatos, numCandidatos, sizeof(Candidato), compara);
    
    printf("\nClassificação Final:\n");
    for (i = 0; i < (numCandidatos < 5 ? numCandidatos : 5); i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].notaFinal);
    }
    
    return 0;
}
