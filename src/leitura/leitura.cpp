#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#define BUFFER 4096

char** lerVotos(int* numVotos)
{
    // Abrir arquivo .txt 
    FILE* arquivo = fopen("votos.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }    

    // Criar vetor dinâmico
    char** votos = NULL;

    // Ler os votos
    while (!feof(arquivo))
    {
        char* voto = (char*) malloc(BUFFER * sizeof(char));

        if (voto == NULL)
        {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }

        if (fscanf(arquivo, "%s", voto) == EOF)
        {
            printf("Erro ao ler o arquivo.\n");
            exit(1);
        }

        // Adicionar o voto lido no vetor dinâmico
        char** aux = (char**) realloc(votos, (*numVotos + 1) * sizeof(char*));

        if (aux == NULL)
        {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }

        votos = aux;
        votos[(*numVotos)++] = voto;
    }

    // Fechar arquivo
    fclose(arquivo);
    return votos;
}