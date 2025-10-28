- File handling in C++ allows you to store data permanently on a disk (in a file) instead of keeping it temporarily in memory (RAM).
  You can:

1. Create / open
2. Read data and Process data
3. Write data
4. Close

- C++ provides <fstream> for file handling.

| Class      | Purpose                  | Example                     |
| ---------- | ------------------------ | --------------------------- |
| `ofstream` | Write (output) to a file | `ofstream out("data.txt");` |
| `ifstream` | Read (input) from a file | `ifstream in("data.txt");`  |
| `fstream`  | Read + Write both        | `fstream file("data.txt");` |

## Creating

```cpp
#include<fstream>
int main()
{
    ofstream fout;
    fout.open("db.txt");  //if exist open ,if not exit create->open
    fout<<"Hellow world"; // write
    fout.close();         // close,free the resources
    return 0;
}
```

## Read

- fin>>c : read one by one avoid space
- c=fin.get() : read one by one with space

```cpp
#include<fstream>
int main()
{
    ifstream fin;
    fin.open("db.txt");
    char c;
    while(!fin.eof())         // run untill end of the file
    {
        // fin>>c;            // get one letter at a time (avoid space)    o/p: Hellowworld
        c=fin.get();          // get one letter at a time with space    o/p: Hellow world
        cout<<c;
    }
    fin.close();
    return 0;
}
```

- create arr -> write in file -> sort data -> again wirte in file

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // for sort()
using namespace std;

int main() {
    vector<int> arr(5); // vector of 5 integers
    cout << "Enter 5 items: ";

    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }

    ofstream fout("db.txt"); // open file directly in constructor
    if (!fout) {
        cout << "Error opening file!";
        return 1;
    }

    fout << "Original Data:\n";
    for (int i = 0; i < 5; i++) {
        fout << arr[i] << " ";
    }

    sort(arr.begin(), arr.end()); // sort in ascending order

    fout << "\n\nSorted Data:\n";
    for (int i = 0; i < 5; i++) {
        fout << arr[i] << " ";
    }

    fout.close();
    cout << "Data written to file successfully!\n";

    return 0;
}

```

- Write/Read line by line by getline()

```cpp
#include<fstream>

int main()
{
    // # Write line by line
    ofstream fout;
    fout.open("db.txt");
    if(!fout)
    {
        cout<<"Error during opening files";
        return 1;
    }
    fout<<"Hellow rahul\n";
    fout<<"Hellow deepak\n";
    fout<<"Hellow suraj";
    fout.close();

    // # Read line by line
    ifstream fin;
    fin.open("db.txt");
    string line;
    while(getline(fin,line))
    {
        cout<<line<<endl;
    }
    fin.close();
    return 0;
}
```

- No need to create file if not exist only need to check
```cpp
ifstream file("./data/db.txt");
if (!file)
{
    cout << "Error :: DB file not found!!";
    return;
}
```


- Check file is empty of not
```cpp
if(file.peek()== ifstream::traits_type::eof())
{
    cout<<"Empty file";
}
else{
    cout<<"File is not empty.";
}
```
