#include "TAD_Lista.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){

    srand(time(NULL));
    Lista *lista;
    Processo *item;
    FILE *teste, *saida;
    int N, Nlo, vezes_insere, vezes_retira, opcao, Qt, Op, nteste1, nteste2, contador;
    char teste_txt[100];
    double tempo_execucao_insercao, tempo_execucao_remocao, tempo_execucao;
    clock_t t1, t2, t;

    printf("PARA ENTRADA PADRAO, DIGITE 0\nPARA ENTRADA COM ARQUIVO, DIGITE 1\n");
    scanf("%d", &opcao);                        //recebe a opção de entrada de dados

    switch (opcao){
        case 0:                             //entrada padrão
        t = clock();                        //pega o tempo inicial

        printf("TAMANHO DO VETOR: ");
        scanf("%d", &N);
        printf("QUANTIDADE DE VEZES QUE A FUNCAO INSERE_ITEM SERA CHAMADA: ");
        scanf("%d", &vezes_insere);
        printf("QUANTIDADE DE VEZES QUE A FUNCAO RETIRA_PRIMEIRO_ITEM SERA CHAMADA: ");
        scanf("%d", &vezes_retira);

        

        incializa_lista(&lista, N);                 //chama a função inicializa e passa os parâmetros 

        for (int i = 0; i< vezes_insere; i++){      //nessa estrutura for, ocorre a inserção dentro do vetor, atraves da chamada 
            cria_processo(&item);                   //das funções e realiza isso o numero de vezes que foi recebido
            insere_lista(&lista, item, N);  
        }
        for (int i = 0; i<vezes_retira; i++){       //nessa estrutura for, ocorre a remoção dentro do vetor, atraves da chamada
            retira_primeiro_item(&lista);           //das funções e realiza isso o numero de vezes que foi recebido
        }

        imprime_vetor(lista);           //imprime o vetor

        t = clock() - t;                    //calcula o tempo gasto
        tempo_execucao = ((double)t)/CLOCKS_PER_SEC;   //divide o tempo gasto para obtê-lo em segundos

        printf("Tempo gasto: %.5fs\n", tempo_execucao);
        break;

        case 1:
        printf("POR FAVOR, DIGITE O NOME DO ARQUIVO QUE DEVE SER LIDO: " );
        scanf("%s",teste_txt);
        
        teste = fopen(teste_txt,"r"); //abrindo o arquivo pra leitura
        if (teste == NULL){
            printf("erro na abertura\n");  //trata o erro pra caso o arquivo esteja vazio
            system ("pause");
            exit(1);
        }

        fscanf(teste,"%d", &N);     //na primeira linha do arquivo fica o tamanho do vetor de cursores

        incializa_lista(&lista, N); //inicia a lista com o vetor de tamanho pedido

        fscanf(teste,"%d", &Nlo);   //na segunda linha fica a quantidade de linhas de operações que terá o arquivo

        for(contador = 0; contador < Nlo; contador++) {     //vamos ler as proximas linhas o numero de vezes que o Nlo deteerminar
            fscanf(teste,"%d %d", &Op, &Qt);    //lemos qual a operação e quantas vezes deve ser executada

            if(Op == 0){                    //se a operação for dada pelo valor 0 vamos inserir Qt vezes (por isso o for)
                t1 = clock();
                for(int i = 0; i<Qt; i++){ 
                    cria_processo(&item);
                    insere_lista(&lista, item, N);
            }
                t1 = clock() - t1;
                tempo_execucao_insercao = ((double)t1)/CLOCKS_PER_SEC;
            }

            if(Op == 1){ //se a operação for dada pelo valor 1 vamos retirar Qt vezes (por isso o for)
                t2 = clock();
                for(int i = 0; i<Qt; i++){
                    retira_primeiro_item(&lista);
                }
                t2 = clock() - t2;
                tempo_execucao_remocao = ((double)t2)/CLOCKS_PER_SEC;
            }
        }

        fscanf(teste, "%d %d", &nteste1, &nteste2);
        
        //arquivo de saida
        saida = fopen("arquivo_de_saida", "a"); //abre arquivo possibilitando a escrita no final. se não houver arquivo o cria.
        fprintf (saida, "%d <%.5fs>\n%d <%.5fs>\n", nteste1, tempo_execucao_insercao, nteste2, tempo_execucao_remocao); //escreve no arquivo
        fclose(teste);
        break;

        default:
        printf("ENTRADA INVÁLIDA");
    }
    
    return 0;
}
