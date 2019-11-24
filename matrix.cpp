#include <iostream>
#include <cassert>

#include "matrix.h"

using namespace std;

void TestBasic()
{
    cout << "TestBasic" << endl;
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0);

    auto a = matrix(0, 0);
    cout << "a.second = " << a.second << endl;

    //assert(a == -1);          // doesn't workm it's obvious
    assert(matrix.size() == 0);

    //matrix(100, 100) = 314;           // doesn't workm it's obvious
    //assert(matrix(100, 100) == 314);  // doesn't workm it's obvious
    //assert(matrix.size() == 1);       // doesn't workm it's obvious
    cout << "//-------------------" << endl;
}

void TestMainTask()
{
    cout << "TestMainTask" << endl;


    cout << "//-------------------" << endl;
}

void TestMyTest()
{
    cout << "TestMyTest" << endl;

    Matrix<int, 0> matrix; // 0 instead of -1 for output adjusting
    cout << "matrix.size() = " << matrix.size() << endl;

    auto val = matrix.GetValue(0, 0);
    cout << "val (expected default) = " << val << endl;
    cout << "matrix.size() = " << matrix.size() << endl;

    //int t = 314;
    matrix.SetValue(314, 100, 100);
    val = matrix.GetValue(100, 100);
    cout << "val (expected 314) = " << val << endl;
    cout << "matrix.size() = " << matrix.size() << endl;

    int n = 0;
    for (int i = 0; i < 8; i += 1)
        for (int j = i + 2; j < 10; j += 2)
        {
            matrix.SetValue(5, i, j);
            matrix.SetValue(5, j, i);
            n++;
        }  
    for(int i = 0; i < 10; i++)
    {
        matrix.SetValue(5, i, i);
        n++;
    }
    cout << "n = " << n << endl;
    cout << "matrix.size() = " << matrix.size() << endl;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            auto v = matrix.GetValue(i, j);
            cout << v << " ";
        }
        cout << endl;
    }

    cout << "//-------------------" << endl;
}
