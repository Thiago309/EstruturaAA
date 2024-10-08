/****************************************************************** 
 * Nome: Lista com vetores                                        *																  *
 * Autor: Thiago Vinicius e Danilo Mendes                         *          
 * Ultima alteracao: 07/10/2024                                   *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

/* Estrutura para armazenar os dados dos produtos da farmácia */
typedef struct {
    int IdMed;
    char nomeMed[50];
    float precoMed;
    int quantidadeEmEstoque;
    char validade[15];
    char tipoMed[30];
} produtoFarmacia;

/* Estrutura para a lista de produtos */
typedef struct {
    int id;
    produtoFarmacia *elementos;
} Lista;

/* Prototipação das funções */
int atualizarElemento(Lista*, int, produtoFarmacia);
int buscarElemento(Lista*, int);
Lista* criarLista();
Lista* excluirLista(Lista*);
void imprimirElementos(Lista*);
int inserirElemento(Lista*, produtoFarmacia);
int inserirElementoID(Lista*, produtoFarmacia, int);
int inserirElementoInicio(Lista*, produtoFarmacia);
int removerElemento(Lista*, int);
int tamanho(Lista*);
void carregarDados(Lista*, const char*);
void salvarDados(Lista*, const char*);

int main() {
    Lista *lista = criarLista();
    produtoFarmacia produto;

    /* Exemplo de inicialização e inserção */
    produto = (produtoFarmacia){1, "Paracetamol", 5.99, 100, "12/2025", "Analgesico"};
    inserirElemento(lista, produto);

    produto = (produtoFarmacia){2, "Ibuprofeno", 9.49, 50, "06/2024", "Antiinflamatorio"};
    inserirElemento(lista, produto);

    imprimirElementos(lista);

    salvarDados(lista, "produtos.txt");
    return 0;
}

Lista* criarLista() {
    Lista *nova = (Lista*)malloc(sizeof(Lista));
    if (nova == NULL) {
        printf("Nao tem espaco\n");
        return NULL;
    }
    nova->id = 0; 
    nova->elementos = (produtoFarmacia*)malloc(TAM * sizeof(produtoFarmacia));
    if (nova->elementos == NULL) {
        printf("Nao tem espaco\n");
        free(nova);
        return NULL;
    }
    return nova;
}

void imprimirElementos(Lista *lista) {
    int i;
	
	if (lista == NULL || lista->id == 0) {
        printf("Lista vazia ou não criada\n");
        return;
    }
    for (i = 0; i < lista->id; ++i) {
        printf("ID: %d, Nome: %s, Preco: %.2f, Estoque: %d, Validade: %s, Tipo: %s\n",
               lista->elementos[i].IdMed, lista->elementos[i].nomeMed, 
               lista->elementos[i].precoMed, lista->elementos[i].quantidadeEmEstoque,
               lista->elementos[i].validade, lista->elementos[i].tipoMed);
    }
}

int inserirElemento(Lista *lista, produtoFarmacia produto) {
    if (lista == NULL || lista->id >= TAM) {
        printf("A lista nao foi criada ou espaco esgotado\n");
        return 0;
    }
    lista->elementos[lista->id] = produto;
    ++(lista->id);
    return 1;
}

void salvarDados(Lista *lista, const char *nomeArquivo) {
    int i;
	
	FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita\n");
        return;
    }
    for (i = 0; i < lista->id; ++i) {
        fprintf(arquivo, "%d,%s,%.2f,%d,%s,%s\n",
                lista->elementos[i].IdMed, lista->elementos[i].nomeMed,
                lista->elementos[i].precoMed, lista->elementos[i].quantidadeEmEstoque,
                lista->elementos[i].validade, lista->elementos[i].tipoMed);
    }
    fclose(arquivo);
}

void carregarDados(Lista *lista, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura\n");
        return;
    }
    produtoFarmacia produto;
    while (fscanf(arquivo, "%d,%49[^,],%f,%d,%14[^,],%29[^\n]\n",
                  &produto.IdMed, produto.nomeMed, &produto.precoMed, 
                  &produto.quantidadeEmEstoque, produto.validade, produto.tipoMed) != EOF) {
        inserirElemento(lista, produto);
    }
    fclose(arquivo);
}

int tamanho(Lista *lista) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    return lista->id;
}

Lista* excluirLista(Lista *lista) {
    if (lista != NULL) {
        free(lista->elementos);
        free(lista);
    }
    return NULL;
}
