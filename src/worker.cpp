#include "headers/worker.h"
#include <thread>

Worker::Worker()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("database\\tray.sqlite");
    if(!db.open()) {
        QMessageBox::information(0,"Error","Either DB path is incorrect or DB failed to load.");
        throw (new QString("Throwing Exception !"));
    }
    //fork threads

    // Get instance of singleton class
    bdInstance = BaseData::getInstance();
   //Fork thread for continual connection

}

void Worker::extractAndUpdate()
{
    QString temp("");
    bool status = false;
    int rand = 0;
    QVector<QString> wordList; // = new QVector<QString>();


    /********** Query to select all words from database with min count************/
    QSqlQuery query(db);
    status = query.prepare("SELECT word FROM VocabRecords where access_count = (select min(access_count) from vocabRecords)");
    if(status == false || !query.exec() )
    {
        qDebug() << "Database error : " << query.lastError();
        QMessageBox::information(0,"Error","Data Insertion failed");
    }

    while( query.next() )
    {
        temp = query.value(0).toString();
        wordList.push_back(temp);

    }
    rand = qrand() % (wordList.size());  //generate should  be between 0 and size-1

    /********** Query to fetch word from database ************/
    QString extractedWord = wordList.at(rand);
    QSqlQuery queryFetchWord(db);
    status = queryFetchWord.prepare("SELECT word, meaning,example FROM VocabRecords where word = :extractedWord");
    queryFetchWord.bindValue(":extractedWord", extractedWord);

     if(status == false || !queryFetchWord.exec() )
     {
         qDebug() << "Database error : " << queryFetchWord.lastError();
         QMessageBox::information(0,"Error","Data Insertion failed");
     }
     else {
         while (queryFetchWord.next()) {
             //bdInstance->mutex.lock();
             bdInstance->setWord(queryFetchWord.value(0).toString());
             bdInstance->setMeaning(queryFetchWord.value(1).toString());
             bdInstance->setExample(queryFetchWord.value(2).toString());
             //bdInstance->mutex.unlock();

         }
     }

     /********** Query to update last access time ************/
     QSqlQuery updateAccessTimeQuery(db);
     int last_access = QDateTime::currentMSecsSinceEpoch()/1000;
     status = updateAccessTimeQuery.prepare("update VocabRecords set last_access=:last_access where word=:word");
     updateAccessTimeQuery.bindValue(":last_access", last_access);
     updateAccessTimeQuery.bindValue(":word", extractedWord);

     if(status == false || !updateAccessTimeQuery.exec())
     {
         qDebug() << "Database error : " << updateAccessTimeQuery.lastError();
         QMessageBox::information(0,"Error","Data Updation failed - Last Access time");
     }

     /********** Query to update access count ************/
     QSqlQuery updateCountQuery(db);

     // increment the access_count of the word
     status = updateCountQuery.prepare("update VocabRecords set access_count=access_count + 1 where word=:word");
     updateCountQuery.bindValue(":word", extractedWord);
     if(status == false || !updateCountQuery.exec())
     {
         qDebug() << "Database error : " << updateCountQuery.lastError();
         QMessageBox::information(0,"Error","Data Updation failed - Access count");
     }


}

