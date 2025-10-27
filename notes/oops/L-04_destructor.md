Destructor
-----------
- Destructor is an instance member function of a class
- The name of the destructor is same as the name of a class but preceded by tilde (~) symbol   
- Destructors can never be static
- Destructor has no return type
- Destructor takes no argument (No overloading is possible)

- It is invoked implicity when object is going to destroy.
- It’s used to free resources (like memory, files, or network connections) used by object. otherwise unwanted consume  some memory 
```cpp
class Laptop
{
    string brand;
    int version;
    int ram;
    public:
    Laptop()
    {
        cout<<"Object is created..."<<endl;
    }
    ~Laptop()
    {
        cout<<"Object is destroyed..."<<endl;
    }
};
int main()
{
    Laptop l1;
    cout<<"End of the main()...."<<endl;
    return 0;
}

Output:
Object is created...
End of the main()....
Object is destroyed...
```
- If we used dynamic object creation in heap
- destructor will not run cause object still exit in heap
```cpp
class Laptop
{
    string brand;
    int version;
    int ram;
    public:
    Laptop()
    {
        cout<<"Object is created..."<<endl;
    }
    ~Laptop()
    {
        cout<<"Object is destroyed..."<<endl;
    }
};
int main()
{
    Laptop *l2=new Laptop();    // pointer is removed after main frame execution done but object is still in HEAP
    cout<<"End of the main()...."<<endl;
    return 0;
}

Output:
Object is created...
End of the main()....
```

- Need to do remove this object manually from HEAP using delete keyword.
```cpp
int main()
{
    Laptop *l2=new Laptop();
    delete l2;
    cout<<"End of the main()...."<<endl;
    return 0;
}
Output:
Object is created...
Object is destroyed...
End of the main()....
````

```cpp
int main()
{
    Laptop *l2=new Laptop();
    cout<<"End of the main()...."<<endl;
    delete l2;
    return 0;
}

Output:
Object is created...
End of the main()....
Object is destroyed...
```


💡 Important Notes:
- Only one destructor per class.
- Cannot be overloaded.
- If you don’t write one, C++ automatically provides a default destructor.
- Always use delete for objects created with new.
- Use virtual ~ClassName() if your class will be inherited (for safe polymorphism).