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
    return true;
}
void AddToStaff::reset() {
    ui->txtName->clear();
    ui->txtPhone->clear();
    ui->txtWage->clear();
}

void AddToStaff::on_addBtn_clicked()
{
    if (!validateUserInput()) {
        return;
    }
    QString name = ui->txtName->text();
    QString phone = ui->txtPhone->text();
    int wage = ui->txtWage->text().toInt();
    QSqlQuery query(database);
    query.prepare("INSERT INTO Staff (Name, Assigned, MaintenanceID, Phone, Wage) VALUES (:Name, 0,NULL, :Phone, :Wage)");
    query.bindValue(":Name", name);
    query.bindValue(":Phone", phone);
    query.bindValue(":Wage", wage);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }
    emit staffAdded();
    QMessageBox::information(this, "Success", "Staff information added successfully.");

    reset();
}

