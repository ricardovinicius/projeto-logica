#include <stdio.h>
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

}

// function that reads a sentence in natural language and returns a sentence struct 
sentence read_phrase()
{
    //if finds a "if"
    //creates a sentence

}