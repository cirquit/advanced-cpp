# 6-1: Full-Throttle Functional


You perhaps (hopefully) remember a fact that has been overstated in Session-02 and
Session-01 in this course: C++ is a paradigm-agnostic language.

The increasing relevance of functional programming in C++ has become evident in
numerous aspects discussed in the recent sessions.
Along the way, we found that even pure functions can be defined as expressions
that can be calculated at compile-time.

Now, let's put this to a real test and evaluate list expressions in Lisp, the
archangel of functional programming, against compile-time capabilities of C++.

Lisp provides some fundamental functions that suffice to express any algorithm on
value sequences. In C++, we use `std::array` as an equivalent.

> **Q:** `std::array` is a static data structure. Could we benefit from `std::vector`?

These fundamental functions are:

- take
- drop
- split
- concat

Their implementation in C++11, along with some additional common functions like
`head` and `tail`, is attached to this assignment:

[Array Expressions](array_expr.h), [Functional Expressions](functional_expr.h), [Index Sequence](index_sequence.h)

The original code is part of the [DASH](http://www.dash-project.org), a research
project of our chair et al., and can be found
[here](https://github.com/dash-project/dash/tree/feat-191-lranges/dash/include/dash/util).

Study the code and try to reason about these function definitions from what you
learned so far.


The support of `constexpr` functions is drastically improved in C++14 so most of
the "intruiging" mechanisms you will stumble upon are not needed.

In effect, the function `reverse` which reverses the order of elements in a
sequence can be defined as:

```c++
template <
  class        ValueT,
  std::size_t  NElem >
constexpr std::array<ValueT, NElem>
reverse(
  const std::array<ValueT, NElem> & values) {
  return (NElem > 1
          ? ( ce::append(
                ce::reverse(
                  ce::tail(values)),
                ce::head(values)) )
          : values);
}
```

An equivalent implementation in Lisp:

```Lisp
(define (reverse l)
  (if (null? l)
     nil
     (append (reverse (cdr l)) (list (car l)))
  )
)
```

Now the problem assignment:

- Implement compile-time Quicksort using C++11 `constexpr`.
- Implement a compile-time equivalent of `std::transform` using C++11 `constexpr`.