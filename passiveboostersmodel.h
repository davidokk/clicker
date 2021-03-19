#ifndef PASSIVEBOOSTERSMODEL_H
#define PASSIVEBOOSTERSMODEL_H

#include "boost.h"
#include "big_integer.h"

#include <QAbstractListModel>

class PassiveBoostersModel : public QAbstractListModel {
    Q_OBJECT

    static constexpr int BOOSTERS_COUNT = 10;
public:
    PassiveBoostersModel(QObject* parent = nullptr);

    Q_INVOKABLE std::string buy(int index, std::string balance);

    int rowCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex& Qindex, int role) const override;

private:
    std::vector<PassiveBoost> boosters;
};

#endif // PASSIVEBOOSTERSMODEL_H
