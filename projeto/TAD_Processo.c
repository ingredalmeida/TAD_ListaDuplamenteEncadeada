#include "TAD_Processo.h"

int PIDS[700000];

void set_PID(Processo **item){
    int i = 0;
    int novo_pid = rand()%700000;  //o PID recebe um número aleatório gerado por rand
    while(1){
        if (novo_pid != PIDS[novo_pid]){
            PIDS[novo_pid] = novo_pid;    //verifica se o PID está repetido
            break;
        } 
        novo_pid++;  
    }     
    (*item)->PID = novo_pid;    //o item recebe o PID
}

int get_pid(Processo *item){
    return item->PID;           //retornando o valor do PID
}

void set_prioridade(Processo **item){
    int nova_prioridade = rand_int(1, 5);  //prioridade é gerada atraves de um rand
    (*item)->prioridade = nova_prioridade;      //o item recebe a nova prioridade
}

int get_prioridade(Processo *item){
    return item->prioridade;            //retornando o valor da prioridade
}

/*void set_hora_atual(Processo **item){
    time_t t;
    time(&t);
    strcpy((*item)->hora_atual, ctime(&t));
}

char* get_hora_atual(Processo *item){
    return item->hora_atual;
}*/

int rand_int(int min, int max) {  //função rand que gera numeros aleatorios
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void cria_processo(Processo **item){            //cria o item, e o item recebe os valores retornados pelas funções set's
    (*item) = (Processo*) malloc(sizeof(Processo));
    set_PID(item);
    set_prioridade(item);
}
