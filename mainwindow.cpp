#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainPlaylist = new QMediaPlaylist;
    playlist = new QMediaPlaylist;
    mediaPlayer = new QMediaPlayer;
    m_p = new music_properties;
    ui->music_properties_layout->addWidget(m_p);
    m_p->hide();
    list_w_pls_open = new listWidgetPlsOpen;
    mainMenu = new QMenu(this); //menu
    subMenu = new QMenu("add",mainMenu);
    subMenu->setIcon(QIcon(":/image/glyphicons-191-circle-plus.png"));
    mainMenu->addAction(subMenu->menuAction());
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tabWidget->setTabsClosable(true);
    table = new tablePls;
    qwtHistogram = new qwt;
    ui->histogramLayout->addWidget(qwtHistogram->myPlot);
    probe = new QAudioProbe;
    probe->setSource(mediaPlayer);


    connect(mediaPlayer,SIGNAL(metaDataChanged()),this,SLOT(metaDataChanged()));
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64))); //mediaPlayer
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    connect(mediaPlayer,SIGNAL(currentMediaChanged(QMediaContent)),this,SLOT(current_play()));
    connect(subMenu,SIGNAL(triggered(QAction*)),this,SLOT(add_to_playlist(QAction*)));
    connect(list_w_pls_open->ui->listWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(open_pls()));
    connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(close_my_tab(int)));
    connect(probe,SIGNAL(audioBufferProbed(QAudioBuffer)),this,SLOT(processBuffer(QAudioBuffer)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFilesButton_clicked()
{
    i = ui->tableWidget->rowCount();
    QStringList fileNames = open_files();
    foreach (QString const &argument, fileNames) //convert string_list to sring
    {
            QFileInfo fileInfo(argument);//send this string to fileInfo

            if (fileInfo.exists())
            {
                QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
                mainPlaylist->addMedia(url);//playlist->add->url
                ui->tableWidget->insertRow(i);
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(g_t.gettags_artist(fileInfo.absoluteFilePath())));
                ui->tableWidget->setItem(i,1,new QTableWidgetItem(g_t.gettags_title(fileInfo.absoluteFilePath())));
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(g_t.gettags_album(fileInfo.absoluteFilePath())));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(g_t.gettags_time(fileInfo.absoluteFilePath())));
                ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignCenter);
                i++;
                qDebug()<<fileInfo.absoluteFilePath();

            }
    }
    mediaPlayer->setPlaylist(mainPlaylist);
    mediaPlayer->play();
    ui->playButton->setIcon(QIcon(":/image/glyphicons-175-pause.png"));
    ui->tableWidget->selectRow(mainPlaylist->currentIndex());
}

QStringList MainWindow::open_files()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                          "Select one or more files to open",
                                                          "/home/grzesiek/Muzyka",
                                                          "(*.mp3 *.wav *.mp4 )");
    return fileNames;
}


void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    QString tabName= ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    playlist->setObjectName(tabName);
    QString tabFirst = "new playlist";
    	if(!ui->tabWidget->currentIndex()==0||tabName!=tabFirst)
    		{
    			playlist->clear();
    			qDebug()<<tabName;
    			qDebug()<<"test";
		        tabName = tabName+".m3u";
		        playlist->load(QUrl(QUrl::fromLocalFile(tabName)),"m3u");
		    	mediaPlayer->setPlaylist(playlist);
		    	mediaPlayer->play();
		    	playlist->setCurrentIndex(index.row());
		    	tableObjectSelected();
    		}
    	else
    		mediaPlayer->setPlaylist(mainPlaylist);
    		mainPlaylist->setCurrentIndex(index.row());
    		ui->tableWidget->selectRow(mainPlaylist->currentIndex());
    		mediaPlayer->play();
    		changeTablePositonOnPlay();

    ui->playButton->setIcon(QIcon(":/image/glyphicons-175-pause.png"));
}



void MainWindow::positionChanged(qint64 position)
{
    ui->TrackSlider->setValue(position);
    set_track_time();
}

void MainWindow::durationChanged(qint64 duration)
{
    ui->TrackSlider->setRange(0, duration);
    ui->tableWidget->selectRow(mainPlaylist->currentIndex());
    changeTablePositonOnPlay();
}

void MainWindow::on_TrackSlider_sliderMoved(int position)
{
    mediaPlayer->setPosition(position);
}

void MainWindow::set_track_time()
{
    QString format = "mm:ss";
    
    if (mediaPlayer->duration() > 360000)
    {
        format = "hh:mm:ss";
    }

    QTime time(0,0);
    time = time.addMSecs(mediaPlayer->position());
    ui->labelTimeLeft ->setText(time.toString(format));
    ui->labelTimeLeft->setAlignment(Qt::AlignCenter);

    QTime time1(0,0);
    time1=time1.addMSecs(mediaPlayer->duration());
    ui->labelTime->setText(time1.toString(format));
    ui->labelTime->setAlignment(Qt::AlignCenter);
    if(mediaPlayer->position()==0)
    {
        ui->labelTimeLeft->setText("00:00");
    }
}

void MainWindow::changeTablePositonOnPlay()
{
    tableObjectSelected();
}

void MainWindow::tableObjectSelected()
{
    for(i=0; i<tableObject.size();i++)
    {
        if(ui->tabWidget->tabText(i+1)==ui->tabWidget->tabText(ui->tabWidget->currentIndex()))
        {
            tableObject[i]->ui->tableWidget->selectRow(mediaPlayer->playlist()->currentIndex());

        }
    }
}

void MainWindow::on_nextButton_clicked()
{
    if(!mediaPlayer->playlist()->isEmpty())
    {
        mediaPlayer->playlist()->next();
        tableObjectSelected();
    }
    else playlist->next();
    ui->tableWidget->selectRow(mainPlaylist->currentIndex());

    changeTablePositonOnPlay();

}

void MainWindow::on_previousButton_clicked()
{
    if(!mediaPlayer->playlist()->isEmpty())
    {
        mediaPlayer->playlist()->previous();
        tableObjectSelected();

    }
    else playlist->previous();
    ui->tableWidget->selectRow(mainPlaylist->currentIndex());
    changeTablePositonOnPlay();
}

void MainWindow::on_stopButton_clicked()
{
    playlist->clear();
    mainPlaylist->clear();
    this->setWindowTitle("crude");

    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }
    i = 0;
    ui->labelTime->setText("00:00");

}

void MainWindow::on_playButton_clicked()
{
    if(!mediaPlayer->playlist()->isEmpty())
    {
        switch(mediaPlayer->state())
        {
            case QMediaPlayer::PlayingState:
                mediaPlayer->pause();
                ui->playButton->setIcon(QIcon(":/image/glyphicons-174-play.png"));
                break;
            default:
                mediaPlayer->play();
                ui->playButton->setIcon(QIcon(":/image/glyphicons-175-pause.png"));
                break;
        }
    }
}





void MainWindow::on_createPlaylistButton_clicked()
{
    bool ok;

    QString text = QInputDialog::getText(this, tr(""),
                                         tr("Playlist name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    {
        text=text+".m3u";
        QFile file(text);
        if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))return;
        QFile file_1("playlists.txt");
        if (!file_1.open(QFile::WriteOnly | QFile::Text | QFile::Append))return;
        QTextStream out_1(&file_1);
        out_1 << text<<"\n";
    }
    ////////////////////////////////////////////////////////////////////////////////////open file
    QString fileName = "playlists.txt"; // or "/absolute/path/to/your/file"
    QFile file1(fileName);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))return;
    QStringList stringList;
    QTextStream textStream(&file1);
    while (!textStream.atEnd())
    {
        stringList << textStream.readLine();//load to container
        qDebug() << stringList;
    }
    file1.close();
    message_duplicates(stringList);
    stringList.removeDuplicates();
    qDebug()<<stringList;
    QString fileName_2 = "playlists.txt"; // or "/absolute/path/to/your/file"
    QFile file2(fileName_2);
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text))return;
    QTextStream out(&file2);
    for (int i = 0; i < stringList.size(); ++i)
    {
        out << stringList.at(i) << '\n';      //save file from container
    }
    file2.close();
}

void MainWindow::message_duplicates(QStringList stringList)
{
    if(stringList.removeDuplicates()){
        QMessageBox msgBox;
        msgBox.setText("This playlist name is already exists.\n");
        msgBox.exec();
    }
}

void MainWindow::on_openPlaylistButton_clicked()
{
    list_w_pls_open->show();
}

void MainWindow::on_VolumeSlider_sliderMoved(int position)
{
    QPixmap p(":/image/glyphicons-183-mute.png");
    QPixmap p1(":/image/glyphicons-185-volume-up.png");
    QPixmap p2(":/image/glyphicons-184-volume-down.png");
    mediaPlayer->setVolume(position);

    if(position>0)
    {
         ui->labelVolume->setPixmap(p1);
         ui->labelVolume->setAlignment(Qt::AlignCenter);
    }
    if(position==0)
    {
        ui->labelVolume->setPixmap(p);
        ui->labelVolume->setAlignment(Qt::AlignCenter);

    }
    if (position<50&&position>0)
    {
        ui->labelVolume->setPixmap(p2);
        ui->labelVolume->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_randomButton_clicked(bool checked)
{
    if(mediaPlayer->media()==mainPlaylist)//mainplaylist
    {
    if(checked==false)
    {
        mainPlaylist->setPlaybackMode(QMediaPlaylist::Sequential);
    }
    if(checked==true)
    {
        mainPlaylist->setPlaybackMode(QMediaPlaylist::Random);
    }
    ui->tableWidget->selectRow(mainPlaylist->currentIndex());
    }
    if(mediaPlayer->media()==playlist)//playlist
    {
    if(checked==false)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    }
    if(checked==true)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    }
    ui->tableWidget->selectRow(playlist->currentIndex());
    }
}

void MainWindow::musicProperties(QFileInfo fileInfo)
{
    m_p->ui->label->setPixmap(QPixmap::fromImage(g_t.gettags_cover(fileInfo.absoluteFilePath())));
    m_p->ui->tableWidget->setItem(0,0,new QTableWidgetItem(g_t.gettags_title(fileInfo.absoluteFilePath())));
    m_p->ui->tableWidget->setItem(1,0,new QTableWidgetItem(g_t.gettags_artist(fileInfo.absoluteFilePath())));
    m_p->ui->tableWidget->setItem(2,0,new QTableWidgetItem(g_t.gettags_album(fileInfo.absoluteFilePath())));
    m_p->ui->tableWidget->setItem(3,0,new QTableWidgetItem(g_t.gettags_time(fileInfo.absoluteFilePath())));
    m_p->ui->tableWidget->setItem(4,0,new QTableWidgetItem(g_t.gettags_bitrate(fileInfo.absoluteFilePath())));
    m_p->ui->tableWidget->setItem(5,0,new QTableWidgetItem(g_t.gettags_genre(fileInfo.absoluteFilePath())));
    m_p->ui->tableWidget->setItem(6,0,new QTableWidgetItem(g_t.gettags_sampleRate(fileInfo.absoluteFilePath())));
    m_p->ui->tableWidget->setItem(7,0,new QTableWidgetItem(g_t.gettags_year(fileInfo.absoluteFilePath())));
}

void MainWindow::current_play()
{

    if(!mediaPlayer->media().isNull())
    {
        QFileInfo fileInfo(mediaPlayer->currentMedia().canonicalUrl().path());
        if(fileInfo.exists())
        {
            QString windowTitle_1 = g_t.gettags_title(fileInfo.absoluteFilePath());
            QString windowTitle_2 = g_t.gettags_artist(fileInfo.absoluteFilePath());
            this->setWindowTitle(windowTitle_1+" - "+windowTitle_2);
            musicProperties(fileInfo);
        }
    }


}

void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    subMenu->clear();
    QPoint globalpos = ui->tableWidget->mapToGlobal(pos);
    QTableWidgetItem* pointedItem = ui->tableWidget->itemAt(pos);
    QFile file("playlists.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;

    QTextStream in(&file);
    QString line = in.readLine();

    while (!line.isNull())
    {
        QFileInfo fileInfo(line);
        subMenu->addAction(fileInfo.completeBaseName())->setIcon(QIcon(":/image/glyphicons-160-playlist.png"));
        line = in.readLine();
    }

    if(pointedItem)
    {
        mainMenu->exec(globalpos);
    }

}

void MainWindow::add_to_playlist(QAction *a)
{

qDebug()<<"nazwa"<<ui->tabWidget->tabText(ui->tabWidget->currentIndex());
    for(i=0; i<tableObject.size();i++)
    {
        if(ui->tabWidget->tabText(i+1)==ui->tabWidget->tabText(ui->tabWidget->currentIndex())&&mediaPlayer->playlist())
        {
            QString text=a->text();
            QUrl url = tableObject[i]->playlist->media(tableObject[i]->ui->tableWidget->currentIndex().row()).canonicalUrl();
            text=text+".m3u";
            qDebug()<<"////////////";
            qDebug() <<text;
            qDebug() <<url.toString();
            QFile file(text);
            if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))return;
            QTextStream out(&file);
            out<<url.toString()<<"\n";
        }
        else
        {
            QString text=a->text();
            QUrl url = mainPlaylist->media(ui->tableWidget->currentIndex().row()).canonicalUrl();
            text=text+".m3u";
            qDebug() <<text;
            qDebug() <<url.toString();
            QFile file(text);
            if (!file.open(QFile::WriteOnly | QFile::Text | QFile::Append))return;
            QTextStream out(&file);
            out<<url.toString()<<"\n";}
            qDebug()<<i;
        }

}



void MainWindow::open_pls()
{
    i=0;
    MainWindow *savePlaylists = new MainWindow;
    ui->tabWidget->insertTab(ui->tabWidget->count(),savePlaylists->ui->tableWidget,list_w_pls_open->ui->listWidget->currentItem()->text());
    ui->tabWidget->addTab(savePlaylists->ui->tableWidget,list_w_pls_open->ui->listWidget->currentItem()->text());
    playlist->clear();
    int pageIndex = ui->tabWidget->indexOf( ui->tabWidget->currentWidget() ) ;
    ui->tabWidget->setCurrentIndex( pageIndex + 1 ) ;
    QString text = list_w_pls_open->ui->listWidget->currentItem()->text();
    text=text+".m3u";
    savePlaylists->playlist->load(QUrl(QUrl::fromLocalFile(text)),"m3u");
    mediaPlayer->setPlaylist(savePlaylists->playlist);
    mediaPlayer->play();

    QFile file(text);
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return;
       QTextStream in(&file);
       QString line = in.readLine();

       while (!line.isNull())
       {
           QFileInfo fileInfo(line);
           savePlaylists->ui->tableWidget->insertRow(i);
           savePlaylists->ui->tableWidget->setItem(i,0,new QTableWidgetItem(g_t.gettags_artist(fileInfo.filePath().remove(0,6))));
           savePlaylists->ui->tableWidget->setItem(i,1,new QTableWidgetItem(g_t.gettags_title(fileInfo.filePath().remove(0,6))));
           savePlaylists->ui->tableWidget->setItem(i,2,new QTableWidgetItem(g_t.gettags_album(fileInfo.filePath().remove(0,6))));
           savePlaylists->ui->tableWidget->setItem(i,3,new QTableWidgetItem(g_t.gettags_time(fileInfo.filePath().remove(0,6))));
           savePlaylists->ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignCenter);
           ++i;
           line = in.readLine();
       }
    newTab(savePlaylists);
    savePlaylists->ui->tableWidget->selectRow(playlist->currentIndex());
    connect(savePlaylists->ui->tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_tableWidget_doubleClicked(QModelIndex)));
    connect(savePlaylists->subMenu,SIGNAL(triggered(QAction*)),this,SLOT(add_to_playlist(QAction*)));
    tableObject.push_back(savePlaylists);
    savePlaylists->ui->tableWidget->selectRow(mediaPlayer->playlist()->currentIndex());
    ui->playButton->setIcon(QIcon(":/image/glyphicons-175-pause.png"));

}

void MainWindow::close_my_tab(int a)
{
    if(!a==0)
    {
        tableObject.remove(a-1);
        ui->tabWidget->removeTab(a);
    }
}
void MainWindow::newTab(MainWindow *table_2)
{
    table_2->ui->tableWidget->selectRow(playlist->currentIndex());
}
void MainWindow::processBuffer(QAudioBuffer buffer)
{
    QAudioBuffer::S32F *frames = buffer.data<QAudioBuffer::S32F>();
    // input signal parameters
    const Aquila::FrequencyType f_lp = 44100;
    const Aquila::FrequencyType f1 = frames->left, f2 = frames->right;
    Aquila::SineGenerator sineGenerator1 = Aquila::SineGenerator(sampleFreq);
    sineGenerator1.setAmplitude(32).setFrequency(f1).generate(SIZE);
    Aquila::SineGenerator sineGenerator2 = Aquila::SineGenerator(sampleFreq);
    sineGenerator2.setAmplitude(8).setFrequency(f2).setPhase(0.75).generate(SIZE);
     auto sum = sineGenerator1 + sineGenerator2;
    Aquila::TextPlot plt("Signal waveform before filtration");
       //plt.plot(sum);

       // calculate the FFT
       auto fft = Aquila::FftFactory::getFft(SIZE);
       Aquila::SpectrumType spectrum = fft->fft(sum.toArray());
       plt.setTitle("Signal spectrum before filtration");
       //plt.plotSpectrum(spectrum);

       // generate a low-pass filter spectrum
       Aquila::SpectrumType filterSpectrum(SIZE);
       for (std::size_t i = 0; i < SIZE; ++i)
       {
           if (i < (SIZE * f_lp / sampleFreq))
           {
               // passband
               filterSpectrum[i] = 1;
           }
           else
           {
               // stopband
               filterSpectrum[i] = 0;
           }
       }
       plt.setTitle("Filter spectrum");
       //plt.plotSpectrum(filterSpectrum);

       // the following call does the multiplication of two spectra
       // (which is complementary to convolution in time domain)
       std::transform(
           std::begin(spectrum),
           std::end(spectrum),
           std::begin(filterSpectrum),
           std::begin(spectrum),
           [] (Aquila::ComplexType x, Aquila::ComplexType y) { return x * y; }
       );
       plt.setTitle("Signal spectrum after filtration");
       //plt.plotSpectrum(spectrum);

       // Inverse FFT moves us back to time domain
       double x1[SIZE];
       fft->ifft(spectrum, x1);
       plt.setTitle("Signal waveform after filtration");
       //plt.plot(x1, SIZE);

    /////////////////////////////////////////////////////////
    std::size_t halfLength = spectrum.size() / 2;
    std::vector<int> absSpectrum(halfLength);

    for (int i = 0; i < absSpectrum.size(); ++i)
    {
        absSpectrum[i] = std::abs(spectrum[i]);

    }
    for(int i = 0;i<absSpectrum.size();i++)
    {
        //std::cout<<absSpectrum[i];
        //std::cout<<"\n";
    }
    plt.setTitle("Spectrum");
    //plt.plotSpectrum(spectrum);
    QPolygonF points;
    for( int h = 0; h < absSpectrum.size(); ++h)
    {
        int bin_value = absSpectrum.at(h);
        points << QPointF((int)h, bin_value);
    }
    QVector<QwtIntervalSample> samples(SIZE);   //histogram
    for(int i = 0;i<absSpectrum.size(); i++)
    {
        samples.append(QwtIntervalSample(absSpectrum[i], i, i+1));
    }
    qwtHistogram->histogram->setSamples(samples);
    //curve1->setSamples( points );
    qwtHistogram->myPlot->replot();
}
void MainWindow::metaDataChanged()
{





}


void MainWindow::on_musicProperties_clicked()
{
    if(m_p->isHidden())
    {
        m_p->show();
    }
    else m_p->hide();
}
