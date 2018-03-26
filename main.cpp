


#include <QCoreApplication>
#include <QStringList>
#include <QRegExp>
#include <QFile>
#include <QDebug>

QStringList listTime,listOther;

int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);
    QFile fpx("/home/alex/lcx/work_dir/perceptin_test/zuluko_mono_robot.INFO");
    if(!fpx.open(QIODevice::ReadOnly))
        qDebug()<<"can not open";
    while(!fpx.atEnd()){
        QString pattern("Reading sensor data done");
        char buf[1024];
        fpx.readLine(buf,sizeof(buf));
        QString strTemp = QString(buf);
        bool i =  strTemp.contains(pattern,Qt::CaseInsensitive);
        if(i){
            //            QString pattern("([0-9]{2}\:[0-9]{2}\:[0-9]{2}\.[0-9]{6})(?:\\s*)(\\d{3})");
            QString pattern("(?:\\s)([0-9\:\.]*)(?:\\s*)(\\d{3})");
            QRegExp rx(pattern);
            int pos2 = 0;
            while ((pos2 = rx.indexIn(strTemp, pos2)) != -1) {
                listTime << rx.cap(1);          // 第一个捕获到的文本,即时间
                listOther<<rx.cap(2);
                pos2 += rx.matchedLength(); // 上一个匹配的字符串的长度
            }
        }
    }
//    qDebug()<<listTime.size()<<" "<<listOther.size();
    for(int i=0;i<listTime.size();i++){
        qDebug()<<"time: "<<listTime.at(i)<<"   thread_id: "<<listOther.at(i);
    }

    return a.exec();
}


