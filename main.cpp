#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int TO4NOST = 0;

string code(double number);
double decode(string number2);
string to2(int number);
string to2(double number);
int to10(string number2);

int main() {
    setlocale(LC_ALL, "rus");

    double number;
    string number2;
    int coding;

    cout << "0 - половинная точность\n";
    cout << "1 - одинарная точность\n";
    cout << "2 - двойная точность\n";

    cout << "Выберите номер точности: ";
    cin >> TO4NOST;

    cout << "0 - закодировать\n";
    cout << "1 - декодировать\n";

    cout << "Выберите что делать: ";
    cin >> coding;

    cout << "Введите число: ";
    switch (coding) {
    case 0:
        cin >> number;
        cout << code(number) << endl;
        break;
    case 1:
        cin >> number2;
        cout << decode(number2) << endl;
        break;
    
    default:
        cout << "Ты больной?\n";
    }

    return 0;
}

string code(double number) {
    string znak = (number < 0) ? "1" : "0";
    number = abs(number);
    int left = (int)number;
    double right = number - left;
    string left2 = to2(left), right2 = to2(right);
    int p;
    if (number > 1) {
        for (int i = 1; i < left2.length(); i++)
            right2.insert(i - 1, to_string(left2.at(i) - '0'));
        p = left2.length() - 1;
    } else {
        for (int i = 0; i < right2.length(); i++) {
            if (right2.at(i) == '1')
                p = -(i + 1);
        }
    }
    int e;
    switch (TO4NOST) {
    case 0:
        e = 15;
        break;
    case 1:
        e = 127;
        break;
    case 2:
        e = 1023;
        break;
    
    default:
        break;
    }
    int n = p + e;
    string n2 = to2(n);
    while (n2.length() < 5)
        n2.insert(0, "0");
    string res_ = znak + n2 + right2;
    string res = "";
    switch (TO4NOST) {
    case 0:
        for (int i = 0; i < 16; i++)
            res.append(to_string(res_.at(i) - '0'));
        break;

    case 1:
        for (int i = 0; i < 32; i++)
            res.append(to_string(res_.at(i) - '0'));
        break;

    case 2:
        for (int i = 0; i < 64; i++)
            res.append(to_string(res_.at(i) - '0'));
        break;
    
    default:
        break;
    }
    return res;
}

double decode(string number2) {
    int e = 0;
    string n2, right2;
    switch (TO4NOST) {
    case 0:
        e = 15;
        n2 = number2.substr(1, 5);
        right2 = number2.substr(6);
        break;
    case 1:
        e = 127;
        n2 = number2.substr(1, 8);
        right2 = number2.substr(9);
        break;
    case 2:
        e = 1023;
        n2 = number2.substr(1, 11);
        right2 = number2.substr(12);
        break;
    default:
        break;
    }
    int n = to10(n2);
    int p = n - e;

    string left2 = "1";
    if (p >= 0) {
        for (int i = 0; i < p; i++)
            left2.append(to_string(right2.at(i) - '0'));
        right2.erase(0, p);
    } else {
        right2.append(left2);
        left2 = "0";
        for (int i = 0; i < abs(p) - 1; i++)
            right2.insert(0, "0");
    }

    double number = 0;
    for (int i = left2.length() - 1, j = 0; i >= -right2.length(), j < (left2 + right2).length(); i--, j++) {
        number += pow(2, i) * (((left2 + right2).at(j) == '1') ? 1 : 0);
        if ((left2 + right2).at(j) == '1') cout << i << " ";
    }
    cout << "\n";
    return number * ((number2.at(0) == '0') ? 1 : -1);
}

string to2(int number) {
    string num2 = "";

    while (number > 0) {
        int ost = number % 2;
        num2.insert(0, to_string(ost));
        number /= 2;
    } 

    return num2;
}

string to2(double number) {
    string num2 = "";

    switch (TO4NOST) {
    case 0:
        for (int i = 0; i < 10; i++) {
            number *= 2;
            if (number >= 1) {
                number -= 1;
                num2.append("1");
            } else
                num2.append("0");
        }
        break;

    case 1:
        for (int i = 0; i < 23; i++) {
            number *= 2;
            if (number >= 1) {
                number -= 1;
                num2.append("1");
            } else
                num2.append("0");
        }
        break;

    case 2:
        for (int i = 0; i < 52; i++) {
            number *= 2;
            if (number >= 1) {
                number -= 1;
                num2.append("1");
            } else
                num2.append("0");
        }
        break;
    
    default:
        break;
    }

    return num2;
}

int to10(string number2) {
    int num = 0;

    for (int i = number2.length() - 1, j = 0; i >= 0, j < number2.length(); i--, j++)
        num += pow(2, i) * ((number2.at(j) == '1') ? 1 : 0);

    return num;
}