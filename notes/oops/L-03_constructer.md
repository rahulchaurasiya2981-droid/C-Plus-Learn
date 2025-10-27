Constructors
--------------
- A constructor is a special member function of a class.
- Also call IMF.

- It is automatically/implicitly called when an object of the class is created.
- compiler call default constructor untill developer not make any constructor code.
- if developer create any constructor thatn compiler not call any default constructor all need to manage by developer.
```cpp
class Person
{
    string name;
    int age;
    public:
    Person()
    {
        cout<<"---- object is created/intailized----------"<<endl;
    }
};
int main()
{
    Person s1,s2,s3;
    return 0;
}
```

- Its main purpose is to initialize the object.
- It has the same name as the class and no return type (not even void)(no return keyword).
- It solve the problem of object initialization 
    - instance variable take garbage value after object creation
    - if any member function is used the member variable and perform operration this operation happen in garbase value so conflict behaviour effect the real enity
    - avoiding this we intialize the objecct by creating constructor explicit & passing value to intialize the object variable
    - so that object variable not contain garbage value 

Types of Constructors
-----------------------
1. Default Constructor
- A constructor with no parameters.
- Initializes objects with default values.
```cpp
class Student
{
    string name;
    int age;

    public:
    Student()
    {
        name="Unknown";
        age=0;
    }
    void display()
    {
        cout<<"Name : "<<name<<endl;
        cout<<"Age : "<<age;
    }
};
int main()
{
    Student s1;
    // Student s2("rahul",14); //  error: no matching function for call to 'Student::Student(const char [6], int)'
    s1.display();
    return 0;
}
```
2. Parameterized Constructor
- Takes arguments to initialize an object with custom values.
```cpp
class Student
{
    string name;
    int age;

    public:
    Student(string n,int a)
    {
        name=n;
        age=a;
    }
    void display()
    {
        cout<<"Name : "<<name<<endl;
        cout<<"Age : "<<age;
    }
};
int main()
{
    Student s1("Rahul", 22);
    s1.display();
    // Student s2;  // error: no matching function for call to 'Student::Student()'
    return 0;
}
```
3. Copy Constructor
- Used to create a new object as a copy of an existing object.
-Default copy constructor is provided by the compiler.
- Syntax: ClassName(const ClassName &obj)
- When we create a new object from an existing object compiler will run the default copy constructor,if any explict CC is not defined by developer.

```cpp
class Student
{
    string name;
    int age;

    public:
    Student(string n,int a)
    {
        name=n;
        age=a;
    }
    void display()
    {
        cout<<"Name : "<<name<<endl;
        cout<<"Age : "<<age;
    }
};
int main()
{
    Student s1("rahul",19);
    Student s2=s1; // s2(s1) inetnally -> CC implict run
    s2.display();
    return 0;
}
```

- When developr made any CC
```cpp
class Student
{
    string name;
    int age;

    public:
    Student(string n,int a)
    {
        name=n;
        age=a;
    }
    Student(Student s) 
    {
        name=s.name;
        age=s.age;
    }
    void display()
    {
        cout<<"Name : "<<name<<endl;
        cout<<"Age : "<<age;
    }
};
int main()
{
    Student s1("rahul",19);
    Student s2=s1; // s2(s1) inetnally
    s2.display();
    return 0;
}
```
- Output : error: invalid constructor; you probably meant 'Student (const Student&)'
- When CC is a Student (Student s) it will do again call the CC by value that CC become infinite loop.
- It creates an infinite loop because passing by value calls the copy constructor again to make a copy of s.
- Compiler detect this flage so give erro so solution in is Here copy by reference!!

```cpp
    Student(Student &s) 
    {
        name=s.name;
        age=s.age;
    }
```
- Passing by reference avoids making a copy, which prevents recursion and saves memory.
- Passing by value would try to create a copy first, which calls the copy constructor again → infinite loop.

- If you don't use const than original data can we modified
```cpp
Student(Student &s) { 
    s.age = 100; // oops! original object modified
}
```

```cpp
Student(const Student &s) { 
    // s.age = 100;  // ❌ error
}
```

4. Constructor Overloading
- A same C overloaded with multiple job (by different in parameter) is called CO
- by differnet in parameter
    - Differ number of parameter
    - Differ DT
```cpp
class Student
{
private:
    string name;
    int age;

public:
    Student() // Default C
    {
        name = "Unkown";
        age = 0;
    }
    Student(string a) // Parameterized C
    {
        name = a;
    }
    Student(string a, int b) // Parameterized C
    {
        name = a;
        age = b;
    }
    Student(const Student &s) // Copy C
    {
        name = s.name;
        age = s.age;
    }
    void display()
    {
        cout<<"-----------------"<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Age : "<<age<<endl;
    }
};

int main()
{
    Student s1;
    Student s2("rahul");  // s2="rahul" for 1 parameter
    Student s3("Deepak",18);
    Student s4=s3;  // s4(s3); internally happen

    s1.display();
    s2.display();
    s3.display();
    s4.display();
    return 0;
}
```

Key Points About Constructors
------------------------------
- Constructor has no return type.
- Name must match class name.
- Can be overloaded.
- Can be explicit to prevent implicit conversions.
- Can be used for dynamic object initialization.
- Static members cannot be initialized inside constructors directly; they are class-level.


Dynamic Initialization with Constructor
----------------------------------------
- s1 → Stack, created at runtime(when scop start), size known compile time,auto destroyed after frame execution done.
```cpp
int main()
{
    Student s1("Rahul", 22);
    s1.display();
    return 0;
}
```
- s2 → Pointer on stack, object on heap, created at runtime,not auto destroyed.
- new keyword
    - Allocates memory from the heap (at runtime).
    - Calls the constructor to initialize the object.
    - Return the address of the object
```cpp
int main()
{
    Student *s2 = new Student("Rahul", 22);
    s2->display();
    delete s; // need to delete manually other wise dead object in heap
    return 0;
}
```
