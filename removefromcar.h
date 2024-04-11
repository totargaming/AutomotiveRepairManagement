#ifndef REMOVEFROMCAR_H
#define REMOVEFROMCAR_H

#include <QDialog>
#include "SQLheader.h"
#include "validation.h"
#include <QMessageBox>
namespace Ui {
class RemoveFromCar;
}

class RemoveFromCar : public QDialog, Validation
{
    Q_OBJECT

public:
    explicit RemoveFromCar(QWidget *parent = nullptr);
    bool validateUserInput();
    void loadBox();
    void showEvent(QShowEvent *event);

    ~RemoveFromCar();
signals:
    void carRemoved();

private slots:
    void on_removeList_currentTextChanged(const QString &arg1);

    void on_removeBtn_clicked();

private:
    Ui::RemoveFromCar *ui;
    QSqlDatabase database;
};

#endif // REMOVEFROMCAR_H
