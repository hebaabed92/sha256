// Everett Hildenbrandt
// Attempt to implement SHA256 in C to learn some programming and Cryptography

#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    char input[513];
    if(argc > 1) {
        printf("Input from stdin, not command line (for security reasons?)\n");
        return 1;
    }
    if(fgets(input, 513, stdin) == NULL) {
        printf("Error reading stdin - fgets returned NULL. Returning.\n");
        return 2;
    }

    

    
    return 0;
}
