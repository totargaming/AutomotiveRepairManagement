#include "maintenance.h"
#include "ui_maintenance.h"

Maintenance::Maintenance(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Maintenance)
{
    ui->setupUi(this);
    calendar = ui->calendarWidget;
    loadAll();
    addToMaintenance_ptr = new AddToMaintenance();
    connect(addToMaintenance_ptr,&AddToMaintenance::assigned, this, &Maintenance::loadAll);

}

Maintenance::~Maintenance()
{
    delete ui;
    delete addToMaintenance_ptr;

}

void Maintenance::loadAll() {
    qDebug() << "Maintenance: Entering loadAll";
    QString selectedDate = calendar->selectedDate().toString("yyyy-MM-dd");
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Maintenance: Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT Model FROM Vehicle WHERE date(StartDate) = date(:selectedDate)");
    query.bindValue(":selectedDate", selectedDate);
    if (!query.exec()) {
        qDebug() << "Maintenance: Failed to execute query" << query.lastError();
        return;
    }

    QSqlQueryModel* startDateModel = new QSqlQueryModel();
    startDateModel->setQuery(query);
    ui->startDateTable->setModel(startDateModel);

    query.prepare("SELECT Model FROM Vehicle WHERE date(Deadline) = date(:selectedDate)");
    query.bindValue(":selectedDate", selectedDate);
    if (!query.exec()) {
        qDebug() << "Maintenance: Failed to execute query" << query.lastError();
        return;
    }

    QSqlQueryModel* deadlineModel = new QSqlQueryModel();
    deadlineModel->setQuery(query);
    ui->deadlineTable->setModel(deadlineModel);

    qDebug() << "Maintenance: Exiting loadAll";
}

void Maintenance::on_calendarWidget_selectionChanged()
{
    qDebug() <<calendar->selectedDate().toString("yyyy-MM-dd");
    loadAll();
}


void Maintenance::on_addBtn_clicked()
{
    addToMaintenance_ptr->setWindowTitle("Maintenance: Assign");
    addToMaintenance_ptr->show();
}


void Maintenance::on_removeBtn_clicked()
{

}


void Maintenance::on_startDateTable_clicked(const QModelIndex &index)
{

}


void Maintenance::on_deadlineTable_clicked(const QModelIndex &index)
{

}

