//
// Created by unifgmorassi on 20/09/2023.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "biblioteca.h"

// Função para ler tarefas de um arquivo e carregá-las em uma lista
void limpa(){
    //função para arrumar o bug de pular um scanf
    //ela vai limpar o buffer e arrumar o erro
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
void lerTarefas(struct tarefa lista[], int *quantidadeDeTarefas) {
    FILE *arquivo = fopen("tarefas", "rb");//ele abre o arquivo como ler binario
    if (arquivo) {//se obter sucesso ele vai ler com o fread e armazenara no arquivo aberto
        //as informaçoes ficarão na lista q foi passada como parametro
        while (fread(&lista[*quantidadeDeTarefas], sizeof(struct tarefa), 1, arquivo) == 1) {
            (*quantidadeDeTarefas)++;//ele vai ler de 1 em 1 até o fim do arquivo, a cada leitura ele soma 1 na quantidade de tarefas
            //para manter o controle de tarefas
        }
        fclose(arquivo);//ele fecha o arquivo
    }
}

// Função para salvar tarefas de uma lista em um arquivo
void salvarTarefas(struct tarefa lista[], int quantidadeDeTarefas) {
    FILE *arquivo = fopen("tarefas", "wb");//abre o arquivo como write em binario

    if (arquivo) {//se ele obter sucesso
        //ele escreve tudo da lista de structs no arquivo q foi aberta
        fwrite(lista, sizeof(struct tarefa), quantidadeDeTarefas, arquivo);
        fclose(arquivo);//fecha o arquivo
    }
}

// Função para deletar uma tarefa da lista
void deletarTarefa(struct tarefa lista[], int *quantidadeDeTarefas, int pos) {
    for (int i = pos; i < (*quantidadeDeTarefas) - 1; i++) {
        lista[i] = lista[i + 1];//ele vai pegar a tarefa do próximo indice e colocar no atual
        //começando da posição inicial digitada
    }
    (*quantidadeDeTarefas)--;//ele diminui a quantidade de tarefas em 1 para q tenhamos o controle
}

// Função para listar as tarefas na lista
void listarTarefas(struct tarefa lista[], int quantidadeDeTarefas) {
    while(1){
        printf("Selecione como deseja printar suas tarefas!\n");
        printf("1.Listar por ordem de adição! \n");
        printf("2.Listar por categoria!\n");
        printf("3.Listar por prioridade!\n");
        printf("4.Listar por estado!\n");
        printf("5.Listar por prioridade e categoria!\n");
        printf("0.Sair do menu de listar  \n");
        int escolha;
        scanf("%d",&escolha);
        limpa();
        if(escolha ==1) {
            int encontrado =0;
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                printf("Tarefa de Numero: %d \n", x);
                printf("Prioridade: %d\n", lista[x].prioridade);
                printf("Descrição: %s", lista[x].desc);
                printf("Estado: %d\n", lista[x].estado);

                printf("Categoria: %s\n", lista[x].categoria);
                printf("\n");
                encontrado =1;
            }
            if(encontrado ==0){
                printf("Nenhuma tarefa encontrada!\n");
            }
        }
        if(escolha == 2){
            char categoria[100];
            scanf("%100[^\n]s", &categoria);
            limpa();
            int encontrado =0;

            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                printf("%d\n",strcmp(lista[x].categoria,categoria));
                if(strcmp(lista[x].categoria,categoria)==0) {


                    printf("Tarefa de Numero: %d \n", x);
                    printf("Prioridade: %d\n", lista[x].prioridade);
                    printf("Descrição: %s\n", lista[x].desc);
                    printf("Estado: %d\n", lista[x].estado);
                    printf("Categoria: %s\n", lista[x].categoria);
                    printf("\n");
                    encontrado =1;
                }
            }
            if(encontrado ==0){
                printf("Nenhuma tarefa encontrada!\n");
            }

        }
        if(escolha == 3){
            int priority;
            int encontrado =0;
            printf("Digite a prioridade a ser buscada: \n");
            scanf("%d",&priority);
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                if(priority==lista[x].prioridade) {
                    printf("Tarefa de Numero: %d \n", x);
                    printf("Prioridade: %d\n", lista[x].prioridade);
                    printf("Descrição: %s\n", lista[x].desc);
                    printf("Estado: %d\n", lista[x].estado);
                    printf("Categoria: %s\n", lista[x].categoria);
                    printf("\n");
                    encontrado =1;
                }
            }
            if(encontrado ==0){
                printf("Nenhuma tarefa encontrada!\n");
            }
        }
        if(escolha == 4){
            int estate;
            int encontrado =0;
            printf("Digite quais estados vão aparecer:\n");
            printf("0.Não realizado!\n");
            printf("1.Em andamento!\n");
            printf("2.Finalizado!\n");
            scanf("%d",&estate);
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                if(estate==lista[x].estado) {
                    printf("Tarefa de Numero: %d \n", x);
                    printf("Prioridade: %d\n", lista[x].prioridade);
                    printf("Descrição: %s\n", lista[x].desc);
                    printf("Estado: %d\n", lista[x].estado);
                    printf("Categoria: %s\n", lista[x].categoria);
                    printf("\n");
                    encontrado =1;
                }
            }
            if(encontrado == 0){
                printf("Nenhuma tarefa encontrada!\n");
            }
        }
        if(escolha == 0){
            printf("Saindo do menu!!\n");
            break;
        }
    }

}

// Função para criar uma nova tarefa e adicioná-la à lista
void criarNovaTarefa(struct tarefa lista[], int *quantidadeDeTarefas, int tamanhoMaximo) {
    if (*quantidadeDeTarefas < tamanhoMaximo) {
        struct tarefa nova;//cria uma struct vazia
        //agora daqui para baixo ele vai printar e recolher as informações
        printf("Prioridade: ");
        scanf("%d", &nova.prioridade);
        limpa();
        printf("Descrição: ");
        scanf("%300[^\n]s", &nova.desc);
        limpa();
        printf("Estado: ");
        printf("0.Não realizado!\n");
        printf("1.Em andamento!\n");
        printf("2.Finalizado!\n");
        scanf("%d",&nova.estado);
        limpa();
        printf("Categoria: ");
        scanf("%100[^\n]s", &nova.categoria);

        lista[*quantidadeDeTarefas] = nova;//declara a posição com a struct preechida
        (*quantidadeDeTarefas)++;//soma 1 na variavel q esta controlando a quantia de tarefas
    } else {
        printf("A lista de tarefas está cheia.\n");//ele vai printar isto quando a quantidade de tarefas for maior que 100
    }
}

#include "biblioteca.h" // Inclui novamente o cabeçalho