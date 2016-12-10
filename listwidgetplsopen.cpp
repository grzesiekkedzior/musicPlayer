#include "listwidgetplsopen.h"
#include "ui_listwidgetplsopen.h"

listWidgetPlsOpen::listWidgetPlsOpen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listWidgetPlsOpen)
{
    ui->setupUi(this);
    QFile file("playlists.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;

    QTextStream in(&file);
    QString line = in.readLine();

    while (!line.isNull())
    {
        QFileInfo fileInfo(line);
        ui->listWidget->addItem(fileInfo.completeBaseName());
        line = in.readLine();
    }
}

listWidgetPlsOpen::~listWidgetPlsOpen()
{
    delete ui;
}
