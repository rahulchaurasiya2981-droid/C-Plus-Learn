#include <iostream>
#include <cmath>   // for math functions
#include <cstdlib> // for system("cls")
#include <limits>  // for input validation
using namespace std;

void show_calculator()
{
    cout << "----------------------------------------------" << endl;
    cout << "-----                                    -----" << endl;
    cout << "--               SCIENTIFIC                 --" << endl;
    cout << "--               CALCULATOR                 --" << endl;
    cout << "-----                                    -----" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "|     +        |      -       |        *     |" << endl;
    cout << "|    Add       |    Minus     |     Multiply |" << endl;
    cout << "---------------------------------------------|" << endl;
    cout << "|      /       |      m       |        L     |" << endl;
    cout << "|    Divide    |     Mod      |       Log    |" << endl;
    cout << "---------------------------------------------|" << endl;
    cout << "|      S       |      C       |        p     |" << endl;
    cout << "|    Square    |     Cube     |      Power   |" << endl;
    cout << "---------------------------------------------|" << endl;
    cout << "|     s        |      c       |        t     |" << endl;
    cout << "|    sin       |     cos      |       tan    |" << endl;
    cout << "---------------------------------------------|" << endl;
    cout << "|     r        |      k       |        .     |" << endl;
    cout << "|  sq root     |    clear     |      close   |" << endl;
    cout << "---------------------------------------------|" << endl;
}
void show_output(double answer)
{
    cout << "|---------------------------------------------" << endl;
    cout << "|----                 ------------------------" << endl;
    cout << "|-       OPERATION    | " << endl;
    cout << "|-       OUTPUT IS:   | " << answer << "          " << endl;
    cout << "|----                 ------------------------" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "|     +        |      -       |        *     |" << endl;
    cout << "|    Add       |    Minus     |     Multiply |" << endl;
    cout << "---------------------------------------------|" << endl;
    cout << "|      /       |      m       |        L     |" << endl;
    cout << "|    Divide    |     Mod      |       Log    |" << endl;
    cout << "---------------------------------------------|" << endl;
    cout << "|      S       |      C       |        p     |" << endl;
    cout << "|    Square    |     Cube     |      Power   |" << endl;
    cout << "---------------------------------------------|" << endl;
    cout << "|     s        |      c       |        t     |" << endl;
    cout << "|    sin       |     cos      |       tan    |" << endl;
    cout << "---------------------------------------------|" << endl;
    cout << "|     r        |      k       |        .     |" << endl;
    cout << "|  sq root     |    clear     |      close   |" << endl;
    cout << "---------------------------------------------|" << endl;
}

// Function to safely take numeric input
double get_number(const string &label)
{
    double num;
    while (true)
    {
        cout << "Enter " << label << ": ";
        cin >> num;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
        else
        {
            return num;
        }
    }
}

int main()
{
    char op;
    string input;
    double num1, num2, answer;
    show_calculator();
    while (1)
    {

        cout << "Enter operations : ";
        cin >> input;
        if (input.size() != 1)
        {
            cout << "Invalid input! Please enter only ONE character (+, -, *, /, .)\n";
            continue;
        }
        op = input[0];

        if (op == '.')
        {
            cout << "\nCalculator closed. Goodbye!\n";
            break;
        }

        switch (op)
        {
        case '+':
            num1 = get_number("num1");
            num2 = get_number("num2");
            answer = (num1 + num2);
            system("cls");
            show_output(answer);
            break;

        case '-':
            num1 = get_number("num1");
            num2 = get_number("num2");
            answer = (num1 - num2);
            system("cls");
            show_output(answer);
            break;

        case '*':
            num1 = get_number("num1");
            num2 = get_number("num2");
            answer = (num1 * num2);
            system("cls");
            show_output(answer);
            break;

        case '/':
            num1 = get_number("num1");
            num2 = get_number("num2");
            answer = (num1 / num2);
            system("cls");
            show_output(answer);
            break;

        case 'm':
            num1 = get_number("num1");
            num2 = get_number("num2");
            answer = fmod(num1, num2);
            system("cls");
            show_output(answer);
            break;

        case 'L':
            num1 = get_number("num1");
            if (num1 <= 0)
            {
                cout << "Logarithm defined only for positive numbers.\n";
                break;
            }
            answer = log10(num1);
            system("cls");
            show_output(answer);
            break;

        case 'S':
            num1 = get_number("num1");
            answer = pow(num1, 2);
            system("cls");
            show_output(answer);
            break;

        case 'C':
            num1 = get_number("num1");
            answer = pow(num1, 3);
            system("cls");
            show_output(answer);
            break;

        case 'p':
            num1 = get_number("num1");
            num2 = get_number("num2");
            answer = pow(num1, num2);
            system("cls");
            show_output(answer);
            break;

        case 's':
            num1 = get_number("num1");
            answer = sin(num1);
            system("cls");
            show_output(answer);
            break;

        case 'c':
            num1 = get_number("num1");
            answer = cos(num1);
            system("cls");
            show_output(answer);
            break;

        case 't':
            num1 = get_number("num1");
            answer = tan(num1);
            system("cls");
            show_output(answer);
            break;

        case 'r':
            num1 = get_number("num1");
            answer = sqrt(num1);
            system("cls");
            show_output(answer);
            break;

        case 'k':
            system("cls");
            show_calculator();
            break;

        default:
            cout << "Please Enter Valid Operations!" << endl;
        }
    }

    return 0;
}