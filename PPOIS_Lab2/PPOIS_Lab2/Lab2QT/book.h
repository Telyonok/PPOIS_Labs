#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QString>

class Book
{
public:
    Book(QString name,
    QString authorName,
    QString publisher,
    int tomeCount,
    int edition);

    QString name;
    QString authorName;
    QString publisher;
    int tomeCount;
    int edition;
};

#endif // BOOK_H
