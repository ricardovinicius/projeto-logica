#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <strings.h>

int main(int argc, char *argv[])
{
    char string[50] = "Hello! We are learning about strtok";
    // Extract the first token
    char * token = strtok(string, " ");
    // loop through the string to extract all other tokens
    while( token != NULL ) {
        printf( " %s\n", token ); //printing each token
        token = strtok(NULL, " ");
    }
}


