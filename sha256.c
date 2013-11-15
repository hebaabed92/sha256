// Everett Hildenbrandt
// Attempt to implement SHA256 in C to learn some programming and Cryptography

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <byteswap.h>

//Macro definitions of constants
#define MSGSIZE 512
#define STORSIZE 64
#define HVALS {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,\
               0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19}
#define KVALS {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,\
               0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,\
               0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,\
               0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,\
               0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,\
               0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,\
               0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,\
               0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,\
               0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,\
               0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,\
               0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,\
               0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,\
               0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,\
               0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,\
               0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,\
               0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2}

//Macro definitions of functions we'll need for hashing
#define Ch(x, y, z) ((x&y)^((~x)&z))
#define Maj(x, y, z) ((x&y)^(x&z)^(y&z))
#define rotR(x, n) ((x>>n)|(x<<(32-n)))
#define shiftR(x, n) (x>>n)
#define SIG0(x) (rotR(x, 2)^rotR(x, 13)^rotR(x, 22))
#define SIG1(x) (rotR(x, 6)^rotR(x, 11)^rotR(x, 25))
#define sig0(x) (rotR(x, 7)^rotR(x, 18)^shiftR(x, 3))
#define sig1(x) (rotR(x, 17)^rotR(x, 19)^shiftR(x, 10))

//SHA256 Compression Function
void sha256Compress(uint32_t W[64], uint32_t H[8], uint32_t K[64])
{
    uint32_t a, b, c, d, e, f, g, h;

    //Initializing the values ("registers" - maybe, who knows), and the message Schedule (W)
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];
    for(i=16; i<64; i++)
        W[i] = sig1(W[i-2])+W[i-7]+sig0(W[i-15])+W[i-16];
    
    //SHA-256 compression function loop
    for(i=0; i<64; i++)
    {
        T1 = h + SIG1(e) + Ch(e, f, g) + K[i] + W[i];
        T2 = SIG0(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
        //printf("\nt=%d\t%08x %08x %08x %08x %08x %08x %08x %08x", i, a, b, c, d, e, f, g, h);
    }

    //Update our hash values for this block
    H[0] += a;
	H[1] += b;
	H[2] += c;
	H[3] += d;
	H[4] += e;
	H[5] += f;
	H[6] += g;
	H[7] += h;
}

//Main function :)
int main(int argc, char *argv[])
{
    //Declarin variables so early
    //gave your grandma a necklace - pearly!
    int i = 0, readBytes = 0;
    bool msgLeft = TRUE, zeroBlock = FALSE;
    union {
        uint8_t all[MSGSIZE/8];
        struct {
            char message[(MSGSIZE-STORSIZE)/8];
            uint64_t length;
        } info;
        uint32_t mi[MSGSIZE/32];
    } input;
    uint8_t tempMsg[MSGSIZE/8];
    uint64_t msgSize = 0;
    uint32_t a, b, c, d, e, f, g, h;
    uint32_t T1, T2;
    uint32_t W[64];
    uint32_t K[64] = KVALS;
    uint32_t H[8] = HVALS;
    
    //Make sure user knows how to use (I suppose)
    if(argc > 1) {
        printf("Input from stdin, not command line (for security reasons?)\n");
        return 1;
    }
    /*
    do {
        if(!zeroBlock)
            readBytes = fread(tempMsg, 1, MSGSIZE/8, stdin);
        else
            for(i = 0; i < MSGSIZE/8; i++)
                tempMsg[i] = 0;
        if(ferror(stdin)) {
            printf("\n\n\tError returned reading from stdin - returning.\n");
            return 1;
        }
        if(feof(stdin)) {
            //Pad Zeros
            if(readBytes > ((MSGSIZE-MSGSTOR)/8-1)) {
                for(i = readBytes; i < MSGSIZE/8; i++)
                    tempMsg[i] = 0;
                zeroBlock = TRUE;
            }
            else
            
            msgLeft = FALSE;
        msgSize = strlen(input.all);
        if(msgSize > ((MSGSIZE-STORSIZE)/8)-1)
            msgSize = ((MSGSIZE-STORSIZE)/8-1);
        for(i = msgSize; i < MSGSIZE/8; i++)
            input.all[i] = (0<<7);
        input.all[msgSize] = (1<<7);
        input.info.length = bswap_64(msgSize*8);
        for(i = 0; i < (MSGSIZE/32); i++)
            input.mi[i] = bswap_32(input.mi[i]);
   } while(msgLeft);
   */

    readBytes = fread(tempMsg, 1, MSGSIZE/8, stdin);
    if(ferror(stdin)) {
        printf("\n\n\tError reading from stdin, returning.\n");
        return 1;
    }
    for(i = 0; i < (MSGSIZE/32); i++)
        input.mi[i] = bswap_32(tempMsg[i]);
        



    //Pre-processing - truncate the message (we are only using 1 block)
    //Pad the message according to the SHA256 specification
    //Print the size of the message in bits at the end of the block
   
    for(i=0; i<8; i++)
        printf("%x", H[i]);
    printf("\n");
    for(i=0; i<8; i++)
        printf("%x ", H[i]);
    printf("\n");

    return 0;
}
