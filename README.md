# [CppCon 2017: Vinnie Falco “Make Classes Great Again! (Using Concepts for Customization Points)”](https://www.youtube.com/watch?v=WsUnnYEKPnI)

The repository contains code of the presentation called `Make Classes Great Again! (Using Concepts for Customization Points)`
of CppCon 2017 from [Vinnie Falco](https://github.com/vinniefalco).

Everything starts with version `v1` and gets refactored to solve certain problems.

## v1
First version of an implementation.

Problems
- `write` calls specific methods on the body type, they would have to be the same (name and behavior) for all types
    - for example reading a file and writing the content is not possible
- `Body` type uses space even though it is not necessarily used

## v2 (zero-cost abstraction - don't pay for what you don't use)
This version tries to solve the problems from v1.

Instead of the body template parameter as the type for the container, use a nested type named `value_type`.
This prevents the instantiation and just names another type.

In the `write` function delegate the call to a static member function of the `Body` type.
If write is not implemented (null object), we don't have unnecessary calls.

## v3
Solve the problem that the size of the body member can't be zero.
```
assert(sizeof(req_v2_1.body) == 0);  // fails with v2 implementation
```
>The address of any data member of a class must be distinct from the address of every other data member.

To solve this the member is replaced by accessor functions. For this the [Empty base optimization - cppreference.com](https://en.cppreference.com/w/cpp/language/ebo) feature is used.

>If a class is derived from another class and that other class has no data members, then it does not add to the size of the derived class.