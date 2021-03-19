#include "boost.h"

#include <sstream>
#include <QString>

PassiveBoost::PassiveBoost(size_t boost_index) {
  boost_index++;
  std::string s = "1";
  for (size_t i = 0; i < 3 * boost_index; ++i)
    s.push_back('0');
  price_ = BigInteger(s);
  growth_ = price_ * 0.001;
  factor_ = 0.5;
  level_ = 0;
}

ClickBoost::ClickBoost() {
  price_ = BigInteger(250);
  growth_ = BigInteger(1);
  level_ = 0;
  factor_ = 0;
}

std::ostream& operator<<(std::ostream& out, const Boost& boost) {
  out << "price: " << boost.price_.ToLongString() << std::endl;
  out << "growth: " << boost.growth_.ToLongString() << std::endl;
  out << "level: " << boost.level_ << std::endl;
  out << "factor: " << boost.factor_ << std::endl;
  return out;
}

std::istream& operator>>(std::istream& in, Boost& boost) {
  std::string s;
  in >> s >> s;
  boost.price_ = BigInteger(s);
  in >> s >> s;
  boost.growth_ = BigInteger(s);
  double x;
  in >> s >> x;
  boost.level_ = x;
  in >> s >> x;
  boost.factor_ = x;
  return in;
}

QString Boost::TextForButton() const {
  std::ostringstream os;
  os << "------------------\n";
  os << "Price: " << price_.ToShortString() << "\nNext bonus: " << Profit().ToShortString();
  os << "\n------------------\n" << "Bought: " << level_;
  return QString::fromStdString(os.str());
}

BigInteger PassiveBoost::UpdateForLevel() {
  ++level_;
  price_ += price_ * factor_;
  BigInteger profit = Profit();
  growth_ += profit;
  if (factor_ > 0.01)
    factor_ -= 0.01;
  return profit;
}

BigInteger ClickBoost::UpdateForLevel() {
  ++level_;
  price_ *= 2.25;
  BigInteger profit = Profit();
  growth_ += profit;
  return profit;
}

BigInteger PassiveBoost::Profit() const {
  BigInteger profit = (growth_ * factor_ == BigInteger(0) ?
                       growth_ + BigInteger(1) : growth_ * (1 + factor_)) - growth_;
  return profit;
}

BigInteger ClickBoost::Profit() const {
  return growth_;
}
