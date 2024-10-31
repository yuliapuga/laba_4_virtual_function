/* Створити клас TNumber з віртуальними методами для знаходження суми цифр та
знаходження першої/останньої цифри.
На основі цього класу створити класи-нащадки TIntNumber та TRealNumber,
у яких реалізовано перевизначені віртуальні методи.
Створити m об’єктів цілих чисел та n
об’єктів дійсних чисел (дані згенерувати випадковим чином).
Знайти суму перших цифр цілих чисел та суму останніх цифр дійсних чисел. */


#include <iostream>
#include <corecrt_math.h>
#include <vector>
#include <cmath>
#include <cstdlib> 
#include <ctime>
#include <Windows.h>

using namespace std;
//Абстрактний клас tNumber
class TNumber {
protected:
    double m_number;

public:
    TNumber(double givennum) : m_number(givennum) {}

    virtual unsigned int getSumofDigits() const = 0;
    virtual unsigned int getFirstDigit() const = 0;
    virtual unsigned int getLastDigit() const = 0;
};

//Клас-нащадок TIntNumber
class TIntNumber : public TNumber{
public:
    TIntNumber(int givennum) :TNumber(givennum) {}

    //Метод знаходження суми цифр

    virtual  unsigned int getSumofDigits() const override {
        unsigned int sum = 0;
        int number = static_cast<int>(m_number);
        if (number < 0) {
            number *= -1;
        }
        for (int i = number; i != 0; i = (i-i%10)/10) 
        {
            sum += i % 10;
        }
        return sum;
    }

    //Метод знаходження першої цифри

    virtual unsigned int getFirstDigit() const override {
        unsigned int firstdigit= 0;
        int number = static_cast<int>(m_number);
        if (number < 0) {
            number *= -1;
        }

        for (int i = number; i != 0;)
        {
            firstdigit = i;
            i = (i - i % 10) / 10;

        }
        return firstdigit;
    }

    //Метод для знаходження останньої цифри

    virtual unsigned int getLastDigit() const override
    { 
        return abs(static_cast<int>(m_number)) % 10;
    };
};



class TRealNumber : public TNumber {
public:
    TRealNumber(double givennum) :TNumber(givennum) {}

    //Метод знаходження суми цифр

    virtual  unsigned int getSumofDigits() const override {
        unsigned  int sum = 0;
        int znumber = abs(static_cast<int>(m_number));
        double ostnumber = m_number - znumber;
        for (int i = znumber; i != 0; i = (i - i % 10) / 10) {
            sum += i % 10;
        }
        for (int i = ostnumber; i > 0; i = i - static_cast<int>(i))
        {
            i *= 10;
            sum += static_cast<int>(i);
        }
        return sum;
    }

    //Метод знаходження першої цифри

    virtual unsigned int getFirstDigit() const override {
        unsigned int firstdigit = 0;
        int number = abs(static_cast<int>(m_number));
        for (int i = number; i != 0;)
        {
            firstdigit = i;
            i = (i - i % 10) / 10;
        }
        return firstdigit;
    }

    //Метод для знаходження останньої цифри

    virtual unsigned int getLastDigit() const override {
        double number = fabs(m_number);
        unsigned int lastnumber = 0;

        if (static_cast<int>(number) == number)
        {
            lastnumber = static_cast<int>(number) % 10;
        }
        else {
            number *= 100;
            for (int i = static_cast<int>(number); lastnumber == 0; i = static_cast<int>(i/10) )
            {
                lastnumber = i % 10;
            }
        }
        return lastnumber;
    }
};

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(static_cast<unsigned int>(time(0)));
    int n = 5;
    int m = 5;
    vector<TNumber*> numbers;

    for (int i = 0; i < n; ++i) {
        int randomInt = rand() % 1001;
        cout <<"Випадкове ціле число згенероване під номером: "<<i<<" = " << randomInt << endl;
        numbers.push_back(new TIntNumber(randomInt));
    }
    for (int i = 0; i < m; ++i) {
        double randomReal = static_cast<double>((rand() % 1001) / 10.0 - 500);
        cout << "Випадкове дійсне число згенероване під номером: " << i << " = " << randomReal << endl;
        numbers.push_back(new TRealNumber(randomReal));
    }
    //Знайти суму перших цифр цілих чисел та суму останніх цифр дійсних чисел.

    unsigned int sumoffirstintnum = 0;
    for (int i = 0; i < n; i++) {
        sumoffirstintnum += numbers[i]->getFirstDigit();
    }

    unsigned int sumoflastrealnum = 0;
    for (int i = n; i < n + m; i++) {
        sumoflastrealnum += numbers[i]->getLastDigit();
    }

    cout << "Сума перших цифр цілих чисел: " << sumoffirstintnum << endl;
    cout << "Сума останніх цифр дійсних чисел: " << sumoflastrealnum << endl;
    cout << 441.1 - 441 << endl;
    float a = 441.1;
    float b = static_cast<int>(a);
    float ost = a - b;
    cout << ost << endl;
}