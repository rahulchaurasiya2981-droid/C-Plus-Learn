Pointer
--------

Address of operator (&)
-----------------------
- uniary operator
- operand must be name of the variable
- give address number of that variable
- also called referencing operator


Indirection operator (*)
-------------------------
- uniary operator
- operand must be address of the variable
- give data of the variable at that memory locations
- also called de-referencing operator

```cpp
    int x=100;        
    cout<<x<<"\n";    // 100
    cout<<&x<<"\n";   // 0x61ff0c
    cout<<*&x;        // 100
```

- Pointer are the variable that contain address of the other variable (int *p=&x)
- Pointer size depends on the system architecture, not the RAM size.
- int *j; is dangerous because it creates a pointer that may contain a Garbage address(random address). Dereferencing it is undefined behavior, which can crash your program or corrupt memory invisibly. The safe alternative is: initialize, use nullptr, use smart pointers, prefer references, and employ sanitizers/tools during development.
- A wild pointer is a pointer that has not been initialized and therefore points to an unknown or random memory address.
- Here j is wild pointer

```cpp
    int x=5,*j;
    *j=500;
    cout<<x<<" "<<j<<"\n";    // 5 0x61ff54
    cout<<*j<<" "<<&x<<"\n";  // 500 0x61ff0c
    cout<<*&j;                // 0x61ff54
```

- How to avoid wild pointer

| Safe Practice           | Example                               |
| ----------------------- | ------------------------------------- |
| Initialize to `nullptr` | `int *p = nullptr;`                   |
| Point to valid variable | `int x; int *p = &x;`                 |
| Use dynamic memory      | `int *p = new int(10);`               |
| Use smart pointer       | `auto p = std::make_unique<int>(10);` |
| Use reference instead   | `void func(int &r);`                  |
| Reset after delete      | `delete p; p = nullptr;`              |
| Check before use        | `if (p) cout << *p;`                  |


```cpp
    int x=5,*j;
    j=&x;
    cout<<x<<" "<<j<<"\n";    // 5 0x61ff0c
    cout<<*j<<" "<<&x<<"\n";  // 5 0x61ff0c
    cout<<*&j;                // 0x61ff0c
```
- Pointer always point to base address (1st byte address) of the variable
- Pointer point the vairbale of the same DT as pointer DT (otherwise unwanted byte access)
- Pointer size is depend on system architechre not on DT (64bit -> 8 bytes) (32bit -> 4 bytes)
- Pointer size depends on the compiler’s target architecture, not just your CPU.
    - see by running g++ -v  
        -> --target=mingw32 :-> 4 byte
        -> --target=mingw64 :-> 8 byte
- If you need to compile for 64-bit: g++ -m64 file.cpp -o file -> getting erro so need to install mingw-64 bit compiler


- int x=5,*p,**q,***r;
```cpp
int x=5,*p,**q,***r;
    p=&x;
    q=&p;
    r=&q;
    ***r=6;
    cout<<x<<"\n";   // 6
    **q=7;
    cout<<x<<"\n";   // 7
    *p=8;
    cout<<x<<"\n";   // 8
```

Pointer Arithmetic
--------------------
- +,*,/ of two address is not possible but subtraction (-) is possible of same DT pointer
- p1-p2=literal subtraction/sizeof(type of pointer) :-> give number of bytes 
- can't *,/ integer with addres but +,- we can do to move forward/backward directions
- Pointer + n = Pointer + sizeof(type of pointer)*n   (internall calculations)
- Why &a>&b ( i decalred b after the a so need to take memory after a memory higher address)
```cpp
    int a=10;
    int b=20;
    int *p,*q;
    p=&a;
    q=&b;
    cout<<"&a : "<<&a<<"\n";  // &a : 0x61ff04
    cout<<"&b : "<<&b<<"\n";  // &b : 0x61ff00
```

```md
# Exact Inner working

High address (100)
|↓↓ Stack ↓↓|
|   Free    |
|↑↑ Heap ↑↑ |
|   Code    |
Low address (0)
```

```md
# For visualization we read like this Memory Layout (0 - 100 bytes) : After Swapping

Low address (0)
|   Code    |
|↓↓ Heap  ↓↓|
|   Free    |
|↑↑ Stack ↑↑ |
High address (100)
```
- RAM is linear strip of bytes(array of bytes) (lower to higher in any direction) (0 to 100)
- Stack, heap, code, globals, and free space are all linear segments along this byte array
- This segments are manged by stack pointer, heap pointer, and OS loader etc.
- Every byte in RAM has a unique numeric address.(not float number address)
- Variable arranged in sequence from higher to lower
```cpp
    int *p,a=10,b=20,*q;
    p=&b;
    q=&a;
    // check sequence of address
    cout<<&p<<endl;
    cout<<&a<<endl;
    cout<<&b<<endl;
    cout<<&q<<endl;

    // next memort block address
    cout<<p+1<<endl;
    cout<<q+1<<endl;

    // self memory block address
    cout<<p+2<<endl;
    cout<<q-2<<endl;
```

- Pointer difference in blocks/bytes
    - p1 how much block/byte far from p2
    - p2 how much block/byte far from p1
    - number(or gap) of block/byte between p1/p2
- researcg this topic more by adding varibale between p and q
```cpp
    int *p;
    int a=10,b=20;
    int *q;
    p=&a;
    q=&b;
    cout<<"Blocks gap between p and q: :"<<(&p-&q)<<"\n";
    cout<<"Blocks strictly between p and q: :"<<(&p-&q)-1<<"\n";
    cout << "Bytes gap between *p and *q: "<<(char*)&p - (char*)&q<<"\n";    
    // or (&p-&q)*4 (not used cause not known inner vriable DT)
    cout << "Bytes strictly between *p and *q: "<<((char*)&p - (char*)&q) - sizeof(int*); 
    // or ((&p-&q)-1)*4 (not used cause not known inner vriable DT)
```


Application of pointer -1 with functions
----------------------------------------
- Actual Argument : argument passed from function call
- Forma Argument : receiver of  actual argument called formal arguments form function body
- Call by value : value is copy (changes are not reflected)  -> by ordinary variable
- Call by reference : address is copy (chnages are reflected) -> by reference variable
- Call by pointer : address is copy (chnages are reflected) -> by pointer variable
- Ex: swaping of two numbers

- Call by value -> ordinary variable -> copy value
```cpp
    void swap(int a,int b)   
    {
        int temp=a;
        a=b;
        b=temp;
    }
    swap(a,b);
```
- Call by reference -> reference variable -> copy reference
```cpp
    void swap(int &a,int &b)  
    {
        int temp=a;
        a=b;
        b=temp;
    }
    swap(a,b);
```

- Call by reference -> pointer variable -> copy address
```cpp
    void swap(int *a,int *b)
    {
        int temp=*a;
        *a=*b;
        *b=temp;
    }
    swap(a,b);   // just passing name but will work why undefined bheaviour best to use below code
```
```cpp
    void swap(int *a,int *b)   
    {
        int temp=*a;
        *a=*b;
        *b=temp;
    }
    swap(&a,&b);
```


Application of pointer -2 with array
------------------------------------
- Array always consume memory in contiguous fashion 
- If pointer is incremented or decremented by integer give next or previous block address of the pointing block.
- int a[5];
- base address = a = &a[0] = &*(a+0)
- a[0] = *(a+0)
- a[i] = *(a+i) -> internal working is pointer
- so that we can also create custom pointer and used int *p=a -> (p+index)(address) -> *(p+index)(data at this address)
```cpp
    int n;
    cout<<"Enter array size:";
    cin>>n;
    int a[n];
    // Base address same
    cout<<a<<"\n";
    cout<<&a[0]<<"\n";
    cout<<(a+0)<<"\n";
    // first value same garbage value
    cout<<a[0]<<"\n";
    cout<<*(&a[0])<<"\n";
    cout<<*(&(*(a+0)))<<"\n";
    cout<<*(a+0);
    return 0;
```

- Array input/output without pointer
```cpp
int main()
{
    int n;
    cout<<"Enter array size:";
    cin>>n;
    int a[n];
    cout<<"\n------input----------\n";
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    cout<<"\n------output---------\n";
    for(int i=0;i<n;i++)
    {
        cout<<"|"<<a[i]<<"| ";
    }
    
    return 0;
}
```

- Array i/o with pointer
```cpp
void input(int *p,int n)
{
    cout<<"\n------ input -------\n";
    for(int i=0;i<n;i++)
    {
        cin>>p[i];
        // cin>>*(p+i);
        
    }
}

void output(int *p,int n)
{
    cout<<"\n------ output -------\n";
    for(int i=0;i<n;i++)
    {
        cout<<"|"<<p[i]<<"| ";
        // cout<<"|"<<*(p+i)<<"| ";
    }
}
int main()
{
    int n;
    cout<<"Enter size : ";
    cin>>n;
    int a[n];
    input(a,n);
    output(a,n);
    return 0;
}
```

- Input/Output : Using a pointer variable directly
```cpp
    void input(int *p,int n)
    {
        cout<<"\n------- input --------\n";
        int *end=p+n;
        for(;p<end;p++)
        {
            cin>>*p;
        }
    }

    void output(int *p,int n)
    {
        int *end=p+n;
        for(;p<end;p++)
        {
            cout<<"|"<<*p<<"| ";
        }
    }
```
- Summary
<!-- ![Array with pointer](../images/array_with_pointer.jpg) -->
<img src="../images/array_with_pointer.jpg" width="800" height="800" style="transform: rotate(90deg);">


Application of pointer - 3 with string
--------------------------------------
- String Literal = String Constant = String
- String is array of character and ends with a null character '\0'
```cpp
    char a[10]="computer";  // ['c','o','m','p','u','t','e','r','\0',]
    cout<<a;  
    // print Characters until '\0' null terminator not give base addresss
    // Special overload for char* and int*/float* don't have overload
```
- Special overload : function/ operator overloadding
- char* is internally overloaded to print character no need to make loop (c++ service otherwise get address)
```cpp
    ostream& operator<<(ostream& out, const char* str)
    {
        while (*str != '\0')      // loop until null terminator
            out.put(*str++);      // print each character
        return out;
    }
```
- int* this not internally overloaded so print base address and manually need to write loop for print
```cpp
    ostream& operator<<(ostream&, int);
    ostream& operator<<(ostream&, double);
    ostream& operator<<(ostream&, char);
    ostream& operator<<(ostream&, const char*);
    ostream& operator<<(ostream&, void*);

```


- Traversing a string using pointers (proof char array also point to the base address)
```cpp
    void traverse(const char *p)
    {
        while(*p != '\0')
        {
            cout<<*p;
            p++;
            // or 
            // cout<<*p++;
        }
    }
    int main()
    {
        char a[]="computer";
        traverse(a);
        return 0;
    }
```
| Code                   | Meaning                           | Can modify data?                           |
| ---------------------- | --------------------------------- | ------------------------------------------ |
| `char *p`              | pointer to char                   | ✅ Yes                                      |
| `const char *p`        | pointer to constant char          | ❌ No                                       |
| `char * const p`       | constant pointer to char          | ✅ Yes (but pointer cannot change)          |
| `const char * const p` | constant pointer to constant char | ❌ No (neither pointer nor data can change) |

- Few Operation on string we will cover in sring sections

| Function                  | Purpose                 | Example          |
| ------------------------- | ----------------------- | ---------------- |
| `toUpper()`               | Convert to uppercase    | “abc” → “ABC”    |
| `toLower()`               | Convert to lowercase    | “ABC” → “abc”    |
| `length()`                | Count characters        | “Rahul” → 5      |
| `reverse()`               | Print reverse           | “abc” → “cba”    |
| `copyString()`            | Copy string             | a → b            |

```cpp
#include <iostream>
using namespace std;

void display(const char *p)
{
    while (*p != '\0')
    {
        cout << *p;
        p++;
        // or
        // cout<<*p++;
    }
}

void toUpper(char *p)
{
    char *temp = p;
    while (*p != '\0')
    {
        if (*p >= 'a' && *p <= 'z')
        {
            *p = *p - 32;
        }
        p++;
    }
    cout << "\nUppercase : ";
    display(temp);
}

void toLower(char *p)
{
    char *temp = p;
    while (*p != '\0')
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            *p = *p + 32;
        }
        p++;
    }
    cout << "\nLowercase : ";
    display(temp);
}

int length(char *p)
{
    int count = 0;
    while (*p != '\0')
    {
        count++;
        p++;
    }
    cout << "\nLength : " << count;
    return count;
}

void swap(char *x,char *y)
{
    char temp=*x;
    *x=*y;
    *y=temp;
}   

// # Modify the original string
// # Used when need to used reverse string later
void reverse1(char *p)  
{

    char *start=p;
    char *end=p;
    while(*(end+1) != '\0') end++;
    

    while(start<=end)
    {
        swap(start,end);
        start++;
        end--;
    }
    cout<<"\nReverse : "; 
    display(p);
}

// # Only print without affecting the original string
// # Used when just need reverse string 
void reverse2(const char *p) {
    const char *end=p;
    cout<<"\nReverse : "; 
    while(*(end+1) != '\0') end++;
    while(end>=p)
    {
        cout<<*end;
        end--;
    }
}

void copyString(char *src,char *des)
{
    while(*src != '\0')
    {
        *des=*src;
        *src++;
        *des++;
    }
    *des='\0';
}

int main()
{
    char a[] = "rahul";
    display(a);
    toUpper(a);
    toLower(a);
    length(a);
    reverse1(a);
    reverse2(a);
    char b[length(a)+1];   //+1 added for null terminoator manually 
    copyString(a,b);
    cout<<"\n Copyright : "<<b;
    return 0;
}
```




Lern pointer by also below resources
-------------------------------------
- https://youtu.be/MIL2BK02X8A?si=bqK4RPP4NIiWhvGi
- https://youtu.be/zuegQmMdy8M?si=74hEZldz9Vc996fA
- https://youtu.be/YHwEIfrXZgE?si=ndlmEPf5Df4axxbl
- pointer by code army
- https://youtu.be/qYEjR6M0wSk?si=cRu-LI2cTG0n35C-




Dynamic Memory Allocations (need to read and make notes)
--------------------------------------------------------
1. SMA (static MA)
2. DMA (Dynamic MA)