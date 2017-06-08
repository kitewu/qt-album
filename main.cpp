#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    MainWindow w;
    w.setGeometry(0, 0, 800, 480);
//    QPropertyAnimation *animation = new QPropertyAnimation(&w,"windowOpacity");
//    animation->setDuration(1000);
//    animation->setStartValue(0);
//    animation->setEndValue(1);
//    animation->start();
    w.show();

    return a.exec();
}
