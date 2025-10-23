What is Function?
-----------------
- Function is block of code performing a unit task
- Function has return type,name and arguments
- Function is a way to achieve modularization
- Function can be predefined or user-defined
- Predefined function are declared in header files and defined in library files.


Declaration
-----------
- Function Declaration is also known as Function prototype
- Functions need to be declared before use (just like variables)
- Functions can be declared locally or globally
- ReturnType functionName(argumentList);
- Function definition is a block of code


Ways to define a function?
---------------------------
1. Takes Nothing, Returns Nothing
2. Takes Something, Returns Nothing
3. Takes Nothing, Returns Something
4. Takes Something, Returns Something

Formal and Autal Argument
-------------------------

| Feature        | Formal Argument                    | Actual Argument                      |
| -------------- | ---------------------------------- | ------------------------------------ |
| **Definition** | Placeholder in function definition | Real value/expression passed to call |
| **Scope**      | Local to function                  | Exists in caller's scope             |
| **Purpose**    | Receives values from actual args   | Provides values to the function      |
| **Example**    | `int a, int b`                     | `5, 10` or `x, y`                    |

```cpp
#include <iostream>
using namespace std;

// Function with formal arguments
void add(int a, int b) { // a and b are formal arguments
    cout << "Sum = " << a + b << endl;
}

int main() {
    add(5, 10); // 5 and 10 are actual arguments
    return 0;
}

```

Call by value
--------------
- When formal arguments are ordinary variable than it is function call by value
```cpp
void swap(int,int); -> Fd/FP
void swap(int a,int b){} -> FD/FB
swap(a,b); -> FC
```

Call by address
---------------
- When formal arguments are pointer variable than it is function call by address
```cpp
void swap(int *,int *);
void swap(int *a,int *b){}
swap(&a,&b);
```

Call by reference
-----------------
- When formal arguments are reference variable than it is function call by reference
```cpp
void swap(int &,int &);
void swap(int &a,int &b){}
swap(a,b);
```

Benefits of Functions
----------------------
- Easy to read
- Easy to Modify
- Avoids rewriting of same code
- Easy to debug
- Better memory utilization (save memory)
    - function call -> come in ram -> perform task -> free the ram -> control back
- but function time consuming process 
    - so for small taks not create function (cause save memory but time consume) but not easy to read and maintain
      so c++ provide solutin usnng inline functions.
    - for big task create function (cause save memory but time consume negligible )

Inline Functions
-----------------
- An inline function is a function for which the compiler attempts to insert the function code directly at the point of call,      instead of performing a regular function call.

- The main purpose is to reduce function call overhead, especially for small, frequently called functions.
- Declared using the keyword inline.

Inline is a request
--------------------
- inline is a request not a command.
- Inline functions work well for functions like getters, setters, or simple arithmetic.
- Compiler may ignore it for large functions
- So the compiler may ignore the request in some situations.
- Few of them (situations where the compiler may ignore the inline request):
    1. Function containing loops, switch, goto.
    2. Functions with recursion.
    3. Containing static variable.

```cpp
#include <iostream>
using namespace std;

inline int add(int a, int b) {  // inline function
    return a + b;
}

int main() {
    int x = 5, y = 10;
    cout << "Sum = " << add(x, y) << endl; // function call replaced by code in single line
    return 0;
}

```

💡 Tip: Use inline functions for very small functions to improve performance.


Default Parameter
-----------------
- default parameter as a “fallback value” for a formal argument.
- Rules:
    1. Default values must be provided from right to left.
    ```cpp
    void example(int a, int b = 2, int c = 3); // ✅ valid
    void example(int a = 1, int b, int c);     // ❌ invalid
    ```

    2. Default values can be in declaration or definition, not both (usually).
    ```cpp
    // Example: declaration
    void multiply(int x=1, int y = 1);
    // definition  
    void multiply(int x, int y) {
    cout << x * y << endl;
    }
    ```
    3. Cannot skip a middle parameter.
    ```cpp
    void example(int a = 1, int b, int c = 3); // ❌ invalid
    ```

- Advantages
    1. Reduces function overloading.
    2. Makes function calls simpler.
    3. Provides flexibility in calling functions with fewer arguments.


Function Overloadding
---------------------
- A same function overloaded with multiple job is called FO.
- Different function signature (same function name but diffent in parameter(types/number etc))
- way of implementing compile time polymorphizm
Read this after structuei,class,consrcito and deconstructor concept


