1. Class
2. Object
3. Membership level (CN::)
4. Instance variabel/function
5. Static variabel/function
6. Static local variable

Structure
-----------

```cpp
struct Complex
{
    private:
    int x,y;

    public:
    void setData(int i,int j)
    {   
        x=i;
        y=j;
    }
    // void setData(int x,int y)
    // {
    //     this->x=x;
    //     this->y=y;
    // }
    void showData()
    {
        cout<<"X : "<<x<<endl;
        cout<<"Y : "<<y<<endl;
    }
};

int main(){
    Complex c1;
    c1.setData(4,5);
    c1.showData();
    return 0;
}
```

Class
------
- just replace the struct with class keyword

```cpp
class Complex
{
    private:
    int x,y;

    public:
    void setData(int i,int j)
    {   
        x=i;
        y=j;
    }
    // void setData(int x,int y)
    // {
    //     this->x=x;
    //     this->y=y;
    // }
    void showData()
    {
        cout<<"X : "<<x<<endl;
        cout<<"Y : "<<y<<endl;
    }
};

int main(){
    Complex c1;
    c1.setData(4,5);
    c1.showData();
    return 0;
}
```

Membership Level
-----------------
- `classname::` tells the compiler **which class or scope the member belongs to**.
- Common uses:
    1. Define **member functions** outside the class.  
    2. Access **static members**.  
    3. Access **enums** or **nested classes**.  
- SMV/SMF/IMF can used CN:: but IMV not used cuase IMV is bind with object not shared

```cpp
class Person {
    public:
    string name;
    int age;

    void setName(string n);       // Instance function declaration 
    void printInfo();             // Instance function declaration

    static int population;        // Static member variable
    static void increasePopulation(); // Static function declaration
};


int Person::population = 0;   // SMV


void Person::setName(string n) {  // IMF
    name = n;
}

void Person::printInfo() {  // IMF
    cout << "Name: " << name << ", Age: " << age << endl;
}

void Person::increasePopulation() {  // SMF
    population++;  // only SMV allowed
}

int main() {

    Person p1;
    p1.setName("Rahul");
    p1.age = 22;
    p1.printInfo(); // Output: Name: Rahul, Age: 22

    // Static usage
    // Person::increasePopulation();
    // Person::increasePopulation();
    // cout << "Population: " << Person::population << endl;

    // Static usage by objecct
    p1.increasePopulation();
    p1.increasePopulation();
    cout << "Population: " << p1.population << endl;
    return 0;
}

```

Function call by object & return object 
-----------------------------------------
- Ex: Adding two complex number

```cpp
class Complex
{
    int x, y;

public:
    void setData(int i, int j)
    {
        x = i;
        y = j;
    }
    void showData()
    {
        cout << "----------------\n";
        cout << "X : " << x << endl;
        cout << "Y : " << y << endl;
    }

    Complex add(Complex c)
    {
        Complex temp;
        temp.x = x + c.x;
        temp.y = y + c.y;
        return temp;
    }
};

int main()
{
    Complex c1, c2, c3;
    c1.setData(1, 1);
    c2.setData(2, 2);
    c1.showData();
    c2.showData();
    c3 = c1.add(c2);
    c3.showData();
    return 0;
}
```

Class and object
----------------
- Class is a description of an object (not take memory)
- Object is an instance of a class (only object take memory)
- Instance member variable(IMV)  ::>  Attributes, data members, fields, properties
- Instance member functions(IMF)  ::>  Methods, procedures, actions, operations, services

Static Member
---------------
1. Static Local variable
2. Static Member Variable
3. Static Member Functions


Static Local variable
----------------------
- It behaves like a global variable
- declare by static keyword and default value is 0;
- 
| Feature        | Description                                            |
| -------------- | ------------------------------------------------------ |
| Scope          | Local to the function                                  |
| Lifetime       | Entire program execution (retains value between calls) |
| Initialization | Happens **only once**, first time function is called   |
| Memory Storage | Stored in **data segment**, not on the stack           |

- Stack → regular local variables, created and destroyed each call
- Data segment → local static variables, persist across calls

```cpp
void f() {
    static int x = 5; // memory for x is created first time f() is called
    cout << x << endl;
    x++;
}

int main() {
    cout << "Before calling f()" << endl;
    f(); // x is created and initialized here
    f(); // x retains previous value
    return 0;
}

```

```cpp
void counter()
{
    static int count=0;
    cout<<count<<endl;
    count++;
}
void bro()
{
    cout<<count;

}
int main()
{
    int *p=new int(42);
    int a=500;
    counter();
    counter();
    counter();
    bro();           //  error: 'count' was not declared in this scope 
    cout<<p<<endl;   // p have heap address
    cout<<&p<<endl;  // stack address
    cout<<&a<<endl;  // stack address
    cout<<(void*)&counter<<endl;  // data/text segment address
    cout<<(void*)counter;         // data/text segement address
    return 0;
}

```
- Comparison with normal local variables
| Feature         | Normal local             | Local static           |
| --------------- | ------------------------ | ---------------------- |
| Lifetime        | Function call only       | Entire program         |
| Memory location | Stack                    | Data segment           |
| Value retention | Lost after function ends | Retained between calls |

- Why Use Local Static Variables?
a. Retain value between function calls  ::>  Useful for counters, memoization, caching.
b. Scope is limited  ::>  Unlike globals, they cannot be accessed outside the function.
c. Memory efficient  ::>  Allocated once in the data segment, not on the stack.



Static Member Variable
-----------------------
- Also known as class member variable/CV/SMV
- Declared inside the class body
- They must be defined outside the class (using membership level)
- Static member variable does not belong to any object, but to the whole class.
- There will be only one copy of static member variable for the whole class.
- Any object can use the same copy of class variable
- They can also be used with class name (using membership level) or with object

- A static variable belongs to the class, not to any object.
- It is shared among all objects of the class.
- Memory for a static variable is allocated only once, no matter how many objects are created.
- Static variables are useful for counting objects, storing shared values, etc.


- Declare inside class & define outside class using membership level (CN::)
- If SV is public ::> access by (CN:: , object, IMF)
- If SV is private ::> access by (IMF)

```cpp

class Student
{
    static string collegeName;
    string name;
    int age;
    float grade;

    public:
    void setData(string a, int b, int c)
    {
        name = a;
        age = b;
        grade = c;
    }
    void showData()
    {
        cout<<"---------------------"<<endl;
        cout << "Colleage : " << collegeName << endl;
        cout << "Name : " << name << endl;
        cout << "Age : " << age << endl;
        cout << "Grade : " << grade << endl;
    }
    string getcollegeInfo_IMF(){
        return collegeName;
    }
    static string getcollegeInfo_SMF(){
        return collegeName;
    }
};

string Student::collegeName = "MCC";

int main()
{
    Student s1;
    s1.setData("rahul",18,9.1);
    s1.showData();
    Student s2;
    s2.setData("Deepak",21,5.5);
    s2.showData();
    // cout<<Student::collegeName; // error: 'std::__cxx11::string Student::collegeName' is private within this context
    // cout<<s1.collegeName; // error: 'std::__cxx11::string Student::collegeName' is private within this context
    cout<<s1.getcollegeInfo_IMF()<<endl;  // using IMF
    cout<<s1.getcollegeInfo_SMF();  // using SMF
    return 0;
}
```

Static Member Function
-----------------------
- Only access static member
- Also called class member function
- Define by static keyword in class (or can also declare inside and define outside class using CN::)
- If SMF is public ::> access by (CN:: , object, IMF)
```cpp
class Student
{
    static string collegeName;
    string name;
    int age;
    float grade;

    public:

    string getcollegeInfo_IMF(){
        cout<<"Calling SMF..."<<endl;
        return getcollegeInfo_SMF();
    }
    static string getcollegeInfo_SMF(){
        return collegeName;
    }
};

string Student::collegeName = "MCC";

int main()
{
    Student s1;
    cout<<Student::getcollegeInfo_SMF()<<endl;  // using CN::
    cout<<s1.getcollegeInfo_SMF()<<endl;        // using object
    cout<<s1.getcollegeInfo_IMF()<<endl;        // using IMF
    return 0;
}
```
- If SMF is private ::> access by (IMF)
```cpp
class Student
{
    static string collegeName;
    string name;
    int age;
    float grade;
    static string getcollegeInfo_SMF()
    {
        return collegeName;
    }

public:
    string getcollegeInfo_IMF()
    {
        cout << "Calling SMF..." << endl;
        return getcollegeInfo_SMF();
    }
};

string Student::collegeName = "MCC";

int main()
{
    Student s1;
    // cout<<Student::getcollegeInfo_SMF()<<endl;  // error: 'static std::__cxx11::string Student::getcollegeInfo_SMF()' is private within this context
    // cout<<s1.getcollegeInfo_SMF()<<endl;        // error: 'static std::__cxx11::string Student::getcollegeInfo_SMF()' is private within this context
    cout << s1.getcollegeInfo_IMF() << endl; // using IMF
    return 0;
}
```

```cpp
class Student
{
    static string collegeName;
    string name = "student";
    int age;
    float grade;

public:
    void IMF()
    {
        cout << name << endl; // Accessing IMV
        cout << collegeName; // Accessing SMF
    }
    static void SMF()
    {
        // cout << name << endl; // Accessing IMV : error: invalid use of member 'Student::name' in static member function
        cout << collegeName; // Accessing SMF
    }
};

string Student::collegeName = "MCC";

int main()
{
    Student s1;
    s1.IMF();
    cout<<endl<<"-----------"<<endl;
    s1.SMF();
    return 0;
}
```