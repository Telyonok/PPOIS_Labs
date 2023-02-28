#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qtablemodel.h"
#include <searchdialog.h>
class SearchDialog;
#include <booktablecontroller.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    BookTableController bookTableController;
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    SearchDialog *searchDialog;
public slots:
    void FilteredMode(bool enabled = true);
    void DeletedNotification(QList<Book> deletedBooks);
private slots:
    void AddBook();
    void DeleteBook();
    void Save();
    void Load();
    void PreviousPage();
    void NextPage();
    void SearchFilter();
    void on_pushButton_9_clicked();
};
#endif // WIDGET_H
