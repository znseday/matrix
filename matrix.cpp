#include <iostream>
#include <cassert>

#include "matrix.h"

using namespace std;

void TestBasic()
{
    cout << endl << "TestBasic" << endl;
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0);

    int a = matrix[0][0];         // In case 'auto a': 'a' is ProxyAtOnce. So, I wrote 'int' explicitly
    assert(a == -1);
    assert(matrix.size() == 0);

    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);
    cout << "Success" << endl;
    cout << "//-------------------" << endl;
}

void TestMainTask()
{
    cout << endl << "TestMainTask" << endl;
    const int N = 10;

    Matrix<int, 0> m;
    for (int i = 0 ; i < N; i++)
    {
        m[i][i] = m[N-1-i][i] = i;
    }

    int n = 0;
    for (int i = 0; i < 8; i++)
        for (int j = i + 2; j < 10; j += 2)
        {
            m[i][j] = m[j][i] = 0;
            n++;
        }
    for(int i = 0; i < 5; i++)
    {
        m[i][i] = m[10-i-1][10-i] = 0;
        n++;
    }
    assert(n == 25); // 25 interations

    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            //auto v = m[i][j];
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    cout << "m.size() = " << m.size() << endl;

    for (auto item : m)
        cout << item.first << " = " << item.second << endl;

    cout << "//-------------------" << endl;
}

void TestPro4D()
{
    cout << endl << "TestPro4D" << endl;

    Matrix<int, -1, 4> matrix;
    int val = matrix[0][0][0][0];    // In case 'auto val': 'a' is ProxyAtOnce. So, I wrote 'int' explicit
    cout << "val (expected default) = " << val << endl;
    cout << "matrix.size() = " << matrix.size() << endl;

    matrix[0][0][0][0] = 314;
    cout << "matrix.size() = " << matrix.size() << endl;
    val = matrix[0][0][0][0];
    cout << "val (expected 314) = " << val << endl;
    cout << "matrix.size() = " << matrix.size() << endl;

    for (int i = 1; i < 5; i++)
        matrix[i+10][0][i*i][i*i*i] = i*i;

    for (auto item : matrix)
        cout << item.first << " = " << item.second << endl;

    cout << "matrix.size() = " << matrix.size() << endl;

    cout << "//-------------------" << endl;
}

void TestMyTest()
{
    cout << endl << "TestMyTest" << endl;

    Matrix<int, 0> matrix;
    cout << "matrix.size() = " << matrix.size() << endl;

    auto val = matrix.GetValue(0, 0);
    cout << "val (expected default) = " << val << endl;
    cout << "matrix.size() = " << matrix.size() << endl;

    //int t = 314;
    matrix.SetValue(314, 100, 100);
    val = matrix.GetValue(100, 100);
    cout << "val (expected 314) = " << val << endl;
    cout << "matrix.size() = " << matrix.size() << endl;

    int n = 0; int v;
    for (int i = 0; i < 8; i += 1)
        for (int j = i + 2; j < 10; j += 2)
        {
            v = i*10 + j;
            matrix.SetValue(v, i, j);
            matrix.SetValue(v, j, i);
            n++;
        }  
    for(int i = 0; i < 5; i++)
    {
        v = i*10 + i;
        matrix.SetValue(v, i, i);
        matrix.SetValue(v, 10-i-1, 10-i);
        n++;
    }
    cout << "n = " << n << endl;
    cout << "matrix.size() = " << matrix.size() << endl;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auto v = matrix.GetValue(i, j);
            cout << v << "\t"; // t instead of ' ' temporarily
        }
        cout << endl;
    }

    cout << endl;
    for (auto item : matrix)
        cout << item.first << " = " << item.second << endl;

    cout << "//-------------------" << endl;
}

/*
void TestMyRef()
{
    cout << endl << "TestMyTest" << endl;

    Matrix<int, -1> matrix;
    int val = matrix[0][0];
    cout << "val (expected default) = " << val << endl;
    cout << "matrix.size() = " << matrix.size() << endl;
    matrix[0][0] = 314;
    cout << "matrix.size() = " << matrix.size() << endl;

    val = matrix[0][0];
    cout << "val (expected 314) = " << val << endl;
    cout << "matrix.size() = " << matrix.size() << endl;


    int n = 0; int v;
    for (int i = 0; i < 8; i += 1)
        for (int j = i + 2; j < 10; j += 2)
        {
            v = i*10 + j;
            matrix[i][j] = v;
            matrix[j][i] = v;
            n++;
        }
    for(int i = 0; i < 5; i++)
    {
        v = i*10 + i;
        matrix[i][i] = v;
        matrix[10-i-1][10-i] = v;
        n++;
    }
    cout << "n = " << n << endl;
    cout << "matrix.size() = " << matrix.size() << endl;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int v = matrix[i][j];
            cout << v << "\t"; // t instead of ' ' temporarily
        }
        cout << endl;
    }

    cout << endl;
    for (auto item : matrix)
        cout << item.first << " = " << item.second << endl;


    cout << "//-------------------" << endl;
}
*/

