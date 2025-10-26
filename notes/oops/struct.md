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
``` 