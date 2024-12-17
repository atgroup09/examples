#include "matrix.h"


Matrix_t A, B, C, D1, D2;
float ArrA[1][2] = { {1.0, 0.0} };
float ArrB[2][2] = { {1.0, 0.0}, {0.0, 1.0} };
float ArrC[2][1] = { {1.0}, {0.0} };
float ArrD1[4][4] = { {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0} };
float ArrD2[4][4] = { {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0} };

int main()
{
    MatrixInit(&A, (float *)ArrA, 1, 2);
    MatrixInit(&B, (float *)ArrB, 2, 2);
    MatrixInit(&C, (float *)ArrC, 2, 1);
    MatrixInit(&D1, (float *)ArrD1, 4, 4);
    MatrixInit(&D2, (float *)ArrD2, 4, 4);

    if(MatrixMulNum(&B, 0.6329, &D1))
    {
        printf("B*0.6329=D\n");
        MatrixPrint(&D1);
        printf("\n");
    }

    return (0);
}
