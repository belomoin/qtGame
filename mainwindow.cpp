#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTimer>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(HEIGHT,WIDTH);
    this->setWindowTitle(QString("%1 points").arg(score));

    QTimer* mainTimer = new QTimer();   // таймер появления кнопок
    mainTimer->start();

    connect(mainTimer,&QTimer::timeout,this,[this,mainTimer](){

        mainTimer->setInterval(rand() % 1000);  // чтобы кнопки появлялись через разные интервалы времени
        QTimer* timer = new QTimer();   // таймер отвечающий за скорость кнопки
        timer->start(MAXSPEED + rand() % DIFSPEED);

        /* Создание кнопки */
        QPushButton* btn = new QPushButton(this);
        btn->setFixedSize(20,20);
        btn->setText("*");
        btn->move(rand()%(HEIGHT - 20),rand()%100);
        btn->show();

        /* обработка нажатия */
        connect(btn,&QPushButton::pressed,btn,[btn,this](){
            if(this->windowTitle().contains("YOU LOOSE!") == 0) // после проигрыша кнопочки не работают
            {
                btn->deleteLater();
                this->setWindowTitle(QString("%1 points").arg(++score));
            }

        });

        /* движение вниз */
        connect(timer,&QTimer::timeout,btn,[btn,this](){
            if(btn->pos().y() > WIDTH){   // когда достигли дна
                btn->deleteLater();
                this->setWindowTitle(QString("YOU LOOSE! ... %1 points").arg(score));
                QPalette pal(this->palette());
                pal.setColor(QPalette::Background, Qt::red);
                this->setAutoFillBackground(true);
                this->setPalette(pal);
            }

            /* убегание от курсора */

            /* при подходе справа*/
            if(QCursor::pos().x() - this->x() - btn->pos().x() < 50
                    && QCursor::pos().x() - this->x() - btn->pos().x() > 10
                    && abs(QCursor::pos().y() - this->y() - btn->pos().y() - 40) < 30)
            {
                btn->move(btn->pos().x() - 1,btn->pos().y());
            };
            /* при подходе слева */
            if(QCursor::pos().x() - this->x() - btn->pos().x() > - 50
                    && QCursor::pos().x() - this->x() - btn->pos().x() < 10
                    && abs(QCursor::pos().y() - this->y() - btn->pos().y() - 40) < 30)
            {
                btn->move(btn->pos().x() + 1,btn->pos().y());
            };

            /* зацикливание перемещения по горизонтали */
            if(btn->pos().x() < - 10)
                btn->move(btn->pos().x() + (HEIGHT - 10),btn->pos().y());
            if(btn->pos().x() > (HEIGHT - 10))
                btn->move(btn->pos().x() - (HEIGHT - 10),btn->pos().y());


            btn->move(btn->pos().x(),btn->pos().y() + 1);
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

