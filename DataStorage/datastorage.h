#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QString>
#include <QList>

struct Country
{
    unsigned int mcc;
    QString code;
    QString name;
};

struct Operator
{
    QString mcc;
    QString mnc;
    QString name;
};

class DataStorage
{
public:
    virtual ~DataStorage() {}
    virtual QList<Country> getCountries() const = 0;
    virtual QList<Operator> getOperators(const unsigned int &mcc) const = 0;
};

#endif
