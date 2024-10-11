#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//------------------------------------//
    QTimer *timer = new QTimer(this);

private:
    Ui::MainWindow *ui;
//-------------------------------------------------------------------------//
public slots:
    //void set_tank_level();
   // void set_tank_capacity();
    void simulacion();
    void tiempo_timer();
    void actualizarcaudalentrada(int value);
    void actualizarcaudalsalida(int value);
private:
    int capacidad_tank;//capacidad del tanque
    int qin =0;//Caudal maximo de entrada
    int qout=0;//caudal maximo de salida

};
#endif // MAINWINDOW_H
