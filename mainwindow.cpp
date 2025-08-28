#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pass_line->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->pass_line, &QLineEdit::customContextMenuRequested,
            this, &MainWindow::onLineEditContextMenu);

    //Устанавливаем прогрессбар в нужное значение(я не нашла как это сделать через дизайнер так что прописала здесь)
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setValue(0);
    ui->progressBar->setStyleSheet("color: red;");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLineEditContextMenu(const QPoint &pos)
{
    QLineEdit *pass_line = qobject_cast<QLineEdit*>(sender());
    if (!pass_line) return;

    //Создаем контексное меню
    QMenu menu;

    // Копировать
    //Создаем действие с текстом "Копировать"
    QAction *copyAction = menu.addAction("Копировать");
    //Проверяем не пустая ли строка
    copyAction->setEnabled(!pass_line->text().isEmpty());
    //Подключаем копирование
    connect(copyAction, &QAction::triggered, [pass_line]() {
        QApplication::clipboard()->setText(pass_line->text());
        qDebug() << "Пароль скопирован";
    });

    // Очистить
    //Тоже самое но с "Очистить"
    QAction *clearAction = menu.addAction("Очистить");
    clearAction->setEnabled(!pass_line->text().isEmpty() && !pass_line->isReadOnly());
    connect(clearAction, &QAction::triggered, [pass_line]() {
        pass_line->clear();
    });
    //Отображение меню
    menu.exec(pass_line->mapToGlobal(pos));
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
        //Создаем пул букв и символов
        QString charset = "";
        if (lowercase) charset += "abcdefghijklmnopqrstuvwxyz";
        if (uppercase) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        if (numbers)     charset += "0123456789";
        if (specials)    charset += "!@#$%^&*";

    QString pass = password.PasswordGenerating(charset, lenght);
    ui->pass_line->setText(pass);
    ui->pass_line->setStyleSheet("color: black;");

    QString strenght = password_strenght.Strenght(pass);
    ui->result->setText(strenght);
    if(strenght == "Очень слабый" || strenght == "Слабый"){
        ui->result->setStyleSheet("color: red;");
        value = 20;
    }
    if(strenght == "Средний"){
        ui->result->setStyleSheet("color: orange;");
        value = 50;
    }
    if(strenght == "Надежный" || strenght == "Очень надежный"){
        ui->result->setStyleSheet("color: green;");
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


void MainWindow::on_action_triggered()
{
    QApplication::quit();
}


void MainWindow::on_action_2_triggered()
{
    ui->pass_line->setText("Программа генерирует пароль, чтобы ей воспользоваться выберите нужные параметры и нажмите кнопку 'Сгенерировать'.");
}

