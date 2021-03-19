#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <iostream>
#include <map>
#include <vector>

static std::map<std::string, int> degrees = {
        {" ", 0},
        {"k", 3},
        {"M", 6},
        {"B", 9},
        {"T", 12},
        {"q", 15},
        {"Q", 18},
        {"s", 21},
        {"S", 24},
        {"O", 27}
};

static std::map<int, std::string> string_degrees = {
        {0, " "},
        {3, "k"},
        {6, "M"},
        {9, "B"},
        {12, "T"},
        {15, "q"},
        {18, "Q"},
        {21, "s"},
        {24, "S"},
        {27, "O"}
};


class BigInteger {
public:
    BigInteger();

    explicit BigInteger(long long x);
    explicit BigInteger(std::vector<int> x);
    explicit BigInteger(const std::string& x);

    friend BigInteger operator+(const BigInteger& l_number,const BigInteger& r_number);
    friend BigInteger operator-(const BigInteger& l_number,const BigInteger& r_number);
    friend BigInteger operator*(BigInteger l_number, double r_number);
    friend BigInteger operator*(BigInteger l_number, int r_number);
    BigInteger& operator+=(const BigInteger& r_number);
    BigInteger& operator-=(const BigInteger& r_number);
    BigInteger& operator*=(double r_number);
    BigInteger& operator*=(int r_number);

    friend bool operator<(const BigInteger& l_number, const BigInteger& r_number);
    friend bool operator>(const BigInteger& l_number, const BigInteger& r_number);
    friend bool operator>=(const BigInteger& l_number, const BigInteger& r_number);
    friend bool operator==(const BigInteger& l_number, const BigInteger& r_number);
    friend bool operator!=(const BigInteger& l_number, const BigInteger& r_number);

    std::string ToShortString() const;
    std::string ToLongString() const;

private:
    std::vector<int> number_;
};

#endif //  BIG_INTEGER_H
