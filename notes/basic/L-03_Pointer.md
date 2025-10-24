Pointer concept
----------------
# Pointer Mastery Roadmap

## Core Concepts
0. Bits, Bytes, RAM, Memory Segments, Address, OS Memory Management  
1. Pointer  
2. Pointer Arithmetic  
3. Pointer to Pointer  
4. Pointer with Function (Pass & Return)  
5. Pointer with Array (1D / 2D / 3D)  
6. Pointer with Char  
7. Pointer with String  
8. Pointer Type Conversion  
9. Void Pointer  
10. Dangling Pointer  
11. Function Pointer & Callback  
12. main() Arguments  
13. Dynamic Memory Management  
14. Pointer with DMM  
15. Dynamic Memory Handling — C (Functions) vs C++ (Operators)  
16. Memory Leak and Handling  

## Advanced Concepts
17. Structs and Pointer Interaction (`struct*`, arrays of structs, `->` operator)  
18. Pointer Alignment and Padding (Memory alignment rules)  
19. Pointer Aliasing (Optimizations, restrictions, strict aliasing rule)  
20. Smart Pointers in C++ (`unique_ptr`, `shared_ptr`, `weak_ptr`)  
21. Memory Safety Tools (Valgrind, AddressSanitizer, detecting invalid access/leaks)  
22. Function Pointers in Complex Systems (Callbacks, event-driven design, plugins)  
23. Multi-level Pointers and Pointer Graphs (Pointers to pointers to pointers…)  
24. Pratice pointer questions

---------------------------------------------------------------------------------------------------
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
<img src="../images/array_with_pointer.jpg" width="800" height="800">


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
    

    while(start<end)
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

Resource to lean pointer 1 : https://youtu.be/MIL2BK02X8A?si=bqK4RPP4NIiWhvGi
--------------------------------------------------------------------------------

- OS ::>
- OS load your program file from disk to RAM (private area on RAM or virtual memory space)
- OS will create process for this program 
- Each process will have their own separate memory segments (stack/free space/heap/code)
- So, if you run 4 programs, the OS creates 4 separate processes, each with its own isolated memory layout
- OS is king or master program that control almost everything
- RAM is like electrical notepad,pencil is keyboard and CPU is smart calculator
- RAM is array of byte and each byte have unique address(integer but write in hexadecimal format)
- Address always incresing order (independent of direction horizontal/vertical)

- Prative C/C++ by visualizing memory structure by this compiler
- URL : https://pythontutor.com/cpp.html#mode=edit

- Call by value 
    1. Easy to understand
    2. Safe(original data not updated)(copy pass)
    3. Performance overhead (passing big object)
    4. Short reach (only modified local scope)

- Call by reference 
    1. Efficiency (bettre performance)(only pass address of big object)
    2. Direct Access (can we updte original data)
    3. Side effect (can update at given memory location)
    4. Complexity (Taming pointer,Multilevel pointer)

- Pointer size is same not dependent on data types
- Pointer arithmatics

- Pointer type casting 
- The pointer Data type tells the compiler how to interpret the memory at that address
- Depending on DT, we are going to read bytes pointed by pointer
- Type conversion in pointer

```cpp
int main()
{
    int np=42;
    int *ptr=&np;
    cout<<*ptr;      // show memory content in integer format
    cout<<*(float *)ptr; // show memory content in floating format (now int* pointer become float* pointer)
    return 0;
}
```

| Expression      | What changes           | Address      | What you see                                 |
| --------------- | ---------------------- | ------------ | -------------------------------------------- |
| `*ptr`          | interpreted as `int`   | same (`&np`) | 42                                           |
| `*(float *)ptr` | interpreted as `float` | same (`&np`) | meaningless float (different interpretation) |

- “When you typecast a pointer type, you do not change the memory or address — you only change how the compiler interprets the bits at that address.”
- ⚠️ Warning: This is called type punning — it’s unsafe unless you really know what you’re doing (e.g., in embedded or system-level programming)

```cpp
int main()
{
    int nb=0b1100001;  // dec:97 
    int *ptr=&nb;
    cout<<nb<<endl;   // 97
    cout<<ptr<<endl;  // 0x61ff08
    cout<<*(char*)ptr; //a
    return 0;
}
```

```cpp
int main()
{
    int nb=0b10010110;  // dec:150
    int *ptr=&nb;
    cout<<nb<<endl;    // 150
    cout<<ptr<<endl;   // 0x61ff08
    cout<<*(char*)ptr; //û (show wired sybmol if character not exist in ASCII table)
    return 0;
}
```
- Type casting to void 
    - No assigned a role (still need to know what role is best for you)
    - generic (no type) pointer

```cpp
void printData(void *p,char dataType)
{
    if(dataType == 'i') cout<<"Integer : "<<*(int*)p<<endl;
    if(dataType == 'f') cout<<"Float : "<<*(float*)p<<endl;
    if(dataType == 'c') cout<<"Char : "<<*(char*)p<<endl;
}

int main()
{
    int a=42;
    printData(&a,'i');
    printData(&a,'f');
    printData(&a,'c');
    return 0;
}
```

Very common C++ pitfall: returning the address of a local variable.
--------------------------------------------------------------------
```cpp
int* foo()
{
    int n;
    n=42;
    return &n;
}
int main()  
{
    int *pn;
    pn=foo();    // pn now holds an invalid pointer
    cout<<*pn<<endl;   // undefined behavior!
    return 0;
}
```
- Output : warning: address of local variable 'n' returned [-Wreturn-local-addr]
- n is part of foo stack frame,when foo() finished execution than memory is freed up
- That means n’s memory is no longer valid.
- The pointer you returned (&n) still contains that memory address —
but that address is no longer valid for your program to access. 
- pn = dangling pointer  ❌
- You’re trying to read from a memory location that no longer belongs to you.
- At this point, anything can happen:

| Possible Outcome             | Explanation                                                   |
| ---------------------------- | ------------------------------------------------------------- |
| Prints garbage               | The memory still holds old bits from `n`, but it’s not valid. |
| Prints 42                    | You got lucky — the stack wasn’t reused yet.                  |
| Crashes (Segmentation fault) | The OS prevented your program from touching invalid memory.   |
| Corrupts other data          | Reading or writing could damage adjacent stack data.          |

- The C++ standard does not specify what should happen (undefine behavior) —
the program can do anything: crash, corrupt memory, print nonsense, or appear to work.

- ✅ Safe Fixes ::> Solution to avoid this undefined behaviour
- Try this fix for visualization by 
| Fix             | Example                           | Why Safe                                   |
| --------------- | --------------------------------- | ------------------------------------------ |
| Return by value | `int foo(){return 42;}`           | Copies the value out, no pointer issues    |
| Use `static`    | `static int n=42; return &n;`     | Variable persists after function returns   |
| Use `new`       | `int* n = new int(42); return n;` | Allocated on heap, survives until `delete` |

- Solution 1 : retrun by value
```cpp
int foo()
{
    int n;
    n=42;
    return n;
}
int main()  
{
    int pn;
    pn=foo();    
    cout<<pn<<endl; 
    return 0;
}
```
- Solution 1 : using static keyword (alive after function frame memory freed-up)
```cpp
int* foo()
{
    static int n;
    n=42;
    return &n;
}
int main()
{
    int* pn;
    pn=foo();
    cout<<*pn;
    return 0;
}
```

- Solution 2 : using heap memory (alive untill delete)
```cpp
int* foo()
{
    int* n=new int(42); //or used malloc
    return n;
}
int main()
{
    int* pn;
    pn=foo();
    cout<<*pn;
    return 0;
}
```

```cpp
void bar()
{
    int* nb=new int(5000);
}
int* foo()
{
    int *n=new int(42);
    return n;
}
int main()
{
    int* pn;
    pn=foo();
    cout<<"*pn : "<<*pn<<endl;  //42
    bar();
    cout<<"*pn : "<<*pn;  // 42
    return 0;  
}
```

- Array name have address of the 1st element and acts like like constant pointer
- Decaying an array to a pointer lets a function access the array without copying it, passing only the first element’s address and saving memory and time.
- Pointer also give flexibility to accept address of different array size


int main(int argc,char **argv)(argument vector)
-----------------------------------------------
- argv is argv->p(array of address each address point some char array/NULL)->char array
- So, the parameters of main allow your program to accept input from the command line.
- so array is pointer not array!!(intrenally)
```cpp
int main(int argc,char **argv) 
{
    int i=0;
    while(*(argv+i))  
    {
        int j=0;
        while(*(*(argv+i) + j))  
        {
            cout<<*(*(argv+i) + j);
            j++;
        }
        cout<<endl;
        i++;
    }
}
```
```cpp
int main(int argc, char *argv[]) // whole array is pointer variable
{
    int i=0;
    while(argv[i])
    {
        int j=0;
        while(argv[i][j])
        {
            cout<<argv[i][j];
            j++;
        }
        cout<<endl;
        i++;
    }
    return 0;
}
```


```cpp
int main(int argc,char *argv[])
{
    while(*argv)    // or (*argv != NULL)
    {
        char *p=*argv;
        while(*p)   // or (*p != '\0')
        {
            cout<<*p;
            p++;
        }
        cout<<endl;
        argv++;
    }
    return 0;
}
```

```cpp
int main(int argc,char *av[])
{
    while(*av)    
    {
        while(**av != '\0')  
        {
            cout<<*(*av);
            (*av)++;

            // or cout<< *(*av)++;  
            // hints: updted the content of av[0] by address of char array one by one so no need extra memory
            // doing by updating the argv array address
            // so above code is best to use without modified original (future use)
        }
        cout<<endl;
        av++;
    }
    return 0;
}
```
Note
----
- int a[] == int *a;
- char *argv[] == char *(*argv) == char **argv;
- when we run and not pass anything by commond than it will give the directroy path (it hackes bro)

Fake Main method
----------------
```cpp
void fake_main(const char **av)  // const char *av[]
{
    while(*av) cout<<*av++<<endl;

}
int main()
{
    // char *av[]={"C-Plus-Learnemp.exe","rahul","user1","...",NULL}; 
    // give warnign cause string is constan by compiler 
    // And i am telling my av pointer is pointin to char and will update so conflict
    // solution : follow the compiler rull (add const)
    const char *av[]={"C-Plus-Learnemp.exe","rahul","user1","...",NULL}; 
    fake_main(av);
    return 0;
}
```


- Let's check function is stored in other space called code/text segment

```cpp
int add(int a,int b){
    return a+b;
}
int subtract(int a,int b){
    return a-b;
}
int multiply(int a,int b)
{
     return a*b;
}
int division(int a,int b)
{
     return a/b;
}

int main()
{
    int a;
    int *p=new int(42);
    // # cout not have for function pointer so is internall typecasted into bool than 1
    cout<<main<<endl;      // 1
    cout<<add<<endl;;      // 1
    cout<<subtract<<endl;  // 1
    cout<<multiply<<endl;  // 1
    cout<<division<<endl;  // 1

    // # store in stack segment
    cout<<&a<<endl;   // &a : 0x61ff0c
    
    // # Store in Heap -> used to confirm function  stroe in code/text segment
    cout<<p<<endl;           //
    

    // # store in code/text segment 
    cout<<(void *)main<<endl;       
    cout<<(void *)add<<endl;        
    cout<<(void *)subtract<<endl;   
    cout<<(void *)multiply<<endl;   
    cout<<(void *)division<<endl;   

}
```
Function Pointer
------------------
- Only the function environment is set up on the stack, but execution happens from the code/text segment.
- Code/Text Segment → The book (function instructions). (actual function body store here)(read only)
- Stack Frame → The workspace where you write temporary notes while reading that book.
- When you call the function, you open the book to the right page and start writing on your workspace.
When done, you erase the workspace (pop the stack frame) — but the book stays the same.

```cpp
int add(int a,int b){
    return a+b;
}
int subtract(int a,int b){
    return a-b;
}
int multiply(int a,int b)
{
     return a*b;
}
int division(int a,int b)
{
     return a/b;
}

int performArithmetic(int a,int b,int (*operationn)(int ,int))  // creating the function pointer
{
    return operationn(a,b);
}


int main()
{
    cout<<"Sum : "<<performArithmetic(2,2,add)<<endl; // passing numberr and reference of function
    cout<<"Subtract : "<<performArithmetic(2,2,subtract)<<endl;
    cout<<"Multiply : "<<performArithmetic(2,2,multiply)<<endl;
    cout<<"Division : "<<performArithmetic(2,2,division)<<endl;
    return 0 ;
}  
```



Resource to lean pointer 2 : https://youtu.be/zuegQmMdy8M?si=74hEZldz9Vc996fA
------------------------------------------------------------------------------

Resource to lean pointer 3 : https://youtu.be/YHwEIfrXZgE?si=ndlmEPf5Df4axxbl
--------------------------------------------------------------------------------

Resource to lean pointer 4 : pointer by code army
-------------------------------------------------

Resource to lean pointer 5 : https://youtu.be/qYEjR6M0wSk?si=cRu-LI2cTG0n35C-
------------------------------------------------------------------------------





Dynamic Memory Allocations (need to read and make notes)
--------------------------------------------------------
1. SMA (static MA)
2. DMA (Dynamic MA)