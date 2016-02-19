#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QWindow>
#include<QList>
#include<QDebug>
#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    char const *vlc_argv[] = { "" };
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);

    vcl_instance = libvlc_new( vlc_argc , vlc_argv );
    vlc_media_player = libvlc_media_player_new( vcl_instance );
    vlc_events = libvlc_media_player_event_manager( vlc_media_player );
    libvlc_media_player_set_hwnd( vlc_media_player, (void*)ui->widgetPlayer->winId() );
    vlc_play_list_instance =  libvlc_media_list_player_new( vcl_instance );
    vlc_media_list_instance = libvlc_media_list_new( vcl_instance );
    libvlc_media_list_player_set_media_list( vlc_play_list_instance, vlc_media_list_instance );

    QList<libvlc_event_e> list;
    list << libvlc_MediaPlayerMediaChanged
         << libvlc_MediaPlayerNothingSpecial
         << libvlc_MediaPlayerOpening
         << libvlc_MediaPlayerBuffering
         << libvlc_MediaPlayerPlaying
         << libvlc_MediaPlayerPaused
         << libvlc_MediaPlayerStopped
         << libvlc_MediaPlayerForward
         << libvlc_MediaPlayerBackward
         << libvlc_MediaPlayerEndReached
         << libvlc_MediaPlayerEncounteredError
         << libvlc_MediaPlayerTimeChanged
         << libvlc_MediaPlayerPositionChanged
         << libvlc_MediaPlayerSeekableChanged
         << libvlc_MediaPlayerPausableChanged
         << libvlc_MediaPlayerTitleChanged
         << libvlc_MediaPlayerSnapshotTaken
         << libvlc_MediaPlayerLengthChanged
         << libvlc_MediaPlayerVout;

    foreach(const libvlc_event_e &event, list) {
        libvlc_event_attach( vlc_events, event, libvlc_callback, this );
    }
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}
//-----------------------------------------------------------------------------
void MainWindow::ShowErrorVlc( void )
{
    QString str_error = QString::fromUtf8( libvlc_errmsg() );
    if( !str_error.isEmpty() )
    {
        qWarning() << "Error: " << str_error;
        libvlc_clearerr();
    }
}
//-----------------------------------------------------------------------------
void MainWindow::slotPlayPlayer( void )
{
    qDebug() << "START";
    //vlc_media = libvlc_media_new_location( vcl_instance, "http://www.youtube.com/watch?v=cgNrZbVbq0Y" );
    /*vlc_media = libvlc_media_new_path( vcl_instance, "qwe.avi" );
    libvlc_media_list_add_media( vlc_media_list_instance, vlc_media );
    vlc_media = libvlc_media_new_path( vcl_instance, "Usher - Yeah.avi" );
    libvlc_media_list_add_media( vlc_media_list_instance, vlc_media );
    libvlc_media_list_player_set_media_list( vlc_play_list_instance, vlc_media_list_instance );
    tmp_media =  libvlc_media_list_item_at_index(vlc_media_list_instance, 0 );
    libvlc_media_player_set_media( vlc_media_player, tmp_media );
    libvlc_media_player_play(vlc_media_player);*/
    qDebug() << "END";
}
//-----------------------------------------------------------------------------
void MainWindow::on_buttonOpenFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName( this, "Open File",
                                                     QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ),
                                                     "Video (*.*)" );
    if( !fileName.isEmpty() )
    {
        fileName = QDir::toNativeSeparators( fileName );
        libvlc_media_t *tmp_media = libvlc_media_new_path( vcl_instance, fileName.toUtf8().data() );
        libvlc_media_list_add_media( vlc_media_list_instance, tmp_media );
        libvlc_media_release( tmp_media );

        libvlc_media_player_set_media( vlc_media_player,
                                       libvlc_media_list_item_at_index(vlc_media_list_instance, 0 ) );
        libvlc_media_player_play(vlc_media_player);
    }
}
//-----------------------------------------------------------------------------
void MainWindow::on_pushButton_2_clicked()
{
    libvlc_media_player_stop( vlc_media_player );
    libvlc_media_player_release( vlc_media_player );

    //libvlc_media_release( vlc_media );
    libvlc_release( vcl_instance );

    ShowErrorVlc();
}
//-----------------------------------------------------------------------------
void MainWindow::slotPositionChanged( double pos )
{
    ui->horizontalSliderProgress->blockSignals( true );
    ui->horizontalSliderProgress->setValue( int(pos*1000) );
    ui->horizontalSliderProgress->blockSignals( false );
}
//-----------------------------------------------------------------------------
void MainWindow::on_horizontalSliderProgress_valueChanged( int value )
{
    if( vlc_media_player )
        libvlc_media_player_set_position( vlc_media_player, ((double)value) /1000 );
}
//-----------------------------------------------------------------------------
void MainWindow::libvlc_callback(const libvlc_event_t *event, void *data)
{
    MainWindow *mainWin = (MainWindow*)data;

    switch(event->type)
    {
        case libvlc_MediaPlayerMediaChanged: qDebug() << "1";
      //      emit core->mediaChanged(event->u.media_player_media_changed.new_media);
            break;
        case libvlc_MediaPlayerPaused:qDebug() << "2";
      //      emit core->paused();
            break;
        case libvlc_MediaPlayerStopped:qDebug() << "3";
      //      emit core->stopped();
            break;
        case libvlc_MediaPlayerForward:qDebug() << "4";
      //      emit core->forward();
            break;
        case libvlc_MediaPlayerEndReached:qDebug() << "5";
       //     emit core->end();
            break;
        case libvlc_MediaPlayerEncounteredError:qDebug() << "6";
       //     emit core->error();
            break;
        case libvlc_MediaPlayerPositionChanged:
            emit mainWin->slotPositionChanged( event->u.media_player_position_changed.new_position );
            break;
        default:
            break;
    }
}

void MainWindow::on_horizontalSliderVolume_valueChanged( int value )
{
    if( vlc_media_player )
        libvlc_audio_set_volume( vlc_media_player, value );
}
