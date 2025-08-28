#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QClipboard>
#include <QGuiApplication>
#include "passwordlogic.h"
#include "passwordstrenght.h"
#include <QProgressBar>

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

private slots:
    void on_capital_letters_stateChanged(int state);

    void on_lowercase_letters_stateChanged(int state);

    void on_numbers_stateChanged(int state);

    void on_specials_stateChanged(int state);

    void on_spinBox_valueChanged(int len);

    void on_generate_clicked();

    void on_copy_in_bufer_clicked();

    void on_action_triggered();

    void on_action_2_triggered();

    void onLineEditContextMenu(const QPoint &pos);


private:
    Ui::MainWindow *ui;
    bool lowercase{false};
    bool uppercase{false};
    bool numbers{false};
    bool specials{false};
    int lenght{0};
};
#endif // MAINWINDOW_H
