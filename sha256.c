// Everett Hildenbrandt
// Attempt to implement SHA256 in C to learn some programming and Cryptography

#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    char input[257];
    if(argc > 1) {
        printf("Input from stdin, not command line (for security reasons?)\n");
        return 1;
    }
    if(fgets(input, 257, stdin) != NULL)
        printf("Input recieved: %s", input);    
    else
        printf("Error.");
    return 0;
}
