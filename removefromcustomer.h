#ifndef REMOVEFROMCUSTOMER_H
#define REMOVEFROMCUSTOMER_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>
namespace Ui {
class RemoveFromCustomer;
}

class RemoveFromCustomer : public QDialog, Validation
{
    Q_OBJECT

public:
    explicit RemoveFromCustomer(QWidget *parent = nullptr);
    bool validateUserInput();
    void loadBox();
    void showEvent(QShowEvent *event);
    ~RemoveFromCustomer();
signals:
    void customerRemoved();

private slots:
    void on_removeList_currentTextChanged(const QString &arg1);

    void on_removeBtn_clicked();

private:
    Ui::RemoveFromCustomer *ui;
    QSqlDatabase database;

};

#endif // REMOVEFROMCUSTOMER_H
