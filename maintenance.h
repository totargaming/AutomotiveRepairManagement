#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QWidget>
#include "SQLheader.h"
#include <QCalendarWidget>
namespace Ui {
class Maintenance;
}

class Maintenance : public QWidget
{
    Q_OBJECT

public:
    explicit Maintenance(QWidget *parent = nullptr);
    void loadAll();
    ~Maintenance();

private slots:
    void on_calendarWidget_selectionChanged();

    void on_addBtn_clicked();

    void on_removeBtn_clicked();

    void on_startDateTable_clicked(const QModelIndex &index);

    void on_deadlineTable_clicked(const QModelIndex &index);

private:
    Ui::Maintenance *ui;
    QCalendarWidget *calendar;
    QSqlQueryModel *startDateModel;
    QSqlQueryModel *deadlineModel;
};

#endif // MAINTENANCE_H
