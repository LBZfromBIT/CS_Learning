#include "ap_widget.h"
#include "ui_ap_widget.h"


AP_Widget::AP_Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AP_Widget)
{

    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    this->setWindowTitle("音乐播放器");
    player = new QMediaPlayer(this);//绑定播放器
    playlist = new QMediaPlaylist(this);//绑定播放列表
    player->setPlaylist(playlist);//播放器指定播放列表
    player->setVolume(50);//设置默认音量大小为50
    playlist->setPlaybackMode(QMediaPlaylist::Loop);//播放模式默认为列表循环
    urllist = nullptr;//文件信息列表置空
    //设置默认封面,适应控件大小，保持比例，平滑缩放
    QImage cover(":/new/prefix1/default.png");
    QPixmap defCover = QPixmap::fromImage(cover);
    ui->AP_CoverLabel->setPixmap(defCover.scaled(ui->AP_CoverLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    Lyric.Type = "Nothing";
    UpdateTime =0;
    //设置歌词单元样式
    //居中
    ui->AP_Lyric1->setAlignment(Qt::AlignCenter);
    ui->AP_Lyric2->setAlignment(Qt::AlignCenter);
    ui->AP_Lyric3->setAlignment(Qt::AlignCenter);
    ui->AP_Lyric4->setAlignment(Qt::AlignCenter);
    ui->AP_Lyric5->setAlignment(Qt::AlignCenter);
    ui->AP_Lyric6->setAlignment(Qt::AlignCenter);
    ui->AP_Lyric7->setAlignment(Qt::AlignCenter);

    //字体大小都为12,中间一个加粗且变为14
    QFont other;
    other.setPointSize(12);
    ui->AP_Lyric1->setFont(other);
    ui->AP_Lyric2->setFont(other);
    ui->AP_Lyric3->setFont(other);
    ui->AP_Lyric5->setFont(other);
    ui->AP_Lyric6->setFont(other);
    ui->AP_Lyric7->setFont(other);
    QFont mid;
    mid.setPointSize(14);
    mid.setBold(true);
    ui->AP_Lyric4->setFont(mid);

    //样式：居中一个背景橙色，字体白色
    ui->AP_Lyric4->setStyleSheet("background-color:rgb(242,184,12);color:rgb(255,255,255)");

    //初始化内容
    ui->AP_Lyric4->setText("未能获取歌词信息");
    ui->AP_Lyric1->clear();
    ui->AP_Lyric2->clear();
    ui->AP_Lyric3->clear();
    ui->AP_Lyric5->clear();
    ui->AP_Lyric6->clear();
    ui->AP_Lyric7->clear();

    //绑定槽函数
    QObject::connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(duration_change(qint64)));
    QObject::connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(position_change(qint64)));
    QObject::connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(lyric_move(qint64)));
    QObject::connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(info_change(int)));
    QObject::connect(ui->AP_VolumeBar,SIGNAL(valueChanged(int)),this,SLOT(show_volume(int)));
    QObject::connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(show_song(int)));
}

AP_Widget::~AP_Widget()
{
    delete ui;
}

void AP_Widget::on_AP_PLay_clicked()//播放暂停
{
    if(player->state() == QMediaPlayer::PlayingState){
        player->pause();
    }
    else{
        player->play();
    }
}

void AP_Widget::on_AP_Select_clicked()//新建列表
{
    //显式调用摧毁函数
    on_AP_Destory_clicked();
    //选择多个文件，储存在QStringist中
    QStringList chosen = QFileDialog::getOpenFileNames(this,"选择您的音乐","..","*.mp3");

    //如果未选择，直接返回
    if(chosen.size() < 1){
        QMessageBox notion(this);
        notion.setWindowTitle("Error");
        notion.setText("未选择歌曲");
        notion.setButtonText(1,"OK");
        notion.exec();
        return;
    }

    //选择了，为每个歌创建一个记录，写入playlist,同时重写chosen[]为歌曲名
    urllist = new QString[chosen.size()];
    for(int i=0;i<chosen.size();i++){
        QString url = chosen[i];
        AP_INFO temp;
        chosen[i] = (temp.GetInfo(url)).Name;
        urllist[i] = url;
        playlist->addMedia(QUrl::fromLocalFile(url));
    }
    ui->AP_List->addItems(chosen);//写入List
    ui->AP_ListNotion->setText("当前列表中有"+QString::number(ui->AP_List->count())+"首歌曲");

    playlist->setCurrentIndex(0);
    player->play();
}

void AP_Widget::on_AP_PreOne_clicked()//上一首
{
    int current = playlist->currentIndex();
    if(playlist->playbackMode()==QMediaPlaylist::Random){
        playlist->previous();
    }
    else if(playlist->playbackMode()==QMediaPlaylist::CurrentItemInLoop){
        playlist->setCurrentIndex(current);
    }
    else{
        if(current == 0){//在播放队列之首
            playlist->setCurrentIndex(playlist->mediaCount()-1);
        }
        else{
            playlist->setCurrentIndex(current-1);
        }
    }
    player->play();
}

void AP_Widget::on_AP_NextOne_clicked()//下一首
{
    int current = playlist->currentIndex();
    if(playlist->playbackMode()==QMediaPlaylist::Random){
        playlist->next();
    }
    else if(playlist->playbackMode()==QMediaPlaylist::CurrentItemInLoop){
        playlist->setCurrentIndex(current);
    }
    else{
        if(current == playlist->mediaCount()-1){//在播放队列之尾
            playlist->setCurrentIndex(0);
        }
        else{
            playlist->setCurrentIndex(current+1);
        }
    }
    player->play();
}

void AP_Widget::on_AP_Destory_clicked()//清除列表
{
    playlist->clear();
    player->stop();
    delete[] urllist;
    urllist = nullptr;
    ui->AP_NameLabel->setText("歌曲：未知");
    ui->AP_AlbumLabel->setText("专辑：未知");
    ui->AP_SingerLabel->setText("歌手：未知");
    QImage cover(":/new/prefix1/default.png");
    QPixmap defcover = QPixmap::fromImage(cover);
    ui->AP_CoverLabel->setPixmap(defcover.scaled(ui->AP_CoverLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->AP_TimeLabel->setText("0:00/0:00");
    ui->AP_List->clear();
    ui->AP_ListNotion->setText("列表中没有歌曲");

    ui->AP_Lyric1->setStyleSheet("");
    ui->AP_Lyric4->setStyleSheet("");
    //字体大小都为12,中间一个加粗且变为14
    QFont other;
    other.setPointSize(12);
    ui->AP_Lyric1->setFont(other);
    ui->AP_Lyric2->setFont(other);
    ui->AP_Lyric3->setFont(other);
    ui->AP_Lyric5->setFont(other);
    ui->AP_Lyric6->setFont(other);
    ui->AP_Lyric7->setFont(other);
    QFont mid;
    mid.setPointSize(14);
    mid.setBold(true);
    ui->AP_Lyric4->setFont(mid);

    //样式：居中一个背景橙色，字体白色
    ui->AP_Lyric4->setStyleSheet("background-color:rgb(242,184,12);color:rgb(255,255,255)");

    //初始化内容
    ui->AP_Lyric4->setText("未能获取歌词信息");
    ui->AP_Lyric1->clear();
    ui->AP_Lyric2->clear();
    ui->AP_Lyric3->clear();
    ui->AP_Lyric5->clear();
    ui->AP_Lyric6->clear();
    ui->AP_Lyric7->clear();

    Lyric.Type = "Nothing";
    Lyric.Pub.clear();
    UpdateTime =0 ;
}

void AP_Widget::position_change(qint64 position){//歌曲播放位置更新
    //更新当前位置
    ui->AP_TimeBar->setSliderPosition(position);
    //传入参数为毫秒，计算秒数、分数
    int sec = position/1000;
    int min = sec/60;
    sec = sec%60;
    //统一格式为m:ss
    if(sec<10){
        PositionTime = QString::number(min)+":0"+QString::number(sec);
    }
    else{
        PositionTime = QString::number(min)+":"+QString::number(sec);
    }
    //更新label
    ui->AP_TimeLabel->setText(PositionTime+"/"+DurationTime);
}

void AP_Widget::duration_change(qint64 duration){//歌曲长度更新
    //设置进度条最大位置防止越界
    ui->AP_TimeBar->setMaximum(duration);
    //传入参数为毫秒，计算秒数、分数
    int sec = duration/1000;
    int min = sec/60;
    sec = sec%60;
    //统一格式
    if(sec<10){
        DurationTime = QString::number(min)+":0"+QString::number(sec);
    }
    else{
        DurationTime = QString::number(min)+":"+QString::number(sec);
    }
    //更新label
    ui->AP_TimeLabel->setText(PositionTime+"/"+DurationTime);
}

void AP_Widget::info_change(int no){//歌曲信息更新
    //非法位置处理
    if(no<0||no>(playlist->mediaCount()-1)){
        ui->AP_NameLabel->setText("歌曲：未知");
        ui->AP_AlbumLabel->setText("专辑：未知");
        ui->AP_SingerLabel->setText("歌手：未知");
        QImage cover(":/new/prefix1/default.png");
        QPixmap defcover = QPixmap::fromImage(cover);
        ui->AP_CoverLabel->setPixmap(defcover.scaled(ui->AP_CoverLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    }
    else{
        AP_INFO temp;
        MP3INFO info = temp.GetInfo(urllist[no]);
        ui->AP_NameLabel->setText("歌曲："+info.Name);
        ui->AP_AlbumLabel->setText("专辑："+info.Album);
        ui->AP_SingerLabel->setText("歌手："+info.Singer);
        if(info.PicFlag==true){
            QImage cover(info.PicURL);
            QPixmap defcover = QPixmap::fromImage(cover);
            ui->AP_CoverLabel->setPixmap(defcover.scaled(ui->AP_CoverLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        }
        else{
            QImage cover(":/new/prefix1/default.png");
            QPixmap defcover = QPixmap::fromImage(cover);
            ui->AP_CoverLabel->setPixmap(defcover.scaled(ui->AP_CoverLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        }

        Lyric = info.Lyric;
        UpdateTime = 0;
        if(Lyric.Type=="Nothing"){
            //如果无歌词，直接绘制
            ui->AP_Lyric1->setStyleSheet("");
            ui->AP_Lyric4->setStyleSheet("");
            //字体大小都为12,中间一个加粗且变为14
            QFont other;
            other.setPointSize(12);
            ui->AP_Lyric1->setFont(other);
            ui->AP_Lyric2->setFont(other);
            ui->AP_Lyric3->setFont(other);
            ui->AP_Lyric5->setFont(other);
            ui->AP_Lyric6->setFont(other);
            ui->AP_Lyric7->setFont(other);
            QFont mid;
            mid.setPointSize(14);
            mid.setBold(true);
            ui->AP_Lyric4->setFont(mid);

            //样式：居中一个背景橙色，字体白色
            ui->AP_Lyric4->setStyleSheet("background-color:rgb(242,184,12);color:rgb(255,255,255)");

            //初始化内容
            ui->AP_Lyric4->setText("未能获取歌词信息");
            ui->AP_Lyric1->clear();
            ui->AP_Lyric2->clear();
            ui->AP_Lyric3->clear();
            ui->AP_Lyric5->clear();
            ui->AP_Lyric6->clear();
            ui->AP_Lyric7->clear();
        }
        //debug
        QMap<int,QString>::iterator i =Lyric.Pub.begin();
        while(i!=Lyric.Pub.end()){
            i++;
        }
    }

}

void AP_Widget::on_AP_TimeBar_sliderMoved(int position)//拖动进度表
{
    player->setPosition(position);
}

void AP_Widget::on_AP_Silence_clicked()//一键静音
{
    player->setVolume(0);
    ui->AP_VolumeBar->setValue(0);
    ui->AP_VolumeLabel->setText("0");
}

void AP_Widget::on_AP_VolumeBar_valueChanged(int value)//音量条调节
{
    player->setVolume(value);
}

void AP_Widget::show_volume(int volume){//音量显示
    ui->AP_VolumeLabel->setText(QString::number(volume));
}

void AP_Widget::on_AP_ListMode_clicked()//修改播放模式
{
    //点击切换：列表循环 -> 随机播放 ->单曲循环
    if(playlist->playbackMode()==QMediaPlaylist::Loop){
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        ui->AP_ListMode->setText("随机播放");
    }
    else if(playlist->playbackMode()==QMediaPlaylist::Random){
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->AP_ListMode->setText("单曲循环");
    }
    else{
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        ui->AP_ListMode->setText("列表循环");
    }
}

void AP_Widget::on_AP_Insert_clicked()//插入歌曲
{
    QStringList insert = QFileDialog::getOpenFileNames(this,"选择您的音乐","..","*.mp3");
    if(insert.size()>0){
        int oldsize = playlist->mediaCount();
        QString* temp = new QString[oldsize+insert.size()];
        for(int i=0;i<oldsize;i++){
            temp[i]=urllist[i];
        }
        delete[] urllist;
        urllist = temp;
        for(int i=0;i<insert.size();i++){
            QString url = insert[i];
            AP_INFO temp;
            insert[i] = (temp.GetInfo(url)).Name;
            playlist->addMedia(QUrl::fromLocalFile(url));
            urllist[oldsize+i] = url;
        }
        ui->AP_List->addItems(insert);
        ui->AP_ListNotion->setText("当前列表中有"+QString::number(ui->AP_List->count())+"首歌曲");
    }
}

void AP_Widget::on_AP_List_itemClicked(QListWidgetItem *item)//单击跳转播放
{
    int cursor = ui->AP_List->row(item);//返回位置
    playlist->setCurrentIndex(cursor);//跳转
    player->play();
}

void AP_Widget::on_AP_List_itemDoubleClicked(QListWidgetItem *item)//双击删除
{
    int cursor = ui->AP_List->row(item);

    if (playlist->mediaCount() == 1) {
        // 删除唯一一个项目
        playlist->clear();
        player->stop();

        // 清理 urllist
        delete[] urllist;
        urllist = nullptr;

        // 更新界面
        ui->AP_NameLabel->setText("歌曲：未知");
        ui->AP_AlbumLabel->setText("专辑：未知");
        ui->AP_SingerLabel->setText("歌手：未知");
        QImage cover(":/new/prefix1/default.png");
        QPixmap defcover = QPixmap::fromImage(cover);
        ui->AP_CoverLabel->setPixmap(defcover.scaled(ui->AP_CoverLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->AP_TimeLabel->setText("0:00/0:00");
        ui->AP_ListNotion->setText("列表中没有歌曲");

        ui->AP_Lyric1->setStyleSheet("");
        ui->AP_Lyric4->setStyleSheet("");
        //字体大小都为12,中间一个加粗且变为14
        QFont other;
        other.setPointSize(12);
        ui->AP_Lyric1->setFont(other);
        ui->AP_Lyric2->setFont(other);
        ui->AP_Lyric3->setFont(other);
        ui->AP_Lyric5->setFont(other);
        ui->AP_Lyric6->setFont(other);
        ui->AP_Lyric7->setFont(other);
        QFont mid;
        mid.setPointSize(14);
        mid.setBold(true);
        ui->AP_Lyric4->setFont(mid);

        //样式：居中一个背景橙色，字体白色
        ui->AP_Lyric4->setStyleSheet("background-color:rgb(242,184,12);color:rgb(255,255,255)");

        //初始化内容
        ui->AP_Lyric4->setText("未能获取歌词信息");
        ui->AP_Lyric1->clear();
        ui->AP_Lyric2->clear();
        ui->AP_Lyric3->clear();
        ui->AP_Lyric5->clear();
        ui->AP_Lyric6->clear();
        ui->AP_Lyric7->clear();


        Lyric.Pub.clear();
        Lyric.Type = "Nothing";
        UpdateTime = 0;
        // 删除 item
        ui->AP_List->removeItemWidget(item);
        delete item;
        ui->AP_ListNotion->setText("列表中没有歌曲");
    }
    else {
        // 删除非唯一项目
        playlist->removeMedia(cursor);
        ui->AP_List->removeItemWidget(item);
        delete item;

        // 更新 urllist
        for (int i = cursor; i < playlist->mediaCount(); i++) {
            urllist[i] = urllist[i + 1];//cursor后数据前移
        }

        // 更新界面
        ui->AP_ListNotion->setText("列表中有 " + QString::number(playlist->mediaCount()) + " 首歌曲");
        if (cursor < playlist->mediaCount()) {
            playlist->setCurrentIndex(cursor);
            player->play();
        }
        else{
            playlist->setCurrentIndex(0);
            player->play();
        }
        //query:此处index更新不能正确触发，必须显式的更新信息
            info_change(playlist->currentIndex());
    }
}

void AP_Widget::show_song(int index){//高亮播放中的歌曲
    ui->AP_List->setCurrentRow(index);
}

void AP_Widget::lyric_move(qint64 position){//动态歌词
    if(Lyric.Type == "USLT"){//静态
        ui->AP_Lyric1->setStyleSheet("");
        ui->AP_Lyric4->setStyleSheet("");
        //字体大小都为12,第一行加粗且变为14为提示
        QFont other;
        other.setPointSize(12);
        ui->AP_Lyric2->setFont(other);
        ui->AP_Lyric3->setFont(other);
        ui->AP_Lyric4->setFont(other);
        ui->AP_Lyric5->setFont(other);
        ui->AP_Lyric6->setFont(other);
        ui->AP_Lyric7->setFont(other);
        QFont head;
        head.setPointSize(14);
        head.setBold(true);
        ui->AP_Lyric1->setFont(head);

        //样式：第一行背景橙色，字体白色
        ui->AP_Lyric1->setStyleSheet("background-color:rgb(242,184,12);color:rgb(255,255,255)");

        //设置内容
        ui->AP_Lyric1->setText("该歌曲仅提供静态歌词");
        int size = Lyric.Pub.size();
        ui->AP_Lyric2->setText(Lyric.Pub.value((UpdateTime/10)%size));
        ui->AP_Lyric3->setText(Lyric.Pub.value(((UpdateTime/10)+1)%size));
        ui->AP_Lyric4->setText(Lyric.Pub.value(((UpdateTime/10)+2)%size));
        ui->AP_Lyric5->setText(Lyric.Pub.value(((UpdateTime/10)+3)%size));
        ui->AP_Lyric6->setText(Lyric.Pub.value(((UpdateTime/10)+4)%size));
        ui->AP_Lyric7->setText(Lyric.Pub.value(((UpdateTime/10)+5)%size));
    }
    else if(Lyric.Type == "SYLT"){//动态
        ui->AP_Lyric1->setStyleSheet("");
        ui->AP_Lyric4->setStyleSheet("");
        //字体大小都为12,中间一个加粗且变为14
        QFont other;
        other.setPointSize(12);
        ui->AP_Lyric1->setFont(other);
        ui->AP_Lyric2->setFont(other);
        ui->AP_Lyric3->setFont(other);
        ui->AP_Lyric5->setFont(other);
        ui->AP_Lyric6->setFont(other);
        ui->AP_Lyric7->setFont(other);
        QFont mid;
        mid.setPointSize(14);
        mid.setBold(true);
        ui->AP_Lyric4->setFont(mid);

        //样式：居中一个背景橙色，字体白色
        ui->AP_Lyric4->setStyleSheet("background-color:rgb(242,184,12);color:rgb(255,255,255)");

        int pos = position/10;
        QMap<int,QString>::Iterator iter =Lyric.Pub.begin();
        while(iter != Lyric.Pub.end()){
            if((iter.key()>pos && iter.key() < pos+50)||(iter.key()<pos && iter.key()>pos-50)){//position 上下50厘秒搜索
                ui->AP_Lyric4->setText(iter.value());
                //向上一层
                if(iter != Lyric.Pub.begin()){
                    iter--;
                    ui->AP_Lyric3->setText(iter.value());
                    //向上两层
                    if(iter!=Lyric.Pub.begin()){
                        iter--;
                        ui->AP_Lyric2->setText(iter.value());
                        //向上三层
                        if(iter!=Lyric.Pub.begin()){
                            iter--;
                            ui->AP_Lyric1->setText(iter.value());
                            iter++;
                        }
                        else{
                            ui->AP_Lyric1->setText("");
                        }
                        iter++;
                    }
                    else{
                        ui->AP_Lyric2->setText("");
                        ui->AP_Lyric1->setText("");
                    }
                    iter++;
                }
                else{
                    ui->AP_Lyric3->setText("");
                    ui->AP_Lyric2->setText("");
                    ui->AP_Lyric1->setText("");
                }
                //向下一层
                iter++;
                if(iter != Lyric.Pub.end()){
                    ui->AP_Lyric5->setText(iter.value());
                    //向下两层
                    iter++;
                    if(iter !=Lyric.Pub.end()){
                        ui->AP_Lyric6->setText(iter.value());
                        //向下三层
                        iter++;
                        if(iter!=Lyric.Pub.end()){
                            ui->AP_Lyric7->setText(iter.value());
                            return;
                        }
                        else{
                            ui->AP_Lyric7->setText("");
                            return;
                        }
                    }
                    else{
                        ui->AP_Lyric6->setText("");
                        ui->AP_Lyric7->setText("");
                        return;
                    }
                }
                else{
                    ui->AP_Lyric5->setText("");
                    ui->AP_Lyric6->setText("");
                    ui->AP_Lyric7->setText("");
                    return;
                }
            }
            iter++;
        }
    }
    UpdateTime++;
}
