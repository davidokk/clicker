#include "big_integer.h"

#include <algorithm>

BigInteger::BigInteger() {
    number_.push_back(0);
}

BigInteger::BigInteger(long long x) {
    if (x == 0)
        number_.push_back(0);
    while (x) {
        number_.push_back(x % 10);
        x /= 10;
    }
}

BigInteger::BigInteger(std::vector<int> x) {
    number_ = std::move(x);
}

BigInteger::BigInteger(const std::string& x) {
    number_.resize(x.size());
    for (int i = x.size() - 1; i >= 0; i--)
        number_[x.size() - i - 1] = x[i] - '0';
}

BigInteger operator+(const BigInteger& l_number,const BigInteger& r_number) {
    BigInteger res;
    if (l_number.number_.size() > r_number.number_.size()) {
        return r_number + l_number;
    }
    res.number_.resize(r_number.number_.size() + 1);
    for (size_t i = 0; i < r_number.number_.size(); i++) {
        res.number_[i] += r_number.number_[i];
        if (i < l_number.number_.size())
            res.number_[i] += l_number.number_[i];
        if (res.number_[i] >= 10) {
            res.number_[i + 1]++;
            res.number_[i] -= 10;
        }
    }
    while (res.number_.size() != 1 && res.number_.back() == 0)
        res.number_.pop_back();
    return res;
}

BigInteger& BigInteger::operator+=(const BigInteger &r_number) {
    return *this = *this + r_number;
}

BigInteger operator-(const BigInteger& l_number,const BigInteger& r_number) {
    BigInteger res;
    res.number_ = l_number.number_;
    for (size_t i = 0; i < res.number_.size(); i++) {
        if (i < r_number.number_.size())
            res.number_[i] -= r_number.number_[i];
        if (res.number_[i] < 0) {
            res.number_[i] += 10;
            res.number_[i + 1]--;
        }
    }
    while (res.number_.size() != 1 && res.number_.back() == 0)
        res.number_.pop_back();
    return res;
}

BigInteger& BigInteger::operator-=(const BigInteger &r_number) {
    return *this = *this - r_number;
}

BigInteger operator*(BigInteger l_number, double r_number) {
    int r = static_cast<int>(r_number * 10000);
    for (auto& el : l_number.number_)
        el *= r;
    for (size_t i = 0; i < l_number.number_.size() - 1; i++) {
        l_number.number_[i + 1] += l_number.number_[i] / 10;
        l_number.number_[i] %= 10;
    }
    while (l_number.number_.back() >= 10) {
        int x = l_number.number_.back() / 10;
        l_number.number_.back() %= 10;
        l_number.number_.push_back(x);
    }
    std::reverse(l_number.number_.begin(), l_number.number_.end());
    for (int i = 0; i < 4; i++)
        l_number.number_.pop_back();
    std::reverse(l_number.number_.begin(), l_number.number_.end());
    while (l_number.number_.back() == 0)
        l_number.number_.pop_back();
    if (l_number.number_.empty())
        l_number.number_ = {0};
    return l_number;
}

BigInteger operator*(BigInteger l_number, int r_number) {
    size_t r = r_number;
    for (auto& el : l_number.number_)
        el *= r;
    for (size_t i = 0; i < l_number.number_.size() - 1; i++) {
        l_number.number_[i + 1] += l_number.number_[i] / 10;
        l_number.number_[i] %= 10;
    }
    while (l_number.number_.back() >= 10) {
        int x = l_number.number_.back() / 10;
        l_number.number_.back() %= 10;
        l_number.number_.push_back(x);
    }
    while (l_number.number_.back() == 0)
        l_number.number_.pop_back();
    if (l_number.number_.empty())
        l_number.number_ = {0};
    return l_number;
}

BigInteger& BigInteger::operator*=(double r_number) {
    return *this = *this * r_number;
}

BigInteger& BigInteger::operator*=(int r_number) {
    return *this = *this * r_number;
}
bool operator>(const BigInteger& l_number, const BigInteger& r_number) {
    if (l_number.number_.size() != r_number.number_.size())
        return l_number.number_.size() > r_number.number_.size();
    for (int i = (int)l_number.number_.size() - 1; i >= 0; i--)
        if (l_number.number_[i] != r_number.number_[i])
            return l_number.number_[i] > r_number.number_[i];
    return false;
}

bool operator<(const BigInteger& l_number, const BigInteger& r_number) {
    return !(l_number > r_number || l_number == r_number);
}

bool operator==(const BigInteger& l_number, const BigInteger& r_number) {
    return l_number.number_ == r_number.number_;
}

bool operator!=(const BigInteger& l_number, const BigInteger& r_number) {
    return l_number.number_ != r_number.number_;
}

std::string BigInteger::ToShortString() const {
    std::string degree = std::prev(string_degrees.upper_bound(number_.size() - 1))->second;
    size_t size_num = number_.size() - degrees[degree];
    std::string res;
    for (size_t i = 0; i < size_num; i++)
        res += '0' + number_[number_.size() - i - 1];
    if (degree != " ") {
        res += '.';
        for (size_t i = size_num; i < std::min(number_.size(), size_num + 3); i++)
            res += '0' + number_[number_.size() - i - 1];
        while (res.back() == '0')
            res.pop_back();
        if (res.back() == '.')
            res.pop_back();
        res += degree;
    }
    return res;
}

std::string BigInteger::ToLongString() const {
    std::string ret;
    for (int i = number_.size() - 1; i >= 0; i--)
        ret += '0' + number_[i];
    return ret;
}

bool operator>=(const BigInteger& l_number, const BigInteger& r_number) {
    return !(l_number < r_number);
}
