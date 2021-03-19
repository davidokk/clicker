#ifndef BOOST_BOOST_H
#define BOOST_BOOST_H

#include "big_integer.h"
#include <QString>

class Boost {
 public:
    virtual BigInteger UpdateForLevel() = 0;
    virtual BigInteger Profit() const = 0;

    QString TextForButton() const;

    BigInteger getPrice() const { return price_; }
    BigInteger getGrowth() const { return growth_; }
    size_t getLevel() const { return level_; }

    friend std::ostream& operator<<(std::ostream& out, const Boost& boost);
    friend std::istream& operator>>(std::istream& in, Boost& boost);

 protected:
  BigInteger price_;
  BigInteger growth_;
  size_t level_;
  double factor_;
};

class PassiveBoost : public Boost {
 public:
  explicit PassiveBoost(size_t boost_index);
  BigInteger UpdateForLevel() override;
  BigInteger Profit() const override;
};

class ClickBoost : public Boost {
 public:
  ClickBoost();
  BigInteger UpdateForLevel() override;
  BigInteger Profit() const override;
};

#endif //  BOOST_BOOST_H
