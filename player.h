#ifndef PLAYER_H
#define PLAYER_H

#include "big_integer.h"

#include <future>
#include <QObject>

class Player : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString balance READ balance NOTIFY balanceChanged)
    Q_PROPERTY(std::string long_balance READ long_balance)
    Q_PROPERTY(QString per_click READ per_click NOTIFY perClickChanged)
    Q_PROPERTY(QString per_second READ per_second NOTIFY perSecondChanged)
    Q_PROPERTY(int tap_factor READ tap_factor NOTIFY tapFactorChanged)
public:
    Player(QObject* parent = nullptr);

    Q_INVOKABLE void click();
    Q_INVOKABLE void buy(std::string info);

    std::string long_balance() const;
    QString balance() const;
    QString per_click() const;
    QString per_second() const;
    int tap_factor() const;

signals:
    void balanceChanged();
    void perClickChanged();
    void perSecondChanged();
    void tapFactorChanged();

private:
    BigInteger balance_;
    BigInteger per_click_;
    BigInteger per_second_;
    int tap_factor_, clicks_per_prev_second_, seconds_in_row_;

    std::future<void> give_for_second;

    void FullUpdate();
    void AddToBalance(BigInteger count);
    void CalculateTapFactor();
};

#endif // PLAYER_H
