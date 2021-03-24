#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QList>
#include <QLabel>
#include <QDesktopWidget>
#include <iostream>
#include <QTextStream>
#include <string>
#include <QThread>
#include <QTimer>
#include <QEventLoop>
#include <QParallelAnimationGroup>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

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
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QList<QLabel*> labelList;
    int label_size, size_of_arr;

    void find_next();
    void swapl(int ind1, int ind2);
};
#endif // MAINWINDOW_H
