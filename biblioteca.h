//
// Created by unifgmorassi on 20/09/2023.
//

#ifndef PROJETOLISTADETAREFASSALVAEMBINARIO_BIBLIOTECA_H
#define PROJETOLISTADETAREFASSALVAEMBINARIO_BIBLIOTECA_H
struct tarefa
{
    int prioridade;
    char desc[300];
    int estado;
    char categoria[100];
};
void lerTarefas(struct tarefa lista[], int *quantidadeDeTarefas);
void criarNovaTarefa(struct tarefa lista[], int *quantidadeDeTarefas, int tamanhoMaximo);
void listarTarefas(struct tarefa lista[], int quantidadeDeTarefas);
void deletarTarefa(struct tarefa lista[], int *quantidadeDeTarefas);
void salvarTarefas(struct tarefa lista[], int quantidadeDeTarefas);
void listarIndividual(struct tarefa lista[],int position);
void arquivotxt(struct tarefa lista[],int quantidadeDeTarefas);
void listarIndividualarquivo(struct tarefa lista[],int position,FILE *arquivo);
void limpa();
#endif //PROJETOLISTADETAREFASSALVAEMBINARIO_BIBLIOTECA_H
