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
    int jogada;
} jogador;

FILE *arquivo_leitura;
jogador j[3];

void lista_operacoes();
void imprimir_banco_de_dados();
void adicionar_ao_banco_de_dados();
void sortear_palavra(char Pi[], char Pa[][MAXCARC], int *k);
float sortear_valor_letra();
void exibir_tela(char Pi[], int n, char Pa[][MAXCARC], int comp[][MAXCARC]);

int main()
{
    setlocale(LC_ALL, "");

    char codigo, letra;
    char Pista_da_rodada[MAXCARC],Palavra[MAXPAL][MAXCARC], Palavras_da_rodada[MAXPAL][MAXCARC];
    int senha, i, k, Qtd_da_rodada, letras_faltando, cont;
    int Matriz_de_comparacao[MAXPAL][MAXCARC];
    float valor;

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
                Qtd_da_rodada = letras_faltando = 0;
                for(i = 0; i < MAXPAL; i++)
                    strcpy(Palavras_da_rodada[i], "");
                for(i = 0; i < MAXPAL; i++)
                    for(k = 0; k < MAXCARC; k++)
                        Matriz_de_comparacao[i][k] = 0;

                printf("\nOlá vamos iniciar! Por favor insira o nome de cada jogador\n");
                for(i = 0; i < 3; i++)
                {
                    printf("\nQual o nome do jogador %d: ", i+1);
                    fflush(stdin); scanf("%s", &j[i].nome);
                    j[i].valor = j[i].jogada = 0;
                }

                sortear_palavra(Pista_da_rodada, Palavras_da_rodada, &Qtd_da_rodada);

                for (i = 0; i < Qtd_da_rodada; i++)
                {
                    for (k = 0; k < strlen(Palavras_da_rodada[i]); k++)
                    {
                        if (Palavras_da_rodada[i][k] != '\0')
                        {
                            Matriz_de_comparacao[i][k] = 1;
                            letras_faltando ++;
                        }
                    }
                }

                j[0].jogada = 1;
                while(letras_faltando > 0)
                {
                    if (j[0].jogada == 1)
                    {
                        exibir_tela(Pista_da_rodada, Qtd_da_rodada, Palavras_da_rodada, Matriz_de_comparacao);

                        if(letras_faltando > 3)
                        {
                            printf("\n\nRoda a roda!\n");
                            system("pause");
                            valor = sortear_valor_letra();

                            if(valor == 0)
                            {
                               printf("\nPASSA A VEZ");
                               printf("\n\nA vez será passada para %s\n", j[1].nome);
                               j[0].jogada = 0;
                               j[1].jogada = 1;
                            }
                            else
                            {
                                if(valor > 0 && valor < 0.02)
                                {
                                    printf("\nPERDEU TUDO");
                                    printf("\n\nA vez será passada para %s\n", j[1].nome);
                                    j[0].valor = 0;
                                    j[0].jogada = 0;
                                    j[1].jogada = 1;
                                }
                                else
                                {
                                    cont = 0;
                                    do
                                    {
                                        printf("\nUma letra por R$ %.0f,00: ", valor);
                                        fflush(stdin); scanf("%c", &letra);
                                        letra = toupper(letra);
                                    }while (cont != 0);

                                    cont = 0;
                                    for (i = 0; i < Qtd_da_rodada; i++)
                                    {
                                        for (k = 0; k < strlen(Palavras_da_rodada[i]); k++)
                                        {
                                            if (Palavras_da_rodada[i][k] == letra)
                                            {
                                                Matriz_de_comparacao[i][k] = 0;
                                                j[0].valor = j[0].valor + valor;
                                                cont ++;
                                            }
                                        }
                                    }
                                    if(cont == 0)
                                    {
                                        printf("\nNão existe letra %c na palavra.", letra);
                                        printf("\n\nA vez será passada para %s\n", j[1].nome);
                                        j[0].jogada = 0;
                                        j[1].jogada = 1;
                                    }
                                    letras_faltando = letras_faltando - cont;
                                }
                            }
                        }
                        else
                        {
                            valor = sortear_valor_letra();
                            if (valor == 0)
                            {
                                printf("\n\nPASSA A VEZ");
                                printf("\n\nA vez será passada para %s\n", j[1].nome);
                                j[0].jogada = 0;
                                j[1].jogada = 1;
                            }
                            else
                            {
                                if(valor > 0 && valor < 0.02)
                                {
                                    printf("\n\nPERDEU TUDO");
                                    printf("\n\nA vez será passada para %s\n", j[1].nome);
                                    j[0].valor = 0;
                                    j[0].jogada = 0;
                                    j[1].jogada = 1;
                                }
                                else
                                {
                                    j[0].jogada = j[1].jogada = j[2].jogada = 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        if (j[1].jogada == 1)
                        {
                            exibir_tela(Pista_da_rodada, Qtd_da_rodada, Palavras_da_rodada, Matriz_de_comparacao);

                            if(letras_faltando > 3)
                            {
                                printf("\n\nRoda a roda!\n");
                                system("pause");
                                valor = sortear_valor_letra();

                                if(valor == 0)
                                {
                                   printf("\n\nPASSA A VEZ");
                                   printf("\n\nA vez será passada para %s\n", j[2].nome);
                                   j[1].jogada = 0;
                                   j[2].jogada = 1;
                                }
                                else
                                {
                                    if(valor > 0 && valor < 0.02)
                                    {
                                        printf("\n\nPERDEU TUDO");
                                        printf("\n\nA vez será passada para %s\n", j[2].nome);
                                        j[1].valor = 0;
                                        j[1].jogada = 0;
                                        j[2].jogada = 1;
                                    }
                                    else
                                    {
                                        printf("\nUma letra por R$ %.0f,00: ", valor);
                                        fflush(stdin); scanf("%c", &letra);
                                        letra = toupper(letra);
                                        cont = 0;
                                        for (i = 0; i < Qtd_da_rodada; i++)
                                        {
                                            for (k = 0; k < strlen(Palavras_da_rodada[i]); k++)
                                            {
                                                if (Palavras_da_rodada[i][k] == letra)
                                                {
                                                    Matriz_de_comparacao[i][k] = 0;
                                                    j[1].valor = j[1].valor + valor;
                                                    cont ++;
                                                }
                                            }
                                        }
                                        if(cont == 0)
                                        {
                                            printf("\nNão existe letra %c na palavra.", letra);
                                            printf("\n\nA vez será passada para %s\n", j[2].nome);
                                            j[1].jogada = 0;
                                            j[2].jogada = 1;
                                        }
                                        letras_faltando = letras_faltando - cont;
                                    }
                                }
                            }
                            else
                            {
                                valor = sortear_valor_letra();
                                if (valor == 0)
                                {
                                    printf("\n\nPASSA A VEZ");
                                    printf("\n\nA vez será passada para %s\n", j[2].nome);
                                    j[1].jogada = 0;
                                    j[2].jogada = 1;
                                }
                                else
                                {
                                    if(valor > 0 && valor < 0.02)
                                    {
                                        printf("\n\nPERDEU TUDO");
                                        printf("\n\nA vez será passada para %s\n", j[2].nome);
                                        j[1].valor = 0;
                                        j[1].jogada = 0;
                                        j[2].jogada = 1;
                                    }
                                    else
                                    {
                                        j[0].jogada = j[1].jogada = j[2].jogada = 0;
                                    }
                                }
                            }
                        }
                        else
                        {
                            if (j[2].jogada == 1)
                            {
                                exibir_tela(Pista_da_rodada, Qtd_da_rodada, Palavras_da_rodada, Matriz_de_comparacao);

                                if(letras_faltando > 3)
                                {
                                    printf("\n\nRoda a roda!\n");
                                    system("pause");
                                    valor = sortear_valor_letra();

                                    if(valor == 0)
                                    {
                                       printf("\n\nPASSA A VEZ");
                                       printf("\n\nA vez será passada para %s\n", j[0].nome);
                                       j[2].jogada = 0;
                                       j[0].jogada = 1;
                                    }
                                    else
                                    {
                                        if(valor > 0 && valor < 0.02)
                                        {
                                            printf("\n\nPERDEU TUDO");
                                            printf("\n\nA vez será passada para %s\n", j[0].nome);
                                            j[2].valor = 0;
                                            j[2].jogada = 0;
                                            j[0].jogada = 1;
                                        }
                                        else
                                        {
                                            printf("\nUma letra por R$ %.0f,00: ", valor);
                                            fflush(stdin); scanf("%c", &letra);
                                            letra = toupper(letra);
                                            cont = 0;
                                            for (i = 0; i < Qtd_da_rodada; i++)
                                            {
                                                for (k = 0; k < strlen(Palavras_da_rodada[i]); k++)
                                                {
                                                    if (Palavras_da_rodada[i][k] == letra)
                                                    {
                                                        Matriz_de_comparacao[i][k] = 0;
                                                        j[2].valor = j[2].valor + valor;
                                                        cont ++;
                                                    }
                                                }
                                            }
                                            if(cont == 0)
                                            {
                                                printf("\nNão existe letra %c na palavra.", letra);
                                                printf("\n\nA vez será passada para %s\n", j[0].nome);
                                                j[2].jogada = 0;
                                                j[0].jogada = 1;
                                            }
                                            letras_faltando = letras_faltando - cont;
                                        }
                                    }
                                }
                                else
                                {
                                    valor = sortear_valor_letra();
                                    if (valor == 0)
                                    {
                                        printf("\n\nPASSA A VEZ");
                                        printf("\n\nA vez será passada para %s\n", j[0].nome);
                                        j[2].jogada = 0;
                                        j[0].jogada = 1;
                                    }
                                    else
                                    {
                                        if(valor > 0 && valor < 0.02)
                                        {
                                            printf("\n\nPERDEU TUDO");
                                            printf("\n\nA vez será passada para %s\n", j[0].nome);
                                            j[2].valor = 0;
                                            j[2].jogada = 0;
                                            j[0].jogada = 1;
                                        }
                                        else
                                        {
                                            j[0].jogada = j[1].jogada = j[2].jogada = 0;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                printf("Fim de Jogo. Não houve ganhador");
                                letras_faltando = 0;
                            }
                        }
                    }
                }
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

float sortear_valor_letra()
{
    float valor;
    int Qtd_registros;

    arquivo_leitura = fopen("premios.dat", "rb");
    if (arquivo_leitura == NULL)
    {
        printf("\n\tProblemas na abertura do arquivo\n\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        fseek(arquivo_leitura, 0, SEEK_END);
        Qtd_registros = ftell(arquivo_leitura)/sizeof(valor);
        fseek(arquivo_leitura, 0, SEEK_SET);

        srand(time(NULL));
        fseek(arquivo_leitura, (rand() % Qtd_registros)*sizeof(valor) , SEEK_CUR);

        fread(&valor, sizeof(valor), 1, arquivo_leitura);

        fclose(arquivo_leitura);
    }
    return valor;
}

void exibir_tela(char Pi[], int n, char Pa[][MAXCARC], int comp[][MAXCARC])
{
    int i, k;

    printf("\n\tA palavra está associada com: \t%s\n", Pi);
    for (i = 0; i < n; i++)
    {
        printf("\n\t\t\t");
        for (k = 0; k < strlen(Pa[i]); k++)
        {
            if (comp[i][k] == 0)
                printf(" %c", Pa[i][k]);
            if (comp[i][k] == 1)
                printf(" _");
        }
        printf("\n");
    }
    printf("\n\n\t%-20s%-20s%-20s\n", j[0].nome, j[1].nome, j[2].nome);
    printf("\t===========\t    ===========\t\t===========\n");
    printf("\tR$ %5d,00\t    R$ %5d,00\t\tR$ %5d,00\n", j[0].valor, j[1].valor, j[2].valor);
}
