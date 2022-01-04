#include "TAD_Lista.h"

void incializa_lista(Lista **lista, int N){
    (*lista) = (Lista*) malloc(sizeof(Lista));                  //setando a lista
    (*lista)->vetor = (Celula**) malloc(N * sizeof(Celula));   //setando o vetor de celulas
    (*lista)->primeiro = -1;                                  //setando a variável prmeiro com -1 pois não aponta pra ninguem ainda
    (*lista)->ultimo = -1;                                   //setando a variável ultimo com -1 pois não aponta pra ninguem ainda
    (*lista)->qtd_celulas_livres = N;                       //setando qtd_cels_livres com N pois nenhuma ainda foi preenchida
    (*lista)->primeira_celula_livre = 0;                   //setando a primeira cel livre com 0 pois é a primeira posição do vetor
    celulas_livres((*lista)->vetor, N);
}



void celulas_livres(Celula **vetor, int N){
    for(int i=0; i<N; i++){
        vetor[i] = (Celula*) malloc(sizeof(Celula));            //armazena memoria no heap pra essa celula     
        (vetor)[i]->ante = i - 1;                              //setando o ante
        (vetor)[i]->prox = i + 1;                             //setando o prox
        if(i == N -1){
            vetor[i]->prox = -1;                             //setando prox da ultima celula
        }
    }
}



void insere_lista(Lista **lista, Processo *item, int N){
    Celula* aux;
    if((*lista) == NULL){
        incializa_lista(lista, N);                                  //realizando a chamada da função incializa para cada ela esteja NULL
    }
    if((*lista)->qtd_celulas_livres == 0){                          //verifica se a lista está cheia, se sim retorna um erro e sai da função
       printf("\nERRO AO INSERIR: TODAS AS POSIÇÕES DA LISTA ESTÃO OCUPADAS\n");
       return;
    }

    int j = (*lista)->primeira_celula_livre;                       //incializando j com o valor do indice que a primeira cel livre aponta              
    
    (*lista)->vetor[j]->item = item;                               //vetor[j] ou vetor[0] está sendo preenchido com o primeiro item vindo de processo.h
    (*lista)->primeira_celula_livre = (*lista)->vetor[j]->prox;   //agora a primeira cel livre aponta para o prox do vetor[j]
    
    int qtd_celulas_ocupadas = 0;                                   //incializando a var qtd cel ocupadas                   
    qtd_celulas_ocupadas =  N - (*lista)->qtd_celulas_livres;       //a qtd cel ocupadas é a diferença do tam do vetor - cels livres

    if((*lista)->qtd_celulas_livres == N){                      //verificando se a lista esta vazia
        (*lista)->qtd_celulas_livres--;                         //ao inserir item primeiramente, preciso retirar -1 das cels livres
        (*lista)->primeiro = j;                                 //agora como temos um item em vetor, o primeiro aponta pra ele
        (*lista)->ultimo = j;                                   //agora como temos um item em vetor, o ultimo aponta pra ele
        (*lista)->vetor[j]->ante = -1;                          //agora como temos um item em vetor, o seu ante é -1 pois so temos ele ainda
        (*lista)->vetor[j]->prox = -1;                          //agora como temos um item em vetor, o seu prox é -1 pois so temos ele ainda
        return;
    }

    int x = (*lista)->ultimo;           //começaremos a iterar do ultimo, para pegarmos o indice do ultimo (ultimo é o maior PID)
    int z = (*lista)->primeiro;        //var necessaria para caso o novo inserido seja menor que o primeiro           
    do{
        aux = (*lista)->vetor[x];
        if((*lista)->vetor[x]->item->PID > (*lista)->vetor[j]->item->PID){      //comparamos os PID
            x = (*lista)->vetor[x]->ante;                                       //se menor, x assume o indice do anterior do vetor[x] 

            if(x == -1){                                //olhando se o novo inserido é menor que o primeiro, se sim o novo inserido tera a var primeiro apontando pra ele
                (*lista)->primeiro = j;                //primeiro apontando para j
                (*lista)->vetor[j]->ante = -1;         //anterior do novo inserido aponta para -1 pois é o primeiro
                (*lista)->vetor[j]->prox = z;         //proximo do novo inserido aponta para z
                (*lista)->vetor[z]->ante = j;        //anterior do vetor[z] recebe j como ante
                break;
            } 
        }
        else{
            int ultimo = (*lista)->ultimo;
            if((*lista)->vetor[j]->item->PID > (*lista)->vetor[ultimo]->item->PID){     //olhando se o novo inserido é maior que o ultimo, se sim o novo inserido tera a var ultimo apontando pra ele
                (*lista)->ultimo = j;                                                //ultimo apontando para j
                (*lista)->vetor[j]->ante = ultimo;                                   //anterior do novo inserido aponta para x
                (*lista)->vetor[j]->prox = -1;                                      //proximo do novo inserido aponta para -1 pois é o ultimo  
                (*lista)->vetor[ultimo]->prox = j;                                 //proximo de vetor[x] recebe o prox como j
                break;
            }  
            else{
                int aux_prox, aux_ante;                             
                aux_prox = (*lista)->vetor[x]->prox;               //o prox do inserido é agora o prox do que estava na lista
                if (aux_prox == -1){                            
                    (*lista)->vetor[j]->ante = -1;                  //se o prox for -1, o anterio do inserido recebe -1
                    (*lista)->vetor[j]->prox = x;                   //e o seu proximo recebe o numero que estava comparando
                    (*lista)->primeiro = j;                         //o inserido é agora o primeiro
                    (*lista)->vetor[x]->ante = j;                  //e o anterior do que estavamos olhando, é o inserido 
                }else{
                    aux_ante = (*lista)->vetor[aux_prox]->ante;        //a var aux_ante recebe o valor do anterio do que estavamos olhando
                    (*lista)->vetor[x]->prox = j;                      //o proximo do que estavamos olhando é o inserido
                    (*lista)->vetor[aux_prox]->ante = j;             //o anterior do prox do que estavamos olhando agora é o inserido
                    (*lista)->vetor[j]->prox = aux_prox;            //setando o proximo do inserido
                    (*lista)->vetor[j]->ante = aux_ante;            //setando o anterior do inserido
                }
                break;
            }
        }
    }while((*lista)->vetor[j]->ante != -1);

    (*lista)->qtd_celulas_livres -= 1;                      //retira uma posição das celulas livres
}



void retira_primeiro_item(Lista **lista){
    Celula* aux;
    int aux_prox, aux_primeiro, vazia_prox;
    aux_primeiro = (*lista)->primeiro;                      //pegando o indice da posição que quero remover
    aux_prox = (*lista)->vetor[aux_primeiro]->prox;         //pegando o proximo do que estou removendo para torná-lo o primeiro
   
    if ((*lista)->primeiro == (*lista)->ultimo){
        (*lista)->ultimo = -1;                          //caso todos os itens sejam removidos ou tenha apenas um item, o primeiro e o ultimo apontam pra -1
        (*lista)->primeiro = -1;
    }
    else{
        (*lista)->primeiro = aux_prox;                       //primeiro recebe vetor[aux_prox]
        (*lista)->vetor[aux_prox]->ante = -1;                  //anterior do novo primeiro recebe -1
    }
    
    vazia_prox = (*lista)->primeira_celula_livre;              //vazia_prox recebe o valor de primeira cel livre
    (*lista)->primeira_celula_livre = aux_primeiro;           //primeira cel livre agora recebe aux_primeiro

    if((*lista)->qtd_celulas_livres ==  0){                 //se não houver celulas livres, a "primeira celula livre" 
        (*lista)->vetor[aux_primeiro]->prox = -1;           //recebe -1 para não apontar para nenhuma célula, já que todas estão ocupadas
        (*lista)->vetor[aux_primeiro]->ante = -1;           //recebe -1 para não apontar para nenhuma célula, já que todas estão ocupadas
    }else{
        (*lista)->vetor[aux_primeiro]->prox = vazia_prox;        //e a prox da nova primeira cel é agora o indice da antiga primeira cel
        (*lista)->vetor[vazia_prox]->ante = aux_primeiro;         //a celula que era a primeira livre agora tem seu ante apontando para a nova primeira livre
    }
    (*lista)->qtd_celulas_livres++;
}
   


void imprime_vetor(Lista *lista){
    if (lista->primeiro == lista->ultimo){
        return;                             //verifica se está vazio
    }
    Celula** vetor = lista->vetor;      //incializa o vetor
    int i = lista->primeiro;           //var i recebe o valor de primeiro
    do{            
        printf("PID: %d Prioridade: %d\n", vetor[i]->item->PID, vetor[i]->item->prioridade);
        i = vetor[i]->prox;              //a var i recebe o valor do proximo do PID que foi printado
    } while(vetor[i]->prox != -1);
    printf("PID: %d Prioridade: %d\n", vetor[i]->item->PID, vetor[lista->ultimo]->item->prioridade); //printa o ultimo da lista, já que como seu proximo é -1, não entra na estrutura do while acima

}   