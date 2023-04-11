#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "movimento.h"
#include "../coppelia/coppelia.h"
#include "../../dep/include/remoteApi/extApi.h"
#define X 0
#define Y 1
#define Z 2
#define BUFFER 4096
#define PI 3.14159265358979323846
#define FATOR_AJUSTE1 0.025
#define FATOR_AJUSTE2 (5.0 / 180) * PI
#define FATOR_AJUSTE3 (4.5 / 180) * PI

void apertarDigito(int client, int* handleJuntas, char digito)
{
    char pathDigito[BUFFER] = "/TeclaUrna";
    int len = strlen(pathDigito);
    pathDigito[len] = digito;
    pathDigito[len + 1] = '\0';
    int handleDigito = handleObjeto(client, pathDigito);

    char pathExtremidade[BUFFER] = "/NiryoOne/NiryoLGripper/Point";
    int handleExtremidade = handleObjeto(client, pathExtremidade);

    float* posBase = coordenadasObjeto(client, handleJuntas[1]);
    float* posMeio = coordenadasObjeto(client, handleJuntas[2]);
    float* posExtremidade = coordenadasObjeto(client, handleExtremidade);
    float* posDigito = coordenadasObjeto(client, handleDigito);

    float xB = posBase[X], yB = posBase[Y], zB = posBase[Z];
    float xM = posMeio[X], yM = posMeio[Y], zM = posMeio[Z];
    float xE = posExtremidade[X], yE = posExtremidade[Y], zE = posExtremidade[Z];
    float xD = posDigito[X], yD = posDigito[Y], zD = posDigito[Z];

    // Comprimentos dos braços
    float l1 = sqrt(pow(xM - xB, 2) + pow(yM - yB, 2) + pow(zM - zB, 2));
    float l2 = sqrt(pow(xE - xM, 2) + pow(yE - yM, 2) + pow(zE - zM, 2)) + FATOR_AJUSTE1;
    float d = sqrt(pow(xD - xB, 2) + pow(yD - yB, 2) + pow(zD - zB, 2));

    // Rotacionar a base
    float beta = atan((xD - xB) / (yD - yB));
    simxSetJointTargetPosition(client, handleJuntas[0], -beta, simx_opmode_oneshot_wait);

    float phi = atan((zD - zB) / sqrt(pow(xD - xB, 2) + pow(yD - yB, 2)));
    float theta = acos((pow(d, 2) + pow(l1, 2) - pow(l2, 2)) / (2 * d * l1));
    float gamma = acos((pow(d, 2) + pow(l2, 2) - pow(l1, 2)) / (2 * d * l2));

    // Rotacionar braço de comprimento l1
    float alpha1 = PI / 2 - (phi + theta) + FATOR_AJUSTE2;
    simxSetJointTargetPosition(client, handleJuntas[1], -alpha1, simx_opmode_oneshot_wait);

    // Rotacionar braço de comprimento l2
    float alpha2 = PI / 2 - (gamma + theta);
    simxSetJointTargetPosition(client, handleJuntas[2], alpha2, simx_opmode_oneshot_wait);
    extApi_sleepMs(5000);

    // Desrotacionar os braços
    simxSetJointTargetPosition(client, handleJuntas[1], 0, simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(client, handleJuntas[2], 0, simx_opmode_oneshot_wait);
    extApi_sleepMs(2500);
}

void apertarConfirma(int client, int* handleJuntas)
{
    char pathConfirma[BUFFER] = "/TeclaUrnaConfirma";
    int handleConfirma = handleObjeto(client, pathConfirma);

    char pathPonta[BUFFER] = "/NiryoOne/NiryoLGripper/Point";
    int handleExtremidade = handleObjeto(client, pathPonta);

    float* posBase = coordenadasObjeto(client, handleJuntas[1]);
    float* posMeio = coordenadasObjeto(client, handleJuntas[2]);
    float* posExtremidade = coordenadasObjeto(client, handleExtremidade);
    float* posConfirma = coordenadasObjeto(client, handleConfirma);

    float xB = posBase[X], yB = posBase[Y], zB = posBase[Z];
    float xM = posMeio[X], yM = posMeio[Y], zM = posMeio[Z];
    float xE = posExtremidade[X], yE = posExtremidade[Y], zE = posExtremidade[Z];
    float xC = posConfirma[X], yC = posConfirma[Y], zC = posConfirma[Z];

    // Comprimentos dos braços
    float l1 = sqrt(pow(xM - xB, 2) + pow(yM - yB, 2) + pow(zM - zB, 2));
    float l2 = sqrt(pow(xE - xM, 2) + pow(yE - yM, 2) + pow(zE - zM, 2)) + FATOR_AJUSTE1;
    float d = sqrt(pow(xC - xB, 2) + pow(yC - yB, 2) + pow(zC - zB, 2));

    // Rotacionar a base
    float beta = atan((xC - xB) / (yC - yB));
    simxSetJointTargetPosition(client, handleJuntas[0], -beta, simx_opmode_oneshot_wait);

    float phi = atan((zC - zB) / sqrt(pow(xC - xB, 2) + pow(yC - yB, 2)));
    float theta = acos((pow(d, 2) + pow(l1, 2) - pow(l2, 2)) / (2 * d * l1));
    float gamma = acos((pow(d, 2) + pow(l2, 2) - pow(l1, 2)) / (2 * d * l2));

    // Rotacionar braço de comprimento l1
    float alpha1 = PI / 2 - (phi + theta) + FATOR_AJUSTE3;
    simxSetJointTargetPosition(client, handleJuntas[1], -alpha1, simx_opmode_oneshot_wait);

    // Rotacionar braço de comprimento l2
    float alpha2 = PI / 2 - (gamma + theta);
    simxSetJointTargetPosition(client, handleJuntas[2], alpha2, simx_opmode_oneshot_wait);
    extApi_sleepMs(5000);

    // Desrotacionar os braços
    simxSetJointTargetPosition(client, handleJuntas[1], 0, simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(client, handleJuntas[2], 0, simx_opmode_oneshot_wait);
    extApi_sleepMs(2500);
}