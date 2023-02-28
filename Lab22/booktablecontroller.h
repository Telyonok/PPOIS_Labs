#ifndef BOOKTABLECONTROLLER_H
#define BOOKTABLECONTROLLER_H
#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include <QWidget>
#include "book.h"
#include "qtablemodel.h"
#include "FilterType.h"

class BookTableController : public QObject
{
    Q_OBJECT
public:
    QTableModel *model;
    QList<Book> initialList;

    BookTableController();

    void AddBook(Book newBook);
    void DeleteBook(int index);
    void DeleteBooksByFilter(FilterType filterType, QString value1, QString value2 = NULL, QString value3 = NULL);
    void ListBooksByFilter(FilterType filterType, QString value1, QString value2 = NULL, QString value3 = NULL);
    void Save(QString path);
    bool Load(QString path);
    void PreviousPage();
    void NextPage();
    void RemoveFilter();

private:
    void DeleteByAuthor(QString author);

    void DeleteByPublisherAndAuthor(QString publisher, QString author);

    void DeleteByAuthorAndTomeCount(QString author, int from, int to);

    void DeleteByTitle(QString title);

    void DeleteByEdition(int from, int to);

    void DeleteByTomeCount(int from, int to);

    QList<Book> GetListByAuthor(QString author);

    QList<Book> GetListByPublisherAndAuthor(QString publisher, QString author);

    QList<Book> GetListByAuthorAndTomeCount(QString author, int from, int to);

    QList<Book> GetListByTitle(QString title);

    QList<Book> GetListByEdition(int from, int to);

    QList<Book> GetListByTomeCount(int from, int to);
signals:
    void filterApplied(bool applied = true);
    void booksDeleted(QList<Book> deletedBooks);
};

#endif // BOOKTABLECONTROLLER_H
