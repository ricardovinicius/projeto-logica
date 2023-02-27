#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_LENGTH_PHRASE 4096;
#define MAX_LENGTH_CLAUSE 256;
#define flag uint8_t;

typedef struct sentence
{
    sentence first; // if is a atomic sentence, represents the sentence itself
    sentence next; // NULL if is a atomic sentence
    flag operator; // only if is a complex sentence
    atomic atomic; // only if is a atomic sentence
    flag negative; // flag that means if the sentence is negatived or not; 0 = non negatived, 1 = negatived
}
sentence;

typedef struct atomic
{
    char symbol;
    char* phrase;
}
atomic;

int main(void)
{
    Se fizer sol então vou a escola
    0   1      2   3     4 5  6

    if(strcmp(v[0], "Se") = 0)
    {
        inicio = i;
        do
        {
            i++;
        }
        while(strcmp(v[i], "então") = 0)
        fim  = i;

        sentence *n = malloc(sizeof(sentence))



    }
}


char* split_string(char *v)
{
    char *names[] = {
      "Zara Ali",
      "Hina Ali",
      "Nuha Ali",
      "Sara Ali"
   };
    while(*v != '\0')
    {

    }
}

// function that reads a sentence in natural language and returns a sentence struct 
sentence read_phrase(char *v,  )
{
    // TODO: escrever uma função que consiga ler uma string e criar uma sentença lógica a partir dela

    // TODO: escrever um procedimento que leia negações
    while(v[i] != " ")
    {

    }
    // TODO: escrever um procedimento que leia implicação

    // TODO: escrever um procedimento que leia bi-implicação 

    // TODO: escrever um procedimento que leia conjunção

    // TODO: escrever um procedimento que leia disjunção

    // TODO: escrever um procedimento que leia sentenças atômicas
}