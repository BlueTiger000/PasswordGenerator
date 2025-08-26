#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setValue(0);
    ui->progressBar->setStyleSheet("color: red;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_capital_letters_stateChanged(int state)
{
    if (state == Qt::Checked) {
        uppercase = true;
    }
    else if(state == Qt::Unchecked)
    {
       uppercase = false;
    }
}


void MainWindow::on_lowercase_letters_stateChanged(int state)
{
    if (state == Qt::Checked) {
        lowercase = true;
    }
    else if(state == Qt::Unchecked)
    {
        lowercase = false;
    }
}


void MainWindow::on_numbers_stateChanged(int state)
{
    if (state == Qt::Checked) {
        numbers = true;
    }
    else if(state == Qt::Unchecked)
    {
        numbers = false;
    }
}


void MainWindow::on_specials_stateChanged(int state)
{
    if (state == Qt::Checked) {
        specials = true;
    }
    else if(state == Qt::Unchecked)
    {
        specials = false;
    }
}



void MainWindow::on_spinBox_valueChanged(int arg1)
{
    lenght = ui->spinBox->value();
    qDebug() << "Получено после обновления интерфейса:" << lenght;

}




void MainWindow::on_generate_clicked()
{
    PasswordGenerator password;
    PasswordStrenght password_strenght;
    int value;
    if (lenght == 0) {
        ui->statusbar->showMessage("Не указана длина", 2000);
        ui->statusbar->setStyleSheet("color: red;");
        return;
    }
    else if(lenght < 6){
        ui->statusbar->showMessage("Слишком короткий пароль", 2000);
        ui->statusbar->setStyleSheet("color: red;");
        return;
    }
    else if(uppercase == false && lowercase == false && numbers == false && specials == false){
        ui->statusbar->showMessage("Не выбраны параметры", 2000);
        ui->statusbar->setStyleSheet("color: red;");
        return;
    }
    else{
    QString pass = password.PasswordGenerating(lenght, uppercase, lowercase, numbers, specials);
    ui->pass_line->setText(pass);
    ui->pass_line->setStyleSheet("color: black;");

    QString strenght = password_strenght.Strenght(pass);
    ui->result->setText(strenght);
    if(strenght == "Очень слабый" || strenght == "Слабый"){
        ui->result->setStyleSheet("color: red;");
        ui->progressBar->setStyleSheet("color: red;");
        value = 20;
    }
    if(strenght == "Средний"){
        ui->result->setStyleSheet("color: orange;");
        ui->progressBar->setStyleSheet("color: orange;");
        value = 50;
    }
    if(strenght == "Надежный" || strenght == "Очень надежный"){
        ui->result->setStyleSheet("color: green;");
        ui->progressBar->setStyleSheet("color: green;");
        if(strenght == "Надежный"){
            value = 80;
        }
        else if(strenght == "Очень надежный"){
            value = 100;
        }
    }
    QString color;
    if (value == 20) {
        color = "#e74c3c"; // Красный
    } else if (value == 50) {
        color = "#f39c12"; // Оранжевый
    } else {
        color = "#2ecc71"; // Зеленый
    }

    QString style = QString("QProgressBar::chunk { background-color: %1;}").arg(color);

    ui-> progressBar->setStyleSheet(style);
    ui->progressBar->setValue(value);
    }
}


void MainWindow::on_copy_in_bufer_clicked()
{
     QString text = ui->pass_line->text();
    if (text.isEmpty()) {
        ui->statusbar->showMessage("Нет текста для копирования!", 2000);
        ui->result->setStyleSheet("color: red;");
        return;
    }
    // Копируем в буфер обмена
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);

    // Показываем подтверждение
    ui->statusbar->showMessage("Текст скопирован в буфер обмена ✓", 2000);
    ui->statusbar->setStyleSheet("color: black;");
}

