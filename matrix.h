#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <utility>
#include <memory>


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


void TestStaggeredOrder();



//template <typename T>
//struct MyNodeStruct
//{
//	T data;
//	MyNodeStruct<T> *next;
//};

//template <typename T>
//class MyIterator
//{
//private:
//    MyNodeStruct<T> *pCur = nullptr;
//public:
//    MyIterator() = default;
//    MyIterator(MyNodeStruct<T> *p) : pCur(p) {}
//    bool operator!=(MyIterator it) const      // or (const MyIterator &it) as usual ???
//    {
//        return pCur != it.pCur;
//    }
//    MyIterator operator++()  // or MyIterator & operator++() ?
//    {
//        pCur = pCur->next;
//        return *this;
//    }
//    T & operator*() {return pCur->data;}
//    //const T & operator*() const  {return pCur->data;}
//};

//template <typename T, typename Allocator = std::allocator<T> >
//class MyListClass
//{
//private:

//public:

//    MyListClass();
//    MyListClass(const MyListClass &ob);



//    MyIterator<T> begin() {return MyIterator<T>(pHead);}
//    MyIterator<T> end()   {return MyIterator<T>();}

//    MyNodeStruct<T>* GetHead() const {return pHead;}
//    void HeadToNull() {pHead = nullptr;}
//};


