#ifndef AP_WIDGET_H
#define AP_WIDGET_H

#include <QWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QMessageBox>
#include <QListWidgetItem>
#include "ap_info.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AP_Widget; }
QT_END_NAMESPACE

class AP_Widget : public QWidget
{
    Q_OBJECT

public:
    AP_Widget(QWidget *parent = nullptr);
    ~AP_Widget();

private slots:
    void on_AP_PLay_clicked();

    void on_AP_Select_clicked();

    void on_AP_PreOne_clicked();

    void on_AP_NextOne_clicked();

    void on_AP_Destory_clicked();

    void position_change(qint64 position);

    void duration_change(qint64 duration);

    void info_change(int no);

    void on_AP_TimeBar_sliderMoved(int position);

    void on_AP_Silence_clicked();

    void on_AP_VolumeBar_valueChanged(int value);

    void show_volume(int volume);

    void on_AP_ListMode_clicked();

    void on_AP_Insert_clicked();

    void on_AP_List_itemClicked(QListWidgetItem *item);

    void on_AP_List_itemDoubleClicked(QListWidgetItem *item);

    void show_song(int index);

    void lyric_move(qint64 position);
private:
    Ui::AP_Widget *ui;//ui
    QMediaPlayer* player;//播放器
    QMediaPlaylist* playlist;//播放列表
    QString* urllist;//文件位置列表
    QString DurationTime;//单曲时长
    QString PositionTime;//当前位置
    LyricInfo Lyric;//歌词信息
    int UpdateTime;//歌词刷新次数
};
#endif // AP_WIDGET_H
