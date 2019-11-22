#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <utility>
#include <memory.h>
#include <cassert>

using namespace std;

// __FUNCSIG__ is for VS, but Qt (mingw) works with __PRETTY_FUNCTION__
#if ((defined WIN32) || (defined WIN64)) && (defined _MSC_VER)
//#define MY_P_FUNC __FUNCSIG__
#else
#define MY_P_FUNC __PRETTY_FUNCTION__
#endif

#if ((defined NDEBUG) || (defined _NDEBUG))
#define MY_DEBUG_ONLY(x)
#else
#define MY_DEBUG_ONLY(x) (x)
#endif

void TestBasic();
void TestMainTask();
void TestMyTest();
//-----------------------------------------------

// struct CoordStruct_2D  // for the first try
// {
//     int i, j;
//     CoordStruct_2D() = delete;
//     CoordStruct_2D(int _i, int _j) : i(_i), j(_j) {}
//     CoordStruct_2D(const CoordStruct_2D &) = default;
//     CoordStruct_2D(CoordStruct_2D &&) = default;
//     bool operator<(const CoordStruct_2D &ob) {return i < ob.j;} // for map optimization (two coordinats can be separated diagonal line)
// };


template <size_t N = 2>
struct CoordStruct
{
    int axes[N];
    CoordStruct() = default;  // might be dangerous

    template <typename... Args>
    CoordStruct(Args... args)
    {                                // compiled, but doesn't work!(( Even breaks GDB process! Why????????
        const int argc = sizeof...(args);
        assert(N==argc);
        int t[argc] = { (args)... };
        memcpy(axes, t, sizeof(axes));
    }

    CoordStruct(const CoordStruct<N> &) = default;
    CoordStruct(CoordStruct<N> &&) = default;

    bool operator<(const CoordStruct<N> &ob) const
    {
        int sum_1 = 0, sum_2 = 0;
        for (auto v : axes)
            sum_1 += v;
        for (auto v : ob.axes)
            sum_1 += v;
        return sum_1 < sum_2;
    } // return what? I'm thinking about generalized planes, but let it be just sum

    bool operator==(const CoordStruct<N> &ob) const
    {
        return (memcmp(axes, ob.axes, sizeof(axes)) == 0); // Never called. Why????
    }
};
//-----------------------------------------------

template <typename T, const T DefVal, size_t N = 2>
class Matrix
{
private:

    pair<CoordStruct<N>,T> DefPair;
    map<CoordStruct<N>,T> data;

public:

    size_t size() {return data.size();}

    template <typename... Args>
    pair<CoordStruct<N>,T> operator()(Args... args); // just for start to code something

    //T & operator()(int r, int c);

    template <typename... Args>
    void SetValue(const T &Value, Args... args);

    template <typename... Args>
    T & GetValue(Args... args);
};
//-----------------------------------------------

template <typename T, T DefVal, size_t N>
template <typename... Args>
pair<CoordStruct<N>,T>  Matrix<T,DefVal,N>::operator()(Args... args)
{
    assert(N==sizeof...(args));
    int realArgs[sizeof...(args)] = { (args)... };

    //CoordStruct<N> key = { (args)... }; // compiled, but doesn't work!(( Even breaks GDB process! Why?

    CoordStruct<N> key;
    memcpy(key.axes, realArgs, sizeof(realArgs));

    //auto it = data.find(key);
    typename map<CoordStruct<N>,T>::iterator it = data.find(key);

    if (it != data.end()) // found
    {
        return *it;
    }
    else // not found
    {
        memcpy(DefPair.first.axes, realArgs, sizeof(DefPair.first.axes));
        DefPair.second = DefVal; // even if someone changes 'df' before, it's DefVal again. So, 'const' version is not necessery.
        return DefPair;
    }
}
//-----------------------------------------------

template <typename T, T DefVal, size_t N>
template <typename... Args>
void Matrix<T,DefVal,N>::SetValue(const T &Value, Args... args)
{
    assert(N==sizeof...(args));
    int realArgs[sizeof...(args)] = { (args)... };
    //CoordStruct<N> key = { (args)... };

    CoordStruct<N> key;
    memcpy(key.axes, realArgs, sizeof(realArgs));

    auto it = data.find(key);

    if (it != data.end()) // found    (it's that for any key. Why ??????)
    {
        (*it).second = Value; // it's executed for any key. Why ?????????
    }
    else // not found
    {
        //pair<CoordStruct<N>,T> NewPair{key, Value};
        //data.insert(NewPair);

        //data.try_emplace( {(args)... , Value} ); // isn't compiled((( Why ???
        // cppinsight says: 'this->data.try_emplace<>(CoordStruct<2>{(__args1), (__args2), Value});'

        data.try_emplace( key , Value );
    }
}
//-----------------------------------------------

template <typename T, T DefVal, size_t N>
template <typename... Args>
T & Matrix<T,DefVal,N>::GetValue(Args... args)
{
    assert(N==sizeof...(args));
    int realArgs[sizeof...(args)] = { (args)... };
    //CoordStruct<N> key = { (args)... };

    CoordStruct<N> key;
    memcpy(key.axes, realArgs, sizeof(realArgs));

    auto it = data.find(key);

    if (it != data.end()) // found
    {
        return it->second;
    }
    else // not found
    {
        memcpy(DefPair.first.axes, realArgs, sizeof(DefPair.first.axes));
        DefPair.second = DefVal; // even if someone changes 'df' before, it's DefVal again. So, 'const' version is not necessery.
        return DefPair.second;
    }
}
//-----------------------------------------------



//template<typename T>
//void operator=(pair<CoordStruct,T> &dst, const T &src)
//{
//    dst.second = src;
//}

//template<typename T>
//T &operator=(T &dst, const pair<CoordStruct,T> &src)
//{
//    dst = src.second;
//}
