## Friend Function

- Friend Function is not a member function of a class but it is friend of the class
- Declared inside class but defined outside of the class (without using membership level(CN::))
- FF access any member of the class to which it is friend

- FF not access directly member of the class cause not have caller object. (called like normal function but passing object)

```cpp
class Point
{
    int x, y;   // private memberr access by FF

public:
    Point(int a, int b)
    {
        x = a;
        y = b;
    }
    void display()
    {
        cout << "x : " << x << endl;
        cout << "y : " << y << endl;
    }
    friend void showData(Point);
};

// # is not member of class so not need to use CN:: & can't access by caller object
// # call like normal function
// # but not known whoose x/y need to print -> so need to do pass object
void showData(Point p)
{
    cout << "Hi i am FF.." << endl;
    cout << "x : " << p.x << endl;
    cout << "y : " << p.y << endl;
}

int main()
{
    Point p1(1, 1);
    p1.display();
    showData(p1);
    return 0;
}
```

- FF can become friend of the multiple classes
- Ex : The friend function addValues() can access private data from both classes.

```cpp
#include <iostream>
using namespace std;
class B; // Forward declartion for avoiding error FF declartion in Class A
class A
{
    int a;

public:
    A(int a)
    {
        this->a = a;
    }
    friend void add(A, B);
};
class B
{
    int b;

public:
    B(int b)
    {
        this->b = b;
    }
    friend void add(A, B);
};

void add(A o1, B o2)
{
    cout << "Sum : " << (o1.a + o2.b);
}
int main()
{
    A obja(2);
    B objb(3);
    add(obja, objb);
    return 0;
}
```

- Overloading of operators(+) as the FF
- Complex c3=c1+c2;
- Default behviour :> compiler consider c1 caller object & call the operator+ by pass c2 as argument :> c1.operator+(c2)
- After friend keyword :> compiler call the operator+ by passing c1/c2 (no caller object) :> operator+(c1,c2);

```cpp
#include <iostream>
using namespace std;

class Complex
{
    int r, i;

public:
    Complex(int r, int i)
    {
        this->r = r;
        this->i = i;
    }
    void show()
    {
        cout<<"real : "<<r<<endl;
        cout<<"imag : "<<i<<endl;
    }
    // friend Complex add(Complex, Complex);
    friend Complex operator+(Complex, Complex);

};

// Complex add(Complex c1, Complex c2)
// {
//     return Complex(c1.r + c2.r,c1.i + c2.i);
// }

Complex operator+(Complex c1, Complex c2)
{
    return Complex(c1.r + c2.r,c1.i + c2.i);
}

int main()
{
    Complex c1(2, 2);
    Complex c2(3, 3);
    // Complex c3 = add(c1, c2);
    // Complex c3 = operator+(c1, c2);
    Complex c3 = c1 + c2;
    c3.show();
    return 0;
}
```

- Overloading of unary operator as FF
- Complex c2=-c1;
- Default Behaviour : c1.operator-()
- After friend keyword : operator-(c1)

```cpp
class Complex
{
    int r, i;

public:
    Complex(int a=0, int b=0)
    {
        r = a;
        i = b;
    }
    void show()
    {
        cout << "real : " << r << endl;
        cout << "imag : " << i << endl;
    }
    friend Complex operator-(Complex);
};

Complex operator-(Complex c)
{
    return Complex(-(c.r),-(c.i));
}
int main()
{
    Complex c1(2,2);
    c1.show();
    Complex c2;
    c2=-c1;// operator-(c1)
    c2.show();
    return 0;
}
```

- Overloading of the insertion(<<) & extraction(>>) operator
- cin>>c1,cout<<c1

```cpp
class Complex
{
    int r, i;

public:
    Complex(int a = 0, int b = 0)
    {
        r = a;
        i = b;
    }
    void show()
    {
        cout << "real : " << r << endl;
        cout << "imag : " << i << endl;
    }
    friend istream& operator>>(istream&,Complex&); // interstion
    friend ostream& operator<<(ostream&,Complex); // extraction
};

istream& operator>>(istream &din,Complex &obj)
{
    cout << "Enter real : ";
    cin >> obj.r;
    cout << "Enter imag : ";
    cin >> obj.i;
    return din;
}
ostream& operator<<(ostream &dout,Complex obj)
{
    cout<<"real : "<<obj.r<<endl;
    cout<<"imag : "<<obj.i<<endl;
    return dout;
}
int main()
{
    Complex c1;
    cin >> c1;  // cin.operator>>(obj)
    cout<<c1;  // operator<<(cout,obj)
    return 0;
}
```

- Member Function of one class can become FF of another  class
```cpp
class A
{
public:
    void fun()
    {
        // ...
    }
    void foo()
    {
        // ...
    }
};

class B
{
    
    // friend void A::fun();
    // friend void A::foo();
    friend class A;         // all MF of A is becom friends of class B and
};

```
- friend void A::fun(); → Only A::fun() can access B’s private members.
- friend void A::foo(); → Only A::foo() can access B’s private members.
- friend class A; → A has full access to B. :> all MF of A is becom friends of class B 
- so that A can access private/protected/public data of class B