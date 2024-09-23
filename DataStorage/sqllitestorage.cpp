#include "sqllitestorage.h"
#include <QException>
#include <stdexcept>
#include <QDebug>

SqlLiteStorage::SqlLiteStorage(const QString &dbName)
{
    try
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(dbName);

        if (!m_db.open())
        {
            throw std::runtime_error("Failed to open database: " + m_db.lastError().text().toStdString());
        }
    }
    catch (const std::exception &e)
    {
        qDebug() << "Exception caught: " << e.what();
    }
}

SqlLiteStorage::~SqlLiteStorage()
{
    try
    {
        m_db.close();
    }
    catch (const std::exception &e)
    {
        qDebug() << "Exception caught while closing the database: " << e.what();
    }
}

QList<Country> SqlLiteStorage::getCountries() const
{
    QList<Country> countries;
    try {
        QSqlQuery query("SELECT mcc, code, name FROM countries");

        if (!query.exec())
        {
            throw std::runtime_error("Failed to execute query: " + query.lastError().text().toStdString());
        }

        while (query.next())
        {
            Country country;
            country.mcc = query.value(0).toInt();
            country.code = query.value(1).toString();
            country.name = query.value(2).toString();
            countries.append(country);
        }
    }
    catch (const std::exception &e)
    {
        qDebug() << "Exception caught while getting countries: " << e.what();
    }

    return countries;
}

QList<Operator> SqlLiteStorage::getOperators(const unsigned int &mcc) const
{
    QList<Operator> operators;
    try
    {
        QSqlQuery query;
        query.prepare("SELECT mcc, mnc, name FROM operators WHERE mcc = :mcc");
        query.bindValue(":mcc", mcc);

        if (!query.exec())
        {
            throw std::runtime_error("Failed to execute query: " + query.lastError().text().toStdString());
        }

        while (query.next())
        {
            Operator op;
            op.mcc = query.value(0).toString();
            op.mnc = query.value(1).toString();
            op.name = query.value(2).toString();
            operators.append(op);
        }
    }
    catch (const std::exception &e)
    {
        qDebug() << "Exception caught while getting operators: " << e.what();
    }

    return operators;
}
