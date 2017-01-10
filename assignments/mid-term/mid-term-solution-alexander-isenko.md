## Midterm Assignment - Alexander Isenko

### 1. Types, Classes, Objects and their State
#### 1.1 Object Definition
> Assuming your are confronted with a class that supports the following use case:
> ```c++
> DateParser date_parser;
> date_parser.set_date(today);
> 
> auto day = date_parser.day_of_week()
> ```
>
> Q: What is your objection to this? How would you change the interface of class `DateParser`?

**Answer:** The method `day_of_week` is not valid without the previous `set_date` call.
I would enforce to use a constructor with the argument `today`.


#### 1.2 Standard Object Semantics

> Given the following implementation of class `SemanticSurprise`:
> 
> ```c++
> class SemanticSurprise {
> public:
> 
>   SemanticSurprise(int value)
>   : _value(value) { }
> 
>   SemanticSurprise(const SemanticSurprise & other)
>   : _value(other._value) { } 
> 
>   bool operator==(const SemanticSurprise & other) const {
>     return _value == other._value;
>   }
> 
>   int value() {
>     return _value;
>   }
> 
> private:
>   int _value;
> };
> ```

> Q: Are there any compiler errors? If so: why?

**Answer:** There are none. (The following code was not included in this answer)

> ```c++
> 1  SemanticSurprise s1;          // <-- Op?
> 2  s1.value();                   // <-- value?
> 3
> 4  SemanticSurprise s2(4);       // <-- Op?
> 5  s2.value();                   // <-- value?
> 6
> 7  SemanticSurprise s3 = s2;     // <-- Op?
> 8  s3.value();                   // <-- value?
> 9
> 10 SemanticSurprise s4(s3);      // <-- Op?
> 11 s4 == s3;                     // <-- value?
> 12 s2 != s3;                     // <-- value?
> ```

> Q: Name the method/operation on SemanticSurprise in every line marked with Op?, including those that lead to compiler errors.

**Answer:** 
* Line 1, there is a default constructor missing (compile error)
* Line 4, the custom constructor is called
* Line 7, s3 is allocated, copy constructor is called
* Line 10, copy constructor is called

> Q: Which values are returned in the lines marked with value? (given the line does not lead to a compiler error). Explain why these values are returned.

**Answer:**
* Line 2, if this would compile, it should return garbage. (not specified in standart, `g++` returns garbage, `clang++` returns `0`)
* Line 5, returns `4`
* Line 8, returns `4`, because the copy constructor got the value from `s2`
* Line 11, returns `1`, stands for `true`
* Line 12, returns `0`, if this would compile and derive the `operator!=` from `operator==`

> Q: How can this implementation be simplified? What is the requirement for this simplification?

**Answer:**

We could remove the explicit copy constructor (see Rule of Zero).
If we would want that everything compiles, we have to create a constructor and an `operator!=`:

```c++
class SemanticSurprise {
public:

  SemanticSurprise()
  : _value(0) { }

  SemanticSurprise(int value)
  : _value(value) { }

  bool operator==(const SemanticSurprise & other) const {
    return _value == other._value;
  }

  bool operator!=(const SemanticSurprise & other) const {
    return !(*this == other);
  }

  int value() {
    return _value;
  }

private:
  int _value;
};
```

> Given the implementation of SemanticSurprise above, the following use case leads to a compiler error:
>>
> ```c++
> void print_surprise(const SemanticSurprise & s) {
>   std::cout << "SemanticSurprise.value: " << s.value() << std::endl;
> }
> print_surprise(SemanticSurprise(10));
> ```
>
> Q: Explain the compiler error and how the implementation of SemanticSurprise has to be corrected.

**Answer:**

The problem is the `const` identifier in the argument of `print_surprise`. We call `value()` in this function and the compiler can't be sure that this doesn't modify the object. We have to append the `const` keyword to signal the compiler that the use of this function does not change the object in any way. And `constexpr` for future optimizations too.

```c++
class SemanticSurprise {
public:
...
  constexpr int value() const {
    return _value;
  }
...
```

#### 1.3 Resource Ownership

> Consider the following use case:
> 
> ```c++
> // ...
> if (condition) {
>         LogFileReader log_reader("performance.log");
>         if (log_reader.lines().size() > 1024) { return; }
> }
> // ...
> ```
> 
> Q: Judging from its usage illustrated above: which rule must be satisfied in the implementation of class LogFileReader (or one of its members)?

**Answer:**
The Rule of Zero/Three/Five should be satisfied, because if an exception happens after the `LogFileReader` aquired the resource `"performance.log"` it should release it without a doubt. If the destructor it not defined properly, this leads to resource leaks.

> Q: Name a popular technique in resource management that depends on this rule, and briefly explain its principle.

**Answer:**
This technique/iodom is called **RAII** (*Resource acquisition is initialization*) and states that resource allocation happens in the initialization phase and the release of resources happens by the destructor. This means that if there are no object leaks, there aren't any resource leaks.

#### 1.X Bonus

> Have a look at this example code from the lecture “CMSC 12300 - Computer Science with Applications 3” at University of Chicago:
> 
> ```c++
> #include"basefrequentflyer.h"
> #include"frequentflyer.h"
> #include"silverfrequentflyer.h"
> #include"goldfrequentflyer.h"
> #include<iostream>
> using namespace std;
> 
> int main()
> {
>   BaseFrequentFlyer* f[3];
>   
>   f[0] = new FrequentFlyer ("Cornelius Doe", 23166841, 100);
>   f[1] = new SilverFrequentFlyer ("Lucius Doe", 94565432, 100, 5);
>   f[2] = new GoldFrequentFlyer("Rufus Doe", 32155994, 100, 100);
> 
>   f[0]->addMiles(100);
>   f[1]->addMiles(100);
>   f[2]->addMiles(100);
> 
>   f[0]->printData();
>   f[1]->printData();
>   f[2]->printData();
>   
>   delete f[0];
>   delete f[1];
>   delete f[2];
> }
> ```
> 
> Q: Do you have any objections? Improve the implementation.

**Answer**

This would be my implementation:


```c++
// some boilerplate to check validity
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

class BaseFrequentFlyer {
public:

  BaseFrequentFlyer()
  : _name("")
  , _number(0)
  , _miles(0) { }

  BaseFrequentFlyer(std::string name, int number, int miles)
  : _name(name)
  , _number(number)
  , _miles(miles) { }

  void addMiles ( int realMiles ) { _miles += realMiles; }
  void printData ()
  {
      std::cout << "Name: " << _name << std::endl;
      std::cout << "Number: " << _number << std::endl;
      std::cout << "Miles: " << _miles << std::endl;
  }

protected:
  std::string _name;
  int         _number;
  int         _miles;

};

class FrequentFlyer : public BaseFrequentFlyer {
public:
  FrequentFlyer(std::string name, int number, int miles)
  : BaseFrequentFlyer(name, number, miles) { }
};

class SilverFrequentFlyer : public FrequentFlyer {
public:
  SilverFrequentFlyer(std::string name, int number, int miles, int years)
  : FrequentFlyer(name, number, miles), _years(years) { }

private:
  int _years;
};

class GoldFrequentFlyer : public FrequentFlyer {
public:
  GoldFrequentFlyer(std::string name, int number, int miles, int years)
  : FrequentFlyer(name, number, miles), _years(years) { }

private:
  int _years;
};

// implementation starts here

int main()
{
    std::vector<BaseFrequentFlyer> f { FrequentFlyer ("Cornelius Doe", 23166841, 100)
                                     , SilverFrequentFlyer ("Lucius Doe", 94565432, 100, 5)
                                     , GoldFrequentFlyer("Rufus Doe", 32155994, 100, 100) };

    for_each(f.begin()
           , f.end()
           , [](BaseFrequentFlyer & flyer)
           {
             flyer.addMiles(100);
             flyer.printData();
           });
}
```

> Q: Also: what is the most important guideline on the use of new and delete that comes to your mind? (hint: session 02)

**Answer**: Never use `new` and `delete`. Follow the Rule of Zero/Three/Five.

### 2. Container Types, Class Template Basics

### 3. Iterators

#### 3.1 Algorithm Basics

> The following algorithm dereferences and returns a given iterator’s successor unless the successor’s referenced value matches some condition. The algorithm is semantically correct but does not compile for iterators of some containers.

> ```c++
> template <typename Iterator, typename Value = typename Iterator::value_type>
> Value next_value_or_default(Iterator it, Iterator end, Value default) {
>   if (it == end || it+1 == end) { return default; }
>   return it[1];
> }
> ```

> Q: Which containers? Briefly explain why the algorithm does not work for these and how it has to be changed.

**Answer**:
We need at least a RandomAccessIterator, because we make use of `it+1` and `it[1]`. Does not compile for
* istream
* ostream
* inserter
* forward_list
* unordered_map
* unordered_set
* list

The code should be changed to:
```c++
#include <iterator>

template <typename Iterator, typename Value = typename Iterator::value_type>
Value next_value_or_default(Iterator it, Iterator end, Value default) {
  std::advance(it, 1);
  if (it == end ) { return default; }
  return *it;
}
```

#### 3.2 Container Wrapper

> The STL’s `std::vector` guarantess that its elements are stored in a contiguous memory region and is therefore compatible to C-style arrays. The member function .data() returns a pointer to the vector’s underlying raw memory.
>
> For many hardware-tuning techniques, data is accessed in chunks. Assuming a `std::vector<uint32_t>` and 64 bytes per cache line, for example, vector elements could be loaded in chunks of 64/(32/8) = 16 elements.

> Write a container wrapper `cpppc::chunks<B, T, Container>` that provides a sequential container interface on elements in Container in chunks of maximum size B bytes.


** TODO - get the code working not only for chunks **

### 4. Debugging

> Use gdb to debug the program implemented in the attached source file a-midterm/debug.cc. Running the program leads to a segfault.
>
> Q: Use gdb to determine the source code location (stack trace) of the statement that causes the segmentation violation fault. Attach a screenshot or plaintext copy of gdb’s output.

```c++
#include <iostream>
#include <algorithm>
#include <numeric>
#include <list>

template <typename List, typename UnaryPred>
List & drop(List & l, UnaryPred condition) {
  for (auto i = l.begin(); i != l.end(); ++i) {
    if (condition(*i)) {
      l.erase(i);
    }
  }
  return l;
}

int main() {

  std::list<int> l;

  std::generate_n(
    std::back_inserter(l), 10,
    []() { return std::rand() % 1024; });

  auto & ld = drop(l, [](int x) -> bool {
                        return x % 3 == 0;
                      });

  return EXIT_SUCCESS;
}

```


**Answer**: After fixing the obvious errors, like `return` in the lambda and `drop`, `vector -> list` and a missing paramter in `generate_n`, we could compile the program. The problem is that the `erase` call in the `drop` function invalidates the current iterator `i`. That way we can't increment it.

Here is the `gdb` output.

![gdb output](4/gdb-output.png "GDB Output")

The easy fix is to post-increment the iterator:

```c++
template <typename Vector, typename UnaryPred>
Vector & drop(Vector & v, UnaryPred condition) {
  for (auto i = v.begin(); i != v.end(); ++i) {
    if (condition(*i)) {
      v.erase((i++));
    }
  }
  return v;
}
```

### 5. Algorithms, Function Templates, Type Deduction

#### 5.1 Defining Functions

> Implement a function interface `void log10(X)` that accepts a numeric value of type `X` and:

> Q: Prints the base 10 logarithm of the value if it is an integer and
     prints the base 10 logarithm of the value’s square root if it is a floating point value

**Answer**:

```c++
#include <iostream>
#include <algorithm>

template<typename X>
void log10(X x)
{   
    if (std::is_integral<X>::value)
    {
      std::cout << std::log10(x) << '\n';
    } else
    {
      std::cout << std::log10(std::sqrt(x)) << '\n';
    }

    
}

int main(int argc, char const *argv[])
{
  int   i = 10;
  float f = 10.0;
  std::cout << "int: ";
  log10(i);
  std::cout << "double: ";
  log10(f);
  return 0;
}
```
*Output*:

```bash
int: 1
double: 0.5
```

> Q: Implement a function interface `void print_walk(T begin, T end)` that accepts a range of iterators of type T and prints all values in the range. In this, the iteration order depends on the iterator type:
> * for random-access iterators, tha order should be (pseudo) random but every element in the range must only be printed once
> * for input iterators, elements are printed in order from begin to end-1
> * for bidirectional iterators, elements are printed in reverse order from end-1 to begin

**Answer**:

```c++
#include <iostream>
#include <algorithm>
#include <iterator>

#include <vector>
#include <list>
#include <sstream>

// using dispatcher function from cppreference

template <class RandomAccess>
void print_walk(RandomAccess begin, RandomAccess end, std::random_access_iterator_tag)
{
  std::random_shuffle(begin,end);
  std::cout << "RandomAccess Iterator:  ";
  for(auto it = begin; it != end; ++it){
      std::cout << *it << " ";
  }
  std::cout << '\n';

}

template <class BiDirectional>
void print_walk(BiDirectional begin, BiDirectional end, std::bidirectional_iterator_tag)
{
  std::reverse(begin, end);
  std::cout << "BiDirectional Iterator: ";
  for(auto it = begin; it != end; ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << '\n';
}

template <class Input>
void print_walk(Input begin, Input end, std::input_iterator_tag)
{
  std::cout << "Input Iterator:         ";
  for(auto it = begin; it != end; ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << '\n';
}

template< class Iter >
void print_walk(Iter first, Iter last)
{
    print_walk(first, last,
        typename std::iterator_traits<Iter>::iterator_category());
}


int main(int argc, char const *argv[])
{
  std::vector<int>       v  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  std::list<int>         l  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  std::istringstream s("0123456789");
  std::istream_iterator<char> eos;
  std::istream_iterator<char> isi(s);

  std::cout << "Vector          is a  "; 
  print_walk(v.begin(), v.end());
  std::cout << "List            is a  ";
  print_walk(l.begin(), l.end());
  std::cout << "IStreamIterator is an ";
  print_walk(isi, eos);

  return 0;
}
```

*Output*:
```bash
Vector          is a  RandomAccess Iterator:  4 3 7 8 0 5 2 1 6 9 
List            is a  BiDirectional Iterator: 9 8 7 6 5 4 3 2 1 0 
IStreamIterator is an Input Iterator:         0 1 2 3 4 5 6 7 8 9
```

### 6. STL-Compatible Sequence Containers
#### 6.1 Lazy Sequence Container

### 7. Thread-Safety
#### 7.1 Parallelism and STL Containers

> Given the following operations on an instance of `std::vector`, consider operation in the same table row to be executed by multiple threads in parallel:
> ```c++
> // Shared vector instance accessed by thread A and thread B:
> std::vector<int> v;
> 
> // thread A:                    | thread B:
> // =============================|==============================
>    std::vector<int> a;          | std::vector<int> b;           (1)
> // -----------------------------+------------------------------
>    int xa = v[3];               | int xb = v[4];                (2)
> // -----------------------------+------------------------------
>    v[3] = 123;                  | v[4] = 345;                   (3)
> // -----------------------------+------------------------------
>    v[3] = 123;                  | int xb = v[3];                (4)
> // -----------------------------+------------------------------
>    v.push_back(24);             | v.size();                     (5)
> // -----------------------------+------------------------------
>    v.back();                    | v.push_back(54);              (6)
> // -----------------------------+------------------------------
>    v.begin();                   | v.push_back(34);              (7)
> // -----------------------------+------------------------------
>    v.back();                    | v.pop_back();                 (8)
> // -----------------------------+------------------------------
> ```

> Q: For every pair of operation on the same table row, give a brief explanation on the guarantees with respect to thread-safety according to the C++ standard.

**Answer**:

  * (1) Ok, no shared resources used
  * (2) Ok, because [the Thread safety p.4](http://en.cppreference.com/w/cpp/container) guarantees that iterator operations are safe for reading
  * (3) Ok, because [the Thread safety p.3](http://en.cppreference.com/w/cpp/container) says it's ok to modify different elements in the same container
  * (4) Ok, but only because `v[3] = 123` is valid since step 3. Therefore there is no possiblity that this value is ambiguous
  * (5) Not ok, this is a modification of the container and the result of `size()` is dependent on the `push_back(24)`. `size()` may be `4`, or `5`
  * (6) Not ok, same problem as in (5), `back()` is dependent on `push_back(54)`
  * (7) Ok, because `begin()` returns the reference on the first element of the vector and does not change if an element is appended
  * (8) Not ok, same problem as in (5) and (6), `back()` is dependent on `pop_back()`

#### 7.2 Producer-Consumer Problem

> Simply put, one thread is producing goods and another thread is consuming goods. We want the consumer thread to wait using a condition variable, and we want goods.push(i) to be mutually exclusive to goods.pop().
>
>We are letting c++ and c– be surrogates for this mutual exclusion, since we can easily check if we correctly end up with 0 in the end.
>
>Run the code as it is, and you will see that the net value is way off: