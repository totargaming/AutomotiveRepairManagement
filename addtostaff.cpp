#include "addtostaff.h"
#include "ui_addtostaff.h"

AddToStaff::AddToStaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddToStaff)
{
    ui->setupUi(this);
    database = QSqlDatabase::database("DB");

}

AddToStaff::~AddToStaff()
{
    delete ui;
}


bool AddToStaff::validateUserInput() {
    QString name = ui->txtName->text();
    QString phone = ui->txtPhone->text();
    QString wageText = ui->txtWage->text();
    if (name.isEmpty() || phone.isEmpty() || wageText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Name, Phone, and Wage Name should not be empty.");
        return false;
    }

    if (!phone.startsWith('0') || phone.length() != 10) {
        QMessageBox::warning(this, "Input Error", "Phone should start with 0 and have a length of 10.");
        return false;
    }
    for (QChar c : phone) {
        if (!c.isDigit()) {
            QMessageBox::warning(this, "Input Error", "Phone should contain only numeric characters.");
            return false;
        }
    }
}
void AddToStaff::reset() {
    ui->txtName->clear();
    ui->txtPhone->clear();
    ui->txtWage->clear();
}

void AddToStaff::on_addBtn_clicked()
{
    reset();
}

