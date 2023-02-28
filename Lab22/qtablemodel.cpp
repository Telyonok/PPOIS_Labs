#include "qtablemodel.h"
#include <QXmlStreamWriter>
#include <QFile>

QTableModel::QTableModel(QObject *parent)
{
    currentPage = 0;
}

int QTableModel::rowCount(const QModelIndex &parent) const
{
    return 10;
}

int QTableModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant QTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    int realIndex = index.row() + currentPage * 10;

        if (role == Qt::DisplayRole)
        {
            if (realIndex < books.count())
            {
                Book book = books[realIndex];
                switch (index.column())
                {
                case 0:
                return QVariant(book.name);
                break;
                case 1:
                return QVariant(book.authorName);
                break;
                case 2:
                return QVariant(book.publisher);
                break;
                case 3:
                return QVariant(book.tomeCount);
                break;
                case 4:
                return QVariant(book.edition);
                break;
                }
            }
        }

    return QVariant();
}
