# 🔐 Login System v2.0 (C++)

A **modern, secure, and beginner-friendly authentication system** built in **C++**, featuring **file-based user management**, **bcrypt password hashing**,**Object-Oriented Design** and **regex-based validation** for usernames, emails, and passwords. This project demonstrates **real-world login functionality** — registration, login, forgot password, reset password, and data security — all from scratch using standard C++.


## 🧠 Concepts & Keywords

- Object-Oriented Programming (OOP)  
- Encapsulation & Abstraction  
- Modularity & Reusability  
- Regex-based Input Validation  
- bcrypt Password Hashing  
- File Handling & Data Persistence  
- User Registration & Login  
- Password Reset Flow  
- ValidationResult Struct for Error Handling  
- Secure Authentication Logic  
- File-Based Storage  



---

## 🚀 Features

✅ **User Registration**  
- Validates username, email, and password formats  
- Encrypts passwords using **bcrypt hashing**  
- Stores user data securely in a local file (`db.txt`)

✅ **User Login**  
- Verifies credentials using **bcrypt password comparison**  
- Prevents login with invalid credentials

✅ **Forgot / Reset Password**  
- Allows users to securely reset their password  
- Updates stored hash without exposing plaintext password

✅ **Input Validation**  
- Username: 3–15 characters, letters/numbers/underscores  
- Email: Standard RFC-like format (e.g., `user@example.com`)  
- Password: At least 8 chars with uppercase, lowercase, digit & special symbol  

✅ **File-Based User Management**  
- Stores and updates user records in `./data/db.txt`  
- Handles file read/write operations safely

✅ **Simple CLI Interface**  
- Easy-to-navigate text-based menu  
- Interactive prompts with validation feedback

---


## 🧩 How It Works
The program starts by displaying a simple authentication menu interface with options like **Register**, **Login**, and **Reset Password**. 
When you choose an option, it guides you step-by-step — for example:

1. **Register** 
- Takes username,email,password and security answer.
- The inputs are checked using **regex** to ensure they follow valid formats. 
- The password is then **hashed securely using bcrypt** before saving.

2. **Login**
- You enter your email and password
- compare email and bcrypt hash with DB text, and grants access if everything matches.

3. **Forgot Password**
- You confirm your identity (e.g., by giving email)
- Set a new password, and the system updates the stored hash.

4. **Reset Password**
- You confirm your identity (e.g., by giving email)
- Set a new password, and the system updates the stored hash.

```bash
>> g++ app/main.cpp src/bcrypt.cpp src/blowfish.cpp -o main.exe
>> .\main.exe

======== LOGIN SYSTEM =========
1. Register
2. Login
3. Forgot Password
4. Reset Password
5. Logout
Enter choice :


```

