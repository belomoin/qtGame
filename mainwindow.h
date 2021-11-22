#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define HEIGHT 700
#define WIDTH 750
#define MAXSPEED 15
#define DIFSPEED 50

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    int score = 0;

};
#endif // MAINWINDOW_H
