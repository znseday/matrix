#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <cassert>

#include "matrix.h"

using namespace std;

//template <size_t N = 2>
//struct KeyStruct
//{
//    int axes[N];
//    bool operator<(const KeyStruct &ob) const
//    {
//        int sum1 = 0;
//        for(auto i: axes)
//            sum1 += i;
//        int sum2 = 0;
//        for(auto i: ob.axes)
//            sum2 += i;
//        return sum1 < sum2;
//    }
//};


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

//    map<KeyStruct<>, double> m;

//    KeyStruct<> k{1,2};
//    m.try_emplace( k , 12.3 );

//    k = KeyStruct<>{1,5};
//    auto it = m.find(k);

//    if (it != m.end()) // found    (it's that for any key. Why ??????)
//    {
//        (*it).second = 152.66; // it's executed for any key. Why ?????????
//        cout << "k is found" << endl;
//    }

//    k = KeyStruct<>{1,5};
//    m.try_emplace( k , 15.2 );

//    cout << "m.size() = " << m.size() << endl;

//    k = KeyStruct<>{1,5};
//    it = m.find(k);
//    if (it != m.end()) // found    (it's that for any key. Why ??????)
//    {
//        (*it).second = 152.66; // it's executed for any key. Why ?????????
//        cout << "k is found" << endl;
//    }

    return 0;
}

