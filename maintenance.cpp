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
    removeFromMaintenance_ptr = new RemoveFromMaintenance();
    connect(addToMaintenance_ptr,&AddToMaintenance::assigned, this, &Maintenance::loadAll);
    connect(removeFromMaintenance_ptr,&RemoveFromMaintenance::maintenanceRemoved, this, &Maintenance::loadAll);
}

Maintenance::~Maintenance()
{
    delete ui;
    delete addToMaintenance_ptr;
    delete removeFromMaintenance_ptr;

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
    removeFromMaintenance_ptr->setWindowTitle("Maintenance: Dismiss");
    removeFromMaintenance_ptr->show();
}


void Maintenance::on_startDateTable_clicked(const QModelIndex &index)
{
    QString model = index.data().toString();
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Maintenance: Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT Vehicle.*, Staff.Name FROM Vehicle LEFT JOIN Staff ON Vehicle.StaffID = Staff.StaffID WHERE Model = :model AND date(StartDate) = date(:selectedDate)");
    query.bindValue(":model", model);
    query.bindValue(":selectedDate", calendar->selectedDate().toString("yyyy-MM-dd"));
    if (!query.exec() || !query.next()) {
        qDebug() << "Maintenance: Failed to execute query" << query.lastError();
        return;
    }

    QString staff = query.value("Name").toString();
    if (staff.isEmpty()) {
        staff = "Not assigned";
    }

    QString dateAssigned = query.value("StartDate").toString();
    if (!dateAssigned.isEmpty()) {
        dateAssigned = QDate::fromString(dateAssigned, "yyyy-MM-dd").toString("dd/MM/yyyy");
    }

    QString deadline = query.value("Deadline").toString();
    if (!deadline.isEmpty()) {
        deadline = QDate::fromString(deadline, "yyyy-MM-dd").toString("dd/MM/yyyy");
    }

    QString assigned = query.value("Assigned").toBool() ? "Yes" : "No";
    QString finished = query.value("Finished").toBool() ? "Yes" : "No";

    QString dateRemaining;
    if (!deadline.isEmpty()) {
        dateRemaining = QString::number(QDate::currentDate().daysTo(QDate::fromString(deadline, "dd/MM/yyyy")));
    }

    ui->txtInfo->setText("Model: " + model + "\nStaff: " + staff + "\nDateAssigned: " + dateAssigned + "\nDeadline: " + deadline + "\nAssigned: " + assigned + "\nFinished: " + finished + "\nDateRemaining: " + dateRemaining);
}

void Maintenance::on_deadlineTable_clicked(const QModelIndex &index)
{
    QString model = index.data().toString();
    QSqlDatabase database = QSqlDatabase::database("DB");
    if (!database.isOpen()) {
        qDebug() << "Maintenance: Database is not open!";
        return;
    }

    QSqlQuery query(database);
    query.prepare("SELECT Vehicle.*, Staff.Name FROM Vehicle LEFT JOIN Staff ON Vehicle.StaffID = Staff.StaffID WHERE Model = :model AND date(Deadline) = date(:selectedDate)");
    query.bindValue(":model", model);
    query.bindValue(":selectedDate", calendar->selectedDate().toString("yyyy-MM-dd"));
    if (!query.exec() || !query.next()) {
        qDebug() << "Maintenance: Failed to execute query" << query.lastError();
        return;
    }

    QString staff = query.value("Name").toString();
    if (staff.isEmpty()) {
        staff = "Not assigned";
    }

    QString dateAssigned = query.value("StartDate").toString();
    if (!dateAssigned.isEmpty()) {
        dateAssigned = QDate::fromString(dateAssigned, "yyyy-MM-dd").toString("dd/MM/yyyy");
    }

    QString deadline = query.value("Deadline").toString();
    if (!deadline.isEmpty()) {
        deadline = QDate::fromString(deadline, "yyyy-MM-dd").toString("dd/MM/yyyy");
    }

    QString assigned = query.value("Assigned").toBool() ? "Yes" : "No";
    QString finished = query.value("Finished").toBool() ? "Yes" : "No";

    QString dateRemaining;
    if (!deadline.isEmpty()) {
        dateRemaining = QString::number(QDate::currentDate().daysTo(QDate::fromString(deadline, "dd/MM/yyyy")));
    }

    ui->txtInfo->setText("Model: " + model + "\nStaff: " + staff + "\nDateAssigned: " + dateAssigned + "\nDeadline: " + deadline + "\nAssigned: " + assigned + "\nFinished: " + finished + "\nDateRemaining: " + dateRemaining);
}

