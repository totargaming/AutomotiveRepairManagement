#include "addtomaintenance.h"
#include "ui_addtomaintenance.h"

AddToMaintenance::AddToMaintenance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddToMaintenance)
{
    ui->setupUi(this);
    database = QSqlDatabase::database("DB");
    if (!database.isValid() || !database.isOpen()) {
        qDebug() << "RemoveFromCar: Failed to initialize database";
        return;
    }
    qDebug() << "RemoveFromCar: Successfully initialized database";
    loadBox();
}

AddToMaintenance::~AddToMaintenance()
{
    delete ui;
}


bool AddToMaintenance::validateUserInput() {
    qDebug() << "AddToMaintenance: Validating user input";
    if(ui->modelBox->currentText().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Model box is empty");
        qDebug() << "AddToMaintenance: Model box is empty";
        return false;
    }

    QDate startDate = ui->startDateEdit->date();
    QDate deadlineDate = ui->deadlineDateEdit->date();

    if(startDate < QDate::currentDate()) {
        QMessageBox::warning(this, "Validation Error", "Start date cannot be in the past");
        qDebug() << "AddToMaintenance: Start date cannot be in the past";
        return false;
    }

    if(deadlineDate <= startDate) {
        QMessageBox::warning(this, "Validation Error", "Deadline date should be after start date");
        qDebug() << "AddToMaintenance: Deadline date should be after start date";
        return false;
    }

    qDebug() << "AddToMaintenance: User input validated successfully";
    return true;
}

void AddToMaintenance::loadBox() {
    ui->modelBox->clear();
    qDebug() << "AddToMaintenance: Loading box";
    QSqlQuery query(database);
    query.prepare("SELECT Model FROM Vehicle WHERE Scheduled = 0");

    if(query.exec()) {
        while(query.next()) {
            ui->modelBox->addItem(query.value(0).toString());
            qDebug() << "AddToMaintenance: Filling modelBox" << query.value(0).toString();
        }
    } else {
        QMessageBox::warning(this, "Database Error", "Failed to load models");
        qDebug() << "AddToMaintenance: Failed to load models";
    }

    ui->startDateEdit->setDate(QDate::currentDate());
    ui->deadlineDateEdit->setDate(QDate::currentDate());

    qDebug() << "AddToMaintenance: Set start date to current date";
}

void AddToMaintenance::on_addBtn_clicked() {
    qDebug() << "AddToMaintenance: Add button clicked";
    if(!validateUserInput()) {
        return;
    }

    QSqlQuery query(database);
    query.prepare("UPDATE Vehicle SET Scheduled = 1, StartDate = :startDate, Deadline = :deadline WHERE Model = :model");
    query.bindValue(":startDate", ui->startDateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":deadline", ui->deadlineDateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":model", ui->modelBox->currentText());

    if(!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Failed to update vehicle");
        qDebug() << "AddToMaintenance: Failed to update vehicle";
        return;
    }
        QMessageBox::information(this, "Success", "Maintenance information added successfully.");
    loadBox(); // Refresh the combo box
    emit assigned();
}
void AddToMaintenance::showEvent(QShowEvent *event) {
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
}

