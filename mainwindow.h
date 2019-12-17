#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
   void digitClicked();
   void digits_numbers();
   void on_pushButton_dot_clicked();
   void operations();
   void math_oper();
   void on_pushButton_equally_released();
   void on_pushButton_clearStr_clicked();
   void on_pushButton_del_clicked();
   void on_pushButton_fact_clicked();
   void unaryOperatorClicked();
   void on_pushButton_clear_clicked();

private:
    double num_first;
    double num_last;
    QString str;
    bool flag = true;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
