#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "get_tag.h"
#include "listwidgetplsopen.h"
#include "ui_listwidgetplsopen.h"
#include "tablepls.h"
#include "ui_tablepls.h"
#include "qwt.h"
#include "music_properties.h"
#include "ui_music_properties.h"
#include <QMainWindow>
#include <QPixmap>
#include <QIcon>
#include <QFileDialog>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStringList>
#include <QUrl>
#include <QMessageBox>
#include <QInputDialog>
#include <QAction>
#include <QMenu>
#include <QListWidgetItem>
#include <QPoint>
#include <QListWidget>
#include <QVector>
#include <QVideoProbe>
#include <QMediaService>
#include <QMediaMetaData>
#include <QPainter>
#include <QLabel>
#include <QAudioBuffer>
#include <QAudioProbe>
#include <QBitArray>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int i{0};
    int n{0};
    get_tag g_t;
    tablePls *table;
    qwt *qwtHistogram;
    music_properties *m_p;

    listWidgetPlsOpen *list_w_pls_open;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *mainPlaylist;
    QMediaPlaylist *playlist;
    QMenu           *mainMenu;
    QMenu   *subMenu;
    QAction *addToPlaylist;
    QLabel *labelHistogram;
    QVector <MainWindow*> tableObject;
    QAudioProbe *probe;

    QString playlistObjectName;

    const Aquila::FrequencyType sampleFreq = 44100;
    const std::size_t SIZE = 64;

    QStringList open_files();

    void set_track_time();

    void messagebox_inf();
    
    QStringList load_file1_stringlist(QFile file1);
    
    void message_duplicates(QStringList stringList);

    void newTab(MainWindow *table_2);

    void changeTablePositonOnPlay();


    void musicProperties(QFileInfo fileInfo);
    
    void tableObjectSelected();

private slots:
    void on_openFilesButton_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void positionChanged(qint64 position);

    void durationChanged(qint64 duration);

    void on_TrackSlider_sliderMoved(int position);

    void on_nextButton_clicked();

    void on_previousButton_clicked();

    void on_stopButton_clicked();

    void on_playButton_clicked();

    void on_createPlaylistButton_clicked();

    void on_openPlaylistButton_clicked();

    void on_VolumeSlider_sliderMoved(int position);

    void on_randomButton_clicked(bool checked);

    void current_play();

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void add_to_playlist(QAction *a);

    void open_pls();

    void close_my_tab(int a);

    void processBuffer(QAudioBuffer buffer);

    void metaDataChanged();


    void on_musicProperties_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
