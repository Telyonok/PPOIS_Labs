#include "booktablecontroller.h"
#include "qtablemodel.h"
#include <QXmlStreamWriter>
#include <QFile>

BookTableController::BookTableController()
{
    model = new QTableModel();
}


void BookTableController::AddBook(Book newBook)
{
    model->books.append(newBook);
    emit model->layoutChanged();
}

void BookTableController::DeleteBook(int index)
{
    model->books.removeAt(index);
    emit model->layoutChanged();
}

void BookTableController::DeleteBooksByFilter(FilterType filterType, QString value1, QString value2, QString value3)
{
    QList<Book> deletedBooks;
    switch (filterType)
    {
    case author:
        deletedBooks = GetListByAuthor(value1);
        DeleteByAuthor(value1);
        break;
    case publisherAndAuthor:
        deletedBooks = GetListByPublisherAndAuthor(value1, value2);
        DeleteByPublisherAndAuthor(value1, value2);
        break;
    case authorAndTomeCount:
        deletedBooks = GetListByAuthorAndTomeCount(value1, value2.toInt(), value3.toInt());
        DeleteByAuthorAndTomeCount(value1, value2.toInt(), value3.toInt());
        break;
    case name:
        deletedBooks = GetListByTitle(value1);
        DeleteByTitle(value1);
        break;
    case edition:
        deletedBooks = GetListByEdition(value1.toInt(), value2.toInt());
        DeleteByEdition(value1.toInt(), value2.toInt());
        break;
    case tomeCount:
        deletedBooks = GetListByTomeCount(value1.toInt(), value2.toInt());
        DeleteByTomeCount(value1.toInt(), value2.toInt());
        break;
    }

    emit booksDeleted(deletedBooks);
    emit model->layoutChanged();
}

void BookTableController::ListBooksByFilter(FilterType filterType, QString value1, QString value2, QString value3)
{
    QList<Book> filteredBooks;
    switch (filterType)
    {
    case author:
        filteredBooks = GetListByAuthor(value1);
        break;
    case publisherAndAuthor:
        filteredBooks = GetListByPublisherAndAuthor(value1, value2);
        break;
    case authorAndTomeCount:
        filteredBooks = GetListByAuthorAndTomeCount(value1, value2.toInt(), value3.toInt());
        break;
    case name:
        filteredBooks = GetListByTitle(value1);
        break;
    case edition:
        filteredBooks = GetListByEdition(value1.toInt(), value2.toInt());
        break;
    case tomeCount:
        filteredBooks = GetListByTomeCount(value1.toInt(), value2.toInt());
        break;
    }

    //QTableModel *newModel = new QTableModel();
   // newModel->books = filteredBooks;
    if (initialList.count() == 0)
    {
        initialList = model->books;
    }

    model->books = filteredBooks;
    emit filterApplied();
    emit model->layoutChanged();
}

void BookTableController::Save(QString path)
{
   // path.append();
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("books");
    foreach (Book book, model->books)
    {
        xmlWriter.writeStartElement("book");
        xmlWriter.writeAttribute("name", book.name);;
         xmlWriter.writeAttribute("author", book.authorName);
          xmlWriter.writeAttribute("publisher", book.publisher);
           xmlWriter.writeAttribute("tomeCount", QString::number(book.tomeCount));
            xmlWriter.writeAttribute("edition", QString::number(book.edition));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
}

bool BookTableController::Load(QString path)
{
    QFile file(path);
       if (!file.open(QFile::ReadOnly | QFile::Text))
       {
           return false;
       }
       else
       {
           QList<Book> newBooks;
           QXmlStreamReader xmlReader;
           xmlReader.setDevice(&file);
           xmlReader.readNext();
           xmlReader.readNext();
           xmlReader.readNext();
           while (!xmlReader.atEnd())
           {
               if (xmlReader.isStartElement())
               {
                        QString name = xmlReader.attributes()[0].value().toString();
                        QString author = xmlReader.attributes()[1].value().toString();
                        QString publisher = xmlReader.attributes()[2].value().toString();
                        int tomeCount = xmlReader.attributes()[3].value().toInt();
                        int edition = xmlReader.attributes()[4].value().toInt();
                        newBooks.append(*new Book(name, author, publisher, tomeCount, edition));
               }
               xmlReader.readNext();
           }
           file.close();
           model->books = newBooks;
           emit model->layoutChanged();
       }

       return true;
}

void BookTableController::PreviousPage()
{
    if (model->currentPage > 0)
    {
        model->currentPage--;
        emit model->layoutChanged();
    }
}

void BookTableController::NextPage()
{
    if (model->currentPage * 10 + 10 < model->books.count())
    {
        model->currentPage++;
        emit model->layoutChanged();
    }
}

void BookTableController::RemoveFilter()
{
    model->books = initialList;
    initialList.clear();
    emit model->layoutChanged();
}

void BookTableController::DeleteByAuthor(QString author)
{
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].authorName == author)
        {
            model->books.removeAt(i);
            i--;
        }
    }
}

void BookTableController::DeleteByPublisherAndAuthor(QString publisher, QString author)
{
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].authorName == author && model->books[i].publisher == publisher)
        {
            model->books.removeAt(i);
            i--;
        }
    }
}

void BookTableController::DeleteByAuthorAndTomeCount(QString author, int from, int to)
{
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].authorName == author && model->books[i].tomeCount <= to && model->books[i].tomeCount >= from)
        {
            model->books.removeAt(i);
            i--;
        }
    }
}

void BookTableController::DeleteByTitle(QString title)
{
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].name == title)
        {
            model->books.removeAt(i);
            i--;
        }
    }
}

void BookTableController::DeleteByEdition(int from, int to)
{
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].edition <= to && model->books[i].edition >= from)
        {
            model->books.removeAt(i);
            i--;
        }
    }
}

void BookTableController::DeleteByTomeCount(int from, int to)
{
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].tomeCount <= to && model->books[i].tomeCount >= from)
        {
            model->books.removeAt(i);
            i--;
        }
    }
}

QList<Book> BookTableController::GetListByAuthor(QString author)
{
    QList<Book> newList;
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].authorName == author)
        {
            newList.append(model->books[i]);
        }
    }

    return newList;
}

QList<Book> BookTableController::GetListByPublisherAndAuthor(QString publisher, QString author)
{
    QList<Book> newList;
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].authorName == author && model->books[i].publisher == publisher)
        {
            newList.append(model->books[i]);
        }
    }

    return newList;
}

QList<Book> BookTableController::GetListByAuthorAndTomeCount(QString author, int from, int to)
{
    QList<Book> newList;
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].authorName == author && model->books[i].tomeCount <= to && model->books[i].tomeCount >= from)
        {
            newList.append(model->books[i]);
        }
    }

    return newList;
}

QList<Book> BookTableController::GetListByTitle(QString title)
{
    QList<Book> newList;
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].name == title)
        {
            newList.append(model->books[i]);
        }
    }

    return newList;
}

QList<Book> BookTableController::GetListByEdition(int from, int to)
{
    QList<Book> newList;
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].edition <= to && model->books[i].edition >= from)
        {
            newList.append(model->books[i]);
        }
    }

    return newList;
}

QList<Book> BookTableController::GetListByTomeCount(int from, int to)
{
    QList<Book> newList;
    for (int i = 0; i < model->books.count(); i++)
    {
        if (model->books[i].tomeCount <= to && model->books[i].tomeCount >= from)
        {
            newList.append(model->books[i]);
        }
    }

    return newList;
}
