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

    connect( &urlOpenDialog, SIGNAL( signalUrlOK(QString) ), this, SLOT( slotOpenURL(QString) ) );

    stringListModel = new QStringListModel();
    ui->listView->setModel( stringListModel );

    char const *vlc_argv[] = {
        "--verbose=2",
        "--plugin-path=plugins"
    };
    int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);

    vcl_instance = libvlc_new( vlc_argc , vlc_argv );
    vlc_media_player = libvlc_media_player_new( vcl_instance );
    vlc_events = libvlc_media_player_event_manager( vlc_media_player );
    libvlc_media_player_set_hwnd( vlc_media_player, (void*)ui->widgetPlayer->winId() );
    vlc_play_list_instance =  libvlc_media_list_player_new( vcl_instance );
    vlc_media_list_instance = libvlc_media_list_new( vcl_instance );
    libvlc_media_list_player_set_media_list( vlc_play_list_instance, vlc_media_list_instance );

    QList< libvlc_event_e > list;
    list << libvlc_MediaPlayerEncounteredError
         << libvlc_MediaPlayerPositionChanged;

    foreach( const libvlc_event_e &event, list )
    {
        libvlc_event_attach( vlc_events, event, libvlc_callback, this );
    }
}
//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    libvlc_media_player_stop( vlc_media_player );
    libvlc_media_player_release( vlc_media_player );
    libvlc_media_list_player_release( vlc_play_list_instance );
    libvlc_media_list_release( vlc_media_list_instance );
    libvlc_release( vcl_instance );
    ShowErrorVlc();
    delete stringListModel;
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
void MainWindow::on_buttonOpenFile_clicked()
{
    if( filePath.isEmpty() )
    {
        filePath = QStandardPaths::writableLocation( QStandardPaths::DesktopLocation );
    }
    QString fileName = QFileDialog::getOpenFileName( this, "Open File",
                                                     filePath,
                                                     "Video (*.*)" );
    if( !fileName.isEmpty() )
    {
        QFileInfo infFile( fileName );
        filePath = infFile.filePath();
        fileName = QDir::toNativeSeparators( fileName );
        addItemInPlayList( fileName, true );
        Play( stringListView.count() - 1  );
    }
}
//-----------------------------------------------------------------------------
void MainWindow::addItemInPlayList( QString fileName, bool FileUrl )
{
    libvlc_media_t *tmp_media;
    if( FileUrl )
    {
        QFileInfo infFile( fileName );
        stringListView << infFile.fileName();
        stringListModel->setStringList( stringListView );
        tmp_media = libvlc_media_new_path( vcl_instance, fileName.toUtf8().data() );
    }
    else
    {
        stringListView << fileName;
        stringListModel->setStringList( stringListView );
        //tmp_media = libvlc_media_new_path( vcl_instance, fileName.toLatin1() );
        tmp_media = libvlc_media_new_location( vcl_instance, fileName.toUtf8().data() );
    }
    libvlc_media_list_add_media( vlc_media_list_instance, tmp_media );
    libvlc_media_release( tmp_media );
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
        case libvlc_MediaPlayerEncounteredError:
            qDebug() << "libvlc_MediaPlayerEncounteredError";
            break;
        case libvlc_MediaPlayerPositionChanged:
            emit mainWin->slotPositionChanged( event->u.media_player_position_changed.new_position );
            break;
        default:
            break;
    }
}
//-----------------------------------------------------------------------------
void MainWindow::on_horizontalSliderVolume_valueChanged( int value )
{
    if( vlc_media_player )
    {
        libvlc_audio_set_volume( vlc_media_player, value );
        ShowErrorVlc();
    }
}
//-----------------------------------------------------------------------------
void MainWindow::Play( int index )
{
    libvlc_media_player_set_media( vlc_media_player,
                                   libvlc_media_list_item_at_index( vlc_media_list_instance, index ) );
    libvlc_media_player_play( vlc_media_player );
    ShowErrorVlc();
}
//-----------------------------------------------------------------------------
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    qDebug() << index.row();
    if( vlc_media_player )
    {
        Play( index.row() ) ;
    }
}
//-----------------------------------------------------------------------------
void MainWindow::on_buttonPause_clicked()
{
    if( vlc_media_player )
    {
        qDebug() << "PAUSE";
        libvlc_state_t vlc__player_state = libvlc_media_player_get_state( vlc_media_player );
        if( vlc__player_state == libvlc_Playing )
        {
            libvlc_media_player_set_pause( vlc_media_player, 1 );
        }
        else
        {
            libvlc_media_player_set_pause( vlc_media_player, 0 );
        }
        ShowErrorVlc();
    }
}
//-----------------------------------------------------------------------------
void MainWindow::on_buttonOpenUrl_clicked()
{
    urlOpenDialog.show();
}
//-----------------------------------------------------------------------------
void MainWindow::slotOpenURL( QString strURL )
{
    if( !strURL.isEmpty() )
    {
        qDebug() << "OPEN URL: " << strURL;
        addItemInPlayList( strURL, false );
    }
}
//-----------------------------------------------------------------------------
