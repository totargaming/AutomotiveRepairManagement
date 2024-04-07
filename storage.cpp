#include "storage.h"
#include "ui_storage.h"

Storage::Storage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Storage)
{

    ui->setupUi(this);
    loadAll();
    addToStorage_ptr = new addToStorage();
    partUpdate_ptr = new PartUpdate(); // Initialize partUpdate_ptr
    connect(addToStorage_ptr, &addToStorage::partAdded, this, &Storage::loadAll);
    connect(partUpdate_ptr, &PartUpdate::partUpdated, this, &Storage::loadAll);


}

Storage::~Storage()
{
    delete ui;
    delete addToStorage_ptr;
    delete partUpdate_ptr;
}
void Storage::loadAll() {
    QSqlDatabase db = QSqlDatabase::database("DB");
    if (!db.isOpen()) {
        qDebug() << "Database not open!";
        return;
    }

    if (model == nullptr) {
        model = new QSqlQueryModel();
    }

    model->setQuery("SELECT * FROM Storage", db);
    if (model->lastError().isValid()) {
        qDebug() << "Failed to execute query: " << model->lastError();
        return;
    }

    if (ui == nullptr || ui->tableView == nullptr) {
        qDebug() << "UI or tableView is null!";
        return;
    }

    ui->tableView->setModel(model);
}
void Storage::on_searchBtn_clicked()
{
    QString partName = ui->input->text();
    qDebug() << "Part: " << partName;
    QSqlDatabase db = QSqlDatabase::database("DB");

    if(model == NULL)
        model = new QSqlQueryModel();

    if(partName.isEmpty()) {
        loadAll();
    }
    else {
        model->setQuery("select * from Storage where name like '%" + partName + "%'", db);
        ui->tableView->setModel(model);
    }
}


void Storage::on_refreshBtn_clicked()
{
    loadAll();
}


void Storage::on_addBtn_clicked()
{
    addToStorage_ptr->setWindowTitle("Storage: Add Parts");
    addToStorage_ptr->show();
}


void Storage::on_updateBtn_clicked()
{
    partUpdate_ptr->setWindowTitle("Storage: Update");
    partUpdate_ptr->show();
}

