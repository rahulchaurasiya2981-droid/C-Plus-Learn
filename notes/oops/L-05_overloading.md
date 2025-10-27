## Overloading

1. Function Overloading (in single scope) (Different FS)
2. Function Hiding      (in class/base) (in diff scope) (Different FS)
3. Function Overriding  (in class(virtual)/base(override,final)) (same function prototype)
4. Operator Overloading

## Function Overloading

- A same function is overloaded with multiple job is called FO
- Function signature (FN + FA) :> function name + function arguments
- C++ say you can't write function with same FS otherwise i will give error
- FO = Different function signature (same FN + different in FA)
- It is used to implement compile time polymorphism (binding of function call with correct function defination/body happen at)
- also called static polymorphismcompile time.
- compiler follow some rule to bind FC to FD 0. compiler fist find all functino with that function name called -> candidates
  1. Exact Match  
      - number & DT of actual/formal arguments should be same
     2 Type Promotion  
      - actual argument converted into other DT (char -> int) -> than 1st rule check
  2. Type Conversion
     - actual arguent DT convert into all possible primitice DT -> than 1st rule check
     - not if more than 1 version available compiler will show the error

```cpp
int add(int a,int b)
{
    return (a+b);
}

int add(int a,int b,int c)
{
    return (a+b+c);
}

double add(double a,double b)
{
    return (a+b);
}

double add(int a,double b)
{
    return (a+b);
}

int main()
{
    cout<<add(1,1)<<endl;
    cout<<add(1,1,1)<<endl;
    cout<<add(1.1,1.1)<<endl;
    cout<<add(1,1.1)<<endl;
    // cout<<add(1.1,1)<<endl;  // error: call of overloaded 'add(double, int)' is ambiguous
    return 0;
}
```

- In class

```cpp
class Calculator
{
public:
    int add(int a, int b)
    {
        return (a + b);
    }

    int add(int a, int b, int c)
    {
        return (a + b + c);
    }

    double add(double a, double b)
    {
        return (a + b);
    }

    double add(int a, double b)
    {
        return (a + b);
    }
};

int main()
{
    Calculator calc;
    cout << calc.add(1, 1) << endl;
    cout << calc.add(1, 1, 1) << endl;
    cout << calc.add(1.1, 1.1) << endl;
    cout << calc.add(1, 1.1) << endl;
    // cout<<calc.add(1.1,1)<<endl;  // error: call of overloaded 'add(double, int)' is ambiguous
    return 0;
}
```

- Note : FO should be in same scope
- Proof

```cpp
class A
{
    public:
    void add(int a,int b){ cout<<"A::add"<<endl; }
};
class B:public A
{
    public:
    void add(double a,double b){ cout<<"B::add"<<endl; }
};
int main()
{
    B b1;
    b1.add(1,2);      // B::add
    b1.add(1.5,1.5);  // B::add
    return 0;
}
```

- b1.add() running class B method by hidig class A method
- so in This FO is become Funciton hiding (Different FS)(but difined in diffent scope)
- Causes compiler find the add() in B class so no need to search in A class.
- solutin : keep overloaded function inn single scope

```cpp
class A
{

};
class B:public A
{
    public:
    void add(int a,int b){ cout<<"A::add"<<endl; }
    void add(double a,double b){ cout<<"B::add"<<endl; }
};
int main()
{
    B b1;
    b1.add(1,2);      // A::add
    b1.add(1.5,1.5);  // B::add
    return 0;
}
```

## Function hiding

- Function Hiding happen when the derived class function has the same name as a base class function, but the parameter list (function signature) is different.
- In this case, all overloaded versions of that function name in the base class are hidden in the derived class.
- bind happen at compile time(early binding) by using caller object

```cpp
class A
{
    public:
    void show()
    {
        cout<<"Base : show()..."<<endl;
    }
        void show(int x)
    {
        cout<<"Base : show(int)..."<<endl;
    }
};
class B:public A
{
    public:
    void show(string name)
    {
        cout<<"Derived : show(string)..."<<endl;
    }
};
int main()
{
    B b1;
    b1.show("rahul");
    // b1.show();      // error: no matching function for call to 'B::show()'
    // b1.show(1);        // error: no matching function for call to 'B::show(int)'
    return 0;
}
```

- The derived class show(string) hides all overloaded versions of show() in the base class.
- This is not overriding, it’s hiding because : Function signatures differ (string vs int or no argument).

```cpp
class A
{
    public:
    void show()
    {
        cout<<"Base : show()..."<<endl;
    }
        void show(int x)
    {
        cout<<"Base : show(int)..."<<endl;
    }
};
class B:public A
{
};
int main()
{
    B b1;
    // b1.show("rahul");  // error: invalid conversion from 'const char*' to 'int' [-fpermissive]
    b1.show();         // Base : show()...
    b1.show(1);        // Base : show(int)...
    return 0;
}
```

## Function Overriding

- Derived class method need to have same prototype( same RT,FS) with base class method.
- It is way of implementing runtime polymorphism (by using virtual keyword)

```cpp
class A
{
public:
    void f1(int x) { cout << "A::f1()"; }
};

class B : public A
{
public:
    void f1(int x) { cout << "B::f1()"; }  // same functio prototype
};

int main()
{
    B b1;
    b1.f1(1); // B::f1()
    return 0;
}
```

- Parent class pointer can hold parent/child object address
- Child class pointer only hold child object address

```cpp
int main()
{
    A *p=new B;
    p->f1(1);  // A::f1()
    return 0;
}
```

- printing A::f1() but i need B::f1() so metod overriding is not happen in this case cause binding is happen at compile time (early bind)
- the compile bind(early bind) is happen based on pointer DT(caller DT) (so go to class A and search f1 -> pring A::f1())
- so for maintain the F overriding concept we need to use virtual keyword in base class
- virtual : allow the binding happen at runtime
- runtime binding happen based on object pointed by pointer (not pointer DT)

```cpp
class A
{
public:
    virtual void f1(int x) { cout << "A::f1()"; }
};

class B : public A
{
public:
    void f1(int x) { cout << "B::f1()"; }  // same functio prototype
};

int main()
{
    A *p=new B;
    p->f1(1);  // B::f1()
    return 0;
}
```

👉 override : The override keyword is used in a derived class to tell the compiler that a virtual function from the base class is being overridden.
✅ It doesn’t change how overriding works — it simply adds a layer of safety and clarity.

- 💥 You might think Derived overrides show(),but it actually hides it — not override.No compiler error — just wrong behavior at runtime.

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() {
        cout << "Base show()" << endl;
    }
};

class Derived : public Base {
public:
    void show(int x) { // Different parameters ❌ not overriding
        cout << "Derived show(int)" << endl;
    }
};

int main() {
    Base* b = new Derived();
    b->show(); // Calls Base::show(), not Derived
    delete b;
}

```

- avoid this behaviour we can use override keyword
- we get compile errro is not F overriding

```cpp
class Derived : public Base {
public:
    void show(int x) override { // ❌ Compiler Error! error: 'void Derived::show(int)' marked 'override', but does not override
        cout << "Derived show(int)" << endl;
    }
};

```

- 👉 The compiler catches the mistake immediately — it tells you that this function does not match any base class virtual function.

- Correct Example Using override

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() {
        cout << "Base show()" << endl;
    }
};

class Derived : public Base {
public:
    void show() override { // ✅ Proper override
        cout << "Derived show()" << endl;
    }
};

int main() {
    Base* b = new Derived();
    b->show();  // Calls Derived::show() ✅
    delete b;
}

```

## 🔒 Why You Should Always Use `override`

✅ **1. Compile-Time Safety**  
Ensures your function actually overrides a base class virtual function — prevents accidental hiding or signature mismatch.

✅ **2. Code Clarity**  
Clearly shows which functions are overrides — makes the code easier to read and understand.

✅ **3. Future-Proofing**  
If the base class function changes, the compiler warns you — helping prevent silent bugs.

## ⚡ Bonus Tip: Combine with final

- Used final to prevent further overriding in subclasses.

```cpp
class Derived : public Base {
public:
    void show() override final { // ✅ cannot be overridden again
        cout << "Derived show()" << endl;
    }
};

class SubDerived : public Derived {
public:
    void show() override {  // ❌ Compiler Error
        cout << "SubDerived show()" << endl;
    }
};
```

✅ **In short**
Always use `override` in modern C++ (C++11 and above).  
It's like telling the compiler:  
**“Hey, I’m overriding this function — please double-check.”**


Operator Overloadding
---------------------
- When operator is overloaded with multiple job is called operator overloadding
- It is a way of implementing compile-time polymorphism.
- Operator Overloading means defining how operators (+, -, *, ==, etc.) work for user-defined types (classes/structs).

```cpp
class Complex
{
    float real, image;

public:
    Complex(float r = 0, float i = 0)
    {
        real = r;
        image = i;
    }

    // Complex add(Complex c)
    Complex operator+(Complex c) // operator keyword allow to use special keyword as function name
    {
        Complex temp;
        temp.real = real + c.real;
        temp.image = image + c.image;
        return temp;
    }
    void display()
    {
        cout << "-------------------" << endl;
        cout << "real : " << real << endl;
        cout << "image : " << image << endl;
    }
};
int main()
{
    Complex c1(1.1, 1.1);
    Complex c2(2.2, 2.2);
    c1.display();
    c2.display();
    // Complex c3=c1+c2; // error: no match for 'operator+' (operand types are 'Complex' and 'Complex')
    // Complex c3=c1.add(c2);
    // Complex c3=c1.operator+(c2);
    Complex c3 = c1 + c2;   // internally c1.operator+(c2); -> call method operator+() using c1 object and by passing c2 object as arguments
    c3.display();
    return 0;
}
```

🎯 Why Use Operator Overloading
✅ Makes custom classes behave like built-in types.
✅ Improves readability and intuitiveness.
✅ Helps implement mathematical, string-like, or logical objects.

⚡ Example: Overloading Multiple Operators
```cpp
class Point
{
    int x, y;

public:
    Point(int x = 0, int y = 0) // constructor
    {
        this->x = x;
        this->y = y;
    }

    Point operator+(Point p) // operator+
    {
        Point temp;
        temp.x = this->x + p.x;
        temp.y = this->y + p.y;
        return temp;
    }

    Point operator-(Point p) // operator-
    {
        Point temp;
        temp.x = this->x - p.x;
        temp.y = this->y - p.y;
        return temp;
    }

    Point operator*(Point p) // operator*
    {
        Point temp;
        temp.x = this->x * p.x;
        temp.y = this->y * p.y;
        return temp;
    }

    bool operator==(Point p) // operator==
    {
        return (x == p.x && y == p.y);
    }

    void display()
    {
        cout << "---------------" << endl;
        cout << "x : " << x << endl;
        cout << "y : " << y << endl;
    }
};
int main()
{
    Point p1(1, 1);
    Point p2(1, 1);
    p1.display();
    p2.display();
    cout << endl << "------ operration ------" << endl;
    Point p3;
    p3 = p1 + p2;  // +
    p3.display();

    p3 = p1 - p2;  // -
    p3.display();

    p3 = p1 * p2;  // *
    p3.display();

    if (p1 == p2)  // ==
        cout << "Points are equal" << endl;
    else
        cout << "Points are not equal" << endl;
    return 0;
}
```

- Taks 1: operload this Complex c2=-c1;  --> Complex c2=c1.operator-();  --> call this method and give number in negative format
```cpp
    Complex operater-()
    {
        Complex temp;
        temp.x=-x;
        temp.y=-y;
        return temp;
    }
```

- Taks 2: Overloadding of unary operator (pre & post) -> (increment & decrement)
```cpp
class Integer
{
    int x;

public:
    Integer(int a = 0)
    {
        x = a;
    }
    Integer operator++()  // pre-i
    {
        Integer i;
        i.x=++x;
        return i;
    }
    Integer operator++(int) //post-i
    {
        Integer i;
        i.x=x++;
        return i;
    }
    void display()
    {
        cout << "n : " << x << endl;
    }
};

int main()
{
    Integer n(1); // n=1;
    n.display();
    ++n;         // pre-increment (give updated value)
    n.display();
    n++;         // post-increment (first give old value than update)
    n.display();
    return 0;
}
```