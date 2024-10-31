/* �������� ���� TNumber � ����������� �������� ��� ����������� ���� ���� ��
����������� �����/�������� �����.
�� ����� ����� ����� �������� �����-������� TIntNumber �� TRealNumber,
� ���� ���������� ������������ �������� ������.
�������� m �ᒺ��� ����� ����� �� n
�ᒺ��� ������ ����� (��� ����������� ���������� �����).
������ ���� ������ ���� ����� ����� �� ���� ������� ���� ������ �����. */


#include <iostream>
#include <corecrt_math.h>
#include <vector>
#include <cmath>
#include <cstdlib> 
#include <ctime>
#include <Windows.h>

using namespace std;
//����������� ���� tNumber
class TNumber {
protected:
    double m_number;

public:
    TNumber(double givennum) : m_number(givennum) {}

    virtual unsigned int getSumofDigits() const = 0;
    virtual unsigned int getFirstDigit() const = 0;
    virtual unsigned int getLastDigit() const = 0;
};

//����-������� TIntNumber
class TIntNumber : public TNumber{
public:
    TIntNumber(int givennum) :TNumber(givennum) {}

    //����� ����������� ���� ����

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

    //����� ����������� ����� �����

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

    //����� ��� ����������� �������� �����

    virtual unsigned int getLastDigit() const override
    { 
        return abs(static_cast<int>(m_number)) % 10;
    };
};



class TRealNumber : public TNumber {
public:
    TRealNumber(double givennum) :TNumber(givennum) {}

    //����� ����������� ���� ����

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

    //����� ����������� ����� �����

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

    //����� ��� ����������� �������� �����

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
        cout <<"��������� ���� ����� ����������� �� �������: "<<i<<" = " << randomInt << endl;
        numbers.push_back(new TIntNumber(randomInt));
    }
    for (int i = 0; i < m; ++i) {
        double randomReal = static_cast<double>((rand() % 1001) / 10.0 - 500);
        cout << "��������� ����� ����� ����������� �� �������: " << i << " = " << randomReal << endl;
        numbers.push_back(new TRealNumber(randomReal));
    }
    //������ ���� ������ ���� ����� ����� �� ���� ������� ���� ������ �����.

    unsigned int sumoffirstintnum = 0;
    for (int i = 0; i < n; i++) {
        sumoffirstintnum += numbers[i]->getFirstDigit();
    }

    unsigned int sumoflastrealnum = 0;
    for (int i = n; i < n + m; i++) {
        sumoflastrealnum += numbers[i]->getLastDigit();
    }

    cout << "���� ������ ���� ����� �����: " << sumoffirstintnum << endl;
    cout << "���� ������� ���� ������ �����: " << sumoflastrealnum << endl;
    cout << 441.1 - 441 << endl;
    float a = 441.1;
    float b = static_cast<int>(a);
    float ost = a - b;
    cout << ost << endl;
}