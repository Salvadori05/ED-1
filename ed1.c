#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[128];
    char numero[32];
} agenda;

void menu(){
    printf("\n1 - Novo Contato\n2 - Ver Contato\n3 - Salvar arquivo\n0 - Sair\n");
    printf("Escolha: ");
}

void novocontato(agenda lista[], int tamanho, int *cont){
    
    if(*cont >= tamanho){
        printf("Limite de contato atingido!\n");
    }else{
        printf("Digite o nome do contato (apenas um nome): ");
        scanf("%127s", lista[*cont].nome);

        printf("Digite o numero do contato: ");
        scanf("%31s", lista[*cont].numero);
        printf("Contato salvo com sucesso!\n");
        (*cont)++;
    }
}

void vercontato(agenda lista[], int cont){
    int n;

    if(cont == 0){
        printf("Ainda nao existe nenhum contato!\n");
        return;
    }

    printf("Qual contato deseja ver? (1 a %d): ", cont);
    scanf("%d", &n);

    if(n <= 0 || n > cont){
        printf("Contato invalido!\n");
        return;
    }

    printf("Nome: %s\n", lista[n-1].nome);
    printf("Numero: %s\n", lista[n-1].numero);
}

void salvar(agenda lista[], int cont){

    FILE *arquivo;

    arquivo = fopen("contatos.csv", "w");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    for(int i = 0; i < cont; i++){
        fprintf(arquivo, "%s %s\n", lista[i].nome, lista[i].numero);
    }

    fclose(arquivo);

    printf("Contatos salvos com sucesso!\n");
}

void abrirarquivo(agenda lista[], int *cont){

    FILE *arquivo;

    arquivo = fopen("contatos.csv", "r");

    if(arquivo == NULL){
        printf("Iniciando um novo arquivo!\n");
        return;
    }

    while(fscanf(arquivo, "%127s %31s",
        lista[*cont].nome,
        lista[*cont].numero) == 2){

        (*cont)++;

        if(*cont >= 100)
            break;
    }

    fclose(arquivo);

    printf("Lista de contatos carregada!\n");
}

int main(){

    int cont = 0;
    agenda lista[100] = {0};
    int op;

    abrirarquivo(lista, &cont);

    do{
        menu();
        scanf("%d", &op);

        switch(op){

            case 1:
                novocontato(lista, 100, &cont);
                break;

            case 2:
                vercontato(lista, cont);
                break;

            case 3:
                salvar(lista, cont);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    }while(op != 0);

}