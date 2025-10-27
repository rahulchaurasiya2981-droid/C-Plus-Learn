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
2.Parameterized Constructor
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
    Student s2=s1; // s2(s1) inetnally -> CC implict run
    s2.display();
    return 0;
}
```
- Output : error: invalid constructor; you probably meant 'Student (const Student&)'
- When CC is a Student (Student s) it will do again call the CC by value thant CC become infinite loop.
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