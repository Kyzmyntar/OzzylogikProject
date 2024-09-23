#ifndef SQLITESTORAGE_H
#define SQLITESTORAGE_H

#include "datastorage.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class SqlLiteStorage : public DataStorage
{
public:
    SqlLiteStorage(const QString &dbName);
    ~SqlLiteStorage();

    QList<Country> getCountries() const override;
    QList<Operator> getOperators(const unsigned int &mcc) const override;

private:
    QSqlDatabase m_db;
};

#endif
