/*-------------------------------------------------------*
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Calcular media de notas          *
* Data - 26/02/2024                                      * 
* Autor: Nathan Lazzaro			                 *
*--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50
#define MELHORES_CANDIDATOS 15

typedef struct {
    char nome[100];
    float notasPE[4], notasAC[5], notasPP[10], notasEB[3];
    float notaFinal;
} Candidato;

void lerNotas(float *notas, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
}

float calcularMediaCentral(float *notas, int tamanho) {
    float menor = notas[0], maior = notas[0], soma = 0.0;
    for (int i = 1; i < tamanho; i++) {
        if (notas[i] < menor) menor = notas[i];
        if (notas[i] > maior) maior = notas[i];
    }
    for (int i = 0; i < tamanho; i++) {
        soma += notas[i];
    }
    return (soma - menor - maior) / (tamanho - 2);
}

void ordenarCandidatos(Candidato *candidatos, int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = i + 1; j < quantidade; j++) {
            if (candidatos[i].notaFinal < candidatos[j].notaFinal) {
                Candidato temp = candidatos[i];
                candidatos[i] = candidatos[j];
                candidatos[j] = temp;
            }
        }
    }
}

int main() {
    int numCandidatos;
    Candidato candidatos[MAX_CANDIDATOS];

    printf("Informe o número de candidatos (máximo %d): ", MAX_CANDIDATOS);
    scanf("%d", &numCandidatos);

    if (numCandidatos > MAX_CANDIDATOS) {
        printf("Número máximo de candidatos excedido!\n");
        return 1;
    }

    for (int i = 0; i < numCandidatos; i++) {
        printf("\nInforme o nome do candidato %d: ", i + 1);
        scanf(" %s", candidatos[i].nome);

        printf("\nDigite as notas da Prova Escrita (PE):\n");
        lerNotas(candidatos[i].notasPE, 4);
        printf("\nDigite as notas da Análise Curricular (AC):\n");
        lerNotas(candidatos[i].notasAC, 5);
        printf("\nDigite as notas da Prova Prática (PP):\n");
        lerNotas(candidatos[i].notasPP, 10);
        printf("\nDigite as notas da Entrevista em Banca Avaliadora (EB):\n");
        lerNotas(candidatos[i].notasEB, 3);

        float mediaPE = calcularMediaCentral(candidatos[i].notasPE, 4);
        float mediaAC = calcularMediaCentral(candidatos[i].notasAC, 5);
        float mediaPP = calcularMediaCentral(candidatos[i].notasPP, 10);
        float mediaEB = calcularMediaCentral(candidatos[i].notasEB, 3);
        
        candidatos[i].notaFinal = (mediaPE * 0.3) + (mediaAC * 0.1) + (mediaPP * 0.4) + (mediaEB * 0.2);
    }

    ordenarCandidatos(candidatos, numCandidatos);

    printf("\nClassificação dos 15 melhores candidatos:\n");
    for (int i = 0; i < MELHORES_CANDIDATOS && i < numCandidatos; i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].notaFinal);
    }
    return 0;
}