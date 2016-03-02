#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vlc/vlc.h>
#include <QStringListModel>
#include "dialog.h"

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotPositionChanged( double pos );
    void slotOpenURL( QString strURL );
    void on_buttonOpenFile_clicked();
    void on_horizontalSliderProgress_valueChanged(int value);
    void on_horizontalSliderVolume_valueChanged(int value);
    void on_listView_clicked(const QModelIndex &index);
    void on_buttonPause_clicked();
    void on_buttonOpenUrl_clicked();

private:
    static void libvlc_callback( const libvlc_event_t *event, void *data );

    Ui::MainWindow *ui;
    Dialog urlOpenDialog;
    QString filePath;
    QStringList       stringListView;
    QStringListModel *stringListModel;

    libvlc_event_manager_t *vlc_events;
    libvlc_instance_t      *vcl_instance;
    libvlc_media_player_t  *vlc_media_player;
    libvlc_media_list_player_t *vlc_play_list_instance;
    libvlc_media_list_t   *vlc_media_list_instance;

    void Play( int index );
    void addItemInPlayList(QString fileName , bool FileUrl); // FileUrl - true file, false - url
    void ShowErrorVlc( void );
};

#endif // MAINWINDOW_H
