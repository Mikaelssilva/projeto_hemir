
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>

// número máximo de estagiários
# define MAX_ESTAGIARIOS 10

// struct para informações dos funcionários
typedef struct{
    char nome[60];
    int identificacao;
    time_t checkin;
    time_t break_saida;
    time_t break_volta;
    time_t checkout;
} informacao;

    // contador para estagiário e vetor struct
    int cont_estagiario = 0;
    informacao estagiarios[MAX_ESTAGIARIOS];


    // função para adicionar funcionários
void add_estagiario(int id, const char *name){
    if(cont_estagiario < MAX_ESTAGIARIOS){
        estagiarios[cont_estagiario].identificacao = id;
        strcpy(estagiarios[cont_estagiario].nome, name);
        cont_estagiario += 1;
    }
    else
        printf("Número máximo de registros atingido.");
}

void exibir_estagiario(){
    if(cont_estagiario == 0)
        printf("Nenhum estagiário foi registrado.\n");
        
    else
        for(int i = 0; i < cont_estagiario; i++)
        printf("Id: %d; Nome: %s.\n", estagiarios[i].identificacao, estagiarios[i].nome);
}
// função hora de entrada
/*void checkin(){

}

// função hora de saída
void checkout(){

}

// intervalo saída
void breaksaida(){

}

// intervalo volta
void breakvolta(){

}*/
int main(){

    //loop infinito
    while(1){
    int id;
    char nome[60];
    int opcao;
    printf("Menu: \n[0] Cadastrar.\n[1] Registrar horário.\n[2] Exibir estagiários.\n[3] Sair.\n");
    scanf("%d", &opcao);
    
    switch(opcao){
        case 0:
            printf("Digite o Id do funcionário: ");
            scanf("%d", &id);
            printf("Digite o nome do funcionário: ");
            scanf("%s", nome);
            add_estagiario(id, nome);
            break;
        case 1:
            printf("A definir...\n");
            break;
        case 2:
            exibir_estagiario();
            break;
        case 3:
            return 0;
    }
    }
    return 0;
}
