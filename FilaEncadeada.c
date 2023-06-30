/****************************************************************** 
 * Nome: Fila Encadeada                                           *
 * Autores: João Marcos e Lucas Matheus                           *
 ******************************************************************/

/* Importação de Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* Criação da Fila e do Nó, que será responsável pela conexão entre os itens da fila */
typedef struct fila Fila;
typedef struct roteador Roteador;

struct fila{
    Roteador *inicio;
    Roteador *fim;
};

/* Responsável pelos campos da Estrutura do Roteador */
struct roteador{
    Roteador *prox;
    char marca[50];
    char modelo[50];
    float velocidade;
    int antenas;
    int portas;
    char sistemaOperacional[50];
    float valor;
};


/* === Funções Implementadas === */

Fila* criarFila();
int enqueue(Fila*, Roteador*);
void imprimirElementos(Fila*);
int dequeue(Fila*);
int tamanhoFila(Fila*);
Fila* excluirFila(Fila*);
int executavel();
int selecaoOperacao();
Roteador* criarElemento();
void registrandoDados(Fila*);

/* Função Main */
int main(){
    executavel();
    return 0;
}

int executavel(){

    Fila *fila;
    Roteador *no;

    int operacao = 1;

    do{
        if(operacao == 1){
            printf("\n=============================================================================\n");
            printf("\t\t* Olá, seja bem vindo ao Controle de Roteadores.\n\n");
            printf("\tNotei que você não tem nenhuma fila de roteadores, não é? \n\tAntes de prosseguir, você precisa criar uma fila.\n\n\tPressione 1 - para criar uma fila\n\tPressione 2 - para finalizar o programa\n");
            int criarRoteador;
            scanf("%d", &criarRoteador);
            printf("\n=============================================================================\n");
            if(criarRoteador == 1){
                operacao = 0;
                fila = criarFila();
            } else{
                operacao = -1;
            }
        }
        else{
            operacao = selecaoOperacao(fila);
        }
    } while(operacao >= 0);

    return 0;
}

int selecaoOperacao(Fila *fila){
    printf("\n====================================================================================================\n");
    printf("\t\t\t\tDigite a opção que deseja executar: \n\n");
    printf("\tPressione 1 - para inserir um elemento na fila. (Enqueue)\n");
    printf("\tPressione 2 - para mostrar os elementos da fila.\n");
    printf("\tPressione 3 - para remover o primeiro da fila. (Dequeue)\n");
    printf("\tPressione 4 - para saber o tamanho da fila.\n");
    printf("\tPressione 5 - para excluir a fila.\n");
    printf("\tPressione 6 - para finalizar o programa.\n");
    
    int operacao;
    scanf("%d", &operacao);
    
    switch (operacao) {
        case 1:
            enqueue(fila, criarElemento());
            break;
            
        case 2:
            imprimirElementos(fila);
            break;
        
        case 3:
            dequeue(fila);
            break;
        
        case 4:
            printf("A fila tem %d roteadores.\n", tamanhoFila(fila));
            break;
        
        case 5:
            excluirFila(fila);
            return 1;
        
        case 6:
            return -1;
                
        default:
            printf("Desculpa, Digite um número válido!\n\n");
            sleep(1);
            break;
    }

    int bla = 0;
    return bla;
}

/* Função Responsável pela criação de uma Fila */
Fila* criarFila(){
    // Criação da Fila e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma fila
    Fila *nova = (Fila*)malloc(sizeof(Fila));

    // Verifica se o espaço foi realmente alocado
    if (nova == NULL){
        printf("Não foi possível o alocamento, pois não há espaço disponível.\n");
        return NULL;
    }

    nova->inicio = NULL;
    return nova;
}

/* Função Responsável pela criação de um elemento*/
Roteador* criarElemento(){
    Roteador *fila = (Roteador*) malloc(sizeof(Roteador)); // aloca espaço para um novo elemento

    char marca[50];
    printf("Digite a marca do roteador: ");
    scanf("%s", marca);
    strcpy(fila->marca, marca);

    char modelo[50];
    printf("Digite o modelo do roteador: ");
    scanf("%s", modelo);
    strcpy(fila->modelo, modelo);
    
    float velocidade;
    printf("Digite a velocidade do roteador: ");
    scanf("%f", &velocidade);
    fila->velocidade = velocidade;
    
    int antenas;
    printf("Digite a quantidade de antenas do roteador: ");
    scanf("%d", &antenas);
    fila->antenas = antenas;
    
    int portas;
    printf("Digite a quantidade de portas do roteador: ");
    scanf("%d", &portas);
    fila->portas = portas;
    
    char sistemaOperacional[50];
    printf("Digite o Sistema Operacional do roteador: ");
    scanf("%s", sistemaOperacional);
    strcpy(fila->sistemaOperacional, sistemaOperacional);
    

    float valor;
    printf("Digite o valor do roteador: ");
    scanf("%f", &valor);
    fila->valor = valor;

    fila->prox = NULL;

    return fila; // retorna o ponteiro para o novo elemento criado
}

int enqueue(Fila *fila, Roteador *nova){  
    
    /*Verificando se o espaco foi reservado corretamente*/
    if(nova == NULL){
        printf("Sem espaco\n");
        return 0;
    }

    /* Preparando as informacoes inciais do elemento a ser inserido */
    nova->prox = NULL;

    /*Tratamento para inserir um elemento quando a fila esta vazia*/
    if(fila->inicio == NULL){
        fila->inicio = nova;
        fila->fim = nova;
        return 1;
    }

    /*Procurando o ultimo ponteiro da fila para receber o novo elemento*/
    fila->fim->prox = nova;
    fila->fim = nova;

    return 1;
}

int dequeue(Fila *fila){
    Roteador *p;

    /* Verificando se a fila existe */
    if(fila == NULL){
        printf("A fila nao foi criada\n");
        return 0;
    }

    /*Verificando se a fila foi criada*/
    if(fila->inicio == NULL){
        printf("A fila esta vazia\n");
        return 0;
    }

    if(fila->inicio == fila->fim){
        p = fila->inicio;
        fila->inicio = NULL;
        fila->fim = NULL;
        free(p);
        return 1;
    }

    p = fila->inicio;
    fila->inicio = fila->inicio->prox;
    free(p);
    return 1;
}

/* Função responsável pela exclusão da fila */
Fila* excluirFila(Fila* fila){
    Roteador *aux;

    while(fila->inicio != NULL){
        aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        free(aux);
    }

    free(fila);

    printf("fila excluida!\n");
    return NULL;
}

/* Função Responsável pela impressão de uma fila, isto é, mostrar seus itens */
void imprimirElementos(Fila *fila){
    Roteador *p;

    if(fila == NULL){
        printf("Não foi possível filar elementos pois a fila não foi criada.\n");
        return ;
    }

    if(fila->inicio == NULL){
        printf("Não foi possível filar elementos pois a fila está vazia.\n");
        return ;
    }

    for(p = fila->inicio; p != NULL; p = p->prox){
        printf("\nMarca: %s \n", p->marca);
        printf("Modelo: %s \n", p->modelo);
        printf("Velocidade: %.2f Mbps\n", p->velocidade);
        printf("Antenas: %d \n", p->antenas);
        printf("Portas: %d \n", p->portas);
        printf("Sistema operacional: %s \n", p->sistemaOperacional);
        printf("Valor: R$ %.2f \n\n", p->valor);
    }
}

/* Função responsável por retornar a quantidade de itens dentro da fila */
int tamanhoFila(Fila *fila){
    Roteador *p;  

    /* Calcula quantos itens tem na fila, através do contador */
    int contador = 0;
    for(p = fila->inicio; p != NULL; p = p->prox){
        ++contador;
    }

    return contador;
}

