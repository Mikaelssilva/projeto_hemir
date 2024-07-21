#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define MAX_USUARIOS 51

int count_estagiario = 0;

struct usuario{
    char nome[100];
    char senha[100];
};

struct usuario usuarios[MAX_USUARIOS];

void pedir_usuario(int x){
    char usuario_x[100];
    char senha_x[100];
    int validade = 0;
    printf("Digite seu nome (usuario %d): ", x + 1);
    fflush(stdin);
    fgets(usuario_x, 100, stdin);
    usuario_x[strcspn(usuario_x, "\n")] = 0;
    for(int i = 0;i<strlen(usuario_x);i++){
        usuario_x[i] = toupper(usuario_x[i]);
    }
    strcpy(usuarios[x].nome,usuario_x);
    while(validade == 0){
    printf("Digite sua senha (usuario %d): ", x + 1);
    fgets(senha_x, 100, stdin);
    senha_x[strcspn(senha_x, "\n")] = 0;
    if(strlen(senha_x) != 8){
        puts("Senha devera conter 8 digitos");
        validade = 0;
    } else{
        strcpy(usuarios[x].senha,senha_x);
        count_estagiario++;
        validade = 1;
        }
    }
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    FILE *pArquivo_horario;
    FILE *pArquivo_usuarios;
    puts("***************************************************************************");
    puts("**            PROJETO PONTO ELETRONICO PARA ESTAGIARIOS                  **");
    puts("**                     PROF: HEMIR SANTIAGO                              **");
    puts("**                                                                       **");
    puts("***************************************************************************");

    strcpy(usuarios[50].nome,"admin");
    strcpy(usuarios[50].senha,"12345678");

    pArquivo_usuarios = fopen("Usuarios_registrados.txt", "r");
    int count = 0;

    while(fgets(usuarios[count].nome,100,pArquivo_usuarios) != NULL){
        usuarios[count].nome[strcspn(usuarios[count].nome, "\n")] = 0;
            if(fgets(usuarios[count].senha,100,pArquivo_usuarios) != NULL){
                usuarios[count].senha[strcspn(usuarios[count].senha, "\n")] = 0;
                count++;
                count_estagiario++;
        }
    }
    fclose(pArquivo_usuarios);

    for (;;) {
        char opcao;
        printf("PONTO ELETRONICO -- MENU PRINCIPAL:\n");
        printf("1. Registrar Usuario\n");
        printf("2. Registrar Horario\n");
        printf("3. Sair\n");
        scanf(" %c", &opcao);

        pArquivo_horario = fopen("Horario_de_entrada.txt", "a");

        switch (opcao) {
            case '1':
                pArquivo_usuarios = fopen("Usuarios_registrados.txt", "a");
                char nome_adm[100];
                char senha_adm[100];
                printf("Digite o login de adm: ");
                fflush(stdin);
                fgets(nome_adm, 100, stdin);
                nome_adm[strcspn(nome_adm, "\n")] = 0;
                printf("Digite a senha de adm: ");
                fgets(senha_adm, 100, stdin);
                senha_adm[strcspn(senha_adm, "\n")] = 0;
                if(strcmp(nome_adm, usuarios[50].nome) == 0 && strcmp(senha_adm,usuarios[50].senha) == 0){
                    pedir_usuario(count_estagiario);
                    fprintf(pArquivo_usuarios,"%s\n%s\n",usuarios[count_estagiario-1].nome,usuarios[count_estagiario-1].senha);
                } else{
                    puts("login ou senha de adm errado");
                }
                fclose(pArquivo_usuarios);
                break;
            case '2':
                if (strcmp(usuarios[0].senha,"\0") != 0) {
                    time_t tempo = time(NULL);
                    struct tm tm = *localtime(&tempo);
                    printf("DATA E HORARIO: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

                    struct tm tempo_limite = *localtime(&tempo);
                    tempo_limite.tm_hour = 12; tempo_limite.tm_min = 0; tempo_limite.tm_sec = 0;
                    tempo_limite.tm_mon = tm.tm_mon; tempo_limite.tm_mday = tm.tm_mday;
                    double atraso = difftime(tempo, mktime(&tempo_limite));

                    int encontrado = 0;
                    char nome_input[100];
                    char senha_input[100];
                    printf("Digite seu nome: ");
                    fflush(stdin);
                    fgets(nome_input, 100, stdin);
                    nome_input[strcspn(nome_input, "\n")] = 0;
                    for(int i = 0;i<strlen(nome_input);i++){
                    nome_input[i] = toupper(nome_input[i]);
                    }
                    printf("Digite sua senha: ");
                    fgets(senha_input, 100, stdin);
                    senha_input[strcspn(senha_input, "\n")] = 0;
                    for (int i = 0; i < count_estagiario; i++) {
                        if (strcmp(nome_input, usuarios[i].nome) == 0 && strcmp(senha_input,usuarios[i].senha) == 0) {
                            encontrado = 1;
                            if (atraso > 0) {
                                time_t atraso_time_t = (time_t) atraso;
                                struct tm *atraso_tm = gmtime(&atraso_time_t);

                                char tempo_de_chegada[100];
                                char tempo_atraso_str[100];

                                strftime(tempo_de_chegada, sizeof(tempo_de_chegada), "%Y-%m-%d %H:%M:%S", &tm);
                                strftime(tempo_atraso_str, sizeof(tempo_atraso_str), "%H:%M:%S", atraso_tm);

                                printf("Voce se atrasou %d horas %d minutos e %d segundos\n", atraso_tm->tm_hour, atraso_tm->tm_min, atraso_tm->tm_sec);
                                fprintf(pArquivo_horario, "Tempo de entrada de %s: %s com um atraso de %s\n", usuarios[i].nome, tempo_de_chegada, tempo_atraso_str);
                            } else {
                                printf("Voce chegou dentro do horario\n");
                                char tempo_de_chegada[100];
                                strftime(tempo_de_chegada, sizeof(tempo_de_chegada), "%Y-%m-%d %H:%M:%S", &tm);
                                fprintf(pArquivo_horario, "Tempo de entrada de %s: %s sem atraso\n", usuarios[i].nome, tempo_de_chegada);
                            }
                            break;
                        }
                    }
                    if (encontrado == 0) {
                        printf("Nome ou senha incorretos\n");
                    }
                    fclose(pArquivo_horario);
                    fclose(pArquivo_usuarios);

                } else {
                    printf("Nenhum usuario registrado\n");
                }
                break;
            case '3':
                exit(0);
                break;
            default:
                puts("Opcao invalida");
        }
    }
}
