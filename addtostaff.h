#ifndef ADDTOSTAFF_H
#define ADDTOSTAFF_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>
namespace Ui {
class AddToStaff;
}

class AddToStaff : public QDialog, public Validation
{
    Q_OBJECT

public:
    explicit AddToStaff(QWidget *parent = nullptr);
    bool validateUserInput();
    void reset();
    ~AddToStaff();
signals:
    void staffAdded();
private slots:

    void on_addBtn_clicked();

private:
    Ui::AddToStaff *ui;
    QSqlDatabase database;

};

#endif // ADDTOSTAFF_H
