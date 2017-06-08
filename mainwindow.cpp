#include "mainwindow.h"
#include "ui_mainwindow.h"

QList<QString>::iterator it;//迭代器
int WIDTH = 800;
int HEIGHT = 480;

int arr_b[4][4] = {{-WIDTH,0,WIDTH, HEIGHT},
                   {WIDTH,0,WIDTH,HEIGHT},
                   {0,WIDTH,WIDTH,HEIGHT},
                   {0,-WIDTH,WIDTH,HEIGHT}};
int arr_e[4][4] = {{WIDTH,0,WIDTH,HEIGHT},
                   {-WIDTH,0,WIDTH,HEIGHT},
                   {0,-WIDTH,WIDTH,HEIGHT},
                   {0,WIDTH,WIDTH,HEIGHT}};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(get_images()));
    qlist = new QList<QString>;
    pics = new QList<QString>;

    ui->label->setGeometry(0,0,WIDTH, HEIGHT);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(pix);
    ui->label_2->setGeometry(0,0,WIDTH, HEIGHT);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_2->setPixmap(pix2);
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground, true);

    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(move_left()));
    timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(move_right()));
    timer4 = new QTimer(this);
    connect(timer4, SIGNAL(timeout()), this, SLOT(move_up()));
    timer5 = new QTimer(this);
    connect(timer5, SIGNAL(timeout()), this, SLOT(move_down()));

    timer->start(5000);
}

void MainWindow::getPicsList()
{
    QFileInfoList file_list = GetFileList("/udisk");
    QFileInfoList::iterator fit;//迭代器
    for(fit = file_list.begin(); fit != file_list.end(); fit++){
        if(fit->fileName().endsWith(".png")||
                fit->fileName().endsWith(".jpg")||
                fit->fileName().endsWith(".jpeg")||
                fit->fileName().endsWith(".gif")||
                fit->fileName().endsWith(".bmp") ){
            qlist->append(fit->filePath());
        }
    }
}

//打开文件
void MainWindow::get_images()
{
    getPicsList();
    if(qlist->size() == 0){
        pics->clear();
        ui->label->setText("无照片");
    }
    else{
        if(pics->empty()){
            pics = qlist;
            qlist = new QList<QString>;
            it = pics->begin();
        }
        imageshow();
    }
}

//显示文件
void MainWindow::imageshow()
{
    if((*it).endsWith(".gif")){
        QMovie* movie=new QMovie(*it);
        ui->label_2->setMovie(movie);
        movie->start();
    }else{
        pix.load(*it);
        pix = pix.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
        ui->label_2->setPixmap(pix);
    }
    if(++it == pics->end())
        it = pics->begin();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    move_image(qrand()%4);
}
//读取图片路径信息
QFileInfoList MainWindow::GetFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for(int i = 0; i != folder_list.size(); i++)
    {
        QString name = folder_list.at(i).absoluteFilePath();
        QFileInfoList child_file_list = GetFileList(name);
        file_list.append(child_file_list);
    }
    return file_list;
}

void MainWindow::move_image(int i)
{
    if(i == 0)
        timer2->start(50);
    else if(i == 1)
        timer3->start(50);
    else if(i == 2)
        timer4->start(50);
    else if(i == 3)
        timer5->start(50);
}

int c_w2 = 0;
int c_w_new2 = WIDTH;
void MainWindow::move_left()
{
    c_w2 -= 40;
    ui->label->move(c_w2, 0);
    c_w_new2 -= 40;
    ui->label_2->move(c_w_new2, 0);
    if(c_w_new2 <= 0){
        ui->label->move(-WIDTH, 0);
        ui->label_2->move(0, 0);
        timer2->stop();
        QLabel* t = ui->label;
        ui->label = ui->label_2;
        ui->label_2 = t;
        c_w2 = 0;
        c_w_new2 = WIDTH;
    }
}

int c_w3 = 0;
int c_w_new3 = -WIDTH;
void MainWindow::move_right()
{
    c_w3 += 40;
    ui->label->move(c_w3, 0);
    c_w_new3 += 40;
    ui->label_2->move(c_w_new3, 0);
    if(c_w_new3 >= 0){
        ui->label->move(WIDTH, 0);
        ui->label_2->move(0, 0);
        timer3->stop();
        QLabel* t = ui->label;
        ui->label = ui->label_2;
        ui->label_2 = t;
        c_w3 = 0;
        c_w_new3 = -WIDTH;
    }
}

int c_w4 = 0;
int c_w_new4 = -HEIGHT;
void MainWindow::move_up()
{
    c_w4 += 40;
    ui->label->move(0, c_w4);
    c_w_new4 += 40;
    ui->label_2->move(0, c_w_new4);
    if(c_w_new4 >= 0){
        ui->label->move(0, HEIGHT);
        ui->label_2->move(0, 0);
        timer4->stop();
        QLabel* t = ui->label;
        ui->label = ui->label_2;
        ui->label_2 = t;
        c_w4 = 0;
        c_w_new4 = -HEIGHT;
    }
}

int c_w5 = 0;
int c_w_new5 = HEIGHT;
void MainWindow::move_down()
{
    c_w5 -= 40;
    ui->label->move(c_w5, 0);
    c_w_new5 -= 40;
    ui->label_2->move(c_w_new5, 0);
    if(c_w_new5 <= 0){
        ui->label->move(0, -HEIGHT);
        ui->label_2->move(0, 0);
        timer5->stop();
        QLabel* t = ui->label;
        ui->label = ui->label_2;
        ui->label_2 = t;
        c_w5 = 0;
        c_w_new5 = HEIGHT;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
