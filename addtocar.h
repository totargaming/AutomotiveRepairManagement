#ifndef ADDTOCAR_H
#define ADDTOCAR_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>
namespace Ui {
class AddToCar;
}

class AddToCar : public QDialog, public Validation
{
    Q_OBJECT

public:
    explicit AddToCar(QWidget *parent = nullptr);
    bool validateUserInput();
    void reset();
    ~AddToCar();

signals:
    void carAdded();
private slots:

    void on_addBtn_clicked();

private:
    Ui::AddToCar *ui;
    QSqlDatabase database;
};

#endif // ADDTOCAR_H
