#include "passiveboostersmodel.h"

PassiveBoostersModel::PassiveBoostersModel(QObject* parent) : QAbstractListModel(parent) {
    for (int i = 0; i < BOOSTERS_COUNT; ++i) {
        boosters.emplace_back(i);
    }
}

std::string PassiveBoostersModel::buy(int index, std::string balance) {
    BigInteger price = boosters[index].getPrice();
    if (BigInteger(balance) >= price) {
        BigInteger profit = boosters[index].UpdateForLevel();
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
        return profit.ToLongString() + " " + price.ToLongString();
    }
    return "0 0";
}

int PassiveBoostersModel::rowCount(const QModelIndex &) const {
    return BOOSTERS_COUNT;
}

QVariant PassiveBoostersModel::data(const QModelIndex &Qindex, int role) const {
    int index = Qindex.row();
    return QVariant::fromValue(boosters[index].TextForButton());
}


