#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
//#include <QPropertyAnimation>
//#include <QParallelAnimationGroup>
#include <QDebug>
#include <QMovie>
#include <QFileDialog>
#include <QList>
#include <QTimer>
#include <QTime>
#include <QFileInfoList>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QFileInfoList GetFileList(QString path);
      //读取图片
    void getPicsList();

private slots:
    void get_images();
    void move_image(int);
    void imageshow();   //自动播放
    void move_left();
    void move_right();
    void move_up();
    void move_down();

private:
    Ui::MainWindow *ui;
    QPixmap pix;        //定义图片变量用来设置图片的属性
    QPixmap pix2;
    QList<QString> *pics;//存储图片路径
    QList<QString> *qlist;//存储图片路径
    QTimer *timer;      //定义时间变量用来设置定时器
    QTimer *timer2;      //定义时间变量用来设置定时器
    QTimer *timer3;      //定义时间变量用来设置定时器
    QTimer *timer4;      //定义时间变量用来设置定时器
    QTimer *timer5;      //定义时间变量用来设置定时器
};

#endif // MAINWINDOW_H
