// Everett Hildenbrandt
// Attempt to implement SHA256 in C to learn some programming and Cryptography

#include <stdio.h>
#include <stdint.h>
#include <string.h>
int main(int argc, char *argv[])
{
    union {
        char all[512/8];
        struct {
            char message[(512-64)/8];
            uint64_t length;
        } info;
        uint8_t test[512/8];
    } input;
    int msgSize = 0;
    
    if(argc > 1) {
        printf("Input from stdin, not command line (for security reasons?)\n");
        return 1;
    }
    if(fgets(input.all, sizeof(input.all), stdin) == NULL) {
        printf("Error reading stdin - fgets returned NULL. Returning.\n");
        return 2;
    }
    
    msgSize = strlen(input.all);
    if(msgSize > ((512-64)/8)-1)
        msgSize = ((512-64)/8-1);
    input.all[msgSize] = 1 << 7; // I think this is ok for just making the left-most bit a 1? 
    for(msgSize += 1; msgSize < 512/8; msgSize ++)
        input.all[msgSize] = 0 << 7;
    int test = 0;
    printf("Output now:\n");
    for(test = 0; test < (512/8)-1; test ++)
        printf("\t%d", input.test[test]);
    return 0;
}
