#include <stdio.h>
#include <stdlib.h>
#include <time.h>

    int main(){

    struct cadastro {
    int cadastro;
};

    struct cadastro cadastro1;
    cadastro1.cadastro = 12345678;

    struct cadastro cadastro2;
    cadastro2.cadastro = 23456789;

    struct cadastro cadastro3;
    cadastro3.cadastro = 34567890;

    struct cadastro cadastro4;
    cadastro4.cadastro = 45678901;

    struct cadastro cadastro5;
    cadastro5.cadastro = 56789012;

    struct cadastro cadastro6;
    cadastro6.cadastro = 67890123;

    struct cadastro cadastro7;
    cadastro7.cadastro = 78901234;

    struct cadastro cadastro8;
    cadastro8.cadastro = 89012345;

    struct cadastro cadastro9;
    cadastro9.cadastro = 90123456;

    struct cadastro cadastro10;
    cadastro10.cadastro = 12345679;

    struct cadastro cadastro11;
    cadastro11.cadastro = 23456780;

    struct cadastro cadastro12;
    cadastro12.cadastro = 34567891;

    struct cadastro cadastro13;
    cadastro13.cadastro = 45678902;

    struct cadastro cadastro14;
    cadastro14.cadastro = 56789013;

    struct cadastro cadastro15;
    cadastro15.cadastro = 67890124;

    struct cadastro cadastro16;
    cadastro16.cadastro = 78901235;

    struct cadastro cadastro17;
    cadastro17.cadastro = 89012346;

    struct cadastro cadastro18;
    cadastro18.cadastro = 90123457;

    struct cadastro cadastro19;
    cadastro19.cadastro = 12345680;

    struct cadastro cadastro20;
    cadastro20.cadastro = 23456791;

    //vetor contendo os cadastros
    int cadastros[512] = {
    12345678, 23456789, 34567890, 45678901, 56789012,
    67890123, 78901234, 89012345, 90123456, 12345679,
    23456780, 34567891, 45678902, 56789013, 67890124,
    78901235, 89012346, 90123457, 12345680, 23456791
};

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
        int len = sizeof(cadastros);
        printf("Digite seu cadastro: \n");
        scanf("%d",&numero_de_cadastro);
        for(int i = 0;i<len;i++){
            if(numero_de_cadastro==cadastros[i]){
                if(difftime(tempo,mktime(&tempo_limite))>0){
                    printf("Voce se atrasou!\n");
                } else{
                    printf("voce chegou dentro do horario\n");
                }
                break;
            } else{
                printf("cadastro invalido\n");
                break;
            }
        }
    }
    }
