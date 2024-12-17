/* @page matrix.h
 *       2023
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdint.h>


/** @def Use printf()
 */
#define MATRIX_PRINT


/** @typedef Matrix[Rows][Cols]
 */
typedef struct Matrix_t_
{
    //@var number of rows and columns (current matrix size)
    uint8_t Rows;
    uint8_t Cols;

    //@var number of rows and columns (source matrix size)
    uint8_t RowsSrc;
    uint8_t ColsSrc;

    //@var pointer to array ([RowsSrc][ColsSrc])
    float*  Arr;

} Matrix_t;


/** @brief  Init. a matrix.
 *  @param  AIn    - pointer to matrix.
 *  @param  ArrIn  - pointer to array.
 *  @param  RowsIn - number of rows.
 *  @param  ColsIn - number of columns.
 *  @return None.
 */
void MatrixInit(Matrix_t *AIn, float *ArrIn, uint8_t RowsIn, uint8_t ColsIn);

/** @brief  Init. a matrix + Zeroes.
 *  @param  AIn    - pointer to matrix.
 *  @param  ArrIn  - pointer to array.
 *  @param  RowsIn - number of rows.
 *  @param  ColsIn - number of columns.
 *  @return None.
 */
void MatrixInit2(Matrix_t *AIn, float *ArrIn, uint8_t RowsIn, uint8_t ColsIn);

/** @brief  Zeroed a matrix.
 *  @param  AIn    - pointer to matrix.
 *  @return None.
 */
void MatrixZero(Matrix_t *AIn);

/** @brief  Reset a matrix to source sizes.
 *  @param  AIn - pointer to matrix.
 *  @return None.
 */
void MatrixReset(Matrix_t *AIn);


#ifdef MATRIX_PRINT

#include <stdio.h>
#include <stdlib.h>

/** @brief  Print a matrix.
 *  @param  AIn - pointer to matrix.
 *  @return None.
 */
void MatrixPrint(const Matrix_t *AIn);

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
uint8_t MatrixAdd(const Matrix_t *AIn, const Matrix_t *BIn, Matrix_t *CIn);

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
uint8_t MatrixSub(const Matrix_t *AIn, const Matrix_t *BIn, Matrix_t *CIn);

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
uint8_t MatrixMul(const Matrix_t *AIn, const Matrix_t *BIn, Matrix_t *CIn);

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
uint8_t MatrixMulNum(const Matrix_t *AIn, float NumIn, Matrix_t *CIn);

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
uint8_t MatrixSet(Matrix_t *AIn, uint8_t RowIn, uint8_t ColIn, float ValIn);

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
uint8_t MatrixGet(const Matrix_t *AIn, uint8_t RowIn, uint8_t ColIn, float *ValIn);

#endif /* MATRIX_H_ */
