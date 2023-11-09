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
    if (arquivo) {
        fseek(arquivo, 0, SEEK_END);
        long tamanho_arquivo = ftell(arquivo);//descobre o tamanho em bytes do arquivo
        rewind(arquivo);//volta o ponteiro do arquivo para o inicio
        *quantidadeDeTarefas = tamanho_arquivo / sizeof(struct tarefa);//divide o tamanho total do arquivo pelo tamanho da struct
        //para descobrir a quantidade de tarefas
        fread(lista, sizeof(struct tarefa), *quantidadeDeTarefas, arquivo);
        fclose(arquivo);
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
void deletarTarefa(struct tarefa lista[], int *quantidadeDeTarefas) {
    while(1){//esse while é para o menu sempre ficar ativo, sendo possivel usar varias vezes a funções.
        printf("Seja bem vindo ao menu de deletar tarefas!\n");
        printf("1.Listar tarefas!\n");
        printf("2.Deletar tarefa!\n");
        printf("0.Sair do menu de deletar tarefas!\n");
        printf("Opcao: \n");
        int choose;
        scanf("%d",&choose);
        if(choose == 1){
            //neste daqui ele vai listar todas a tarefas por ordem de adição para caso ele precisa consultar o numero da tarefa

            for(int x =0 ; x < (*quantidadeDeTarefas);x++){
                listarIndividual(lista,x);
            }
        }
        if(choose == 2) {
            printf("Qual posição você deseja apagar?(-1 desistir)\n");
            int pos;
            scanf("%d", &pos); // Lê a posição da tarefa a ser deletada
            // Chama a função para deletar a tarefa
            if (pos > 0) {


                for (int i = pos; i < (*quantidadeDeTarefas) - 1; i++) {
                    lista[i] = lista[i + 1];//ele vai pegar a tarefa do próximo indice e colocar no atual
                    //começando da posição inicial digitada
                }
                (*quantidadeDeTarefas)--;//ele diminui a quantidade de tarefas em 1 para q tenhamos o controle
            }
            else{
                printf("Operação cancelada!\n");
            }
        }
        if(choose == 0){
            printf("Saindo do menu de deletar tarefas");
            break;
        }
    }

}

// Função para listar as tarefas na lista
void listarIndividual(struct tarefa lista[],int position){
    //nesta função ele vai receber a lista e a posição, e vai ser chamada em todos os for para mostrar as tarefas de maneira consistente
    //ou seja, vai ter um padrão no print da tarefas
    printf("Tarefa de Numero: %d \n", position);
    printf("Prioridade: %d\n", lista[position].prioridade);
    printf("Descrição: %s\n", lista[position].desc);
    if(lista[position].estado == 0){
        printf("Estado: Não realizado!\n");}
    else if(lista[position].estado == 1){

        printf("Estado: Em andamento!\n");}
    else if(lista[position].estado == 2){

        printf("Estado: Finalizado!\n");
    }
    printf("Categoria: %s\n", lista[position].categoria);
    printf("\n");
}
void listarIndividualarquivo(struct tarefa lista[],int position,FILE *arquivo){
    //esta função funciona parecido com o de listarindividual, mas ela vai ter mais um argumento q é o aquivo
    //sendo o lugar onde ele vai digitar as tarefas, funciona da mesma maneira.
    fprintf(arquivo,"Prioridade: %d\n", lista[position].prioridade);
    fprintf(arquivo,"Categoria: %s\n", lista[position].categoria);
    if(lista[position].estado == 0){
        fprintf(arquivo,"Estado: Não realizado!\n");}
    else if(lista[position].estado == 1){

       fprintf(arquivo,"Estado: Em andamento!\n");
    }
    else if(lista[position].estado == 2){

        fprintf(arquivo,"Estado: Finalizado!\n");
    }

    fprintf(arquivo,"Descrição: %s\n", lista[position].desc);
    fprintf(arquivo,"\n");
}
void arquivotxt(struct tarefa lista[],int quantidadeDeTarefas){
    while(1){//este while é para funcionar como menu desta função, onde ele pode escolher o filtro utilizado para
        //printar no arquivo as tarefas
        printf("Selecione como deseja printar suas tarefas no arquivo!\n");
        printf("1.Listar por ordem de adição! \n");
        printf("2.Listar por categoria!\n");
        printf("3.Listar por prioridade!\n");
        printf("4.Listar por estado!\n");
        printf("5.Listar por prioridade e categoria!\n");
        printf("0.Sair do menu de listar em arquivo  \n");
        int escolha;
        scanf("%d",&escolha);
        limpa();
        if(escolha ==1) {
            FILE *arquivo = fopen("AllTasks.txt","w");
            //nesta escolha ele simplismente irá varrer no for todas as tarefas e printar no arquivo
            //AllTasks.txt que é o terceiro argumento da função listarIndividualarquivo.
            int encontrado =0;
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                listarIndividualarquivo(lista,x,arquivo);
                encontrado =1;
                //ele vai atualizar para 1 caso tenha alguma repetição no looping
            }
            fclose(arquivo);//aqui ele fecha o arquivo
            if(encontrado ==0){
                printf("Nenhuma tarefa encontrada!\n");
                //caso n tenha nenhuma tarefa encontrada pelo for ele printa isso
            }else{
                printf("Arquivo gerado com sucesso!\n");
                //caso dê tudo certo ele printa Arquivo gerado com sucesso.

            }
        }
        if(escolha == 2){

            char categoria[100];
            printf("Digite a categoria:\n");
            scanf("%100[^\n]s", &categoria);
            limpa();
            //nesta escolha ele vai colocar a categoria que ele deseja
            int encontrado =0;
            FILE *arquivo = fopen("filtredbycategories.txt","w");
            //ele vai salvar no arquivo filtredbycategories.txt
            for (int ordem = 10; ordem >= 0; ordem--) {
                for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                    //até a quantidade de tarefas ja criadas
                    if (strcmp(lista[x].categoria, categoria) == 0 && lista[x].prioridade == ordem) {//caso a tarefa observada
                        //tenha a categoria digitada no inicio da escolha ele vai chamar a função desejada de digitalizar no arquivo
                        listarIndividualarquivo(lista, x, arquivo);
                        encontrado = 1;
                    }
                }
            }
            fclose(arquivo);

            if(encontrado ==0){
                printf("Nenhuma tarefa encontrada!\n");
            }else{
                printf("Arquivo gerado com sucesso!\n");
            }

        }
        if(escolha == 3){
            int priority;
            FILE *arquivo = fopen("filtredbypriorities.txt","w");
            do{
                printf("Digite a prioridade a ser buscada(1 a 10): \n");
                scanf("%d",&priority);
            }while(priority<1||priority>10);
            //ele vai pedir a prioridade até q seja uma que esteja nos limites do programa, que é de 1 a 10.
            int encontrado =0;
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                if(priority==lista[x].prioridade) {//ele vai verificar se a tarefa tem a prioridade digitada
                    listarIndividualarquivo(lista,x,arquivo);
                    encontrado =1;
                }
            }
            fclose(arquivo);//fecha o arquivo
            if(encontrado ==0){
                printf("Nenhuma tarefa encontrada!\n");
            }else{
                printf("Arquivo gerado com sucesso!\n");

            }
        }
        if(escolha == 4){
            int estate;
            int encontrado =0;
            FILE *arquivo = fopen("filtredbyestate.txt","w");

            printf("Digite quais estados vão aparecer:\n");
            printf("0.Não realizado!\n");
            printf("1.Em andamento!\n");
            printf("2.Finalizado!\n");
            //ele vai pedir o estado atuala da tarefa, dando a opcao de 0 a 2 para usar de filtro no for
            scanf("%d",&estate);
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                if(estate==lista[x].estado) { //caso o valor digitado seja igual a tarefa observada no for
                    //ele executa a função de printar no arquivo .
                    listarIndividualarquivo(lista,x,arquivo);
                    encontrado =1;
                }
            }
            fclose(arquivo);//fecha o arquivo filtredbyestate.txt
            if(encontrado == 0){
                printf("Nenhuma tarefa encontrada!\n");
            }else{
                printf("Arquivo gerado com sucesso!\n");

            }
        }
        if(escolha == 5) {
            FILE *arquivo = fopen("filtredbycategoriesandpriorities.txt", "w");

            int prioridade;
            char categoria[100];
            int encontrado = 0;
            do {
                printf("Digite a prioridade:\n");
                scanf("%d", &prioridade);
                limpa();
            }while(prioridade<1||prioridade>10);
            //aqui ele vai digitar a prioridade e o estado da tarefa para usar de filtro
            printf("Digite a categoria:\n");
            scanf("%100[^\n]s", &categoria);
            limpa();
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                if(prioridade==lista[x].prioridade&& strcmp(lista[x].categoria,categoria)==0) {
                    //agora o verificador vai ver se a tarefa contem a prioridade e a categoria igual a digitada
                    listarIndividualarquivo(lista,x,arquivo);
                    encontrado =1;
                }
            }
            fclose(arquivo);//ele vai fechar o arquivo filtredbycategoriesandpriorities.txt
            if(encontrado == 0){
                printf("Nenhuma tarefa encontrada!\n");
            }else{
                printf("Arquivo gerado com sucesso!\n");

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
        do{
            printf("Prioridade(1 a 10): ");
            scanf("%d", &nova.prioridade);
        }while(nova.prioridade<1 ||nova.prioridade>10);
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
void listarTarefas(struct tarefa lista[], int quantidadeDeTarefas){
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
                listarIndividual(lista,x);
                encontrado =1;
            }
            if(encontrado ==0){
                printf("Nenhuma tarefa encontrada!\n");
            }
        }
        if(escolha == 2) {
            char categoria[100];
            printf("Digite a categoria:\n");
            scanf("%100[^\n]s", &categoria);
            //ele pede a categoria para ser usada de filtro
            limpa();
            int encontrado = 0;
            for (int ordem = 10; ordem >= 1; ordem--) {//ele vai começar do 10 para o 1, que vai servir de ordenador
                for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                    //até a quantidade de tarefas ja criadas
                    if (strcmp(lista[x].categoria, categoria) == 0 && lista[x].prioridade == ordem) {
                        //caso tenha a ordem e a categoria digitada ele printa a tarefa observada
                        //chamando a função listarindividual passando a lista e a posição de argumento.
                        listarIndividual(lista, x);
                        encontrado = 1;
                    }
                }
            }
            if(encontrado ==0){//caso n tenha encontrado nada ele printa isso
                printf("Nenhuma tarefa encontrada!\n");
            }

        }
        if(escolha == 3){
            int priority;
            int encontrado =0;
            do{

            printf("Digite a prioridade a ser buscada(1 a 10): \n");
            scanf("%d",&priority);
            }while(priority<1||priority>10);
            //ele vai pedir a prioridade até que atenda as condições (1 a 10)
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                if(priority==lista[x].prioridade) {//caso a tarefa observada pelo for atual tiver a prioridade igual a digitada
                    //ele chama a função de printar no terminal
                    listarIndividual(lista,x);
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
            //ele vai pedir o estado da tarefa para usar de filtro
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                if(estate==lista[x].estado) {//caso a tarefa atual observada pelo for que vai do 0 para a quantidade de tarefas
                    //tenha o estado que ele digitou como filtro ele vai chamar a função de printar no terminal
                    listarIndividual(lista,x);
                    encontrado =1;
                }
            }
            if(encontrado == 0){
                printf("Nenhuma tarefa encontrada!\n");
            }
        }
        if(escolha == 5){
            int prioridade;
            char categoria[100];
            int encontrado =0;
            do {
                printf("Digite a prioridade(1 a 10):\n");
                scanf("%d", &prioridade);
                limpa();
            }while(prioridade<1||prioridade>10);
            printf("Digite a categoria:\n");
            scanf("%100[^\n]s", &categoria);
            limpa();
            //agora nesta escolha
            //ele vai pedir a prioridade e a categoria
            //para usar de filtro
            for (int x = 0; x < quantidadeDeTarefas; x++) {//ele vai começar do zero e vai
                //até a quantidade de tarefas ja criadas
                if(prioridade==lista[x].prioridade&& strcmp(lista[x].categoria,categoria)==0) {//nesta linha ele verifica se a prioridade
                    //e a categoria que foi digitada esta de acordo com a tarefa que esta sendo analizada no for, caso verdade ele chama
                    //a função de printar no terminal, (listarIndividual), passando a lista e a posição como argumento
                    listarIndividual(lista,x);
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
};
void alterarTarefas(struct tarefa lista[], int quantidadeDeTarefas){

    while(1){
        printf("Seja bem vindo ao menu de atualizar tarefas.\n");
        printf("Temos algumas opcoes aqui, o que voce deseja?.\n");
        printf("Selecione a opcao!.\n");
        printf("1.Listar tarefas!\n");
        printf("2.Atualizar tarefas!\n");
        printf("0.Sair do menu!\n");
        // Obtém a escolha do usuário
        int choose;
        scanf("%d",&choose);
        limpa();//função para limpar o buffer de entrada

        // Verifica a escolha do usuário
        if(choose == 1){
            // Lista todas as tarefas
            for(int x = 0 ; x < quantidadeDeTarefas;x++){
                listarIndividual(lista,x);
            }
        }
        if(choose == 2){
            // Opção para atualizar tarefas
            while(1){
                printf("Olá, neste menu voce pode escolher o que alterar da tarefa desejada!\n");
                printf("Me diga qual a posicao da tarefa que voce deseja alterar!(-1 para voltar)\n");
                // Obtém a posição da tarefa a ser alterada
                int posicao;
                scanf("%d",&posicao);

                // Verifica se o usuário deseja sair
                if(posicao <0){
                    break;
                }
                limpa();
                // Exibe informações sobre a tarefa selecionada
                printf("A tarefa selecionada é a da posicao %d\n",posicao);
                printf("Agora me diga o que voce deseja alterar!\n");
                printf("Voce tem essas opcoes:\n");
                printf("1.Prioridade.\n");
                printf("2.Estado.\n");
                printf("3.Categoria.\n");
                printf("4.Descrição.\n");
                printf("5.Desistir.\n");
                printf("Qual você escolhe?\n");
                int opcaodetroca;
                // Obtém a opção de troca do usuário
                scanf("%d",&opcaodetroca);
                limpa();
                // Realiza a alteração com base na escolha do usuário
                if(opcaodetroca == 1){
                    // Altera a prioridade da tarefa
                    int newpriority;
                    do{

                    printf("Qual vai ser a nova prioridade desta tarefa?\n");
                    scanf("%d",&newpriority);//pede a nova prioridade
                    limpa();
                    }while(newpriority<1||newpriority>10);//enquanto estiver fora do intervalo correto
                    //ele vai pedir até for correto

                    lista[posicao].prioridade = newpriority;//atualiza
                }
                if(opcaodetroca == 2){
                    //Altera o estado da tarefa
                    printf("Qual vai ser o novo estado desta tarefa?\n");
                    printf("0.Não realizado!\n");
                    printf("1.Em andamento!\n");
                    printf("2.Finalizado!\n");
                    int newestate;
                    scanf("%d",&newestate);//pede o novo estado da tarefa
                    limpa();

                    lista[posicao].estado = newestate;
                }
                if(opcaodetroca == 3){
                    //Altera a categoria da tarefa
                    printf("Qual vai ser a nova categoria desta tarefa?\n");

                    char newcategorie[100];//pede a nova categoria
                    scanf("%100[^\n]s", &newcategorie);
                    limpa();
                    strcpy(lista[posicao].categoria,newcategorie);
                }
                if(opcaodetroca == 4){
                    //atualiza a descrição da tarefa
                    printf("Qual vai ser a nova descricao desta tarefa?\n");

                    char newdesc[300];
                    //pede a nova descrição
                    scanf("%300[^\n]s", &newdesc);
                    limpa();
                    strcpy(lista[posicao].desc,newdesc);
                }
                // Verifica se o usuário deseja sair do menu de atualização de tarefas
                if(opcaodetroca == 0){
                    break;
                }

            }
        }
        // Sai do menu se a escolha do usuário for 0
        if(choose == 0){
            break;
        }

    }


}



#include "biblioteca.h" // Inclui novamente o cabeçalho