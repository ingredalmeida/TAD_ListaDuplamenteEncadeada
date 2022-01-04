#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int PID;  
    int prioridade;
    //char hora_atual[27];
}Processo; 

void set_PID(Processo **item);
int get_pid(Processo *item);

void set_prioridade(Processo **item);
int get_prioridade(Processo *item);

/*void set_hora_atual(Processo **item);
char* get_hora_atual(Processo *item);*/

int rand_int(int min, int max);

void cria_processo(Processo **item);

