#include <stdio.h>
#include <stdlib.h>
#include "coppelia.h"
#include "..\..\dep\include\remoteApi\extApi.h"
#define PORT 19999
#define TIME_OUT 2000
#define THREAD_CYCLE 5

int clientCoppelia()
{
    // Conectar com o CoppeliaSim
    int client = simxStart("127.0.0.1", PORT, true, true, TIME_OUT, THREAD_CYCLE);

    // Verificar se a conexão com simulador foi feita com sucesso
    if (client == -1)
    {
        printf("Erro ao concectar com o CoppeliaSim.\n");
        exit(1);
    }
    else
    {
        printf("Conectado com sucesso ao CoppeliaSim.\n");
        return client;
    }
}

int handleObjeto(int client, char path[])
{
    int handle;
    simxGetObjectHandle(client, path, &handle, simx_opmode_oneshot_wait);
    return handle;
}

float* coordenadasObjeto(int client, int handle)
{
    float* coordenadas = (float*) calloc(3, sizeof(float));

    if (coordenadas == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    else
    {
        simxGetObjectPosition(client, handle, -1, coordenadas, simx_opmode_oneshot_wait);
        return coordenadas;
    }
}