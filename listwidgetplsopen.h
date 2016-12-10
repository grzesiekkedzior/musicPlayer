#ifndef LISTWIDGETPLSOPEN_H
#define LISTWIDGETPLSOPEN_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QFileInfo>
namespace Ui {
class listWidgetPlsOpen;
}

class listWidgetPlsOpen : public QWidget
{
    Q_OBJECT

public:
    explicit listWidgetPlsOpen(QWidget *parent = 0);
    ~listWidgetPlsOpen();
    Ui::listWidgetPlsOpen *ui;
private:

};

#endif // LISTWIDGETPLSOPEN_H
