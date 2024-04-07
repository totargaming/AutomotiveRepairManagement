#ifndef ADDTOSTORAGE_H
#define ADDTOSTORAGE_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>
namespace Ui {
class addToStorage;
}

class addToStorage : public QDialog, public Validation
{
    Q_OBJECT

public:
    explicit addToStorage(QWidget *parent = nullptr);
    bool validateUserInput();
    void reset();
    ~addToStorage();

signals:
    void partAdded();
private slots:

    void on_addBtn_clicked();

private:
    Ui::addToStorage *ui;
    QSqlDatabase database;
};

#endif // ADDTOSTORAGE_H
