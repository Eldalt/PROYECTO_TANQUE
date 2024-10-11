#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 //-------------------------------------------------------------------//
  //seteo el valor de forma instantanea.
  //connect(ui->input_level, SIGNAL(textChanged(const QString &)), this, SLOT(set_tank_level()));
    // Conectar el slot al QLineEdit en el constructor o en la configuración del UI
    //connect(ui->input_capacity, SIGNAL(editingFinished()), this, SLOT(set_tank_capacity()));
    ui->input_qin_dial->setValue(0);
    ui->input_qout_dial->setValue(0);

    connect(timer, SIGNAL(timeout()), this, SLOT(simulacion()));  // Conectamos la señal timeout() al slot updateSimulation()
    //timer->start(1000);  // El temporizador emitirá la señal timeout() cada 1000 ms (1 segundo)
    connect(ui->set_boton_tiempo, SIGNAL(clicked()), this, SLOT(tiempo_timer()));
    // Conectar los diales y QLineEdit para caudal de entrada y salida
    connect(ui->input_qin_dial, SIGNAL(valueChanged(int)), this, SLOT(actualizarcaudalentrada(int)));
    connect(ui->input_qout_dial, SIGNAL(valueChanged(int)), this, SLOT(actualizarcaudalsalida(int)));
    connect(ui->input_qin, SIGNAL(editingFinished()), this, SLOT(actualizarCaudalEntradaConTexto()));
    connect(ui->input_qout, SIGNAL(editingFinished()), this, SLOT(actualizarCaudalSalidaConTexto()));
     ui->tank->setStyleSheet("QProgressBar::chunk { background-color: red; }");

}

MainWindow::~MainWindow()
{
    delete ui;
}
/*void MainWindow::set_tank_level()
{
    ui->tank->setValue(ui->input_level->text().toInt());
}*/

/*void MainWindow::set_tank_capacity()
{
    //obtengo el nuevo valor del tanque
    ui->tank->setValue(0);
    int new_capacity=ui->input_capacity->text().toInt();
    // Actualizar la capacidad máxima de la barra de nivel del tanque (QProgressBar)
    ui->tank->setRange(0, new_capacity);
     // Aquí es donde se actualiza la variable interna capacity
    capacidad_tank=new_capacity;
}*/
void MainWindow::actualizarcaudalentrada(int value)
{
    int caudal_max_entrada = ui->input_qin->text().toDouble();
    qin = caudal_max_entrada * (value / 100.0);
    qDebug() << "Nuevo caudal de entrada (Qin): " << qin;

}


void MainWindow::actualizarcaudalsalida(int value)
{
    int caudal_max_salida = ui->input_qout->text().toDouble();
    qout = caudal_max_salida * (value / 100.0);
    qDebug() << "Nuevo caudal de salida (Qout): " << qout;
}


void MainWindow::simulacion()
{   capacidad_tank=ui->input_capacity->text().toInt();
    ui->tank->setRange(0, capacidad_tank);
    //if(ui->tank->value()<capacidad_tank)
    //ui->tank->setValue(ui->tank->value());
    //leeo el tanque
    int nivel_actual=ui->tank->value();
    //obtengo el intervalo de tiempo esta en ms
    double clock1=timer->interval();
    //lo convierto a segundos
    double clock2=clock1/1000.0;
    //obtener el porcentaje de apertura de los diales(valor de 0 100)
    //int porcentaje_entrada=ui->input_qin_dial->value();
    //int porcentaje_salida=ui->input_qout_dial->value();
    //caluclar la cantidad de agua que entra y sale basado en el porcentaje de apertura de los diales
    double agua_que_entra=(qin*clock2);
    double agua_que_sale=(qout*clock2);
    //ajusto el nivel del tanque
    int nuevo_nivel=nivel_actual+agua_que_entra-agua_que_sale;
    // Asegurarse de que el nivel no exceda la capacidad del tanque ni sea negativo
    if (nuevo_nivel > capacidad_tank)
    {
        nuevo_nivel = capacidad_tank;
    }
    else if (nuevo_nivel < 0)
    {
        nuevo_nivel = 0;
    }

    // Actualizar el nivel del tanque en la interfaz
    ui->tank->setValue(nuevo_nivel);

}

void MainWindow::tiempo_timer()
{
    int intervalo = ui->tt->text().toInt();
    if (intervalo > 0)
    {
        timer->start(intervalo);
        qDebug() << "Temporizador iniciado con intervalo:" << intervalo;
    } else
    {
        qDebug() << "Intervalo no válido";
    }




}

