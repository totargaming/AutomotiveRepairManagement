#include "partupdate.h"
#include "ui_partupdate.h"

PartUpdate::PartUpdate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PartUpdate)
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

PartUpdate::~PartUpdate()
{
    delete ui;
}

bool PartUpdate::validateUserInput() {
    QString selectedItem = ui->removeList->currentText();
    if (selectedItem.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select an item");
        return false;
    }
    return true;
}

void PartUpdate::loadBox() {
    ui->removeList->clear();
    QSqlQuery query(database);
    query.prepare("SELECT name FROM Storage");
    query.exec();
    while(query.next()){
        ui->removeList->addItem(query.value(0).toString());
        qDebug() << "PartUpdate: Filling removeList" << query.value(0).toString();
    }
    qDebug() << "PartUpdate: Last query" << query.lastQuery();
    qDebug() << "PartUpdate: Last error" << query.lastError().text();
}

void PartUpdate::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event); // Call base class implementation
    loadBox(); // Refresh the combo box
}

void PartUpdate::on_deleteBtn_clicked()
{
    if (!validateUserInput()) {
        return;
    }
    QString selectedItem = ui->removeList->currentText();

    QSqlQuery query(database);
    query.prepare("DELETE FROM Storage WHERE name = :name");
    query.bindValue(":name", selectedItem);
    if (query.exec()) {
        qDebug() << "PartUpdate: Item deleted successfully";
        QMessageBox::information(this, "Success", "Item deleted successfully");
    } else {
        qDebug() << "PartUpdate: Failed to delete item" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to delete item: " + query.lastError().text());
    }
    loadBox(); // Refresh the combo box
    emit partUpdated();
}

void PartUpdate::on_updateBtn_clicked()
{
    if (!validateUserInput()) {
        return;
    }
    QString selectedItem = ui->removeList->currentText();

    int newQuantity = ui->quantitySelect->value(); // Assuming quantitySelect is a QComboBox
    QSqlQuery query(database);
    query.prepare("UPDATE Storage SET quantity = :quantity WHERE name = :name");
    query.bindValue(":name", selectedItem);
    query.bindValue(":quantity", newQuantity);
    if (query.exec()) {
        qDebug() << "PartUpdate: Item updated successfully";
        QMessageBox::information(this, "Success", "Item updated successfully");
    } else {
        qDebug() << "PartUpdate: Failed to update item" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to update item: " + query.lastError().text());
    }
    loadBox(); // Refresh the combo box
    emit partUpdated();
}

void PartUpdate::on_removeList_currentTextChanged(const QString &text)
{
    QSqlQuery query(database);
    query.prepare("SELECT quantity FROM Storage WHERE name = :name");
    query.bindValue(":name", text);
    query.exec();
    if (query.next()) {
        int quantity = query.value(0).toInt();
        ui->quantityReport->setText("Last updated quantity: " + QString::number(quantity));
    }
}
