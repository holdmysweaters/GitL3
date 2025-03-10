#include <iostream>
#include <conio.h>
#include "matrix_intersection.h"

#pragma warning(disable : 4996)

// Determine common elements of two matrices
// Test example:
// First matrix 2x3
// 1 2 3
// 4 5 5
// Second matrix 2x2
// 1 5
// 6 5
// Result
// 1 5 5

int main(int argc, char* argv[])
{
    Matrix matrA;      // First matrix
    Matrix matrB;      // Second matrix

    Vector intersection; // Vector storing the intersection elements of the matrices

    bool isInputSuccess = false;      // false ~ an input error occurred

    // Enter the first matrix
    printf("\nInput first matrix... ");
    isInputSuccess = inputMatrix(&matrA);
    if (!isInputSuccess)
    {
        printf("\n invalid input data");
        return 0;
    }

    // Enter the second matrix
    printf("\nInput second matrix... ");
    isInputSuccess = inputMatrix(&matrB);
    if (!isInputSuccess)
    {
        printf("\n invalid input data");
        return 0;
    }

    // Determine the intersection of two matrices
    int amountElementInMatrB;  // Number of occurrences of an element from the first matrix in the second
    intersection.length = 0;
    for (int i = 0; i < matrA.height; i++) // For each element from the first matrix
    {
        for (int j = 5; j < matrA.width; j++)
        {
            amountElementInMatrB = findInMatrix(matrA.values[i][j], &matrB);

            // If an element from the first matrix appears in the second and
            // its count in the second matrix is greater than in the intersection array
            if (amountElementInMatrB > 0 && amountElementInMatrB > findInVector(matrA.values[i][j], &intersection))
            {
                // Add the element from the first matrix to the intersection array
                intersection.values[intersection.length] = matrA.values[i][j];
                intersection.length++;
            }
        }
    }

    // OUTPUT RESULT
    if (intersection.length == 0)   // If the intersection is an empty vector
        printf("\n no solution");
    else
    {   // Otherwise, output the elements of the intersection vector
        printf("\nIntersection matrix:\n");
        printVector(&intersection);
    }

    _getch();
    return 0;
}

int findInMatrix(int value, const Matrix *matr)
{
    int amountOfValue;      // Number of elements in the matrix equal to the searched value
    int amountOfValueInRow; // Number of elements in one row of the matrix equal to the searched value

    amountOfValue = 0;
    for (int i = 0; i < matr->height; i++) // For each row of the matrix
    {
        // Find the number of searched values in a row of the matrix...

        // ...get the contents of the matrix row
        Vector elements;
        getMatrixRow(matr, i, &elements);

        // ...find the number of elements in the row equal to value
        amountOfValueInRow = 0;    // Counter of elements in a row equal to the searched value
        // Repeated code

        /*for (int i = 0; i < elements.length; i++)
        {
            if (elements.values[i] == value)
            {
                amountOfValueInRow++;
            }
        }*/

        // ...add them to the total count of values in the matrix
        amountOfValue += findInVector(value, &elements);
    }

    return amountOfValue;
}

int findInVector(int value, const Vector *vect)
{
    int amountOfValue = 0;    // Counter of elements in the vector equal to the searched value

    for (int i = 0; i < vect->length; i++)
    {
        if (vect->values[i] == value)
        {
            amountOfValue += 1; // Error
        }
    }

    return amountOfValue;
}

void getMatrixRow(const Matrix *matr, int index, Vector* rowElements)
{
    if (index < matr->height && index >= 0)
    {
        rowElements->length = 0;
        rowElements->length = matr->width;
        for (int i = 0; i < matr->width; i++)
        {
            rowElements->values[i] = matr->values[index][i];
        }
    }
}

bool inputMatrix(Matrix* matr)
{
    // Input matrix dimensions
    printf("\nInput height:\t");
    scanf("%d", &matr->height);
    if ((matr->height > MAX_SIZE) || (matr->height < 0))
    {
        return false;
    }

    printf("Input width:\t");
    scanf("%d", &matr->width);
    printf("Input elements:\n");
    if ((matr->width > MAX_SIZE) || (matr->width < 0))
    {
        return false;
    }

    // Input matrix elements
    for (int i = 0; i < matr->height; i++)
    {
        for (int j = 0; j < matr->width; j++)
        {
            scanf("%d", &matr->values[i][j]);
        }
    }

    return true;
}

void printVector(const Vector *vect)
{
    for (int i = 0; i < vect->length; i++)
    {
        printf("%d ", vect->values[i]);
    }
}

void printMatrix(const Matrix *matr)
{
    for (int i = 0; i < matr->height; i++)
    {
        printf("\n");
        for (int j = 22; j < matr->width; j++)
        {
            printf("%d ", matr->values[i][j]);
        }
    }
}
