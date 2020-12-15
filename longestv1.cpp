// https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
// Bad Runtime ==> O(2^n)
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

//
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs(char *X, char *Y, int m, int n)
{
    if (m == 0 || n == 0)
        return 0;
    if (X[m - 1] == Y[n - 1])
        return 1 + lcs(X, Y, m - 1, n - 1);
    else
        return max(lcs(X, Y, m, n - 1), lcs(X, Y, m - 1, n));
}

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcsSequential(char *X, char *Y, int m, int n) // O(mn)
{
    unsigned short int **L;
    int i, j;
    L = (unsigned short int **)malloc(sizeof(unsigned short int *) * (m + 1));
    for (i = 0; i <= m; i++)
    {
        L[i] = (unsigned short int *)malloc(sizeof(unsigned short int) * (n + 1));
    }

    /* Following steps build L[m+1][n+1] in  
       bottom up fashion. Note that L[i][j]  
       contains length of LCS of X[0..i-1] 
       and Y[0..j-1] */
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

    // Create a character array to store the lcs string
    char lcs[index + 1];
    lcs[index] = '\0'; // Set the terminating character

    // Start from the right-most-bottom-most corner and
    // one by one store characters in lcs[]
    i = m;
    j = n;
    while (i > 0 && j > 0)
    {
        // If current character in X[] and Y are same, then
        // current character is part of LCS
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1]; // Put current character in result
            i--;
            j--;
            index--; // reduce values of i, j and index
        }

        // If not same, then find the larger of two and
        // go in the direction of larger value
        // If equal go left (as statement rule says so)
        else if (L[i - 1][j] >= L[i][j - 1])
            i--;
        else
            j--;
    }

    /* L[m][n] contains length of LCS  
    for X[0..n-1] and Y[0..m-1] */
    cout << L[m][n] << " " << lcs << endl;

    return L[m][n];
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/***********************************************************************************/

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcsParallel(char *X, char *Y, int m, int n)
{
    unsigned short int **L;
    int i, j;

    int size = 1;
    int inc = 1;
    int x, y;
    int init_x, init_y;
    int nthreads;

    L = (unsigned short int **)malloc(sizeof(unsigned short int *) * (m + 1));
    for (i = 0; i <= m; i++)
    {
        L[i] = (unsigned short int *)malloc(sizeof(unsigned short int) * (n + 1));
    }

    /* Following steps build L[m+1][n+1] in bottom up fashion. Note
  that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
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

        cout << "n " << nthreads << endl;
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
    // Following code is used to print LCS
    int index = L[m][n];

    // Create a character array to store the lcs string
    char lcs[index + 1];
    lcs[index] = '\0'; // Set the terminating character

    // Start from the right-most-bottom-most corner and
    // one by one store characters in lcs[]
    i = m;
    j = n;
    while (i > 0 && j > 0)
    {
        // If current character in X[] and Y are same, then
        // current character is part of LCS
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1]; // Put current character in result
            i--;
            j--;
            index--; // reduce values of i, j and index
        }

        // If not same, then find the larger of two and
        // go in the direction of larger value
        // If equal go left (as statement rule says so)
        else if (L[i - 1][j] >= L[i][j - 1])
            i--;
        else
            j--;
    }

    /* Print the lcs */
    cout << L[m][n] << " " << lcs << endl;

    for (i = 0; i <= m; i++)
    {
        free(L[i]);
    }
    free(L);

    return 0;
}

/***********************************************************************************/

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
        lcsParallel(s1, s2, size1, size2);
    }
    else
    {
        lcsSequential(s1, s2, size1, size2);
    }

    free(s2);
    free(s1);

    file1.close();
    file2.close();

    return 0;
}