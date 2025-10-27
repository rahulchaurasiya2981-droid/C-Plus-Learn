- C++ structure (or struct) is a keyword which used to define custome data types by grouping the variable of different data types.
- strcture = collection of dissimilar element = user-defined DT
- Used to combine related data into single object.
- By default all members is public

```cpp
struct Student
{
    string name;
    int age;
    float grade;
}s2;

int main()
{
    Student s1={"rahul",18,9.1};
    // Student s1;      // struct Student s1;
    // s1.name="rahul";
    // s1.age=18;
    // s1.grade=9.1;
    s2={"student2",50,5.5};
    // s2.name="student2";
    // s2.age=50;
    // s2.grade=5.5;
    cout<<"--------- student 1 -----------"<<endl;
    cout<<"Name : "<<s1.name<<endl;
    cout<<"Age : "<<s1.age<<endl;
    cout<<"Grade : "<<s1.grade<<endl;
    cout<<"--------- student 2 -----------"<<endl;
    cout<<"Name : "<<s2.name<<endl;
    cout<<"Age : "<<s2.age<<endl;
    cout<<"Grade : "<<s2.grade<<endl;
    return 0;
}
```
- private member control by public member function 
- this is pointer pointing to caller object
- stack follow the higher to lower address direction (like l1 and l2)
- but object innerr member follow are follow lower to higher directions (name,version,ram)

| Concept           | Controls                                        | Direction  | Who decides it                                    |
| ----------------- | ----------------------------------------------- | ---------- | ------------------------------------------------- |
| **Stack growth**  | How each *variable or frame* is placed in RAM   | High → Low | **CPU + OS + ABI (Application Binary Interface)** |
| **Object layout** | How bytes *inside a single object* are arranged | Low → High | **C++ compiler (language rule)**                  |


```cpp
struct Laptop
{
    int name;
    float version;
    int ram;
};

int main()
{
    cout<<"-------- object 1 ---------------"<<endl;
    Laptop l1;
    cout<<"size of l1 : "<<sizeof(l1)<<endl;    // int + float + int = 4+4+4=12 byte
    cout<<"&l1 : "<<&l1<<endl;                  // 0x61ff04 (base address)
    cout<<"&l1.name : "<<&l1.name<<endl;        // 0x61ff04 (base address)
    cout<<"&l1.version : "<<&l1.version<<endl;  // 0x61ff08
    cout<<"&l1.ram : "<<&l1.ram<<endl;          // 0x61ff0c   ---> why address in increasing order bro cause stack follow the highr to lower direction rule.

    cout<<"-------- object 2 ---------------"<<endl;
    Laptop l2; 
    cout<<"size of l2 : "<<sizeof(l2)<<endl;    // int + float + int = 4+4+4=12 byte
    cout<<"&l2 : "<<&l2<<endl;                  // 0x61fef8 (base address)
    cout<<"&l2.name : "<<&l2.name<<endl;        // 0x61fef8 (base address)
    cout<<"&l2.version : "<<&l2.version<<endl;  // 0x61fefc 
    cout<<"&l2.ram : "<<&l2.ram<<endl;          // 0x61ff00

    // # summary
    // - stack follow the higher to lower address direction (l1/l2);
    // - object layout follow lower to higher address direction (name,versionm,ram);
    return 0;
}

```

- l1 is not pointer is just named variable that containe group of variable of different DT
- cout  not know how to pring l1 need to do explicity operator overloadding

```cpp
struct Laptop
{
    int name=100;
    float version=200;
    int ram=300;
};

int main()
{
    // cout<<l1;   // It is custom object so compiler not know how to handle and print (you need to do operator overload)
    cout<<&l1<<endl;
    cout<<&l1.name<<endl;
    // cout<<*&l1;    // erro : operator not overloaded (cause compiler not know how to handle and control custom DT)
    cout<<*(&l1.name); // it print cause compiler know name is int DT
    return 0;
}
```

- Activity : Access the private variable using pointer in main method() (without using memmber functions)

Access modifiers
----------------
| Type     | Default access for members | Default access for inheritance |
| -------- | -------------------------- | ------------------------------ |
| `struct` | **public**                 | public                         |
| `class`  | **private**                | private                        |


- struct vs class
| Feature                    | `struct`                     | `class`                                       |
| -------------------------- | ---------------------------- | --------------------------------------------- |
| Default access for members | **public**                   | **private**                                   |
| Default inheritance        | **public**                   | **private**                                   |
| Typical use case           | Simple data containers / POD | Full OOP: encapsulation, methods, inheritance |
| Member functions           | Yes                          | Yes                                           |
| Constructors / Destructors | Yes                          | Yes                                           |
