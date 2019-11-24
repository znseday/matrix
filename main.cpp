#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <cassert>

#include "matrix.h"

using namespace std;

int main()
{
#if (defined WIN32) || (defined WIN64)
    cout << "Homework matrix" << endl << endl;    // for debugging
    cout << MY_P_FUNC << endl;                    // for debugging
#else
    // some
#endif

    MY_DEBUG_ONLY(cout << "Homework matrix (DEBUG detected)" << endl);

    cout << "Hello, matrix!" << endl;

    //TestBasic();

    TestMyTest();

    //TestMainTask();

    return 0;
}

