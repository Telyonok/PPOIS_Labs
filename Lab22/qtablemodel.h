#ifndef QTABLEMODEL_H
#define QTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include "book.h"

class QTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    QList<Book> books;
    int currentPage;
    explicit QTableModel(QObject *parent = 0);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // QTABLEMODEL_H
