// https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
//
// Better O(mn)
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <bits/stdc++.h>
#include <omp.h>
#include <ctype.h>
#include <omp.h>
#include <sched.h>
#include <unistd.h>

using namespace std::chrono;
using namespace std;

int max(int a, int b);
int nthreads, tid;

int lcsSequential(char *X, char *Y, int m, int n) // O(mn)
{
    unsigned short int **L;
    int i, j;
    L = (unsigned short int **)malloc(sizeof(unsigned short int *) * (m + 1));
    for (i = 0; i <= m; i++)
    {
        L[i] = (unsigned short int *)malloc(sizeof(unsigned short int) * (n + 1));
    }

    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;

            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;

            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    int index = L[m][n];

    char lcs[index + 1];
    lcs[index] = '\0';

    i = m;
    j = n;
    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] >= L[i][j - 1])
            i--;
        else
            j--;
    }
    cout << L[m][n] /*<< " " << lcs*/ << endl;

    return L[m][n];
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/***********************************************************************************/

int lcsParallel(char *X, char *Y, int m, int n)
{
    unsigned short int **L;
    int i, j;

    int size = 1;
    int inc = 1;
    int x, y;
    int init_x, init_y;

    L = (unsigned short int **)malloc(sizeof(unsigned short int *) * (m + 1));
    for (i = 0; i <= m; i++)
    {
        L[i] = (unsigned short int *)malloc(sizeof(unsigned short int) * (n + 1));
    }

    for (i = 0; i <= m; i++)
    {
        L[i][0] = 0;
    }

    for (i = 0; i <= n; i++)
    {
        L[0][i] = 0;
    }

    for (i = 1; i <= m + n - 1; i++)
    {
        if (i >= m)
        {
            x = m;
            y = 1 + i - m;
        }
        else
        {
            x = i;
            y = 1;
        }

        if (i == m || i == n)
        {
            inc--;
        }

        if (i == m && i == n)
        {
            inc--;
        }

        init_x = x;
        init_y = y;
// cout << "n " << nthreads << endl;
#pragma omp parallel for private(x, y)
        for (j = 0; j < size; j++)
        {
            x = init_x - j;
            y = init_y + j;

            if (X[x - 1] == Y[y - 1])
            {
                L[x][y] = L[x - 1][y - 1] + 1;
            }
            else
            {
                L[x][y] = max(L[x - 1][y], L[x][y - 1]);
            }
        }
        size += inc;
    }

    cout << L[m][n] /*<< " " << lcs*/ << endl;

    for (i = 0; i <= m; i++)
    {
        free(L[i]);
    }
    free(L);

    return 0;
}

int lcs2(char *X, char *Y, int m, int n)
{
    unsigned short int **L;
    int i, j;

    int size = 1;
    int inc = 1;
    int x, y;
    int init_x, init_y;

    L = (unsigned short int **)malloc(sizeof(unsigned short int *) * (m + 1));
    for (i = 0; i <= m; i++)
    {
        L[i] = (unsigned short int *)malloc(sizeof(unsigned short int) * (n + 1));
    }

    for (i = 0; i <= m; i++)
    {
        L[i][0] = 0;
    }

    for (i = 0; i <= n; i++)
    {
        L[0][i] = 0;
    }

    for (i = 1; i <= m + n - 1; i++)
    {
        if (i >= m)
        {
            x = m;
            y = 1 + i - m;
        }
        else
        {
            x = i;
            y = 1;
        }

        if (i == m || i == n)
        {
            inc--;
        }

        if (i == m && i == n)
        {
            inc--;
        }

        init_x = x;
        init_y = y;
        for (j = 0; j < size; j++)
        {
            x = init_x - j;
            y = init_y + j;

            if (X[x - 1] == Y[y - 1])
            {
                L[x][y] = L[x - 1][y - 1] + 1;
            }
            else
            {
                L[x][y] = max(L[x - 1][y], L[x][y - 1]);
            }
        }
        size += inc;
    }
    int index = L[m][n];

    cerr << L[m][n] /*<< " " << lcs*/ << endl;

    for (i = 0; i <= m; i++)
    {
        free(L[i]);
    }
    free(L);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cout << "usage: ./lcs <s1> <s2> <size1> <size2> [-p]" << endl;
        exit(0);
    }
    sched_setscheduler(getpid(), SCHED_FIFO, NULL);

    ifstream file1;
    ifstream file2;

    file1.open(argv[1]);
    file2.open(argv[2]);
    int size1 = atoi(argv[3]);
    int size2 = atoi(argv[4]);

    char *s1 = (char *)malloc(sizeof(char) * (size1 + 1));
    char *s2 = (char *)malloc(sizeof(char) * (size2 + 1));

    file1 >> s1;
    file2 >> s2;

    if (argc == 6)
    {
        omp_set_num_threads(atoi(argv[5]));
        lcsParallel(s1, s2, size1, size2);
    }
    else
    {
        lcs2(s1, s2, size1, size2);
    }

    free(s2);
    free(s1);

    file1.close();
    file2.close();

    return 0;
}