// Everett Hildenbrandt
// Attempt to implement SHA256 in C to learn some programming and Cryptography

#include <stdio.h>
#include <stdint.h>
#include <string.h>
int main(int argc, char *argv[])
{
    union {
        char input[512/8];
        struct {
            char message[(512-64)/8];
            uint64_t length;
        };
    };
    int msgSize = 0;
    if(argc > 1) {
        printf("Input from stdin, not command line (for security reasons?)\n");
        return 1;
    }
    if(fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading stdin - fgets returned NULL. Returning.\n");
        return 2;
    }
    
    msgSize = strlen(input);
    
        
    
    return 0;
}
