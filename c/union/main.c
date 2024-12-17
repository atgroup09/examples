#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bit.h"


typedef union {
    float    flo;
    uint16_t wo;
    uint32_t dwo;
    uint16_t w2[2];
    uint8_t  b4[4];
} TEST_ut;


void printTest(TEST_ut *In)
{
    if(In)
    {
        uint8_t i;

        printf("flo=%f\n", In->flo);
        printf(" wo=%d\n", In->wo);
        printf("dwo=%d\n", In->dwo);

        printf("w2:\n");
        for(i=0; i<2; i++)
        {
            printf("[%d]=%d\n", i, In->w2[i]);
        }

        printf("b4:\n");
        for(i=0; i<4; i++)
        {
            printf("[%d]=%d\n", i, In->b4[i]);
        }

        printf("\n");
    }
}


int main()
{
    TEST_ut Test;

    Test.flo = 22.8311;
    printTest(&Test);

    return 0;
}

