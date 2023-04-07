#ifndef _COPPELIA_H 
#define _COPPELIA_H

int clientCoppelia();
int handleObjeto(int client, char path[]);
float* coordenadasObjeto(int client, int handle);

#endif