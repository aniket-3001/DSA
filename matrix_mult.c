#include <stdio.h>

int main()
{
    int m1, n1, m2, n2;
    printf("enter dimensions of matrix A: ");
    scanf("%d %d", &m1, &n1);
    printf("enter dimensions of matrix B: ");
    scanf("%d %d", &m2, &n2);
    printf("\n");

    if (n1 != m2)
    {
        printf("matrix multiplication not possible");
    }
    else
    {
        int A[m1][n1], B[m2][n2], C[m1][n2];
        printf("Enter the elements of A row-wise:\n\n");

        for (int i = 0; i < m1; i++)
        {
            for (int j = 0; j < n1; j++)
            {
                scanf("%d", &A[i][j]);
            }
        }

        printf("\n");

        printf("Enter the elements of B row-wise:\n\n");

        for (int i = 0; i < m2; i++)
        {
            for (int j = 0; j < n2; j++)
            {
                scanf("%d", &B[i][j]);
            }
        }

        // matrix multiplication
        for (int i = 0; i < m1; i++)
        {
            for (int j = 0; j < n2; j++)
            {
                C[i][j] = 0;
                for (int k = 0; k < n1; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        // print result matrix
        printf("\nResult matrix C:\n");
        for (int i = 0; i < m1; i++)
        {
            for (int j = 0; j < n2; j++)
            {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
