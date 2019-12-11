#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QDebug"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette p;
    p.setColor(backgroundRole(), QColor(33, 33, 32));
    //прозрачность
    setWindowOpacity( 0.96 );
    this->setPalette(p);
    chek_buttom();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chek_buttom()
{
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digits_numbers()));

    connect(ui->pushButton_plusAmin,SIGNAL(clicked()),this,SLOT(operations()));
    connect(ui->pushButton_percent,SIGNAL(clicked()),this,SLOT(operations()));

    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(math_oper()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(math_oper()));
    connect(ui->pushButton_multip,SIGNAL(clicked()),this,SLOT(math_oper()));
    connect(ui->pushButton_division,SIGNAL(clicked()),this,SLOT(math_oper()));


    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_multip->setCheckable(true);
    ui->pushButton_division->setCheckable(true);
}

void MainWindow::digits_numbers()
{
   QPushButton * button = static_cast<QPushButton*>(sender());
   double all_numbers;
   QString new_label;

   if(ui->result_show->text().contains(".")&& button->text() == "0"){
       new_label = ui->result_show->text() + button->text();
   }else {
   all_numbers = (ui->result_show->text() + button->text()).toDouble();
   new_label = QString::number(all_numbers,'g',15);
}
   ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!ui->result_show->text().contains('.'))
    ui->result_show->setText(ui->result_show->text()+ '.');
}

void MainWindow::operations()
{
    QPushButton * button = static_cast<QPushButton*>(sender());
    double all_numbers;
    QString new_label;

    if(button->text()=="+/-")
    {
        all_numbers = (ui->result_show->text().toDouble());
        all_numbers*=(-1);
        new_label = QString::number(all_numbers,'g',15);
        ui->result_show->setText(new_label);
        ui->pushButton_minus->setCheckable(false);
        ui->pushButton_plus->setCheckable(false);
    }
    else if(button->text()=="%")
    {
        all_numbers = (ui->result_show->text().toDouble());
        all_numbers*=0.01;
        new_label = QString::number(all_numbers,'g',15);
        ui->result_show->setText(new_label);
    }
}

void MainWindow::on_pushButton_equally_released()
{
    double labelNumber=0,secondNum=0;
    secondNum = ui->result_show->text().toDouble();
    QString newlabel;

    if (flag){
        str = str + QString::number(num_first);
        flag=false;
    }

    if(ui->pushButton_plus->isCheckable())
    {
        qDebug()<<"+";
        labelNumber = num_first + secondNum;
        str = str + "+" + QString::number(secondNum);
        newlabel = QString::number(labelNumber,'g',15);
        ui->result_show->setText(newlabel);
        ui->pushButton_plus->setCheckable(false);
    }
    else if(ui->pushButton_minus->isCheckable())
    {
        qDebug()<<"-";
        labelNumber = num_first - secondNum;
        str = str + "-" + QString::number(secondNum);
        newlabel = QString::number(labelNumber,'g',15);
        ui->result_show->setText(newlabel);
        ui->pushButton_minus->setCheckable(false);
    }
    else if(ui->pushButton_multip->isCheckable())
    {
        qDebug()<<"*";
        labelNumber = num_first * secondNum;
        str = str + "*" + QString::number(secondNum);
        newlabel = QString::number(labelNumber,'g',15);
        ui->result_show->setText(newlabel);
        ui->pushButton_multip->setCheckable(false);
    }
    else if(ui->pushButton_division->isCheckable())
    {
        qDebug()<<"%";
        if (secondNum==0.0){
            qDebug()<<"!";
            ui->result_show->setText("Деление на ноль невозможно");
        }else{
        labelNumber = num_first / secondNum;
        newlabel = QString::number(labelNumber,'g',15);
        str = str + "/" + QString::number(secondNum);
        ui->result_show->setText(newlabel);
        ui->pushButton_division->setCheckable(false);
        }
    }

 ui->result_history->setText(str);
}

void MainWindow::math_oper()
{
    QPushButton * button = static_cast<QPushButton*>(sender());
    num_first = ui->result_show->text().toDouble();
    ui->result_show->setText(" ");

    button->setCheckable(true);
}

void MainWindow::on_pushButton_clearStr_clicked()
{
    ui->result_show->setText("0");
    str="";
    flag=true;
    ui->result_history->setText("");
}


void MainWindow::on_pushButton_del_clicked()
{
  // не работает
    QString new_label;
    new_label = ui->result_show->text();
    int len =new_label.length();
    new_label[len]=0;

   ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_fact_clicked()
{
    QString new_label;
    int  n =  ui->result_show->text().toInt();
    int res = 1;
      for (int i = 1; i <= n; i++) {
        res = res * i;
      }
      qDebug()<<res;
    new_label = QString::number(res,'g',15);
     ui->result_show->setText(new_label);
}
