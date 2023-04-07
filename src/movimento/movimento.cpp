#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "movimento.h"
#include "..\coppelia\coppelia.h"
#include "..\..\dep\include\remoteApi\extApi.h"
#define X 0
#define Y 1
#define Z 2
#define BUFFER 4096
#define PI 3.14159265358979323846

void apertarDigito(int client, int* handleJuntas, char digito)
{
    char pathDigito[BUFFER] = "/TeclaUrna";
    int len = strlen(pathDigito);
    pathDigito[len] = digito;
    pathDigito[len + 1] = '\0';
    int handleDigito = handleObjeto(client, pathDigito);

    char pathPonta[BUFFER] = "/NiryoOne/NiryoLGripper/Point";
    int handlePonta = handleObjeto(client, pathPonta);

    float* coordJunta2 = coordenadasObjeto(client, handleJuntas[1]);
    float* coordJunta3 = coordenadasObjeto(client, handleJuntas[2]);
    float* coordPonta = coordenadasObjeto(client, handlePonta);
    float* coordDigito = coordenadasObjeto(client, handleDigito);

    float x2 = coordJunta2[X], y2 = coordJunta2[Y], z2 = coordJunta2[Z];
    float x3 = coordJunta3[X], y3 = coordJunta3[Y], z3 = coordJunta3[Z];
    float xP = coordPonta[X], yP = coordPonta[Y], zP = coordPonta[Z];
    float xD = coordDigito[X], yD = coordDigito[Y], zD = coordDigito[Z];

    // Comprimentos dos braços
    float fatorCorrecaoL2 = 0.025;
    float l1 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2) + pow(z3 - z2, 2));
    float l2 = sqrt(pow(xP - x3, 2) + pow(yP - y3, 2) + pow(zP - z3, 2)) + fatorCorrecaoL2;
    float d = sqrt(pow(xD - x2, 2) + pow(yD - y2, 2) + pow(zD - z2, 2));

    // Rotacionar a base
    float anguloBase = atan((xD - x2) / (yD - y2));
    simxSetJointTargetPosition(client, handleJuntas[0], -anguloBase, simx_opmode_oneshot_wait);

    float phi = atan((zD - z2) / sqrt(pow(xD - x2, 2) + pow(yD - y2, 2)));
    float theta = acos((pow(d, 2) + pow(l1, 2) - pow(l2, 2)) / (2 * d * l1));
    float gamma = acos((pow(d, 2) + pow(l2, 2) - pow(l1, 2)) / (2 * d * l2));

    // Rotacionar braço de comprimento L1
    float fatorCorrecaoA1 = (5.0 / 180) * PI;
    float anguloL1 = PI / 2 - (phi + theta) + fatorCorrecaoA1;
    simxSetJointTargetPosition(client, handleJuntas[1], -anguloL1, simx_opmode_oneshot_wait);

    // Rotacionar braço de comprimento L2
    float anguloL2 = PI / 2 - (gamma + theta);
    simxSetJointTargetPosition(client, handleJuntas[2], anguloL2, simx_opmode_oneshot_wait);
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
    int handlePonta = handleObjeto(client, pathPonta);

    float* coordJunta2 = coordenadasObjeto(client, handleJuntas[1]);
    float* coordJunta3 = coordenadasObjeto(client, handleJuntas[2]);
    float* coordPonta = coordenadasObjeto(client, handlePonta);
    float* coordConfirma = coordenadasObjeto(client, handleConfirma);

    float x2 = coordJunta2[X], y2 = coordJunta2[Y], z2 = coordJunta2[Z];
    float x3 = coordJunta3[X], y3 = coordJunta3[Y], z3 = coordJunta3[Z];
    float xP = coordPonta[X], yP = coordPonta[Y], zP = coordPonta[Z];
    float xC = coordConfirma[X], yC = coordConfirma[Y], zC = coordConfirma[Z];

    // Comprimentos dos braços
    float fatorCorrecaoL2 = 0.025;
    float l1 = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2) + pow(z3 - z2, 2));
    float l2 = sqrt(pow(xP - x3, 2) + pow(yP - y3, 2) + pow(zP - z3, 2)) + fatorCorrecaoL2;
    float d = sqrt(pow(xC - x2, 2) + pow(yC - y2, 2) + pow(zC - z2, 2));

    // Rotacionar a base
    float anguloBase = atan((xC - x2) / (yC - y2));
    simxSetJointTargetPosition(client, handleJuntas[0], -anguloBase, simx_opmode_oneshot_wait);

    float phi = atan((zC - z2) / sqrt(pow(xC - x2, 2) + pow(yC - y2, 2)));
    float theta = acos((pow(d, 2) + pow(l1, 2) - pow(l2, 2)) / (2 * d * l1));
    float gamma = acos((pow(d, 2) + pow(l2, 2) - pow(l1, 2)) / (2 * d * l2));

    // Rotacionar braço de comprimento L1
    float fatorCorrecaoA1 = (4.5 / 180) * PI;
    float anguloL1 = PI / 2 - (phi + theta) + fatorCorrecaoA1;
    simxSetJointTargetPosition(client, handleJuntas[1], -anguloL1, simx_opmode_oneshot_wait);

    // Rotacionar braço de comprimento L2
    float anguloL2 = PI / 2 - (gamma + theta);
    simxSetJointTargetPosition(client, handleJuntas[2], anguloL2, simx_opmode_oneshot_wait);
    extApi_sleepMs(5000);

    // Desrotacionar os braços
    simxSetJointTargetPosition(client, handleJuntas[1], 0, simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(client, handleJuntas[2], 0, simx_opmode_oneshot_wait);
    extApi_sleepMs(2500);
}