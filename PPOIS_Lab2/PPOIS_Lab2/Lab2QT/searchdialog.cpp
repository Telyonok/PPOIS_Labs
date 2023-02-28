#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QDialog>

SearchDialog::SearchDialog(BookTableController *bookTableController, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    this->bookTableController = bookTableController;

    ui->setupUi(this);
    on_comboBox_currentIndexChanged(0);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_comboBox_currentIndexChanged(int index)
{
    ClearLayout(ui->verticalLayout);

    hLayout1 = new QHBoxLayout();
    hLayout2 = new QHBoxLayout();
    label1 = new QLabel();
    label2 = new QLabel();
    label3 = new QLabel();
    lineEdit1 = new QLineEdit();
    lineEdit2 = new QLineEdit();
    lineEdit3 = new QLineEdit();
    switch (index)
    {
    case 0:
        filterType = author;

        label1->setText("Author");
        hLayout1->addWidget(label1);
        hLayout1->addWidget(lineEdit1);
        ui->verticalLayout->addLayout(hLayout1);

        break;
    case 1:
        filterType = publisherAndAuthor;

        label1->setText("Publisher");
        hLayout1->addWidget(label1);
        hLayout1->addWidget(lineEdit1);
        ui->verticalLayout->addLayout(hLayout1);

        label2->setText("Author");
        hLayout2->addWidget(label2);
        hLayout2->addWidget(lineEdit2);
        ui->verticalLayout->addLayout(hLayout2);

        break;
    case 2:
        filterType = authorAndTomeCount;

        label1->setText("Author");
        hLayout1->addWidget(label1);
        hLayout1->addWidget(lineEdit1);
        ui->verticalLayout->addLayout(hLayout1);

        label2->setText("Tomes: From:");
        hLayout2->addWidget(label2);
        hLayout2->addWidget(lineEdit2);
        label3->setText("To:");
        hLayout2->addWidget(label3);
        hLayout2->addWidget(lineEdit3);
        ui->verticalLayout->addLayout(hLayout2);

        break;
    case 3:
        filterType = name;

        label1->setText("Title");
        hLayout1->addWidget(label1);
        hLayout1->addWidget(lineEdit1);
        ui->verticalLayout->addLayout(hLayout1);

        break;
    case 4:
        filterType = edition;

        label1->setText("Edition From:");
        hLayout1->addWidget(label1);
        hLayout1->addWidget(lineEdit1);
        label2->setText("To:");
        hLayout1->addWidget(label2);
        hLayout1->addWidget(lineEdit2);
        ui->verticalLayout->addLayout(hLayout1);

        break;
    case 5:
        filterType = tomeCount;

        label1->setText("Tomes From:");
        hLayout1->addWidget(label1);
        hLayout1->addWidget(lineEdit1);
        label2->setText("To:");
        hLayout1->addWidget(label2);
        hLayout1->addWidget(lineEdit2);
        ui->verticalLayout->addLayout(hLayout1);

        break;
    }
}

void SearchDialog::on_pushButton_clicked()
{
    bookTableController->DeleteBooksByFilter(filterType, lineEdit1->text(), lineEdit2->text(), lineEdit3->text());
    close();
}

void SearchDialog::ClearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            ClearLayout(item->layout());
            delete item->layout();
        }
        else if (item->widget()) {
           delete item->widget();
        }
        else
        {
            delete item;
        }
    }
}

void SearchDialog::on_pushButton_2_clicked()
{
    bookTableController->ListBooksByFilter(filterType, lineEdit1->text(), lineEdit2->text(), lineEdit3->text());
    close();
}
