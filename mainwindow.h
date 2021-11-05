#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <thread>

namespace Ui {
class MainWindow;
}

class CTestThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void test1();
    void test2();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    CTestThread*   m_pthread;

    std::shared_ptr<std::thread> m_thread;
};

class CTestThread: public QObject {
    Q_OBJECT
public:
    CTestThread();

    void test_1();
    void test_2();

public slots:
    void on_test1();
    void on_test2();

private:
    QThread thread;
};

#endif // MAINWINDOW_H
