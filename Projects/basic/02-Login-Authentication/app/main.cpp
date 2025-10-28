#include <iostream>
#include <regex>
#include <fstream>
#include "../include/bcrypt.h"
#include <sstream>
using namespace std;

struct ValidationResult
{
    bool status;
    string message;
};

class AuthSystem
{
    string fileName = "db.txt";

public:
    void showMenu();
    void loginUser();
    ValidationResult validateUser(const string &, const string &);
    void registerUser();
    // # Validation Function
    bool isValidUsername(const string &);
    bool isValidEmail(const string &);
    bool isValidPassword(const string &);
    string getUserName();
    string getEmail();
    string getPassword();
    // # Hashing password
    string hashPassword(const string &);
    bool verifyPassword(const string &, const string &);
    bool checkUserExist(const string &);
    ValidationResult saveUserData(const string &, const string &, const string &);
    void forgotPassword();
    void resetPassword();
    void logoutUser();
};

void homePage()
{
    cout << "Welcome to my Application.." << endl;
    cout << "<<-------------------------------------->>";
}

void AuthSystem::showMenu()
{
    while (true)
    {

        int choice = 0;
        cout << "\n==============================";
        cout << "\n|      LOGIN SYSTEM v2.0     |";
        cout << "\n==============================";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Forgot Password\n";
        cout << "4. Reset Password\n";
        cout << "5. Logout\n";
        cout << "Enter choice : ";
        cin >> choice;

        // Validate input
        // if (!(cin >> choice))
        // {
        //     cout << "\nInvalid choice! Please enter a number.\n";
        //     cin.clear();
        //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //     continue;
        // }

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            forgotPassword();
            break;
        case 4:
            resetPassword();
            break;
        case 5:
            return logoutUser();

        default:
            cout << "Please enter valid choice.";
        }
    }
}

void AuthSystem::loginUser()
{
    string email, password;
    cout << "Enter email : ";
    cin >> email;
    cout << "Enter password : ";
    cin >> password;
    ValidationResult responce = validateUser(email, password);
    if (!responce.status)
    {
        cout << "\n<<-------------------------------------->>" << endl;
        cout << responce.message << endl;
        cout << "<<-------------------------------------->>";
        return;
    }
    cout << "<<-------------------------------------->>" << endl;
    cout << responce.message << endl;
    homePage();
}

ValidationResult AuthSystem::validateUser(const string &email, const string &password)
{
    // # Step 1: Check user exist or not
    bool isUserExist = checkUserExist(email);
    if (!isUserExist)
    {
        return {false, "User Not Found, Please resgister.."};
    }

    // # Step 2: Verify credentials
    ifstream file("./data/db.txt"); // no need to create file if not exist only need to check
    if (!file)
    {
        return {false, "Error :: DB file not found.."};
    }

    string line;
    string dummy, storedEmail, storedPass;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        ss >> dummy >> storedEmail >> storedPass; // read using space
        if (email == storedEmail)
        {
            if (verifyPassword(password, storedPass))
                return {true, "Login Successfully.."}; // user exist
            else
                return {false, "Invalid Password.."};
        }
    }
    file.close();
    return {false, "Invalid Email.."}; // user not exist
}

string AuthSystem::getUserName()
{
    string userName = "";
    // # User name input validations
    cout << "\nUsername Requirements:\n";
    cout << "- Must be 3-15 characters long\n";
    cout << "- Can contain letter,number and underscores\n";
    while (true)
    {
        cout << "\nEnter username : ";
        cin >> userName;
        if (isValidUsername(userName))
        {
            cout << "Username accepted!\n";
            break;
        }
        else
        {
            cout << "Invalid username.Please follow the rule above\n";
        }
    }
    return userName;
}

string AuthSystem::getEmail()
{
    string email = "";
    // # Email input validations
    cout << "\nEmail Requirements:\n";
    cout << "- Must contain a valid '@' symbol (e.g. user@example.com)\n";
    cout << "- Domain name must be valid (e.g. gmail.com, outlook.in)\n";
    cout << "- Can include letters, numbers, dots (.), underscores (_), hyphens (-), or plus (+)\n";
    cout << "- Must end with a valid domain extension like .com, .in, .org, etc.\n";
    cout << "- Example of valid email: johndoe_123@gmail.com\n";
    while (true)
    {
        cout << "\nEnter email : ";
        cin >> email;
        if (isValidEmail(email))
        {
            cout << "Email accepted!\n";
            break;
        }
        else
        {
            cout << "Invalid email.Please follow the rule above\n";
        }
    }
    return email;
}

string AuthSystem::getPassword()
{
    string password = "";
    // # Password input validations
    cout << "\nPassword Requirements:\n";
    cout << "- Minimum 8 characters\n";
    cout << "- At least one upper letter\n";
    cout << "- At least one lower letter\n";
    cout << "- At least one digit\n";
    cout << "- At least one special character (@$!%*?&)\n";

    while (true)
    {
        cout << "\nEnter password : ";
        cin >> password;
        if (isValidPassword(password))
        {
            cout << "Strong password accepted!\n";
            break;
        }
        else
        {
            cout << "Weak password.Please follow the rule above\n";
        }
    }
    return password;
}

void AuthSystem::registerUser()
{
    string userName = getUserName();
    string email = getEmail();
    string password = getPassword();

    // # Save in DB(file)
    ValidationResult responce = saveUserData(userName, email, password);
    if (!responce.status)
    {
        cout << "\n<<-------------------------------------->>" << endl;
        cout << responce.message << endl;
        cout << "<<-------------------------------------->>" << endl;
        return;
    }
    cout << "\n<<-------------------------------------->>" << endl;
    cout << responce.message << endl;
    cout << "<<-------------------------------------->>" << endl;
}

bool AuthSystem::isValidUsername(const string &username)
{
    regex usernamePattern("^[A-Za-z0-9_]{3,15}$");
    return regex_match(username, usernamePattern);
}

bool AuthSystem::isValidEmail(const string &email)
{
    regex emailPattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,63}$)");
    return regex_match(email, emailPattern);
}

bool AuthSystem::isValidPassword(const string &password)
{
    regex passwordPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[@$!%*?&])[A-Za-z0-9@$!%*?&]{8,}$");
    return regex_match(password, passwordPattern);
}

string AuthSystem::hashPassword(const string &password)
{
    string hash = bcrypt::generateHash(password);
    return hash;
}

bool AuthSystem::verifyPassword(const string &password, const string &hash)
{
    return bcrypt::validatePassword(password, hash);
}

bool AuthSystem::checkUserExist(const string &email)
{
    ifstream file("./data/db.txt");
    if (!file)
    {
        return false;
    }
    string line;
    string dummy, storedEmail;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        ss >> dummy >> storedEmail; // used dummy to get 2nd position value
        if (email == storedEmail)
        {
            return true; // user exist
        }
    }
    file.close();
    return false; // user not exsit
}

ValidationResult AuthSystem::saveUserData(const string &userName, const string &email, const string &password)
{
    // # Step 1: check user exist or not
    bool isUserExist = checkUserExist(email);
    if (isUserExist)
    {
        return {false, "User Already Exit,Please Register.."};
    }
    // # Store in file
    ofstream file;
    file.open("./data/db.txt", ios::app);
    if (!file)
    {
        return {false, "Error :: Error during openings file!"};
    }

    // # Step 2: if user not exist save in DB

    // # Hashing of the password
    string hasedPassword = hashPassword(password);

    file << userName << " " << email << " " << hasedPassword << " " << "\n";
    file.close();
    return {true, "Registration Successfully"};
    ;
}

void AuthSystem::forgotPassword()
{
    resetPassword();
}

void AuthSystem::resetPassword()
{
    string email = "", newpassword = "", hashedPassword = "";
    cout << "Enter email : ";
    cin >> email;

    // # Step 1: check user exist or not
    bool isUserExist = checkUserExist(email);
    if (!isUserExist)
    {
        cout << "\n<<-------------------------------------->>" << endl;
        cout << "User Not Found, Please resgister.." << endl;
        cout << "<<-------------------------------------->>" << endl;
        return;
    }

    // # Step 2: Password input validations
    newpassword = getPassword();
    hashedPassword = hashPassword(newpassword);

    // # Step 3: File reading & writing
    ifstream inFile("./data/db.txt");
    ofstream outFile("./data/temp.txt");
    if (!inFile || !outFile)
    {
        cout << "Error : during file openings..";
        return;
    }

    string line;
    string username, storedEmail, storedPassword;
    while (getline(inFile, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        ss >> username >> storedEmail >> storedPassword;
        if (email == storedEmail)
        {
            outFile << username << " " << storedEmail << " " << hashedPassword << "\n";
            continue;
        }
        outFile << line << "\n";
    }

    outFile.close();
    inFile.close();
    remove("./data/db.txt");
    rename("./data/temp.txt", "./data/db.txt");
    cout << "<<-------------------------------------->>" << endl;
    cout << "Pasword is successfully updated,Please login.." << endl;
    cout << "<<-------------------------------------->>" << endl;
    return;
}

void AuthSystem::logoutUser()
{
    cout << "<<-------------------------------------->>" << endl;
    cout << "Logout from the Applications.." << endl;
    cout << "<<-------------------------------------->>" << endl;
    return;
}

int main()
{
    AuthSystem auth;
    auth.showMenu();
    return 0;
}