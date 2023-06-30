/****************************************************************** 
 * Nome: Lista Com vetores                                        *
 * Autores: João Marcos e Lucas Matheus                           *
 ******************************************************************/

/* Importação de Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definindo tamanho da Lista */
#define TAM 100

/* Responsável pelos campos da Estrutura do Roteador */
typedef struct{
  char marca[50];
  char modelo[50];
  float velocidade;
  int antenas;
  int portas;
  char sistemaOperacional[50];
  float valor;
}Roteador;


/* Lista */
typedef struct{
    int id;
    Roteador *elementos;
} Lista;


//funcao implementada
int atualizarElemento(Lista* ,char*,char*, char*, char*, float, int, int, float); 
int buscarElemento(Lista*, char*);
Lista* criarLista();
Lista* excluirLista(Lista*);
void imprimirElementos(Lista*);
int inserirElemento(Lista*, char*, char*,float,int,int,char*,float);
int inserirElementoID(Lista*, char*,char*, float, int, int, char*,float,int);
int inserirElementoInicio(Lista*, char*, char*, float, int, int, char*, float);
int removerElemento(Lista*, int);
int removerElementoNome(Lista*, char*);
int tamanhoLista(Lista*);

/* Função Main */
int main(){
    Lista *lista = NULL;
    int opcao = 0;
    char marca[50], modelo[50], sistemaOperacional[50], busca[50];
    float velocidade, valor;
    int antenas, portas, posicao;

    do {
        printf("---- MENU ----\n");
        printf("1 - Criar lista\n");
        printf("2 - Inserir elemento\n");
        printf("3 - Buscar elemento\n");
        printf("4 - Atualizar elemento\n");
        printf("5 - Remover elemento\n");
        printf("6 - Remover elemento por nome\n");
        printf("7 - Inserir elemento no in�cio\n");
        printf("8 - Inserir elemento ID\n");
        printf("9 - Imprimir elementos\n");
        printf("10 - Tamanho da lista\n");
        printf("0 - Sair\n");
        printf("Digite sua op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                lista = criarLista();
                printf("Lista criada com sucesso!\n");
                break;
            case 2:
                printf("Digite a marca: ");
                scanf("%s", marca);
                printf("Digite o modelo: ");
                scanf("%s", modelo);
                printf("Digite a velocidade: ");
                scanf("%f", &velocidade);
                printf("Digite o n�mero de antenas: ");
                scanf("%d", &antenas);
                printf("Digite o n�mero de portas: ");
                scanf("%d", &portas);
                printf("Digite o sistema operacional: ");
                scanf("%s", sistemaOperacional);
                printf("Digite o valor: ");
                scanf("%f", &valor);
                inserirElemento(lista, marca, modelo, velocidade, antenas, portas, sistemaOperacional, valor);
                printf("Elemento inserido com sucesso!\n");
                break;
            case 3:
                printf("Digite a marca a ser buscada: ");
                scanf("%s", marca);
                posicao = buscarElemento(lista, marca);
                if (posicao != -1) {
                    printf("Elemento encontrado na posi��o %d!\n", posicao);
                    printf("Marca: %s \t", lista->elementos[posicao].marca);
                    printf("Modelo: %s \t", lista->elementos[posicao].modelo);
                    printf("Velocidade: %.2f Mbps\t", lista->elementos[posicao].velocidade);
                    printf("Antenas: %d \t", lista->elementos[posicao].antenas);
                    printf("Portas: %d \t", lista->elementos[posicao].portas);
                    printf("Sistema operacional: %s \t", lista->elementos[posicao].sistemaOperacional);
                    printf("Valor: R$ %.2f \n\n\n", lista->elementos[posicao].valor);
                } else {
                    printf("Elemento n�o encontrado!\n");
                }
                break;
           case 4:
                printf("Digite algum par�metro do roteador que deseja atualizar: ");
                scanf("%s", busca);
             	printf("Digite a nova marca: ");
                scanf("%s", marca);
                printf("Digite a nova modelo: ");
                scanf("%s", modelo);
                printf("Digite o novo sistema operacional: ");
                scanf("%s", sistemaOperacional); 
		        printf("Digite a nova velocidade: ");
                scanf("%f", &velocidade);
                printf("Digite o novo n�mero de antenas: ");
                scanf("%d", &antenas);
                printf("Digite o novo n�mero de portas: ");
                scanf("%d", &portas);   
                printf("Digite o novo valor: ");
                scanf("%f", &valor);
           if (atualizarElemento(lista, busca, marca, modelo, sistemaOperacional, velocidade, antenas, portas, valor)) {
           printf("Elemento atualizado com sucesso!\n");
	       } else {
           printf("Elemento n�o encontrado!\n");
	       }
         break;
         case 5:
            int exclusao;
            printf("Digite Valor: ");
            scanf("%d", &exclusao);
            removerElemento(lista, exclusao);
            printf("o removido com sucesso!\n");              
            break;
        
        case 6:
            printf("Digite a marca a ser removida: ");
            scanf("%s", marca);
            posicao = removerElementoNome(lista, marca);
            printf("o removido com sucesso!\n");              
            break;
             
        case 7:
            printf("Digite a marca: ");
            scanf("%s", marca);
            printf("Digite o modelo: ");
            scanf("%s", modelo);
            printf("Digite a velocidade: ");
            scanf("%f", &velocidade);
            printf("Digite o n�mero de antenas: ");
            scanf("%d", &antenas);
            printf("Digite o n�mero de portas: ");
            scanf("%d", &portas);
            printf("Digite o sistema operacional: ");
            scanf("%s", sistemaOperacional);
            printf("Digite o valor: ");
            scanf("%f", &valor);
            inserirElementoInicio(lista, marca, modelo, velocidade, antenas, portas, sistemaOperacional, valor);
            printf("Elemento inserido no in�cio com sucesso!\n");
            break;
        case 8:
            printf("Digite a marca: ");
            scanf("%s", marca);
            printf("Digite o modelo: ");
            scanf("%s", modelo);
            printf("Digite a velocidade: ");
            scanf("%f", &velocidade);
            printf("Digite o n�mero de antenas: ");
            scanf("%d", &antenas);
            printf("Digite o n�mero de portas: ");
            scanf("%d", &portas);
            printf("Digite o sistema operacional: ");
            scanf("%s", sistemaOperacional);
            printf("Digite o valor: ");
            scanf("%f", &valor);
            printf("Digite a posi��o desejada: ");
            scanf("%d", &posicao);
            if (inserirElementoID(lista, marca, modelo, velocidade, antenas, portas, sistemaOperacional, valor,posicao)) {
                printf("Elemento inserido na posi��o %d com sucesso!\n", posicao);
            } else {
                printf("Posi��o inv�lida!\n");
            }
            break;
        case 9:
            imprimirElementos(lista);
            break;
        case 10:
            printf("Tamanho da lista: %d\n", tamanhoLista(lista));
            break;	
        case 0:
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Op��o inv�lida!\n");
     }

	} while (opcao != 0);

return 0;

}



/* Função Responsável pela atualização dos elementos */
int atualizarElemento(Lista *lista, char *busca, char *marca, char *modelo, char *sistemaOperacional, float velocidade, int antenas, int portas, float valor) {
    int i;
	
    if (lista == NULL) {
        printf("A lista n�o foi criada\n");
        return 0;
    }
    
    for (i = 0; i < lista->id; ++i) {
        if (strcmp(lista->elementos[i].marca, busca) == 0) {
            strcpy(lista->elementos[i].marca, marca);
            strcpy(lista->elementos[i].modelo, modelo);
            lista->elementos[i].velocidade = velocidade;
            lista->elementos[i].antenas = antenas;
            lista->elementos[i].portas = portas;
            strcpy(lista->elementos[i].sistemaOperacional, sistemaOperacional);
            lista->elementos[i].valor = valor;
			
            return 1;
        }
    }
    return 0;
}


/* Função Responsável pela Busca de Elementos a partir da marca*/
int buscarElemento(Lista *lista, char *marca) {
    int i;

    /* Verificando se a lista foi criada */
    if (lista == NULL) {
        printf("A lista não foi criada\n");
        return -1;
    }

    /* Verificando qual a posição onde está a marca desejada */
    for (i = 0; i < lista->id; ++i) {
        if (strcmp(lista->elementos[i].marca, marca) == 0) {
            return i;
        }
    }


    return -1;
}


/* Função Responsável pela criação de uma Lista */
Lista* criarLista(){
    
    Lista *nova = (Lista*)malloc(sizeof(Lista));

    /* Verificando se a lista foi criada */
    if(nova == NULL){
        printf("Nao tem espaco\n");
        return NULL;
    }
    
    nova->id = 0; 
    nova->elementos = (Roteador*)malloc(TAM*sizeof(Roteador));
    
    /* Verificando se a lista há espaço para lista */
    if(nova->elementos == NULL){
        printf("Nao tem espaco\n");
        free(nova);
        return NULL;
    }
   
    return nova;
}


/* Função Responsável pela exclusão de uma lista */
Lista* excluirLista(Lista *lista) {
    free(lista->elementos);
    free(lista);
    lista = NULL;
    
	return lista;
}


/* Função Responsável pela impressão de uma lista, isto é, mostrar seus itens */
void imprimirElementos(Lista *lista){
    int i;

    /* Verificando se a lista foi criada */
    if(lista == NULL){
        printf("Lista não foi criada\n");
        return ;
    }

    /* Verificando se a lista está vazia */
    if(lista->id == 0){
        printf("Lista vazia\n");
        return ;
    }

    /*Mostrando cada roteador na lista*/
    for(i = 0; i < lista->id; ++i){
    printf("Marca: %s \t", lista->elementos[i].marca);
    printf("Modelo: %s \t", lista->elementos[i].modelo);
    printf("Velocidade: %.2f Mbps\t", lista->elementos[i].velocidade);
    printf("Antenas: %d \t", lista->elementos[i].antenas);
    printf("Portas: %d \t", lista->elementos[i].portas);
    printf("Sistema operacional: %s \t", lista->elementos[i].sistemaOperacional);
    printf("Valor: R$ %.2f \n\n", lista->elementos[i].valor);
    }
    printf("\n");
}

/* Função Repsonsável por adicionar novos elementos para lista */
int inserirElemento(Lista *lista, char *marca, char *modelo, float velocidade, int antenas, int portas, char *sistemaOperacional, float valor){
    /* Verificando se a lista foi criada */
    if(lista == NULL){
        printf("A lista não foi criada\n");
        return 0;
    }

    if(lista->id < TAM){
        /*Inserindo as informacoes do roteador na lista*/
        strcpy(lista->elementos[lista->id].marca, marca);
        strcpy(lista->elementos[lista->id].modelo, modelo);
        lista->elementos[lista->id].velocidade = velocidade;
        lista->elementos[lista->id].antenas = antenas;
        lista->elementos[lista->id].portas = portas;
        strcpy(lista->elementos[lista->id].sistemaOperacional, sistemaOperacional);
        lista->elementos[lista->id].valor = valor;
        //Atualizando a quantidade de roteadores na lista
        ++(lista->id);
        return 1;
    } else {
        printf("Lista cheia\n");
        return 0;
    }
}


/* Função responsável por adicionar novos elementos para lista, em um posição específica */
int inserirElementoID(Lista *lista, char *marca, char *modelo, float velocidade, int antenas, int portas, char *sistemaOperacional, float valor, int posicao) {
    int i;

    /* Verificando se a lista foi criada */
    if(lista == NULL){
        printf("A lista n�o foi criada\n");
        return 0;
    }

    if(lista->id < TAM){
       
        if(posicao <= lista->id){ /* Corrigindo o erro na condi��o */
            for(i = lista->id; i > posicao; --i){
                strcpy(lista->elementos[i].marca, lista->elementos[i-1].marca);
                strcpy(lista->elementos[i].modelo, lista->elementos[i-1].modelo);
                lista->elementos[i].velocidade = lista->elementos[i-1].velocidade;
                lista->elementos[i].antenas = lista->elementos[i-1].antenas;
                lista->elementos[i].portas = lista->elementos[i-1].portas;
                strcpy(lista->elementos[i].sistemaOperacional, lista->elementos[i-1].sistemaOperacional);
                lista->elementos[i].valor = lista->elementos[i-1].valor;
            }
            
            
            strcpy(lista->elementos[posicao].marca, marca);
            strcpy(lista->elementos[posicao].modelo, modelo);
            lista->elementos[posicao].velocidade = velocidade;
            lista->elementos[posicao].antenas = antenas;
            lista->elementos[posicao].portas = portas;
            strcpy(lista->elementos[posicao].sistemaOperacional, sistemaOperacional);
            lista->elementos[posicao].valor = valor;
  
            ++(lista->id);
        } else {
            printf("Posicao fora do intervalo permitido\n");
            return 0;
        }
    } else {
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
}

    
/* Função responsável por adicionar novos elementos para lista, no início da lista */
int inserirElementoInicio(Lista *lista, char *marca, char *modelo, float velocidade, int antenas, int portas, char *sistemaOperacional, float valor){
    int i;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista não foi criada\n");
        return 0;
    }

    /*Verificando se existe espaco para inserir mais uma pessoa na lista*/
    if(lista->id < TAM){
        /*Deslocando todas as pessoas para o final da lista*/
        for(i = lista->id; i > 0; --i){
            strcpy(lista->elementos[i].marca, lista->elementos[i-1].marca);
            strcpy(lista->elementos[i].modelo, lista->elementos[i-1].modelo);
            lista->elementos[i].velocidade = lista->elementos[i-1].velocidade;
            lista->elementos[i].antenas = lista->elementos[i-1].antenas;
            lista->elementos[i].portas = lista->elementos[i-1].portas;
            strcpy(lista->elementos[i].sistemaOperacional, lista->elementos[i-1].sistemaOperacional);
            lista->elementos[i].valor = lista->elementos[i-1].valor;
        }
        /*Inserindo a pessoa na primeira posicao da lista*/
        strcpy(lista->elementos[0].marca, marca);
        strcpy(lista->elementos[0].modelo, modelo);
        lista->elementos[0].velocidade = velocidade;
        lista->elementos[0].antenas = antenas;
        lista->elementos[0].portas = portas;
        strcpy(lista->elementos[0].sistemaOperacional, sistemaOperacional);
        lista->elementos[0].valor = valor;
        /*Atualizando a quantidade de pessoas da lista*/
        ++(lista->id);
    }else{
        printf("Espaco esgotado\n");
        return 0;
    }
    return 1;
}


/* Função responsável por remover elementos da lista, a partir de um valor específico */
int removerElemento(Lista *lista, int valor){
    int j;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista não foi criada\n");
        return 0;
    }

    /*Verificando se a posicao e permitida*/
    if (valor <lista->id){
        /*Deslocando as pessoas para o final da lista*/
        for(j = valor; j < lista->id-1; ++j){
            strcpy(lista->elementos[j].marca, lista->elementos[j+1].marca);
            strcpy(lista->elementos[j].modelo, lista->elementos[j+1].modelo);
            lista->elementos[j].velocidade = lista->elementos[j+1].velocidade;
            lista->elementos[j].antenas = lista->elementos[j+1].antenas;
            lista->elementos[j].portas = lista->elementos[j+1].portas;
            strcpy(lista->elementos[j].sistemaOperacional, lista->elementos[j+1].sistemaOperacional);
            lista->elementos[j].valor = lista->elementos[j+1].valor;
    
        }
        /*Atualizando a quantidade de pessoas da lista*/
        --(lista->id);
        return 1;
    }else{
        printf("Posicao invalida\n");
    }

    return 0;
}


/* Função responsável por remover elementos da lista, a partir de uma posição específica */
int removerElementoID(Lista *lista, char *marca){
    int i, j;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista não foi criada\n");
        return 0;
    }

    /*Percorre todos as pessoas da lista*/
    for(i = 0; i <lista->id; ++i){
       
        if(strcmp(lista->elementos[i].marca, marca) == 0){
      
            for(j = i; j < lista->id-1; ++j){
            strcpy(lista->elementos[j].marca, lista->elementos[j+1].marca);
            strcpy(lista->elementos[j].modelo, lista->elementos[j+1].modelo);
            lista->elementos[j].velocidade = lista->elementos[j+1].velocidade;
            lista->elementos[j].antenas = lista->elementos[j+1].antenas;
            lista->elementos[j].portas = lista->elementos[j+1].portas;
            strcpy(lista->elementos[j].sistemaOperacional, lista->elementos[j+1].sistemaOperacional);
            lista->elementos[j].valor = lista->elementos[j+1].valor;
    
            }
            /*Atualizando a quantidade de pessoas da lista*/
            --(lista->id);
            return 1;
        }
    }

    return 0;
}

int removerElementoNome(Lista *lista, char *marca) {
    int i, j;

    /* Verificando se a lista foi criada */
    if (lista == NULL) {
        printf("A lista n�o foi criada\n");
        return 0;
    }

    /* Buscando o elemento a ser removido pelo nome */
    int posicao = buscarElemento(lista, marca);

    if (posicao != -1) {
        /* Removendo o elemento encontrado */
        for (i = posicao; i < lista->id - 1; ++i) {
            strcpy(lista->elementos[i].marca, lista->elementos[i + 1].marca);
            strcpy(lista->elementos[i].modelo, lista->elementos[i + 1].modelo);
            lista->elementos[i].velocidade = lista->elementos[i + 1].velocidade;
            lista->elementos[i].antenas = lista->elementos[i + 1].antenas;
            lista->elementos[i].portas = lista->elementos[i + 1].portas;
            strcpy(lista->elementos[i].sistemaOperacional, lista->elementos[i + 1].sistemaOperacional);
            lista->elementos[i].valor = lista->elementos[i + 1].valor;
        }

        /* Atualizando o contador da lista */
        --(lista->id);
        return 1;
    }

    return 0;
}

    

//Função responsável por retornar a quantidade de itens dentro da lista 
int tamanhoLista(Lista *lista){
    int contador = 0;
    for(int i = 0; i < lista->id; ++i){
        ++contador;
    }
    return contador;
}
