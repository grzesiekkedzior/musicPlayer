#ifndef TABLEPLS_H
#define TABLEPLS_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>
namespace Ui {
class tablePls;
}

class tablePls : public QWidget
{
    Q_OBJECT

public:
    explicit tablePls(QWidget *parent = 0);
    ~tablePls();
    Ui::tablePls *ui;
    QMediaPlaylist *playlist;


private:

};

#endif // TABLEPLS_H
