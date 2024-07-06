#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    int main(){

    int matricula[512];
    int invalidade;
    int quant;
    //o usuario ira digirar quantos usuarios serao registrados
    printf("Digite quantos usuarios serao cadastrados (limite 512): \n");

    void pedir_quant(){
    scanf("%d",&quant);
    if(quant<0 || quant>512){
        invalidade=1;
    } else{
        invalidade=0;
    }
    while(invalidade==1){
        printf("quantidade invalida\n");
        pedir_quant();
    }
}
    //chamando a funcao
    pedir_quant();
    //pedindo a matricula de cada usuario
    void pedir_matricula(int x){
    printf("digite sua matricula (usuario %d):\n",x+1);
    scanf("%d",&matricula[x]);
    }
    for(int j=0;j<quant;){
        pedir_matricula(j);
        if(matricula[j] < 10000000 || matricula[j] > 99999999){
            printf("matricula invalida\n");
        } else{
            j++;
        }
        }

    //mostrar tempo atual na tela
    time_t tempo = time(NULL);
    struct tm tm = *localtime(&tempo);
    printf("DATA E HORARIO: %d-%02d-%02d %02d:%02d:%02d\n\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    //tempo de chegada, exemplo: meio dia
    struct tm tempo_limite=*localtime(&tempo);
    tempo_limite.tm_hour = 12; tempo_limite.tm_min = 0; tempo_limite.tm_sec = 0;
    tempo_limite.tm_mon = tm.tm_mon;  tempo_limite.tm_mday = tm.tm_mday;

    //pedir cadastro e verificar atraso
    for(;;){
        int numero_de_cadastro;
        printf("Digite seu cadastro: \n");
        scanf("%d",&numero_de_cadastro);
        int encontrado=0;
        for(int i = 0;i<quant;i++){
            if(numero_de_cadastro==matricula[i]){
                encontrado=1;
                if(difftime(tempo,mktime(&tempo_limite))>0){
                    printf("Voce se atrasou!\n");
                } else{
                    printf("voce chegou dentro do horario\n");
                }
                break;
            }
            }
                if (encontrado==0) {
                    printf("Cadastro invalido\n");
            }
        }
    }
