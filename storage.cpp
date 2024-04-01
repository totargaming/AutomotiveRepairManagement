#include "storage.h"
#include "ui_storage.h"

Storage::Storage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Storage)
{

    ui->setupUi(this);
    loadAll();
    addToStorage_ptr = new addToStorage();
    connect(addToStorage_ptr, &addToStorage::partAdded, this, &Storage::loadAll);

}

Storage::~Storage()
{
    delete ui;
}
void Storage::loadAll() {
    QSqlDatabase db = QSqlDatabase::database("DB");
    if (model == nullptr) {
        model = new QSqlQueryModel();
    }
    model->setQuery("SELECT * FROM Storage", db);
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

