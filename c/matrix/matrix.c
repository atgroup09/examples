/* @page matrix.c
 *       2023
 */

#include "matrix.h"


/** @brief  Init. a matrix.
 *  @param  AIn    - pointer to matrix.
 *  @param  ArrIn  - pointer to array.
 *  @param  RowsIn - number of rows.
 *  @param  ColsIn - number of columns.
 *  @return None.
 */
void MatrixInit(Matrix_t *AIn, float *ArrIn, uint8_t RowsIn, uint8_t ColsIn)
{
    AIn->Arr  = ArrIn;
    AIn->Rows = AIn->RowsSrc = RowsIn;
    AIn->Cols = AIn->ColsSrc = ColsIn;
}

/** @brief  Init. a matrix + Zeroes.
 *  @param  AIn    - pointer to matrix.
 *  @param  ArrIn  - pointer to array.
 *  @param  RowsIn - number of rows.
 *  @param  ColsIn - number of columns.
 *  @return None.
 */
void MatrixInit2(Matrix_t *AIn, float *ArrIn, uint8_t RowsIn, uint8_t ColsIn)
{
    MatrixInit(AIn, ArrIn, RowsIn, ColsIn);
    MatrixZero(AIn);
}

/** @brief  Zeroed a matrix.
 *  @param  AIn    - pointer to matrix.
 *  @return None.
 */
void MatrixZero(Matrix_t *AIn)
{
    uint8_t i, j, r = AIn->Rows, c = AIn->Cols;

    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {
            *(AIn->Arr+j+(i*c)) = 0.0;
        }
    }
}

/** @brief  Reset a matrix to source sizes.
 *  @param  AIn - pointer to matrix.
 *  @return None.
 */
void MatrixReset(Matrix_t *AIn)
{
    AIn->Rows = AIn->RowsSrc;
    AIn->Cols = AIn->ColsSrc;
}

#ifdef MATRIX_PRINT
/** @brief  Print a matrix.
 *  @param  AIn - pointer to matrix.
 *  @return None.
 */
void MatrixPrint(const Matrix_t *AIn)
{
    uint8_t i, j;

    for(i=0; i<AIn->Rows; i++)
    {
        for(j=0; j<AIn->Cols; j++)
        {
            printf("%f ", *(AIn->Arr+j+(i*AIn->Cols)));
        }
        printf("\n");
    }
}
#endif // MATRIX_PRINT


/** @brief  Add two matrices.
 *  @param  AIn - pointer to first matrix.
 *  @param  BIn - pointer to second matrix.
 *  @param  CIn - pointer to result matrix.
 *  @return Result code:
 *  @arg    = 0 - Error: the sizes of the matrices are not equal
 *  @arg    = 1 - OK
 *  @note   C = A+B
 *          A.Rows == B.Rows AND A.Cols == B.Cols
 *          C[A.Rows][A.Cols]
 */
uint8_t MatrixAdd(const Matrix_t *AIn, const Matrix_t *BIn, Matrix_t *CIn)
{
    if(!((AIn->Rows == BIn->Rows) && (AIn->Cols == BIn->Cols) && (CIn->Rows == AIn->Rows) && (CIn->Cols == AIn->Cols)))
    {
        return (0);
    }

    uint8_t i, j, r = AIn->Rows, c = AIn->Cols;

    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {
            *(CIn->Arr+j+(i*c)) = *(AIn->Arr+j+(i*c)) + *(BIn->Arr+j+(i*c));
        }
    }

    return (1);
}

/** @brief  Substract two matrices.
 *  @param  AIn - pointer to first matrix.
 *  @param  BIn - pointer to second matrix.
 *  @param  CIn - pointer to result matrix.
 *  @return Result code:
 *  @arg    = 0 - Error: the sizes of the matrices are not equal
 *  @arg    = 1 - OK
 *  @note   C = A-B
 *          A.RowSz == B.RowSz AND A.ColSz == B.ColSz
 *          C[A.RowSz][A.ColSz]
 */
uint8_t MatrixSub(const Matrix_t *AIn, const Matrix_t *BIn, Matrix_t *CIn)
{
    if(!((AIn->Rows == BIn->Rows) && (AIn->Cols == BIn->Cols) && (CIn->Rows == AIn->Rows) && (CIn->Cols == AIn->Cols)))
    {
        return (0);
    }

    uint8_t i, j, r = AIn->Rows, c = AIn->Cols;

    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {
            *(CIn->Arr+j+(i*c)) = *(AIn->Arr+j+(i*c)) - *(BIn->Arr+j+(i*c));
        }
    }

    return (1);
}

/** @brief  Multiple two matrices.
 *  @param  AIn - pointer to first matrix.
 *  @param  BIn - pointer to second matrix.
 *  @param  CIn - pointer to result matrix.
 *  @return Result code:
 *  @arg    = 0 - Error: the sizes of the matrices are not equal
 *  @arg    = 1 - OK
 *  @note   C = A*B
 *          A.ColSz == B.RowSz
 *          C[A.RowSz][B.ColSz]
 */
uint8_t MatrixMul(const Matrix_t *AIn, const Matrix_t *BIn, Matrix_t *CIn)
{
    if(!((AIn->Cols == BIn->Rows) && (CIn->Rows >= AIn->Rows) && (CIn->Cols >= BIn->Cols)))
    {
        return (0);
    }

    uint8_t i, j, k, r = AIn->Rows, c = BIn->Cols, cc = AIn->Cols;
    float sum;

    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {
            sum = 0.0;
            for(k=0; k<cc; k++)
            {
                sum+= (*(AIn->Arr+k+(i*AIn->Cols)))*(*(BIn->Arr+j+(k*BIn->Cols)));
            }
            *(CIn->Arr+j+(i*c)) = sum;
        }
    }

    CIn->Rows = AIn->Rows;
    CIn->Cols = BIn->Cols;

    return (1);
}


/** @brief  Multiple matrix by a number .
 *  @param  AIn   - pointer to matrix.
 *  @param  NumIn - a number.
 *  @param  CIn - pointer to result matrix.
 *  @return Result code:
 *  @arg    = 0 - Error: the sizes of the matrices are not equal
 *  @arg    = 1 - OK
 *  @note   C = A*Num
 *          C[A.RowSz][A.ColSz]
 */
uint8_t MatrixMulNum(const Matrix_t *AIn, float NumIn, Matrix_t *CIn)
{
    if(!((CIn->Rows >= AIn->Rows) && (CIn->Cols >= AIn->Cols)))
    {
        return (0);
    }

    uint8_t i, j, r = AIn->Rows, c = AIn->Cols;

    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {
            *(CIn->Arr+j+(i*c)) = (*(AIn->Arr+j+(i*c)))*NumIn;
        }
    }

    CIn->Rows = AIn->Rows;
    CIn->Cols = AIn->Cols;

    return (1);
}

/** @brief  Set value of an element.
 *  @param  AIn   - pointer to matrix.
 *  @param  RowIn - element row number (1, 2, ...).
 *  @param  ColIn - element column number (1, 2, ...).
 *  @param  ValIn - element value.
 *  @return Result code:
 *  @arg    = 0 - Error the size of the matrix
 *  @arg    = 1 - OK
 *  @note   A[RowIn][ColIn]
 */
uint8_t MatrixSet(Matrix_t *AIn, uint8_t RowIn, uint8_t ColIn, float ValIn)
{
    if(!(RowIn && !(RowIn > AIn->Rows)))
    {
        return (0);
    }

    if(!(ColIn && !(ColIn > AIn->Cols)))
    {
        return (0);
    }

    uint8_t r = RowIn-1;
    uint8_t c = ColIn-1;

    *(AIn->Arr+c+(r*AIn->Cols)) = ValIn;

    return (1);
}

/** @brief  Get value of an element.
 *  @param  AIn   - pointer to matrix.
 *  @param  RowIn - element row number (1, 2, ...).
 *  @param  ColIn - element column number (1, 2, ...).
 *  @param  ValIn - pointer to storage of element value.
 *  @return Result code:
 *  @arg    = 0 - Error the size of the matrix
 *  @arg    = 1 - OK
 *  @note   A[RowIn][ColIn]
 */
uint8_t MatrixGet(const Matrix_t *AIn, uint8_t RowIn, uint8_t ColIn, float *ValIn)
{
    if(!(RowIn && !(RowIn > AIn->Rows)))
    {
        return (0);
    }

    if(!(ColIn && !(ColIn > AIn->Cols)))
    {
        return (0);
    }

    uint8_t r = RowIn-1;
    uint8_t c = ColIn-1;

    *ValIn = *(AIn->Arr+c+(r*AIn->Cols));

    return (1);
}


/* TEST

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
*/
