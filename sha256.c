// Everett Hildenbrandt
// Attempt to implement SHA256 in C to learn some programming and Cryptography

#include <stdio.h>
#include <stdint.h>
#include <string.h>

//Macro definitions of functions we'll need for hashing
#define Ch(x, y, z) ((x&y)^((~x)&z))
#define Maj(x, y, z) ((x&y)^(x&z)^(y&z))
#define rotR(x, n) ((x>>n)|(x<<(32-n)))
#define shiftR(x, n) (x>>n)
#define SIG0(x) (rotR(x, 2)^rotR(x, 13)^rotR(x, 22))
#define SIG1(x) (rotR(x, 6)^rotR(x, 11)^rotR(x, 25))
#define sig0(x) (rotR(x, 7)^rotR(x, 18)^shiftR(x, 3))
#define sig1(x) (rotR(x, 17)^rotR(x, 19)^shiftR(x, 10))


//Main function :)
int main(int argc, char *argv[])
{
    union {
        char all[512/8];
        struct {
            char message[(512-64)/8];
            uint64_t length;
        } info;
        uint32_t mi[512/32];
        //uint8_t test[512/8];
        //int test[512] : 1;
    } input;
    int msgSize = 0;
    int i = 0;
    uint32_t a, b, c, d, e, f, g, h;
    uint32_t T1, T2, K, W;
    
    if(argc > 1) {
        printf("Input from stdin, not command line (for security reasons?)\n");
        return 1;
    }
    if(fgets(input.all, sizeof(input.all), stdin) == NULL) {
        printf("Error reading stdin - fgets returned NULL. Returning.\n");
        return 2;
    }
    
    //Pre-processing - truncate the message (we are only using 1 block)
    //Pad the message according to the SHA256 specification
    //Print the size of the message in bits at the end of the block
    msgSize = strlen(input.all);
    if(msgSize > ((512-64)/8)-1)
        msgSize = ((512-64)/8-1);
    input.all[msgSize] = 1 << 7; // I think this is ok for just making the left-most bit a 1? 
    for(i = msgSize + 1; i < 512/8; i ++)
        input.all[i] = 0 << 7;
    input.info.length = msgSize*8;
    

    //Block for testing whether the pre-processing went correctly
    /*int test = 0;
    printf("Output now:%s\n", input.all);
    for(test = 0; test < (512/8); test ++)
        printf("%d\t", input.test[test]);
    printf("\nStored Message size: %d\n", input.info.length);*/
    
    //Initializing the values
    a = input.mi[0];
    b = input.mi[1];
    c = input.mi[2];
    d = input.mi[3];
    e = input.mi[4];
    f = input.mi[5];
    g = input.mi[6];
    h = input.mi[7];
    
    //SHA-256 compression function loop
    for(i=0; i<64; i++)
    {
        T1 = h + SIG1(e) + Ch(e, f, g) + K + W;
        T2 = SIG0(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }
    return 0;
}
