#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label_size = 20;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MainWindow w;
    while (labelList.size() != 0) {
        QLabel* label = labelList.at(0);
        label->hide();
        labelList.removeAt(0);
    }

    QRegularExpression re("^[0-1]{1,1000}$");

    QString text = ui->lineEdit->text();

    QRegularExpressionMatch match = re.match(text);
    if (match.hasMatch()) {
        ui->errorLabel->setText("");
        //std::string text_str = text.toStdString();
        size_of_arr = text.length();
        for (int i = 0; i < size_of_arr; i ++) {
            QLabel* label = new QLabel(this);
            label->setText(text.at(i));
            label->setAlignment(Qt::AlignCenter);
            label->setGeometry(w.width() / 2 - size_of_arr * (label_size + 5) / 2 + (label_size + 5) * i, w.height() / 2, label_size, label_size);
            label->show();
            labelList.append(label);
        }

        find_next();
        QEventLoop loop;
        QTimer::singleShot(300, &loop, SLOT(quit()));
        loop.exec();

        for (int i = 0; i < size_of_arr; i ++) {
            QLabel* label = labelList.at(i);
            label->setStyleSheet("background-color: green");
            QEventLoop loop;
            QTimer::singleShot(300, &loop, SLOT(quit()));
            loop.exec();
        }
    } else {
        ui->errorLabel->setText("input correct line");
    }
    //rearrangeList();
}

void MainWindow::find_next()
{
    QList<int> zeros_ind;

    for (int i = size_of_arr - 1; i >= 0; i--) {
        QLabel* label = labelList.at(i);

        if (label->text() == '1') {

            while(labelList.at(i - 1)->text() != '0') {

                if (zeros_ind.count() != 0) {
                    swapl(i, zeros_ind.at(0));
                    swapl(zeros_ind.at(0), i);
                    labelList.swapItemsAt(zeros_ind.at(0), i);
                    zeros_ind.removeAt(0);
                }
                i--;
                label->setStyleSheet("background-color: green");
                QEventLoop loop;
                QTimer::singleShot(1000, &loop, SLOT(quit()));
                loop.exec();
                label->setStyleSheet("");
                label = labelList.at(i);
            }
            swapl(i, i-1);
            swapl(i-1,i);
            labelList.swapItemsAt(i-1, i);
            break;
        }

        zeros_ind.append(i);

        label->setStyleSheet("background-color: green");
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, SLOT(quit()));
        loop.exec();
        label->setStyleSheet("");

    }
}

void MainWindow::swapl(int ind1, int ind2)
{
    QPropertyAnimation* animation = new QPropertyAnimation(labelList.at(ind1), "geometry");
    animation->setDuration(500);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setStartValue(QRect(labelList.at(ind1)->x(), labelList.at(ind1)->y(), label_size, label_size));
    animation->setEndValue(QRect(labelList.at(ind2)->x(), labelList.at(ind2)->y(), label_size, label_size));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


