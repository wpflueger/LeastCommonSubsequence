// https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
// Bad Runtime ==> O(2^n)
// Better O(mn)
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <bits/stdc++.h>

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
int lcsNew(char *X, char *Y, int m, int n) // O(mn)
{
    int L[m + 1][n + 1];
    int i, j;

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

    /* L[m][n] contains length of LCS  
    for X[0..n-1] and Y[0..m-1] */
    return L[m][n];
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main()
{
    ifstream file1;
    ifstream file2;
    char data1[100000];
    char data2[100000];
    int size1;
    int size2;

    file1.open("text1.dat");
    file2.open("text2.dat");
    file1 >> data1;
    file2 >> data2;
    size1 = strlen(data1);
    size2 = strlen(data2);

    auto start = high_resolution_clock::now();
    {
        cout << "Length of LCS is "
             << lcs(data1, data2, size1, size2)
             << endl;
    }
    auto stop = high_resolution_clock::now();

    auto duration1 = duration_cast<microseconds>(stop - start);

    cout << "Time taken by O(2^N) function: "
         << duration1.count() << " microseconds" << endl;

    // ++++++++++++++++++++++++++++++++++++++++++++++++++

    start = high_resolution_clock::now();
    {
        cout << "Length of LCS is "
             << lcsNew(data1, data2, size1, size2)
             << endl;
    }
    stop = high_resolution_clock::now();

    auto duration2 = duration_cast<microseconds>(stop - start);

    cout << "Time taken by O(mn) function: "
         << duration2.count() << " microseconds" << endl;

    cout << "The Imporved LCS ran " << (duration1.count() - duration2.count()) << " microseconds faster" << endl;

    return 0;
}