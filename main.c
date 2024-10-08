/****************************************************************** 
 * Nome: Lista com vetores                                        *
 * Descricao: Implementacao de lista com uso de vetores (array).  *
 *            Esse codigo possui as principais operacoes da       *
 *            lista, como:                                        *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista,                                      *
 *            tamanho da lista,                                   *
 *            carregar dados do arquivo,                          *
 *            salvar dados no arquivo.                            *
 * Autor: Mayrton Dias                                            *
 * Ultima alteracao: 07/10/2024                                   *
 ******************************************************************/

/*Include das bibliotecas*/ 
#include <stdio.h>
#include <stdlib.h>

/*Definicao das constantes*/ 
#define TAM 5
#define ARQUIVO "dados_lista.txt"

/*Definicao da estrutura*/ 
typedef struct{
    int id;
    int *elementos;
} Lista;

/*Funcoes implementadas*/
int atualizarElemento(Lista*, int, int);
int buscarElemento(Lista*, int);
Lista* criarLista();
Lista* excluirLista(Lista*);
void imprimirElementos(Lista*);
int inserirElemento(Lista*, int);
int inserirElementoID(Lista*, int, int);
int inserirElementoInicio(Lista*, int);
int removerElemento(Lista*, int);
int tamanho(Lista*);
int carregarDados(Lista*);
int salvarDados(Lista*);

int main(){
    /*Ponteiro usado para a criacao da lista*/
    Lista *lista = criarLista();

    /*Chamada das novas funcoes*/
    carregarDados(lista);
    imprimirElementos(lista);
    salvarDados(lista);

    printf("Tamanho da lista: %d\n", tamanho(lista));

    lista = excluirLista(lista);
    return 0;
}

/* Função: tamanho
 * Parametro: lista - ponteiro para a lista
 * Retorno: Quantidade de elementos na lista
 * Descricao: Retorna a quantidade de elementos presentes na lista
 */
int tamanho(Lista *lista) {
    if(lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    return lista->id;
}

/* Função: carregarDados
 * Parametro: lista - ponteiro para a lista
 * Retorno: 1 - se os dados foram carregados, 0 - caso contrario
 * Descricao: Carrega os dados de um arquivo para a lista
 */
int carregarDados(Lista *lista) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo para leitura\n");
        return 0;
    }

    int valor;
    while (fscanf(arquivo, "%d", &valor) != EOF) {
        if (!inserirElemento(lista, valor)) {
            printf("Falha ao inserir elemento do arquivo na lista\n");
            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

/* Função: salvarDados
 * Parametro: lista - ponteiro para a lista
 * Retorno: 1 - se os dados foram salvos, 0 - caso contrario
 * Descricao: Salva os dados da lista em um arquivo
 */
int salvarDados(Lista *lista) {
    int i;
	
	if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    FILE *arquivo = fopen(ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo para escrita\n");
        return 0;
    }

    for (i = 0; i < lista->id; ++i) {
        fprintf(arquivo, "%d\n", lista->elementos[i]);
    }

    fclose(arquivo);
    return 1;
}

/* Função: imprimirElementos
 * Parametro: lista - ponteiro para a lista
 * Descricao: Imprime todos os elementos da lista
 */
void imprimirElementos(Lista *lista) {
    int i;
	
	if (lista == NULL || lista->id == 0) {
        printf("A lista esta vazia ou nao foi criada\n");
        return;
    }

    printf("Elementos da lista:\n");
    for (i = 0; i < lista->id; ++i) {
        printf("%d ", lista->elementos[i]);
    }
    printf("\n");
}

/* Função: inserirElemento
 * Parametro: lista - ponteiro para a lista
 *            valor - valor do elemento a ser inserido
 * Retorno: 1 - se o elemento foi inserido, 0 - caso contrario
 * Descricao: Insere um elemento no final da lista
 */
int inserirElemento(Lista *lista, int valor) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    if (lista->id >= TAM) {
        printf("A lista esta cheia\n");
        return 0;
    }

    lista->elementos[lista->id] = valor;
    lista->id++;
    return 1;
}

/* Nome: atualizarElemento
 * Parametros: lista - ponteiro que possui o endereco lista
 *             busca - elemento que sera buscado na lista
 *             valor - novo valor do elemento que sera alterado 
 * Retorno: 1 - quando o valor e atualizado e 0 - caso contrario
 * Descricao: Funcao responsavel por atualizar um elemento
 *            da lista, caso o mesmo esteja na lista indicada
 */
int atualizarElemento(Lista *lista, int busca, int valor){
    int i;

    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    for(i = 0; i < lista->id; ++i){
        if(lista->elementos[i] == busca){
            lista->elementos[i] = valor;
            return 1;
        }
    }
    return 0;
}

/* Nome: buscarElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            valor - elemento que sera buscado na lista
 * Retorno: o indice do elemento encontrado, -1 caso contrario
 * Descricao: Funcao criada para buscar um elemento na lista
 */
int buscarElemento(Lista *lista, int valor){
    int i;

    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return -1;
    }

    for(i = 0; i < lista->id; ++i){
        if(lista->elementos[i] == valor){
            return i;
        }
    }
    return -1;
}

/* Nome: criarLista
 * Parametro: void 
 * Retorno: endereco do espaco de memoria reservado pelo malloc
 * Descricao: Funcao responsavel pela criacao da lista e inicializacao
 *            do campo id e alocacao do vetor de elementos
 */
Lista* criarLista(){
    Lista *nova = (Lista*)malloc(sizeof(Lista));

    if(nova == NULL){
        printf("Nao tem espaco\n");
        return NULL;
    }

    nova->id = 0; 
    nova->elementos = (int*)malloc(TAM * sizeof(int));

    if(nova->elementos == NULL){
        printf("Nao tem espaco\n");
        free(nova);
        return NULL;
    }

    return nova;
}

/* Nome: excluirLista
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: NULL para indicar que a lista foi excluida
 * Descricao: Funcao responsavel pela exclusao da lista
 */
Lista* excluirLista(Lista *lista){
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    free(lista->elementos);
    free(lista);
    return NULL;
}
