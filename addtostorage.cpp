#include "addtostorage.h"
#include "ui_addtostorage.h"

addToStorage::addToStorage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addToStorage)
{
    ui->setupUi(this);
    database = QSqlDatabase::database("DB");

}

addToStorage::~addToStorage()
{
    qDebug() << "~addToStorage()";

    delete ui;
}




void addToStorage::on_addBtn_clicked()
{
    if (validateUserInput() == true) {
        QString partName = ui->input->text();
        int quantity = ui->quantitySelect->value();
        // Log all the value to terminal to check
        qDebug() << "partName: " << partName
                 << "Quantity" << quantity;

        // Insert the value to database
        QSqlQuery query(database);
        query.prepare("insert into Storage (name, quantity) values(:name, :quantity)");
        query.bindValue(":name", partName);
        query.bindValue(":quantity", quantity);
        query.exec();
        query.finish();
        query.clear();
        emit partAdded(); // emit the signal

        qDebug() << "No error: " << query.lastError().text();
        QMessageBox::information(this, "Success", "Added succesfully!");
        reset();
    }
}
void addToStorage::reset() {
    ui->input->clear();
    ui->quantitySelect->clear();
}
bool addToStorage::validateUserInput() {
    QString partName = ui->input->text();
    if(partName.isEmpty()) {
        QMessageBox::critical(this, "Validation Error!", "Part's name is left blank!");
        return false;
    }
    QSqlQuery query(database);
    query.prepare("SELECT name FROM Storage");
    query.exec();
    while (query.next()) {
        QString existedName = query.value(0).toString();
        if (partName == existedName) {
            QMessageBox::critical(this,"Validation Error!", "Name already exist!");
            query.finish();
            query.clear();
            qDebug() << "Existed Error: " << query.lastError().text();
            return false;
        }
    }
    query.finish();
    query.clear();
    qDebug() << "No Error: " << query.lastError().text();
    return true;
}

