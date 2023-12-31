#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "biblioteca.h" // Inclui o cabeçalho que declara as funções
int main() {
    int quantidadeDeTarefas = 0; // Variável para rastrear a quantidade de tarefas
    struct tarefa lista[100]; // Array para armazenar as tarefas
    int tamanhoMaximo = 100; // Tamanho máximo da lista

    // Chama a função para ler as tarefas do arquivo
    lerTarefas(lista, &quantidadeDeTarefas);

    while (true) {//aqui é o menu, que é um laço infinito até ele digitar o 4

        printf("Seja bem-vindo às suas Tarefas!!\n");
        printf("1 Criar nova tarefa.\n");
        printf("2 Listar tarefas.\n");
        printf("3 Deletar tarefas.\n");
        printf("4 Criar arquivo de texto.\n");
        printf("5 Alterar tarefas.\n");
        printf("6 Sair e salvar.\n");
        int escolha;
        scanf("%d", &escolha); // Lê a escolha do usuário
        limpa();
        switch (escolha) {
            case 1:
                // Chama a função para criar uma nova tarefa
                criarNovaTarefa(lista, &quantidadeDeTarefas, tamanhoMaximo);
                break;
            case 2:
                // Chama a função para listar as tarefas
                listarTarefas(lista, quantidadeDeTarefas);
                break;
            case 3:
                //Chama a função para deletar tarefa
                deletarTarefa(lista, &quantidadeDeTarefas);
                break;
            case 4:
                //Chama a função de exportar as tarefas por filtros
                arquivotxt(lista,quantidadeDeTarefas);
                break;
            case 5:
                //Chama a função de alterar as tarefas
                alterarTarefas(lista, quantidadeDeTarefas);
                break;
            case 6:
                // Chama a função para salvar as tarefas no arquivo e sai do programa
                salvarTarefas(lista, quantidadeDeTarefas);
                return 0;
            default:
                printf("Escolha inválida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}
