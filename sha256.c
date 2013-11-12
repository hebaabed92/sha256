// Everett Hildenbrandt
// Attempt to implement SHA256 in C to learn some programming and Cryptography

/* Nothing Here Yet */

#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    char input[256];
    if(argc > 1) {
        printf("Input from stdin, not command line (for security reasons?)\n");
        return 1;
    }
    read(stdin, input, 256);
    printf("Input recieved: %s", input);    
    return 0;
}
