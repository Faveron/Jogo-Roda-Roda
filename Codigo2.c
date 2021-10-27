#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define SENHA 8943581
#define MAXCARC 17
#define MAXPAL 3

typedef struct
{
    char Pista[MAXCARC];
    int Qtd;
    char Palavras[MAXPAL][MAXCARC];
} dados;

typedef struct
{
    char nome[MAXCARC];
    int valor;
} jogador;

FILE *arquivo_leitura;

void lista_operacoes();
void imprimir_banco_de_dados();
void adicionar_ao_banco_de_dados();
void sortear_palavra(char Pi[], char Pa[][MAXCARC], int *k);

int main()
{
    setlocale(LC_ALL, "");

    char codigo;
    char Pista_da_rodada[MAXCARC], Palavras_da_rodada[MAXPAL][MAXCARC];
    int senha, i, k, Qtd_da_rodada;
    int Matriz_de_comparacao[MAXPAL][MAXCARC];
    jogador j[3];

    printf("BEM-VIMDO ao jogo Roda a Roda\n");
    lista_operacoes();
    printf("\nDigite o código da operação : ");
    fflush(stdin); scanf("%c", &codigo);

    while (codigo != 'f')
    {
        switch (codigo)
        {
            case 'j' :
                strcpy(Pista_da_rodada, "");
                Qtd_da_rodada = 0;
                for(i = 0; i < MAXPAL; i++)
                    strcpy(Palavras_da_rodada[i], "");
                for(i = 0; i < MAXPAL; i++)
                    for(k = 0; k < MAXCARC; k++)
                        Matriz_de_comparacao[i][k] = 0;

                sortear_palavra(Pista_da_rodada, Palavras_da_rodada, &Qtd_da_rodada);

                printf("\nOlá vamos iniciar! Por favor insira o nome de cada jogador\n");
                for(i = 0; i < 3; i++)
                {
                    printf("\nQual o nome do jogador %d: ", i+1);
                    fflush(stdin); scanf("%s", &j[i].nome);
                    j[i].valor = 0;
                }
                /*
                printf("\n\n\t\tA palavra está associada com: %s\n", Pista_da_rodada);

                for (i = 0; i < Qtd_da_rodada; i++)
                {
                    printf("\n\t\t\t\t\t");
                    for (k = 0; k < strlen(Palavras_da_rodada[i]); k++)
                    {
                        if (Palavras_da_rodada[i][k] != '\0');
                        {
                            printf(" _");
                            Matriz_de_comparacao[i][k] = 1;
                        }
                    }
                    printf("\n");
                }
                */
                break;

            case 'a' :
                printf("\nDigite a senha para acesso ao banco de dados: ");
                fflush(stdin); scanf("%d", &senha);
                if (senha == SENHA)
                    adicionar_ao_banco_de_dados();
                else
                    printf("\nSenha inválida.\n");
                break;

            case 'v' :
                printf("\nDigite a senha para acesso ao banco de dados: ");
                fflush(stdin); scanf("%d", &senha);
                if (senha == SENHA)
                    imprimir_banco_de_dados();
                else
                    printf("\nSenha inválida.\n");
                break;

            default  :
                printf("\nCódigo ( %c )inválido.\n", codigo);
        }
        for(i = 0; i < 114 ; i++)
            printf("-");
        printf("\n");
        lista_operacoes();
        printf("\nDigite o código da operação : ");
        fflush(stdin); scanf("%c", &codigo);
    }
}

void lista_operacoes()
{
    printf("\n  j - Jogar"
           "\n  a - Acrecentar ao banco de dados"
           "\n  v - Visualizar banco de dados"
           "\n  f - finalizar\n");
}

void imprimir_banco_de_dados()
{
    int i;
    char opc;
    dados d;

    arquivo_leitura = fopen("palavras.dat", "rb");
    if (arquivo_leitura == NULL)
    {
        printf("\n\tProblemas na abertura do arquivo\n\tNão existe o banco de dados");
        printf ("\n\nDeseja criar um banco de dados? [s/S = sim] [n/N = não]: ");
        fflush(stdin); scanf("%c",&opc);
        if(opc == 's' || opc == 'S')
            adicionar_ao_banco_de_dados();
        else
            exit(EXIT_FAILURE);
    }
    else
    {
        printf("\n       DICA      |"
               " QUANTIDADE DE PALAVRAS|"
               "                                PALAVRAS\n");
        for(i = 0; i < 114 ; i++)
            printf("-");
        printf("\n");
        while (!feof(arquivo_leitura))
        {
            fread(&d, sizeof(d), 1, arquivo_leitura);
            if(!feof(arquivo_leitura))
            {
                printf("%-17s| \t %-16d|", d.Pista, d.Qtd);
                for(i = 0; i < d.Qtd; i++)
                    printf("\t%-17s", d.Palavras[i]);
            }
            printf("\n");
        }
    }
    printf("Existem %d registros no banco de dados\n", ftell(arquivo_leitura)/sizeof(d));
    fclose(arquivo_leitura);
}

void adicionar_ao_banco_de_dados()
{
    int i;
    char opc;
    dados d;

    arquivo_leitura = fopen("palavras.dat", "ab");
    if (arquivo_leitura == NULL)
        printf("\n\tProblemas na abertura do arquivo\n\n");
    else
    {
        do
        {
            printf("\nDigite a dica (minímo 1 caracter e máximo 17 caracteres): ");
            fflush(stdin); scanf("%s",d.Pista);
            printf("\nDigite quantas palavras (minímo 1 e máximo 3): ");
            fflush(stdin); scanf("%d",&d.Qtd);
            if (d.Qtd > MAXPAL || d.Qtd < 1)
            {
                printf("\nQuantidade de palavras inválido ");
                printf ("\n\nDeseja recomeçar o cadastro? [s/S = sim] [n/N = não]:");
                fflush(stdin); scanf("%c",&opc);
                printf("\n");
            }
            else
            {
                for(i = 0; i < d.Qtd; i++)
                {
                    printf("\nDigite %dº palavra palavras (minímo 1 caracter e máximo 17 caracteres): ", i + 1);
                    fflush(stdin); scanf("%s",d.Palavras[i]);
                }
                fwrite(&d, sizeof(d), 1, arquivo_leitura);
                printf ("\nDeseja cadastrar outro? [s/S = sim] [n/N = não]: ");
                fflush(stdin); scanf("%c",&opc);
                printf("\n\n");
            }
        }while ( opc == 's' || opc == 'S');
    }
    fclose(arquivo_leitura);
}

void sortear_palavra(char Pi[], char Pa[][MAXCARC], int *k)
{
    int Qtd_registros, n, i;
    char opc;
    dados d;

    arquivo_leitura = fopen("palavras.dat", "rb");
    if (arquivo_leitura == NULL)
    {
        printf("\n\tProblemas na abertura do arquivo\n\tNão existe o banco de dados para iniciar o jogo");
        printf ("\n\nDeseja criar um banco de dados? [s/S = sim] [n/N = não]: ");
        fflush(stdin); scanf("%c",&opc);
        if(opc == 's' || opc == 'S')
            adicionar_ao_banco_de_dados();
        else
            exit(EXIT_FAILURE);
    }
    else
    {
        fseek(arquivo_leitura, 0, SEEK_END);
        Qtd_registros = ftell(arquivo_leitura)/sizeof(d);
        fseek(arquivo_leitura, 0, SEEK_SET);

        srand(time(NULL));
        fseek(arquivo_leitura, (rand() % Qtd_registros)*sizeof(d) , SEEK_CUR);

        fread(&d, sizeof(d), 1, arquivo_leitura);
        strcpy(Pi, d.Pista);
        *k = d.Qtd;
        for(i = 0; i < d.Qtd; i++)
            strcpy(Pa[i], d.Palavras[i]);
    }
    fclose(arquivo_leitura);
}
