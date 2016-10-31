#ifndef BASEDATA_H
#define BASEDATA_H

#include <QMutex>
#include <QString>

class BaseData
{
private:
        BaseData() {} //private constructor
public:

    static BaseData* _instance;


    QString word;
    QString meaning;
    QString example;

    static BaseData* getInstance();

    QString getWord() const;
    void setWord(const QString &value);
    QString getMeaning() const;
    void setMeaning(const QString &value);
    QString getExample() const;
    void setExample(const QString &value);
};


#endif // BASEDATA_H
