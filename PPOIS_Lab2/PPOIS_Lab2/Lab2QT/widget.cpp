#include "widget.h"
#include "ui_widget.h"
#include "qtablemodel.h"
#include <QPushButton>
#include <QtGui>
#include <QInputDialog>
#include <QAbstractItemModel>
#include <QFileDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    FilteredMode(false);

    bookTableController.model->setHeaderData(0, Qt::Horizontal, tr("Title"));
    bookTableController.model->setHeaderData(1, Qt::Horizontal, tr("Author"));
    bookTableController.model->setHeaderData(2, Qt::Horizontal, tr("Publisher"));
    bookTableController.model->setHeaderData(3, Qt::Horizontal, tr("Tomes"));
    bookTableController.model->setHeaderData(4, Qt::Horizontal, tr("Edition"));
    ui->tableView->setModel(bookTableController.model);
    searchDialog = new SearchDialog(&bookTableController);
    QObject::connect(&bookTableController, &BookTableController::filterApplied, this, &Widget::FilteredMode);
    QObject::connect(&bookTableController, &BookTableController::booksDeleted, this, &Widget::DeletedNotification);

    QObject::connect(ui->pushButton, SIGNAL(clicked()), SLOT(AddBook()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(DeleteBook()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(Save()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(Load()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(PreviousPage()));
    QObject::connect(ui->pushButton_6, SIGNAL(clicked()), SLOT(NextPage()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(SearchFilter()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::FilteredMode(bool enabled)
{
    ui->pushButton->setEnabled(!enabled);
    ui->pushButton_2->setEnabled(!enabled);
    ui->pushButton_3->setEnabled(!enabled);
    ui->pushButton_4->setEnabled(!enabled);
    if (enabled)
    {
        ui->pushButton_9->show();
    }
    else
    {
        ui->pushButton_9->hide();
    }
}

void Widget::DeletedNotification(QList<Book> deletedBooks)
{
    QString notificationText;
    if (deletedBooks.isEmpty())
    {
        notificationText = "No books were deleted.";
    }
    else
    {
        notificationText.append("Deleted ");
        notificationText.append(deletedBooks.count());
        notificationText.append("books:\n");
        for (int i = 0; i < 10 && i < deletedBooks.count(); i++)
        {
            Book book = deletedBooks[i];
            notificationText.append(QString::number(i + 1));
            notificationText.append(":\t");
            notificationText.append(book.name);
            notificationText.append("\n");
        }

        if (deletedBooks.count() > 10)
        {
            notificationText.append("\n");
            notificationText.append("And ");
            notificationText.append(QString::number(deletedBooks.count() - 10));
            notificationText.append(" more\n");
        }
    }

    QMessageBox::about(this, "Deletion", notificationText);
}

void Widget::AddBook()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                         QString::fromUtf8("Введите название книги"),
                                         QString::fromUtf8("Название книги:"),
                                         QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);

    QString authorName = QInputDialog::getText(this,
                                         QString::fromUtf8("Введите имя автора"),
                                         QString::fromUtf8("Имя автора:"),
                                         QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);

    QString publisherName = QInputDialog::getText(this,
                                         QString::fromUtf8("Введите название редакции"),
                                         QString::fromUtf8("Название редакции:"),
                                         QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);

    int tomeCount = QInputDialog::getInt(this, QString::fromUtf8("Введите количество томов"),
                                     QString::fromUtf8("Количество томов:"), 1, 1, 100, 1, &ok);

    int edition = QInputDialog::getInt(this, QString::fromUtf8("Введите тираж"),
                                       QString::fromUtf8("Тираж:"), 1, 1, 100, 1, &ok);
    bookTableController.AddBook(*new Book(name, authorName, publisherName, tomeCount, edition));
}

void Widget::DeleteBook()
{
    int index = ui->tableView->currentIndex().row();
    bookTableController.DeleteBook(index);
}

void Widget::Save()
{
    QString path = QFileDialog::getSaveFileName(
                this,
                "Save File",
                "Books",
                "*.xml"
                );
    bookTableController.Save(path);
}

void Widget::Load()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C:\\PPOIS\\PPOIS-4sem\\Lab22\\BookLists",
                "XML File (*.xml)"
                );
    if (!bookTableController.Load(path))
    {
        QMessageBox::warning(this,
                             "Ошибка файла",
                             "Не удалось открыть файл",
                             QMessageBox::Ok);
    }
}

void Widget::PreviousPage()
{
    bookTableController.PreviousPage();
}

void Widget::NextPage()
{
    bookTableController.NextPage();
}

void Widget::SearchFilter()
{
    searchDialog->setModal(true);
    searchDialog->show();
}

void Widget::on_pushButton_9_clicked()
{
    bookTableController.RemoveFilter();
    FilteredMode(false);
}
