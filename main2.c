#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_LENGTH_PHRASE 4096
#define MAX_LENGTH_CLAUSE 256
#define flag int

typedef struct atomic
{
    char symbol;
    char* phrase;
}
atomic;

typedef struct sentence
{
    struct sentence *first; // if is a atomic sentence, represents the sentence itself
    struct sentence *next; // NULL if is a atomic sentence
    flag operator; // only if is a complex sentence
    atomic atomic; // only if is a atomic sentence
    flag negative; // flag that means if the sentence is negatived or not; 0 = non negatived, 1 = negatived
}
sentence;



char* split_string(char *v);

int main(void)
{
    char *n = malloc((sizeof(char) * MAX_LENGTH_PHRASE));

    n = "Se for a praia bla bla";

    printf("a\n");

    split_string(n);
    
}


char* split_string(char *v)
{
    // TODO: Função pra splitar a string em um array de palavras na memória 
 
    // Returns first token
    char *token = strtok(v, " ");
   
    while (token != NULL)
    {
        token = strtok(v, " ");
        printf("%s\n", token);
    }
 
}

// function that reads a sentence in natural language and returns a sentence struct 
sentence read_phrase(char *v  )
{
    // TODO: escrever uma função que consiga ler uma string e criar uma sentença lógica a partir dela

    // TODO: escrever um procedimento que leia negações
    int i;
    while(v[i] != " ")
    {

    }

    if(strcmp(v[0], "Se") == 0)
    {
        int inicio = i;
        do
        {
            i++;
        }
        while(strcmp(v[i], "então") == 0);
        int fim  = i;

        sentence *n = malloc(sizeof(sentence));

    }
    // TODO: escrever um procedimento que leia implicação

    // TODO: escrever um procedimento que leia bi-implicação 

    // TODO: escrever um procedimento que leia conjunção

    // TODO: escrever um procedimento que leia disjunção

    // TODO: escrever um procedimento que leia sentenças atômicas
}