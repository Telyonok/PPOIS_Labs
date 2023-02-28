#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <booktablecontroller.h>
#include "widget.h"

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(BookTableController *bookTableController, QWidget *parent = NULL);
    ~SearchDialog();
    BookTableController *bookTableController;
    FilterType filterType;

    QHBoxLayout *hLayout1;
    QHBoxLayout *hLayout2;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit3;
private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void ClearLayout(QLayout *layout);
    Ui::SearchDialog *ui;
};

#endif // SEARCHDIALOG_H
