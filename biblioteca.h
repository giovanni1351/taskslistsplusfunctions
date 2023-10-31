//
// Created by unifgmorassi on 20/09/2023.
//

#ifndef PROJETOLISTADETAREFASSALVAEMBINARIO_BIBLIOTECA_H
#define PROJETOLISTADETAREFASSALVAEMBINARIO_BIBLIOTECA_H
struct tarefa
{
    int prioridade;
    char desc[300];
    char categoria[100];
};
void lerTarefas(struct tarefa lista[], int *quantidadeDeTarefas);
void criarNovaTarefa(struct tarefa lista[], int *quantidadeDeTarefas, int tamanhoMaximo);
void listarTarefas(struct tarefa lista[], int quantidadeDeTarefas);
void deletarTarefa(struct tarefa lista[], int *quantidadeDeTarefas, int pos);
void salvarTarefas(struct tarefa lista[], int quantidadeDeTarefas);

#endif //PROJETOLISTADETAREFASSALVAEMBINARIO_BIBLIOTECA_H
