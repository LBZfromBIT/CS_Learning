#include "ap_info.h"

AP_INFO::AP_INFO()
{
}

QTextCodec* AP_INFO::codeSet(unsigned char temp){
    QTextCodec* codec = nullptr;
    if (temp == 0x00) {
        // ISO-8859-1
        codec = QTextCodec::codecForName("ISO-8859-1");
    }
    else if (temp == 0x01) {
        // UTF-16
        codec = QTextCodec::codecForName("UTF-16");
    }
    else if (temp == 0x02) {
        // UTF-16BE
        codec = QTextCodec::codecForName("UTF-16BE");
    }
    else if (temp == 0x03) {
        // UTF-8
        codec = QTextCodec::codecForName("UTF-8");
    }
    else {
        // 默认使用 UTF-8
        codec = QTextCodec::codecForName("UTF-16");
    }
    return codec;
}

LyricInfo AP_INFO::GetLyric(QString url){
    QFile file(url);
    //打开
    if(!(file.open(QIODevice::ReadOnly))){
        qDebug() << "获取歌词失败";
        LyricInfo Lyric;
        Lyric.Type = "Nothing";
        return Lyric;
    }
    else{
        LyricInfo Lyric;

        QTextStream in(&file);
        in.setCodec("UTF-16");//以utf16读入
        QString data = in.readAll();//存入Qstring
        QStringList LyricList = data.split(QRegExp("\r|\n|\r\n"));//将data按行拆分

        QRegExp timespin("\\[\\d\\d\\S\\d\\d\\S\\d\\d\\]");//设置时间戳的表达式
        Lyric.Type = "SYLT";//默认为动态
        for(int i=0;i<LyricList.size()-1;i++){
            if(timespin.indexIn(LyricList[i])==-1){//一旦有一行没有时间戳，则认为是静态歌词
                Lyric.Type = "USLT";
                break;
            }
        }

        //分别处理
        if(Lyric.Type == "USLT"){//静态
            int line = LyricList.size();//歌词总数
            for(int i=0;i<line;i++){
                Lyric.Pub.insert(i,LyricList[i]);//行数为键，歌词为值
            }
            return Lyric;
        }
        else{//动态，type=="SYLT"
            int line = LyricList.size();//行数
            for(int i=0;i<line;i++){
                int min = (LyricList[i].mid(1,2)).toInt();
                int sec = (LyricList[i].mid(4,2)).toInt();
                int csec = (LyricList[i].mid(7,2)).toInt();
                int time = (min*60+sec)*100+csec;//获得单位为厘秒的时间戳
                QString word = LyricList[i].mid(10);
                Lyric.Pub.insert(time,word);
            }
            return Lyric;
        }

    }
}

MP3INFO AP_INFO::GetInfo(QString url)
{
    // 获得位置
    mURL = url;

    // 考虑到url可能有中文，设置utf-8编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // 使用QFile进行文件操作
    QFile file(mURL);

    // 当未能打开文件时，返回错误信息和一个空白实例
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: 未能打开文件" << mURL;
        MP3INFO blank;
        blank.PicFlag = false;
        return blank;
    }

    //实例化一个MP3INFO;
    MP3INFO info;
    // 创建一个缓冲区用于读取文件
    QByteArray buffer(10, '\0');

    // 读取文件头部
    file.read(buffer.data(), 10); // 读取前10个字节以检查文件头
    if (buffer.startsWith("ID3")) {
        // 文件头是ID3，继续处理

        // 计算ID3标签大小（单位：字节）
        ID3Size = (static_cast<unsigned char>(buffer[6]) & 0x7F) * 0x200000 +
                          (static_cast<unsigned char>(buffer[7]) & 0x7F) * 0x400 +
                          (static_cast<unsigned char>(buffer[8]) & 0x7F) * 0x80 +
                          (static_cast<unsigned char>(buffer[9]) & 0x7F);

        // 开始读取各帧
        int site = 10; // 读取位置
        while (site < ID3Size) {
            // 读取帧信息
            file.seek(site);
            buffer.resize(10);
            buffer.fill('\0');
            file.read(buffer.data(), 10); // 读取帧头
            QByteArray frameHeader = buffer.left(4); // 获取帧ID
            QByteArray frameSizeBytes = buffer.mid(4, 4); // 获取帧大小
            FrameByte = static_cast<unsigned char>(frameSizeBytes[0])*0x1000000+static_cast<unsigned char>(frameSizeBytes[1])*0x10000+static_cast<unsigned char>(frameSizeBytes[2])*0x100+static_cast<unsigned char>(frameSizeBytes[3]);
            site += 10; // 刷新site位置

            // 得到帧名
            QString FrameName = QString::fromLatin1(frameHeader.data());

            // 定位数据开始和结束位置
            int SSite = site;
            int ESite = SSite + FrameByte;
            site = ESite; // 刷新site位置

            if (FrameName == "APIC") {
                QByteArray temp(20, '\0');
                file.seek(SSite);

                if(FrameByte > 20){
                    file.read(temp.data(), 20);
                }
                else {
                    file.read(temp.data(), FrameByte);
                }

                int tag = 0;
                while(tag + 1 < temp.size()){
                    if((static_cast<unsigned char>(temp[tag]) == 0xff) && (static_cast<unsigned char>(temp[tag+1]) == 0xd8)){
                        info.PicFlag = true;
                        info.PicType = ".jpg";
                        break;
                    }
                    else if((static_cast<unsigned char>(temp[tag]) == 0x89) && (static_cast<unsigned char>(temp[tag+1]) == 0x50)){
                        info.PicFlag = true;
                        info.PicType = ".png";
                        break;
                   }
                   tag++;
                }

                int RemainLenth = FrameByte - tag;
                SSite += tag;
                file.seek(SSite);

                QByteArray imageData = file.read(RemainLenth);
                if(imageData.size() != RemainLenth){
                    qDebug() << "Warning: Incomplete image data read.";
                }

                info.PicURL = "../Cover/" + info.Name + info.PicType;

                QDir dir("../Cover");
                if(!dir.exists()){
                    dir.mkpath("../Cover");
                }

                QFile fw(info.PicURL);
                if(fw.open(QIODevice::WriteOnly | QIODevice::Truncate)){
                    qint64 bytesWritten = fw.write(imageData);
                    if (bytesWritten != imageData.size()) {
                        qDebug() << "Error: Not all data was written to file.";
                    }
                    fw.close();
                }
                else{
                    qDebug() << "Error: Unable to open file for writing.";
                }
            }
            else if (FrameName == "TIT2") { // 标题
                // 读取数据
                QByteArray data(FrameByte,'\0');
                file.seek(SSite);
                file.read(data.data(),FrameByte);

                // 解析编码信息
                QTextCodec* codec = codeSet(static_cast<unsigned char>(data[0]));

                // 处理编码标识和终止符
                int start = 1; // 起始位置默认跳过编码标识符长度1
                if (static_cast<unsigned char>(data[0]) == 0x01 || static_cast<unsigned char>(data[0]) == 0x02) {
                    // UTF-16 或 UTF-16BE
                    start = 3;  // 编码标识符长度1+BOM标识长度2
                }

                // 解码
                int end = FrameByte;
                QByteArray dataTemp = data.mid(start, end - start);
                info.Name = codec->toUnicode(dataTemp);
            }
            else if (FrameName == "TALB") { // 专辑名
                // 读取数据
                QByteArray data(FrameByte,'\0');
                file.seek(SSite);
                file.read(data.data(), FrameByte);

                // 解析编码信息
                QTextCodec* codec = codeSet(static_cast<unsigned char>(data[0]));

                // 处理编码标识和终止符
                int start = 1; // 起始位置默认跳过编码标识符长度1
                if (static_cast<unsigned char>(data[0]) == 0x01 || static_cast<unsigned char>(data[0]) == 0x02) {
                    // UTF-16 或 UTF-16BE
                    start = 3;  // 编码标识符长度1+BOM标识长度2
                }

                // 解码
                int end = FrameByte;
                QByteArray dataTemp = data.mid(start, end - start);
                info.Album = codec->toUnicode(dataTemp);
            }
            else if (FrameName == "TPE1") { // 歌手
                // 读取数据
                QByteArray data(FrameByte,'\0');
                file.seek(SSite);
                file.read(data.data(), FrameByte);

                // 解析编码信息
                QTextCodec* codec = codeSet(static_cast<unsigned char>(data[0]));

                // 处理编码标识符和BOM
                int start = 1; // 起始位置默认跳过编码标识符长度1
                if (static_cast<unsigned char>(data[0]) == 0x01 || static_cast<unsigned char>(data[0]) == 0x02) {
                    // UTF-16 或 UTF-16BE
                    start = 3;  // 编码标识符长度1+BOM标识长度2
                }

                // 解码
                int end = FrameByte;
                QByteArray dataTemp = data.mid(start, end - start);
                info.Singer = codec->toUnicode(dataTemp);
            }
            else if(FrameName == "USLT"||FrameName == "SYLT"){//歌词
                info.LyricFlag = true;
                //读入信息
                QByteArray data(FrameByte,'\0');
                file.seek(SSite);
                file.read(data.data(),FrameByte);

                //处理编码
                QTextCodec* codec = codeSet(static_cast<unsigned char>(data[0]));

                //处理编码标识符和BOM
                int start = 4; // 起始位置默认跳过编码标识符长度1和语言代码长度3
                if (static_cast<unsigned char>(data[0]) == 0x01 || static_cast<unsigned char>(data[0]) == 0x02) {
                    // UTF-16 或 UTF-16BE
                    start +=2;  // BOM标识长度2
                    //跳过描述，结尾符号\0\0
                    int desend = data.indexOf("\0\0",start);
                    start =desend+2;
                }
                else{//无BOM的
                    //跳过描述，结尾符号\0
                    int desend = data.indexOf('\0',start);
                    start =desend+1;
                }

                //写入本地
                info.LyricURL = "../Lyric/"+info.Name+".txt";

                QByteArray temp = data.mid(start,FrameByte-start);
                //截断末尾空白和可能的空字符
                int lastNonZeroPos = temp.size() - 1;
                while (lastNonZeroPos >= 0 && temp[lastNonZeroPos] == '\0') {
                    --lastNonZeroPos;
                }
                temp = temp.left(lastNonZeroPos + 1);//lNZ是数组下标，比数据小1

                QDir dir("../Lyric");
                if(dir.exists() == false){
                    dir.mkpath("../Lyric");
                }

                QFile fw(info.LyricURL);
                if(fw.open(QIODevice::WriteOnly|QIODevice::Truncate)){
                    QTextStream in(&fw);
                    in.setCodec(codec);
                    in<<codec->toUnicode(temp)<<endl;
                    fw.close();
                }
                else{
                    qDebug() << "写入歌词错误";
                }
                //获取歌词信息
                info.Lyric = GetLyric(info.LyricURL);
            }
        }

        // 设置其他信息
        info.URL = mURL;
    }
    else {
        // 文件头不是ID3，取消读入
        qDebug() << "未能获得信息";
        MP3INFO info;
        info.URL = mURL;
        info.Name = "未知";
        info.Album = "未知";
        info.Singer = "未知";
    }

    // 关闭文件
    file.close();

    // 返回处理结果
    return info;
}
