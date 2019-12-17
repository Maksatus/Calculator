#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QDebug"
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QPalette p;
   p.setColor(backgroundRole(), QColor(33, 33, 32));
   //прозрачность
   setWindowOpacity( 0.96 );
   this->setPalette(p);
   num_last = 0;
   num_first = 0;

        connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(digitClicked()));
        connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(digitClicked()));
        connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(digitClicked()));
        connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(digitClicked()));
        connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(digitClicked()));
        connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(digitClicked()));
        connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(digitClicked()));
        connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(digitClicked()));
        connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(digitClicked()));
        connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(digitClicked()));

        connect(ui->pushButton_plusAmin,SIGNAL(clicked()),this,SLOT(operations()));

        connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(math_oper()));
        connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(math_oper()));
        connect(ui->pushButton_multip,SIGNAL(clicked()),this,SLOT(math_oper()));
        connect(ui->pushButton_division,SIGNAL(clicked()),this,SLOT(math_oper()));


        connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(unaryOperatorClicked()));
        connect(ui->pushButton_fraction,SIGNAL(clicked()),this,SLOT(unaryOperatorClicked()));
        connect(ui->pushButton_pow,SIGNAL(clicked()),this,SLOT(unaryOperatorClicked()));


        ui->pushButton_minus->setCheckable(false);
        ui->pushButton_plus->setCheckable(false);
        ui->pushButton_multip->setCheckable(false);
        ui->pushButton_division->setCheckable(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digitClicked()
{
    QPushButton * button = static_cast<QPushButton*>(sender());
       double all_numbers;
       QString new_label;

       if(ui->result_show->text().contains(".")&& button->text() == "0"){
           new_label = ui->result_show->text() + button->text();
       }else {
       all_numbers = (ui->result_show->text() + button->text()).toDouble();
       new_label = QString::number(all_numbers,'g',6);
    }
       ui->result_show->setText(new_label);
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
   new_label = QString::number(all_numbers,'g',6);
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
        new_label = QString::number(all_numbers,'g',6);
        ui->result_show->setText(new_label);
//        ui->pushButton_minus->setCheckable(false);
//        ui->pushButton_plus->setCheckable(false);
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
        newlabel = QString::number(labelNumber,'g',6);
        ui->result_show->setText(newlabel);
        ui->pushButton_plus->setCheckable(false);
    }
    else if(ui->pushButton_minus->isCheckable())
    {
        qDebug()<<"-";
        labelNumber = num_first - secondNum;
        str = str + "-" + QString::number(secondNum);
        newlabel = QString::number(labelNumber,'g',6);
        ui->result_show->setText(newlabel);
        ui->pushButton_minus->setCheckable(false);
    }
    else if(ui->pushButton_multip->isCheckable())
    {
        qDebug()<<"*";
        labelNumber = num_first * secondNum;
        str = str + "*" + QString::number(secondNum);
        newlabel = QString::number(labelNumber,'g',6);
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
        newlabel = QString::number(labelNumber,'g',6);
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
    num_last = 0;
    num_first = 0;
    ui->result_show->setText("0");
    str= " ";
    flag=true;
    ui->result_history->setText("");
}


void MainWindow::on_pushButton_del_clicked()
{
    QString new_label;
    new_label = ui->result_show->text();
    new_label.chop(1);

    if(ui->result_show->text()=="0")
    {
       new_label= "0";
    }
   ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_fact_clicked()
{
    QString new_label;
    size_t  n =  ui->result_show->text().toUInt();
    size_t res = 1;
      for (size_t i = 1; i <= n; i++) {
        res = res * i;
      }
      qDebug()<<res;
    new_label = QString::number(res,'g',6);
     ui->result_show->setText(new_label);
}


void MainWindow::unaryOperatorClicked()
{
    QPushButton * button = static_cast<QPushButton*>(sender());
    double all_numbers= 0,result = 0;
    QString new_label;
    bool f =false;

    if (button->text()=="√x")
    {
        qDebug()<<"sqrt";
        all_numbers = (ui->result_show->text().toDouble());
        if (all_numbers < 0.0) {
           f=true;
        }else{
        result = std::sqrt(all_numbers);
        str = str + "+ sqrt(" + QString::number(all_numbers)+")";
        }
    }

    else if (button->text()=="x^2")
    {
        qDebug()<<"x^2";
        all_numbers = (ui->result_show->text().toDouble());
        result = std::pow(all_numbers, 2);
        str = str + "(" + QString::number(all_numbers)+")^2";
    }
    else if (button->text()=="1/x")
    {
        qDebug()<<"1/x";
        all_numbers = (ui->result_show->text().toDouble());
        if (ui->result_show->text()== "0")
        {
            f=true;
        }else
        {
            result = 1.0 / all_numbers;
            str = str + "1/(" + QString::number(all_numbers)+")";
        }
    }

    if(f){
       new_label="Введены неверные данные‬";
    }else{
     new_label = QString::number(result,'g',6);
    }
    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->result_show->setText("0");
}
