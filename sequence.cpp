#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

void sequence(int a, int b)
{
    ofstream file1;
    ofstream file2;
    char c;
    int r;
    int s;

    file1.open("text1.dat");
    file2.open("text2.dat");
    srand(time(NULL));

    if (a > 100000 || b > 100000)
    {
        a = 100000;
        b = 100000;
    }
    for (int i = 0; i < a; i++)
    {
        r = rand() % 26;
        s = rand() % 26;
        c = 'a' + r;
        file1 << c;
        c = 'a' + s;
        file2 << c;
    }
    file1.close();
    file2.close();
}

int main(int argc, char *argv[])
{
    ifstream file1;
    ifstream file2;
    int size1;
    int size2;

    sequence(atoi(argv[1]), atoi(argv[2]));
    return 0;
}