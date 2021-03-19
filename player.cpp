#include "player.h"

#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>

Player::Player(QObject* parent) :
        QObject(parent), balance_(0),
        per_click_(100), per_second_(0), tap_factor_(1),
        clicks_per_prev_second_(0), seconds_in_row_(0) {
    give_for_second = std::async([=](){
       while (true) {
           AddToBalance(per_second_);
           CalculateTapFactor();
//           FullUpdate();
           std::this_thread::sleep_for(std::chrono::seconds(1));
       }
    });
}

void Player::AddToBalance(BigInteger count) {
    balance_ += count;
    emit balanceChanged();
}

void Player::click() {
    AddToBalance(per_click_ * tap_factor_);
    clicks_per_prev_second_++;
}

QString Player::balance() const {
    return QString::fromStdString(balance_.ToShortString());
}

QString Player::per_click() const {
    return QString::fromStdString(per_click_.ToShortString());
}

QString Player::per_second() const {
    return QString::fromStdString(per_second_.ToShortString());
}

int Player::tap_factor() const {
    return tap_factor_;
}

std::string Player::long_balance() const {
    return balance_.ToLongString();
}

void Player::CalculateTapFactor() {
    if (clicks_per_prev_second_)
        seconds_in_row_++;
    else
        seconds_in_row_ = 0;

    if (seconds_in_row_ < 5)
        tap_factor_ = 1;
    else if (seconds_in_row_ < 20)
        tap_factor_ = 2;
    else if (seconds_in_row_ < 40)
        tap_factor_ = 3;
    else if (seconds_in_row_ < 60)
        tap_factor_ = 4;
    else if (seconds_in_row_ < 300)
        tap_factor_ = 5;
    else tap_factor_ = 100;

    clicks_per_prev_second_ = 0;
    emit tapFactorChanged();
}

void Player::FullUpdate() {
    emit balanceChanged();
    emit perClickChanged();
    emit perSecondChanged();
}

void Player::buy(std::string info) {
    //std::cout << info << std::endl;
    std::istringstream is(info);
    std::string price, bonus;
    is >> bonus >> price;
    balance_ -= BigInteger(price);
    per_second_ += BigInteger(bonus);
    perSecondChanged();
    balanceChanged();
}
