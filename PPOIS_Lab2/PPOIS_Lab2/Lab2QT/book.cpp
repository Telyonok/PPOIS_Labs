#include "book.h"

Book::Book(QString name,
QString authorName,
QString publisher,
int tomeCount,
int edition)
{
    this->name = name;
    this->authorName = authorName;
    this->publisher = publisher;
    this->tomeCount = tomeCount;
    this-> edition = edition;
}
