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
        //uint8_t test[512/8];
    } input;
    int msgSize = 0;
    int i = 0;
    
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
    for(i = msgSize + 1; i < 512/8; i ++)
        input.all[i] = 0 << 7;
    input.info.length = msgSize*8;
    

    /*int test = 0;
    printf("Output now:%s\n", input.all);
    for(test = 0; test < (512/8); test ++)
        printf("%d\t", input.test[test]);
    printf("\nStored Message size: %d\n", input.info.length);*/


    return 0;
}
