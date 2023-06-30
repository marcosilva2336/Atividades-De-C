/****************************************************************** 
 * Nome: Pilha com Apontadores                                    *
 * Autores: João Marcos e Lucas Matheus                           *
 ******************************************************************/

/* Importação de Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* Criação da Pilha e do Nó, que será responsável pela conexão entre os itens da pilha */
typedef struct pilha Pilha;
typedef struct pilhaNo PilhaNo;

struct pilha{
    PilhaNo *topo;
};

/* Responsável pelos campos da Estrutura do Roteador */
struct pilhaNo{
    PilhaNo *prox;
    char marca[50];
    char modelo[50];
    float velocidade;
    int antenas;
    int portas;
    char sistemaOperacional[50];
    float valor;
};


/* === Funções Implementadas === */
Pilha* criarPilha();
int push(Pilha*, PilhaNo*);
int pop(Pilha*);
void verTopo(Pilha*);
void ehVazia(Pilha*);
Pilha* excluirPilha(Pilha*);

int executavel();
int selecaoOperacao();
PilhaNo* criarElemento();

int hackFunc(Pilha*, char*, char*, float, int, int, char*, float);

/* Função Main */
int main(){
    executavel();
    return 0;
}

int executavel(){

    Pilha *pilha;
    PilhaNo *no;

    int operacao = 1;

    do{
        if(operacao == 1){
            printf("\n=============================================================================\n");
            printf("\t\t* Olá, seja bem vindo ao Controle de Roteadores.\n\n");
            printf("\tNotei que você não tem nenhuma pilha de roteadores, não é? \n\tAntes de prosseguir, você precisa criar uma pilha.\n\n\tPressione 1 - para criar uma pilha\n\tPressione 2 - para finalizar o programa\n");
            int criarRoteador;
            scanf("%d", &criarRoteador);
            printf("\n=============================================================================\n");
            if(criarRoteador == 1){
                operacao = 0;
                pilha = criarPilha();
            } else{
                operacao = -1;
            }
        }
        else{
            operacao = selecaoOperacao(pilha);
        }
        // system("tput reset"); 
    } while(operacao >= 0);

    return 0;
}

int selecaoOperacao(Pilha *pilha){
    printf("\n====================================================================================================\n");
    printf("\t\t\t\tDigite a opção que deseja executar: \n\n");
    printf("\tPressione 1 - para inserir um elemento na pilha.\n");
    printf("\tPressione 2 - para mostrar o elemento que está no topo da pilha.\n");
    printf("\tPressione 3 - para remover o elemento que está no topo da pilha.\n");
    printf("\tPressione 4 - para saber se a pilha está vazia ou não.\n");
    printf("\tPressione 5 - para excluir a pilha.\n");
    printf("\tPressione 6 - para finalizar o programa.\n");
    
    int operacao;
    scanf("%d", &operacao);
    
    switch (operacao) {
        case 1:
            push(pilha, criarElemento());
            break;

        case 2:
            verTopo(pilha);
            break;
        
        case 3:
            pop(pilha);
            break;

        case 4:
            ehVazia(pilha);
            break;
        
        case 5:
            excluirPilha(pilha);
            return 1;
            
        default:
            printf("Desculpa, Digite um número válido!\n\n");
            sleep(1);
            break;
        }
    
    return 0;
}

/* Função Responsável pela criação de uma Pilha */
Pilha* criarPilha(){
    // Criação da Pilha e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma pilha
    Pilha *nova = (Pilha*)malloc(sizeof(Pilha));

    // Verifica se o espaço foi realmente alocado
    if (nova == NULL){
        printf("Não foi possível o alocamento, pois não há espaço disponível.\n");
        return NULL;
    }

    nova->topo = NULL;
    return nova;
}

/* Função Responsável pela criação de um elemento*/
PilhaNo* criarElemento(){
    PilhaNo *pilha = (PilhaNo*) malloc(sizeof(PilhaNo)); // aloca espaço para um novo elemento

    char marca[50];
    printf("Digite a marca do roteador: ");
    scanf("%s", marca);
    strcpy(pilha->marca, marca);

    char modelo[50];
    printf("Digite o modelo do roteador: ");
    scanf("%s", modelo);
    strcpy(pilha->modelo, modelo);
    
    float velocidade;
    printf("Digite a velocidade do roteador: ");
    scanf("%f", &velocidade);
    pilha->velocidade = velocidade;
    
    int antenas;
    printf("Digite a quantidade de antenas do roteador: ");
    scanf("%d", &antenas);
    pilha->antenas = antenas;
    
    int portas;
    printf("Digite a quantidade de portas do roteador: ");
    scanf("%d", &portas);
    pilha->portas = portas;
    
    char sistemaOperacional[50];
    printf("Digite o Sistema Operacional do roteador: ");
    scanf("%s", sistemaOperacional);
    strcpy(pilha->sistemaOperacional, sistemaOperacional);
    

    float valor;
    printf("Digite o valor do roteador: ");
    scanf("%f", &valor);
    pilha->valor = valor;

    pilha->prox = NULL;

    return pilha; // retorna o ponteiro para o novo elemento criado
}

/* Função responsável por adicionar novos elementos no topo da pilha */
int push(Pilha *pilha, PilhaNo *nova){
    // Criação da Pilha e alocação dela no Heap, sendo o tamanho do alocamento igual ao tamanho utilizado por uma pilha
    PilhaNo *aux;
    
    /* Verificando se há espaço disponível */
    if(nova == NULL){
        printf("Não foi possível o alocamento, pois não há espaço disponível.\n");
        return 0;
    }

    /* Verifica se a pilha está vazia. Se sim, coloca o roteador criado no topo da pilha. */
    if(pilha->topo == NULL){
        nova->prox = NULL;
        pilha->topo = nova;
        return 1;
    }

    /* Adição de um novo roteador e alocação daquele, que até então, estava no topo, para segunda posição (abaixo do topo) */
    nova->prox = pilha->topo;
    pilha->topo = nova;

    return 1;
}

/* Função responsável por remover o elemento que está no topo da pilha */
int pop(Pilha *pilha){
    PilhaNo *aux;
    PilhaNo *p;

    /* Verificando se a pilha existe */
    if(pilha == NULL){
        printf("A pilha nao foi criada\n");
        return 0;
    }

    /*Verificando se a pilha foi criada*/
    if(pilha->topo == NULL){
        printf("A pilha esta vazia\n");
        return 0;
    }

    /* Verifica se a pilha só tem um roteador */
    if(pilha->topo->prox == NULL){
        p = pilha->topo;
        pilha->topo = NULL;
        printf("Roteador excluído da pilha com sucesso!\n");
        free(p);
        return 1;
    }

    p = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(p);
    printf("Roteador excluído da pilha com sucesso!\n");
    return 1;
}

/* Função responsável pela exclusão da pilha */
Pilha* excluirPilha(Pilha* pilha){
    PilhaNo *aux;
    PilhaNo *p;

    p = pilha->topo;
    do {
        aux = p->prox;
        p = aux->prox;
        free(aux);
    	p = p->prox;
	}
	while(p->prox != NULL);

    free(pilha);
    printf("pilha excluida!\n");
    return NULL;
}

/* Função responsável por mostrar se a pilha está ou não vazia */
void ehVazia(Pilha *pilha){
    /* Verifica se a pilha está vazia */
    if(pilha->topo == NULL)
        printf("A pilha está vazia.\n");
    else
        printf("A pilha não está vazia.\n");
}

/* Função Responsável pela impressão do item que está no topo da pilha */
void verTopo(Pilha *pilha){
    /* Verifica se a pilha foi criada */
    if(pilha == NULL){
        printf("Não foi possível pilhar elementos pois a pilha não foi criada.\n");
        return ;
    }

    /* Verifica se a pilha está vazia */
    if(pilha->topo == NULL){
        printf("Não foi possível pilhar elementos pois a pilha está vazia.\n");
        return ;
    }

    /* Mostra o Roteador do topo */
    printf("\nMarca: %s \n", pilha->topo->marca);
    printf("Modelo: %s \n", pilha->topo->modelo);
    printf("Velocidade: %.2f Mbps\n", pilha->topo->velocidade);
    printf("Antenas: %d \n", pilha->topo->antenas);
    printf("Portas: %d \n", pilha->topo->portas);
    printf("Sistema operacional: %s \n", pilha->topo->sistemaOperacional);
    printf("Valor: R$ %.2f \n\n", pilha->topo->valor);
}
