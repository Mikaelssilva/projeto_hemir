#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    int main(){
    //Uma quandidade quant de matriculas sera armazedada no vetor matricula[512]
    FILE *pArquivo;
    int matricula[512];
    int quant;
    //Quantidade de usuarios que serao registrados
    void pedir_quant(){
    int invalidade;
    printf("Digite quantos usuarios serao cadastrados (limite 512): \n");
    scanf("%d",&quant);
    if(quant<0 || quant>512){
        invalidade=1;
    } else{
        invalidade=0;
    }
    while(invalidade==1){
        printf("Quantidade invalida\n");
        pedir_quant();
    }
    }
    //Chamando a funcao
    pedir_quant();
    //Definindo a funcao de realizar cadastro
    void pedir_matricula(int x){
    printf("Digite sua matricula (usuario %d):\n",x+1);
    scanf("%d",&matricula[x]);
    }
    //Registrando matricula de cada usuario
    for(int j=0;j<quant;){
        pedir_matricula(j);
        if(matricula[j] < 10000000 || matricula[j] > 99999999){
            printf("A matricula devera conter 8 digitos\n");
        } else{
            j++;
        }
        }

    //pedir cadastro e verificar atraso
    for(;;){
        //Mostrar tempo atual na tela
        time_t tempo = time(NULL);
        struct tm tm = *localtime(&tempo);
        printf("DATA E HORARIO: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        //Pedir cadastro
        int numero_de_cadastro;
        int encontrado=0;
        printf("Digite seu cadastro: \n");
        scanf("%d",&numero_de_cadastro);
        //Tempo limite
        struct tm tempo_limite=*localtime(&tempo);
        tempo_limite.tm_hour = 12; tempo_limite.tm_min = 0; tempo_limite.tm_sec = 0;
        tempo_limite.tm_mon = tm.tm_mon;  tempo_limite.tm_mday = tm.tm_mday;
        double atraso = difftime(tempo,mktime(&tempo_limite));
        //Verificando se o cadastro existe e calculando o atraso
        for(int i = 0;i<quant;i++){
            pArquivo = fopen("Horario de entrada.txt","a");
            if(numero_de_cadastro==matricula[i]){
                encontrado=1;
                if(atraso>0){
                    time_t atraso_time_t = (time_t)atraso;
                    struct tm *atraso_tm = gmtime(&atraso_time_t);
                    char tempo_de_chegada[100];
                    char tempo_atraso_str[100];
                    strftime(tempo_de_chegada,sizeof(tempo_de_chegada),"%Y-%m-%d %H:%M:%S",&tm);
                    strftime(tempo_atraso_str,sizeof(tempo_atraso_str),"%H:%M:%S",atraso_tm);
                    printf("Voce se atrasou %d horas %d minutos e %d segundos\n",atraso_tm->tm_hour, atraso_tm->tm_min, atraso_tm->tm_sec);
                    fprintf(pArquivo,"Tempo de entrada da matricula %d: %s com um atraso de %s\n",matricula[i],tempo_de_chegada,tempo_atraso_str);
                } else{
                    printf("Voce chegou dentro do horario\n");
                    char tempo_de_chegada[100];
                    strftime(tempo_de_chegada,sizeof(tempo_de_chegada),"%Y-%m-%d %H:%M:%S",&tm);
                    fprintf(pArquivo,"Tempo de entrada da matricula %d: %s sem atraso\n",matricula[i],tempo_de_chegada);
                }
                break;
            }
            }
                if (encontrado==0) {
                    printf("Cadastro invalido\n");
            }
        fclose(pArquivo);
        }
    }
