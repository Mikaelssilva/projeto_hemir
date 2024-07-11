#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#define MAX_USUARIOS 1000

    struct usuario{
        char nome[100];
        int senha;
    };
    //
    struct usuario usuarios[1000];
    //
    void pedir_usuario(int x){
    printf("Digite seu nome (usuário %d): ",x+1);
    scanf("%s",usuarios[x].nome);
    printf("Digite sua senha (usuário %d): ",x+1);
    scanf("%d",&usuarios[x].senha);
    }
    //
    int count_estagiario=0;


int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    FILE *pArquivo_horario;
    FILE *pArquivo_usuarios;
    printf("*******************************************************************************\n");
    printf("****                                                                       ****\n");
    printf("****            PROJETO PONTO ELETRÔNICO PARA ESTAGIÁRIOS                  ****\n");
    printf("****                     PROF: HEMIR SANTIAGO                              ****\n");
    printf("****                                                                       ****\n");
    printf("****                                                                       ****\n");
    printf("*******************************************************************************\n\n");
    for(;;){
    int opcao;
    printf("PONTO ELETRÔNICO -- MENU PRINCIPAL:\n");
    printf("1. Registrar Usuário\n");
    printf("2. Registrar Horário\n");
    printf("3. Sair\n");
    scanf("%d",&opcao);
    //
    pArquivo_usuarios = fopen("Usuários registrados.txt","a");
    pArquivo_horario = fopen("Horário de entrada.txt","a");
    //
    switch(opcao){
    case 1:
    //
    pedir_usuario(count_estagiario);
    //
    if(usuarios[count_estagiario].senha < 10000000 || usuarios[count_estagiario].senha > 99999999){
            printf("A senha deverá conter 8 dígitos\n");
            pedir_usuario(count_estagiario);
    } else{
            fprintf(pArquivo_usuarios,"%s\n",usuarios[count_estagiario].nome);
            count_estagiario++;
    }
    break;
    //
    case 2:
    //
    if(usuarios[0].senha != NULL){
    time_t tempo = time(NULL);
    struct tm tm = *localtime(&tempo);
    printf("DATA E HORÁRIO: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    //
    struct tm tempo_limite=*localtime(&tempo);
    tempo_limite.tm_hour = 12; tempo_limite.tm_min = 0; tempo_limite.tm_sec = 0;
    tempo_limite.tm_mon = tm.tm_mon;  tempo_limite.tm_mday = tm.tm_mday;
    double atraso = difftime(tempo,mktime(&tempo_limite));
    //
    int encontrado=0;
    char nome_foo[100];
    int senha_foo;
    printf("Digite seu nome: ");
    scanf("%s",nome_foo);
    printf("Digite sua senha: ");
    scanf("%d",&senha_foo);
    //
    for(int i = 0; i < count_estagiario; i++){
    if (strcmp(nome_foo, usuarios[i].nome) == 0 && senha_foo == usuarios[i].senha){
        encontrado=1;
        if(atraso>0){
            time_t atraso_time_t = (time_t)atraso;
            struct tm *atraso_tm = gmtime(&atraso_time_t);
            //
            char tempo_de_chegada[100];
            char tempo_atraso_str[100];
            //
            strftime(tempo_de_chegada,sizeof(tempo_de_chegada),"%Y-%m-%d %H:%M:%S",&tm);
            strftime(tempo_atraso_str,sizeof(tempo_atraso_str),"%H:%M:%S",atraso_tm);
            //
            printf("Voce se atrasou %d horas %d minutos e %d segundos\n",atraso_tm->tm_hour, atraso_tm->tm_min, atraso_tm->tm_sec);
            fprintf(pArquivo_horario,"Tempo de entrada de %s: %s com um atraso de %s\n",usuarios[i].nome,tempo_de_chegada,tempo_atraso_str);
        } else{
            printf("Voce chegou dentro do horario\n");
            char tempo_de_chegada[100];
            strftime(tempo_de_chegada,sizeof(tempo_de_chegada),"%Y-%m-%d %H:%M:%S",&tm);
            fprintf(pArquivo_horario,"Tempo de entrada de %s: %s sem atraso\n",usuarios[i].nome,tempo_de_chegada);
        }
        break;
    }
    }
        if (encontrado == 0){
            printf("Nome ou senha incorretos\n");
    }
    fclose(pArquivo_horario);
    fclose(pArquivo_usuarios);
    //
    } else{
        printf("Nenhum usuário registrado\n");
    }
    break;
    case 3:
    exit(0);
    break;
    default:
    printf("%d não é uma opção válida\n",opcao);
    }
    }
}
