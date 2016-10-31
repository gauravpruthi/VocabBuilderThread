#ifndef WORKER_H
#define WORKER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>

#include "headers/basedata.h"

class Worker
{
private:
    QSqlDatabase db;
    BaseData *bdInstance;

public:
    Worker();
    void mainThread();
    void extractAndUpdate();
};

#endif // WORKER_H
