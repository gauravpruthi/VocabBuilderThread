#include "headers/basedata.h"

BaseData* BaseData::_instance = NULL;

BaseData* BaseData::getInstance()
{
    if(_instance == NULL)
        _instance = new BaseData(); //Not thread-safe version
    return _instance;
}


QString BaseData::getWord() const
{
    return word;
}

void BaseData::setWord(const QString &value)
{
    word = value;
}

QString BaseData::getMeaning() const
{
    return meaning;
}

void BaseData::setMeaning(const QString &value)
{
    meaning = value;
}

QString BaseData::getExample() const
{
    return example;
}

void BaseData::setExample(const QString &value)
{
    example = value;
}
