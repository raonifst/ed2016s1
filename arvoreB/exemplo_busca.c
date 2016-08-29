/*

O arquivo 'arvoreB.dat' é organizado da seguinte maneira:

|grau_minimo|RRN raiz|  //cabecalho
|n|chaves|filhos|tipo|  //varios registros



A árvore armazenada no arquivo tem o seguinte layout:


                                       50

                         20|30                 70|90|105

                   5|10  25|29  35|40    67|68  75|77  99|100  106|110

Questões:
1) Entenda e comente o código a seguir.
2) Escreva uma função que devolve a menor chave armazenada na árvore;
3) Escreva uma função que devolve a chave que antecede a chave atual na ordem crescente das chaves (chave predecessora).

data: 3 de abril de 2016 - atualizado em 29 de agosto de 2016
autor: rsilva at gmail dot com
*/

#include <stdio.h>
#include <stdlib.h>

#define TAM_NO(T) (4*T+1)*sizeof(int)

typedef enum{INTERNO, RAIZ, FOLHA} TipoNo;

typedef struct _noarvb {
    int *chaves;
    int *filhos; /*RRN dos registros dos filhos*/
    int n;       /*Quantidade de chaves armazenadas*/
    TipoNo tipo;
}NoArvB;

typedef struct _arvb {
    int grau_min;
    int raiz; /*RRN da raiz*/
}ArvB;

void excecao(char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(0);
}

void apagar_no(NoArvB **no)
{
    NoArvB *tmp = *no;
    free(tmp->chaves);
    free(tmp->filhos);
    free(tmp);
    *no = NULL;
}

NoArvB* ler_no(FILE* arq, int RRN, int t)
{
    NoArvB *no = malloc(sizeof(NoArvB));
    no->chaves = malloc(sizeof(int)*((2*t)-1));
    no->filhos = malloc(sizeof(int)*(2*t));

    fseek (arq, sizeof(ArvB) + TAM_NO(t)*RRN, SEEK_SET);

    fread(&(no->n), sizeof(int), 1, arq);
    fread(no->chaves, sizeof(int), (2*t)-1, arq);
    fread(no->filhos, sizeof(int), (2*t), arq);
    fread(&(no->tipo), sizeof(TipoNo), 1, arq);


    return no;
}

ArvB* ler_arvore(FILE* arq)
{
    ArvB* arvore = malloc(sizeof(ArvB));
    fread(arvore, sizeof(ArvB), 1, arq);

    return arvore;
}

void mostrar_chaves_no(NoArvB *no)
{
    int i;
    printf("***********************\n");
    printf("Informações do no\n");
    printf("Quantidade de chaves: %d\nChaves: ", no->n);
    for(i = 0; i < no->n; i++) printf("%d ", no->chaves[i]);
    printf("\nFilhos: "); if(no->tipo == FOLHA) printf("Nao ha.");
    if(no->tipo != FOLHA) for(i = 0; i <= no->n; i++) printf("%d ", no->filhos[i]);
    printf("\n");
    printf("***********************\n");
}

NoArvB* busca_ArvB(FILE* arq, ArvB* arv, NoArvB* raiz, int chave)
{
    NoArvB* tmp, *x = raiz;
    int i;

    while(x != NULL) {

        for(i = 0; i < x->n && chave > x->chaves[i]; i++) ;

        if(i < x->n  && chave == x->chaves[i])
            return x;

        if(x->tipo != FOLHA) {
            tmp = x;
            x = ler_no(arq, x->filhos[i], arv->grau_min);
            if(tmp != raiz)
                apagar_no(&tmp);
        }else {
	        if(x != NULL && x != raiz)
		        apagar_no(&x); 	    
            //x = NULL;
	      }
    }

    return x;
}



int main()
{
    FILE *arq = fopen("arvoreB.dat", "rb");
    int chave;

    if(arq  == NULL)
        excecao("Erro ao abrir arquivo da Arvore.\nImpossivel continuar.\n");

    ArvB* arvore = ler_arvore(arq);
    NoArvB* raiz = ler_no(arq, arvore->raiz, arvore->grau_min);
    
    /*
    mostrar_chaves_no(raiz);
    */
    printf("Informe uma chave a ser pesquisada: ");
    scanf("%d", &chave);
    NoArvB* no = busca_ArvB(arq, arvore, raiz, chave);
    

    if(no != NULL) {
        mostrar_chaves_no(no);
	      if(no != raiz) /*Evita que a raiz seja apagada duas vezes*/
        	apagar_no(&no);
    } else
        printf("Chave nao encontrada.\n");

    apagar_no(&raiz);
    free(arvore);

    fclose(arq);
    
    return 0;
}
