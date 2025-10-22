#include <iostream>
using namespace std;

double addition(double num1, double num2)
{
    double result = (num1 + num2);
    cout << "\n Reusult : " << result;
}
double subtraction(double num1, double num2)
{
    double result = (num1 - num2);
    cout << "\n Reusult : " << result;
}
double multiplication(double num1, double num2)
{
    double result = (num1 * num2);
    cout << "\n Reusult : " << result;
}
double division(double num1, double num2)
{
    double result = (num1 / num2);
    cout << "\n Reusult : " << result;
}
double modulo(double num1, double num2)
{
    double result = (num1 % num2);
    cout << "\n Reusult : " << result;
}
int main()
{
    char op;
    double num1, num2, result;
    cout << "--------------- Welcome!! ---------------------" << "\n";
    cout << "Enter operation : (+,-,*,/,%)";
    cin >> op;
    cout << "Enter 1st number : ";
    cin >> num1;
    cout << "Enter 2nd number : ";
    cin >> num2;
    switch (op)
    {
    case '+':
        addition(num1, num2);
        return;
    case '-':
        subtraction(num1, num2);
        return;
    case '*':
        multiplication(num1, num2);
        return;
    case '/':
        division(num1, num2);
        return;
    case '%':
        modulo(num1, num2);
        return;
    default:
        cout << "Pleasee insert valid operations....";
    }
    return 0;
}