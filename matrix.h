#pragma once

#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <utility>
#include <cassert>
#include <memory.h>

using namespace std;

// __FUNCSIG__ is for VS, but Qt (mingw) works with __PRETTY_FUNCTION__
#if ((defined WIN32) || (defined WIN64)) && (defined _MSC_VER)
#define MY_P_FUNC __FUNCSIG__
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
// TestMyRef();
void TestPro4D();
//-----------------------------------------------

//struct CoordStruct_2D   // for the first try
//{
//    int i, j;
//    CoordStruct_2D() = delete;
//    CoordStruct_2D(int _i, int _j) : i(_i), j(_j) {}
//    CoordStruct_2D(const CoordStruct_2D &) = default;
//    CoordStruct_2D(CoordStruct_2D &&) = default;
//    bool operator<(const CoordStruct_2D &ob) const {return i < ob.j;} // for map optimization (two coordinats can be separated by a diagonal line)
//};


template <size_t N = 2>
struct CoordStruct
{
    int axes[N];
    CoordStruct() = default;  // might be dangerous

    template <typename... Args>
    CoordStruct(Args... args)
    {                                // compiled, but doesn't work!(( Even breaks GDB process (The GDB process terminated)! Why????????
        const int argc = sizeof...(args);
        assert(N==argc);
        int t[argc] = { (args)... };
        memcpy(axes, t, sizeof(axes));
    }

    CoordStruct(const CoordStruct<N> &) = default;
    CoordStruct(CoordStruct<N> &&) = default;

    bool operator<(const CoordStruct<N> &ob) const
    {
        // return what? I'm thinking about generalized planes, but let it be just something lexicographical

        // Ok, let's do something lexicographical
//        for (int i = 0; i < N; i++)
//        {
//            if (axes[i] == ob.axes[i])
//                continue;

//            if (axes[i] < ob.axes[i])
//                return true;
//            else
//                return false;
//        }
//        return false;

        return lexicographical_compare(axes, axes + N, ob.axes, ob.axes + N);
    }

//    bool operator==(const CoordStruct<N> &ob) const
//    {
//        return (memcmp(axes, ob.axes, sizeof(axes)) == 0); // Never called for std::map.
//    }

};

template <size_t N = 2>
ostream & operator<<(ostream &s, const CoordStruct<N> &ob)
{
    cout << "(";
    for (int i = 0; i < N; i++)
        cout << ob.axes[i] << ((i<N-1) ? ";" : ")");
    return s;
}
//-----------------------------------------------

template <typename T, const T DefVal, size_t N = 2>
class Matrix
{
private:

    pair<CoordStruct<N>,T> DefPair;
    T DefValForRes;
    map<CoordStruct<N>,T> data;
    CoordStruct<N> key;

    class flat_iterator
    {
    private:
       typename map<CoordStruct<N>,T>::iterator it;
    public:
        flat_iterator(typename map<CoordStruct<N>,T>::iterator _it) : it(_it) {}
        bool operator!=(const flat_iterator& _it){return it != _it.it;}
        void operator++() {++it;}
        auto & operator*() {return *it;}
    };

    class ProxyAtOnce
    {
    private:
        Matrix &self;
        CoordStruct<N> key;
    public:
        ProxyAtOnce(Matrix &_matrix, CoordStruct<N> _key) : self(_matrix), key(_key) {}
        ProxyAtOnce & operator=(T val)
        {
            if (val != DefVal)
                self.data.try_emplace(key , val);
            else
                self.data.erase(key);

            return *this;
        }

        ProxyAtOnce & operator=(const ProxyAtOnce &ob)   // =default doesn't work cos of '&self' (((
        {
            //self = ob.self;   doesn't work cos of '&self' (((
            *this = static_cast<T>(ob); // to cause operator T() and then operator=(T val)
            return *this;
        }

        operator T() const
        {
            return self.GetRefVal(key);
        }
    };


    template<int P, typename Dummy = void>
    class SubProxy
    {
    private:
        Matrix &self;
    public:
        SubProxy(Matrix &_matrix) : self(_matrix){}
        SubProxy<P+1> operator[](int i)
        {
            self.key.axes[P+1] = i;
            return SubProxy<P+1>(self);
        }
    };

    template<typename Dummy>
    class SubProxy<N-2, Dummy>
    {
    private:
        Matrix &self;
    public:
        SubProxy(Matrix &_matrix) : self(_matrix){}

        //SubProxy & operator=(const SubProxy & ob) = default;

        ProxyAtOnce operator[](int i)
        {
            self.key.axes[N-1] = i;
            return ProxyAtOnce(self, self.key);
        }
    };

public:

    size_t size() {return data.size();}

    template <typename... Args>
    void SetValue(const T &Value, Args... args);

    template <typename... Args>
    T & GetValue(Args... args);

    template <typename... Args>
    T & GetRefVal(Args... args);

    T & GetRefVal(CoordStruct<N> key);

    SubProxy<0> operator[](int i)
    {
        key.axes[0] = i;
        return SubProxy<0>(*this);
    }

    flat_iterator begin() {return data.begin();}
    flat_iterator end()   {return data.end();}
};
//-----------------------------------------------

template <typename T, T DefVal, size_t N>
template <typename... Args>
T & Matrix<T,DefVal,N>::GetRefVal(Args... args)
{
    assert(N==sizeof...(args));
    int realArgs[sizeof...(args)] = { (args)... };
    CoordStruct<N> key;
    memcpy(key.axes, realArgs, sizeof(realArgs));

    auto it = data.find(key);
    if (it != data.end()) // found (Required super-puper-proper operator<. Doesn't use operator==)
    {
        return (*it).second;
    }
    else // not found
    {
        DefValForRes = DefVal; // even if someone changes 'DefValForRes' before, it's DefVal again. So, 'const' version is not necessery.
        return DefValForRes;
    }
}
//-----------------------------------------------

template <typename T, T DefVal, size_t N>
T & Matrix<T,DefVal,N>::GetRefVal(CoordStruct<N> key)
{
    auto it = data.find(key);
    if (it != data.end()) // found (Required super-puper-proper operator<. Doesn't use operator==)
    {
        return (*it).second;
    }
    else // not found
    {
        DefValForRes = DefVal; // even if someone changes 'df' before, it's DefVal again. So, 'const' version is not necessery.
        return DefValForRes;
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

    if (it != data.end()) // found (Required super-puper-proper operator<. Doesn't use operator==)
    {
        if (Value != DefVal)
            (*it).second = Value;
        else
            data.erase(key);
    }
    else // not found
    {
        //pair<CoordStruct<N>,T> NewPair{key, Value};
        //data.insert(NewPair);

        //data.try_emplace( {(args)... , Value} ); // isn't compiled((( Why ???
        // cppinsight says: 'this->data.try_emplace<>(CoordStruct<2>{(__args1), (__args2), Value});'

        if (Value != DefVal)
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

