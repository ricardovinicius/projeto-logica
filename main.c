#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <strings.h>
#include <stdbool.h>

#define MAX_WORDS 128
#define MAX_WORD_SIZE 128 // pneumonoultramicroscopicsilicovolcanoconiosis
#define MAX_ATOMICS 10 // máximo de símbolos proposicionais conforme a lista

int symbol_qtd = 0; // inicia uma variável global com a quantidade de simbolos atribuídos

int split_string(char *string, char **words);
void evaluate_operators(char** words, int size);
bool check_operator(char* word);
int check_free_symbol(char** atomics);
char* returns_free_symbol(int value);
bool check_atomic(char* word);
void evaluate_atomics(char** words, int size, char** atomics);
void print_sentence(char** words, int size);
void print_atomics(char** atomics);


int main(void)
{
    char *words[MAX_WORDS]; // inicia um array de ponteiros pra strings

    char *string = malloc(MAX_WORD_SIZE * MAX_WORDS * sizeof(char));
    //char string[MAX_WORD_SIZE * MAX_WORDS] = 
    //"Se fizer sol e for domingo, então vou a praia, e se fizer chuva então ficarei em casa";
    
    printf("Escreva a frase: \n");

    fgets(string, MAX_WORD_SIZE * MAX_WORDS * sizeof(char), stdin);
    int size = split_string(string, words);
    
    evaluate_operators(words, size);

    char *atomics[MAX_ATOMICS] = {"", "", "", "", "", "", "", "", "", ""};

    evaluate_atomics(words, size, atomics);
    
    //for(int i = 0; i < size; i++)
    //{
    //    printf("%s ", words[i]);
    //}
    //printf("\n");

    print_sentence(words, size);
    print_atomics(atomics);
}

// functions that splits a string in words, and add each word inside a array of strings
// returns how much words was extracted
int split_string(char *string, char **words)
{
    char *token = strtok(string, " ");
    // loop through the string to extract all other tokens
    int i = 0;

    while( token != NULL ) {
        words[i] = token;
        token = strtok(NULL, " ");
        i++;
    }

    return i;
}

void evaluate_operators(char** words, int size)
{
    //find the implications
    for(int i = 0; i < size; i++)
    {
        if(strcasecmp(words[i], "então") == 0)
        {
            strcpy(words[i], "->");
        }

    }

    for(int i = 0; i < size; i++)
    {
        if(strcasecmp(words[i], "ou") == 0)
        {
            strcpy(words[i], "∨");
        }

    }

    for(int i = 0; i < size; i++)
    {
        if(strcasecmp(words[i], "e") == 0 && strcasecmp(words[i + 1], "somente") != 0)
        {
            strcpy(words[i], "&");
        }
    }

    for(int i = 0; i < size; i++)
    {
        if(strcasecmp(words[i], "sse") == 0)
        {
            strcpy(words[i], "<->");
        }
    }

    for(int i = 0; i < size; i++)
    {
        if(strcasecmp(words[i], "não") == 0)
        {
            strcpy(words[i], "¬");
        }
    }

    for(int i = 0; i < size; i++)
    {
        //printf("palavra atual: %s\n", words[i]);
        if(strcasecmp(words[i], "se") == 0)
        {
            if(i != 0)
            {
                if(strcasecmp(words[i + 1], "e") == 0 && strcasecmp(words[i + 2], "somente") == 0)
                {
                    strcpy(words[i + 1], "<->");
                }
                else if(strcasecmp(words[i-1], "somente") == 0)
                {
                    strcpy(words[i - 1], "<->");
                }
            }
        }
    }
}

void evaluate_atomics(char** words, int size, char** atomics)
{
    for(int i = 0; i < size; i++)
    {
        if(check_operator(words[i]) == true)
        {
            if(check_atomic(words[i - 1]) == false) // checa se não há uma precedência de um átomo
            {
                int j = i;
                do
                {
                    j--;
                }
                while((check_operator(words[j]) == false) && (j >= 0));

                char* atomic = malloc((sizeof(char) * MAX_WORD_SIZE) * ((i - j) + 1)); // aloca um espaço em
                                                                                    // memória pra a quantidade
                                                                                    // de palavras do átomo
                                                                                    // com + 1 de folga

                for(int k = j + 1; k < i; k++)          // concatena as palavras numa só string
                {
                    if(strcasecmp(words[k], "se") != 0)
                    {
                        strcat(atomic, words[k]);
                        strcat(atomic, " ");
                    //strcpy(words[k], " "); // conforme vai percorrendo as palavras do átomo, atribui o valor NULL
                                    // tendo em vista que eles vão estar numa só string
                    }
                }
                //printf("%s\n", atomic);
            

                atomics[check_free_symbol(atomics)] = atomic; // atribui o ponteiro da string concatenada na posição mais anterior
                words[i - 1] = returns_free_symbol(check_free_symbol(atomics)); // atribui um simbolo 
                                                                                // proposicional disponível
            }

            // agora repete para o lado direito do operador
            int j = i;
            do
            {
                j++;
            }
            while((j < size) && (check_operator(words[j]) == false));

            char* atomic = malloc((sizeof(char) * MAX_WORD_SIZE) * ((j - i) + 1)); // aloca um espaço em
                                                                                // memória pra a quantidade
                                                                                // de palavras do átomo
                                                                                // com + 1 de folga

            for(int k = i + 1; k < j; k++)          // concatena as palavras numa só string
            {
                if(strcasecmp(words[k], "se") != 0)
                {
                    strcat(atomic, words[k]);
                    strcat(atomic, " ");
                //strcpy(words[k], " "); // conforme vai percorrendo as palavras do átomo, atribui o valor NULL
                                // tendo em vista que eles vão estar numa só string
                }

            }
            //printf("%s\n", atomic);

            atomics[check_free_symbol(atomics)] = atomic; // atribui o ponteiro da string concatenada na posição mais anterior
            words[j - 1] = returns_free_symbol(check_free_symbol(atomics)); // atribui um simbolo 
                                                                            // proposicional disponível
        }
    }
}

bool check_operator(char* word)
{
    if(strcasecmp(word, "->") == 0 ||
    strcasecmp(word, "<->") == 0 ||
    strcasecmp(word, "&") == 0 ||
    strcasecmp(word, "¬") == 0 ||
    strcasecmp(word, "∨") == 0 
    ) 
    {
        return true;
    }
    
    return false;
}

int check_free_symbol(char** atomics) // avalia qual posição do array dos átomos está disponível
{
        for(int i = 0; i < MAX_ATOMICS; i++)
        {
            if(strcmp(atomics[i], "") == 0)
            {
                return i;
            }
        }
}

char* returns_free_symbol(int value)
{
    switch (value)
    {
        case 1:
            return "symbol_M";
        case 2:
            return "symbol_N";
        case 3:
            return "symbol_O";
        case 4:
            return "symbol_P";
        case 5:
            return "symbol_Q";
        case 6:
            return "symbol_R";
        case 7:
            return "symbol_S";
        case 8:
            return "symbol_U";
        case 9:
            return "symbol_V";
        case 10:
            return "symbol_Z";
    }
}

bool check_atomic(char* word)
{
    if(
    strcasecmp(word, "symbol_M") == 0 ||
    strcasecmp(word, "symbol_N") == 0 ||
    strcasecmp(word, "symbol_O") == 0 ||
    strcasecmp(word, "symbol_P") == 0 ||
    strcasecmp(word, "symbol_Q") == 0 ||
    strcasecmp(word, "symbol_R") == 0 ||
    strcasecmp(word, "symbol_S") == 0 ||
    strcasecmp(word, "symbol_U") == 0 ||
    strcasecmp(word, "symbol_V") == 0 ||
    strcasecmp(word, "symbol_Z") == 0)
    {
        return true;
    }

    return false;
}

void print_sentence(char** words, int size)
{
    for(int i = 0; i < size; i++)
    {
        if(check_operator(words[i]) == true)
        {
            printf("%s ", words[i]);
        }
        else if(check_atomic(words[i]) == true)
        {
            printf("%c ", words[i][7]);
        }
    }
    printf("\n");
}

void print_atomics(char** atomics)
{
    int i = 0;  

    while((strcmp(atomics[i], "") != 0) || i > MAX_ATOMICS)
    {
        printf("%c: %s\n", returns_free_symbol(i + 1)[7], atomics[i]);
        i++;
    }
}