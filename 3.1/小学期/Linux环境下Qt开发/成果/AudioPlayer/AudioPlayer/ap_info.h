#ifndef AP_INFO_H
#define AP_INFO_H


#include <cstring>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QTextCodec>
#include <iostream>
#include <QFont>
#include <QMap>
#include <QRegExp>

struct LyricInfo{//储存歌词信息的结构体
    QString Type = "Nothing";
    QMap<int,QString> Pub;
};

//一个储存歌曲信息的结构体
struct MP3INFO{
    QString URL;//文件本地位置
    QString Name;//歌曲名字
    QString Album;//专辑名称
    QString Singer;//歌手名字
    bool PicFlag = false;//是否有封面
    QString PicType;//封面类型
    QString PicURL;//封面位置
    bool LyricFlag = false;//是否有歌词
    QString LyricURL;
    LyricInfo Lyric;
};

//实现信息提取及储存操作的类
class AP_INFO
{
    public:
        AP_INFO();
        QString mURL;//歌曲url
        int ID3Size;//计算得出的ID3字节数
        int FrameByte;//计算得出的帧字节数,不断更新
        QTextCodec* codeSet(unsigned char temp);//返回数据编码信息的函数
        LyricInfo GetLyric(QString url);//从歌词文档中获取歌词信息并写入本地
        MP3INFO GetInfo(QString url);//获取歌曲信息函数，参数（本地url,歌曲编号）
};

#endif // AP_INFO_H
