#include "storage.h"
#include "ui_storage.h"

Storage::Storage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Storage)
{
    qDebug() << "Entering Storage constructor";
    ui->setupUi(this);
    loadAll();
    addToStorage_ptr = new addToStorage();
    partUpdate_ptr = new PartUpdate(); // Initialize partUpdate_ptr
    connect(addToStorage_ptr, &addToStorage::partAdded, this, &Storage::loadAll);
    connect(partUpdate_ptr, &PartUpdate::partUpdated, this, &Storage::loadAll);
    qDebug() << "Exiting Storage constructor";
}

Storage::~Storage()
{
    qDebug() << "Entering Storage destructor";
    delete ui;
    delete addToStorage_ptr;
    delete partUpdate_ptr;
    qDebug() << "Exiting Storage destructor";
}

void Storage::loadAll() {
    qDebug() << "Storage: Entering loadAll";
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Storage: Database is not open!";
        return;
    model = new QSqlQueryModel();
    model->setQuery("SELECT Name, Quantity FROM Storage", database);

    ui->tableView->setModel(model);
    qDebug() << "Storage: Exiting loadAll";
}
}

void Storage::on_searchBtn_clicked()
{
    qDebug() << "Storage: Entering on_searchBtn_clicked";
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
    qDebug() << "Storage: Exiting on_searchBtn_clicked";
}

void Storage::on_refreshBtn_clicked()
{
    qDebug() << "Storage: Entering on_refreshBtn_clicked";
    loadAll();
    qDebug() << "Storage: Exiting on_refreshBtn_clicked";
}

void Storage::on_addBtn_clicked()
{
    qDebug() << "Storage: Entering on_addBtn_clicked";
    addToStorage_ptr->setWindowTitle("Storage: Add Parts");
    addToStorage_ptr->show();
    qDebug() << "Storage: Exiting on_addBtn_clicked";
}

void Storage::on_updateBtn_clicked()
{
    qDebug() << "Storage: Entering on_updateBtn_clicked";
    partUpdate_ptr->setWindowTitle("Storage: Update");
    partUpdate_ptr->show();
    qDebug() << "Storage: Exiting on_updateBtn_clicked";
}
