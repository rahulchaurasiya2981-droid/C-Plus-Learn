#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class AuthSystem {
private:
    struct User {
        string username;
        string password;
        string securityAnswer;
    };

    string fileName = "users.txt";

public:
    void menu();
    void registerUser();
    void loginUser();
    void forgotPassword();
    void resetPassword();
    void clearScreen();
};

// ------------------ Menu ------------------
void AuthSystem::menu() {
    int choice;
    while (true) {
        clearScreen();
        cout << "=================================\n";
        cout << "     USER AUTHENTICATION SYSTEM  \n";
        cout << "=================================\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Forgot Password\n";
        cout << "4. Reset Password\n";
        cout << "5. Exit\n";
        cout << "---------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                loginUser();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                forgotPassword();
                break;
            case 4:
                resetPassword();
                break;
            case 5:
                cout << "Exiting... Thank you!\n";
                return;
            default:
                cout << "❌ Invalid choice. Try again!\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
    }
}

// ------------------ Register ------------------
void AuthSystem::registerUser() {
    User user;
    ofstream file(fileName, ios::app);

    cout << "\n--- User Registration ---\n";
    cout << "Enter username: ";
    cin >> user.username;
    cout << "Enter password: ";
    cin >> user.password;
    cout << "Enter secret answer (for password recovery): ";
    cin >> user.securityAnswer;

    file << user.username << " " << user.password << " " << user.securityAnswer << endl;
    file.close();

    cout << "✅ Registration successful!\n";
}

// ------------------ Login ------------------
void AuthSystem::loginUser() {
    string username, password;
    cout << "\n--- User Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file(fileName);
    string u, p, s;
    bool found = false;

    while (file >> u >> p >> s) {
        if (u == username && p == password) {
            cout << "✅ Login successful! Welcome, " << username << "!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "❌ Invalid username or password.\n";

    file.close();
}

// ------------------ Forgot Password ------------------
void AuthSystem::forgotPassword() {
    string username, answer;
    cout << "\n--- Forgot Password ---\n";
    cout << "Enter your username: ";
    cin >> username;

    ifstream file(fileName);
    string u, p, s;
    bool found = false;

    while (file >> u >> p >> s) {
        if (u == username) {
            found = true;
            cout << "Enter your secret answer: ";
            cin >> answer;

            if (answer == s)
                cout << "✅ Your password is: " << p << endl;
            else
                cout << "❌ Incorrect secret answer.\n";

            break;
        }
    }

    if (!found)
        cout << "❌ Username not found.\n";

    file.close();
}

// ------------------ Reset Password ------------------
void AuthSystem::resetPassword() {
    string username, oldPass, newPass;
    cout << "\n--- Reset Password ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter old password: ";
    cin >> oldPass;

    ifstream file(fileName);
    ofstream temp("temp.txt");
    string u, p, s;
    bool found = false;

    while (file >> u >> p >> s) {
        if (u == username && p == oldPass) {
            cout << "Enter new password: ";
            cin >> newPass;
            temp << u << " " << newPass << " " << s << endl;
            found = true;
            cout << "✅ Password updated successfully!\n";
        } else {
            temp << u << " " << p << " " << s << endl;
        }
    }

    file.close();
    temp.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");

    if (!found)
        cout << "❌ Username or old password incorrect.\n";
}

// ------------------ Clear Screen ------------------
void AuthSystem::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ------------------ Main ------------------
int main() {
    AuthSystem app;
    app.menu();
    return 0;
}
