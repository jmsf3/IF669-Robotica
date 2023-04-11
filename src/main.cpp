#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "coppelia/coppelia.h"
#include "leitura/leitura.h"
#include "movimento/movimento.h"
#include "../dep/include/remoteApi/extApi.h"
#define BUFFER 4096

int main()
{
    // Conectar com o CoppeliaSim
    int client = clientCoppelia();

    // Carregar vetor dinâmico com os votos
    int numVotos = 0;
    char** votos = lerVotos(&numVotos);

    // Configurar as juntas
    int handleJuntas[3];
    for (int i = 0; i < 3; i++)
    {
        char pathJunta[BUFFER] = "/NiryoOne/Joint";
        int len = strlen(pathJunta);
        pathJunta[len] = '1' + i;
        pathJunta[len + 1] = '\0';
        handleJuntas[i] = handleObjeto(client, pathJunta);
    }
    
    for (int i = 0; i < numVotos; i++) // Iterar sobre os votos
    {
        int numDigitos = strlen(votos[i]);
    
        for (int j = 0; j < numDigitos; j++) // Iterar sobre os dígitos dos votos
        {
            char digito = votos[i][j];
            apertarDigito(client, handleJuntas, digito);
        }

        apertarConfirma(client, handleJuntas);
    }

    // Fechar a conexão com CoppeliaSim 
    simxFinish(client);

    // Liberar memória alocada
    for (int i = 0; i < numVotos; i++)
    {
        // printf("%s\n", votos[i]);
        free(votos[i]);
    }
    free(votos);

    return 0;
}