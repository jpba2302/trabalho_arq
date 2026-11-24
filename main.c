#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Matriz {
    int **dados;
    int altura;
    int largura;
    int max;
};
typedef struct Matriz Matriz;

struct Nodo {
    char caractere;
    int frequencia;
    struct Nodo *esquerda;
    struct Nodo *direita;
};
typedef struct Nodo Nodo;

/**
 * Aloca memória para uma matriz e preenche com valores aleatórios até max
 * @param largura largura da matriz
 * @param altura altura da matriz
 * @param max valor máximo que pode ser gerado aleatoriamente
 * @return NULL se não for possível alocar memória ou matriz com posições preenchidas
 */

int **cria_dados_matriz (int largura, int altura, int max)
{

    int **dados = NULL;
    dados = (int**)malloc(sizeof(int*)*altura);
    if (dados == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    int i, j;
    for (i = 0;i < altura;i++) {
        dados[i] = (int*)malloc(sizeof(int)*largura);
    }

    for (i = 0;i < altura;i++) {
        for (j = 0;j < largura;j++) {
            dados[i][j] = rand() % max;
        }
    }

    return dados;
}

/**
 * Cria uma matriz completa com os dados preenchidos
 * @param largura largura da matriz
 * @param altura altura da matriz
 * @param max valor máximo das posições da matriz
 * @return Matriz preenchida ou NULL caso a alocação falhar
 */

Matriz *cria_matriz (int largura, int altura, int max)
{
    Matriz *aux = NULL;
    aux = (Matriz*)malloc(sizeof(Matriz));
    if (aux == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }
    aux->largura = largura;
    aux->altura = altura;

    aux->dados = cria_dados_matriz(largura, altura, max);

    return aux;
}

void imprime_matriz (Matriz *matriz)
{
    int i, j;
    for (i = 0;i < matriz->altura;i++)
    {
        for (j = 0;j < matriz->largura;j++)
        {
            printf("|%d|",matriz->dados[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Cria uma matriz e preenche ela com os valores da multiplicação da matriz_1 com a matriz_2
 * @param matriz_1 matriz que contém as linhas que serão multiplicadas
 * @param matriz_2 matriz que contém as colunas que serão multiplicadas
 */

Matriz *multiplica_matriz (Matriz *matriz_1, Matriz *matriz_2)
{
    if (matriz_1->altura != matriz_2->altura || matriz_1->largura != matriz_2->largura)
    {
        printf("Impossível multiplicar essas duas matrizes\n");
        return NULL;
    }

    Matriz *matriz_3 = cria_matriz(matriz_1->largura, matriz_1->altura, matriz_1->max);
    int i, j, k;
    for (i = 0;i < matriz_1->altura;i++)
    {
        for (j = 0;j < matriz_2->largura;j++)
        {
                int resultado = 0;
                for (k = 0;k < matriz_1->largura;k++)
                {
                    resultado = (matriz_1->dados[i][k] * matriz_2->dados[k][j]) + resultado;
                }
                matriz_3->dados[i][j] = resultado;
        }
    }
    return matriz_3;
}

int copia_arquivo (char* arquivo_origem, char* arquivo_destino)
{
    FILE *arq_ori;
    FILE *arq_des;
    arq_ori = fopen(arquivo_origem,"rb");
    if (arq_ori == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    arq_des = fopen(arquivo_destino,"wb");
    if (arq_des == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        fclose(arq_ori);
        return 1;
    }
    fseek(arq_ori,0,SEEK_END);
    int tamanho = ftell(arq_ori);
    fseek(arq_ori,0,SEEK_SET);
    int i;
    for (i = 0;i < tamanho;i++)
    {
        int bin = fgetc(arq_ori);
        fputc(bin, arq_des);
    }
    fclose(arq_ori);
    fclose(arq_des);
}

/**
 * Usa o bubblesort para ordenar uma string
 */

void ordena_string (char *s)
{
    int i, j;
    int tamanho = strlen(s);
    for (i = 0;i < tamanho - 1;i++)
    {
        for (j = 0;j < tamanho - 1;j++)
        {
            if (s[j] > s[j + 1])
            {
                char aux = s[j];
                s[j] = s[j + 1];
                s[j + 1] = aux;
            }
        }
    }
}

/**
 * Cria um nodo sem filhos e preenche com o caractere que ele representa e a frequência desse caractere em uma string
 */

Nodo *cria_nodo (char caractere, int frequencia)
{
    Nodo *aux = NULL;
    aux = (Nodo*)malloc(sizeof(Nodo));
    if (aux == NULL)
    {
        printf("Erro ao alocar memória\n");
        return NULL;
    }
    aux->caractere = caractere;
    aux->frequencia = frequencia;
    aux->esquerda = NULL;
    aux->direita = NULL;
}

/**
 * INCOMPLETO!!!
 */

void conta_caracteres (char *s)
{
    int tamanho = strlen(s);
    int i = 0;
    int frequencia = 0;
    char letra = s[i];
    char letra_aux = s[i];
    letra = s[0];
    while (i < tamanho)
    {
        while (letra == letra_aux)
        {
            frequencia++;
            i++;
            letra_aux = s[i];
        }
        cria_nodo(letra, frequencia);
        letra = s[i];
        frequencia = 0;
    }
}

/**
 * Recebe uma string ordenada e conta quantos caracteres diferentes ela tem
 * NÃO VAI SER USADA PROVAVELMENTE SÓ PRA TESTAR
 */

int conta_caracteres_diferentes (char *s)
{
    int tamanho = strlen(s);
    int i = 0;
    char letra = s[i];
    char letra_aux = s[i];
    int caracteres_diferentes = 0;
    for (i = 0;i < tamanho;i++)
    {
        letra_aux = s[i];
        if (letra != letra_aux)
        {
            letra = s[i];
            caracteres_diferentes++;
        }
    }
    return caracteres_diferentes;
}

int main() {

     //MULTIPLICAÇÃO DE MATRIZES
     /*
    srand(time(NULL));
    int largura = 3;
    int altura = 3;
    int valor_max = 3;
    Matriz *matriz_1 = cria_matriz(largura, altura, valor_max);
    Matriz *matriz_2 = cria_matriz(largura, altura, valor_max);
    imprime_matriz(matriz_1);
    imprime_matriz(matriz_2);
    Matriz *matriz_3 = multiplica_matriz(matriz_1, matriz_2);
    imprime_matriz(matriz_3);
    */

    //copia_arquivo("capa_archangels.png","copia.png");

    char *palavra;
    printf("Digite uma palavra: ");
    fgets(palavra,30,stdin);

    ordena_string(palavra);
    printf("%s\n",palavra);
    int diferentes = conta_caracteres_diferentes(palavra);
    printf("%d\n",diferentes);

    return 0;
}
