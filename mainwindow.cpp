#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadpool.h"
#include <QThread>
#include <QDebug>
#include <thread>
#include <future>
#include <chrono>
#include <iostream>

using namespace std;

void fun_thread(MainWindow* mainw) {
    int i=50;
    while (--i) {
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
        qDebug()<<" i "<<i;
    }
}

void set_int(std::promise<int>& pro) {
    qDebug() << "set thread exit value: "<<11<<"\n";
    pro.set_value_at_thread_exit(11);
    std::this_thread::sleep_for(std::chrono::microseconds(3000));
}

void print_int(std::future<int>& fut) {
    qDebug() << "ready get value"<<"\n";
    int x = fut.get(); // 获取共享状态的值.
    qDebug() << "value: " << x << '\n'; // 打印 value: 10.
}

void fun1(int slp)
{
    printf("  hello, fun1 !  %d\n" ,std::this_thread::get_id());
    if (slp>0) {
        printf(" ======= fun1 sleep %d  =========  %d\n",slp, std::this_thread::get_id());
        std::this_thread::sleep_for(std::chrono::milliseconds(slp));
        //Sleep(slp );
    }
}

struct gfun {
    int operator()(int n) {
        printf("%d  hello, gfun !  %d\n" ,n, std::this_thread::get_id() );
        return 42;
    }
};

class A {    //函数必须是 static 的才能使用线程池
public:
    static int Afun(int n = 0) {
        std::cout << n << "  hello, Afun !  " << std::this_thread::get_id() << std::endl;
        return n;
    }

    static std::string Bfun(int n, std::string str, char c) {
        std::cout << n << "  hello, Bfun !  "<< str.c_str() <<"  " << (int)c <<"  " << std::this_thread::get_id() << std::endl;
        return str;
    }
};

void test_threadpool() {
    try {
            std::threadpool executor{ 50 };
            A a;
            std::future<void> ff = executor.commit(fun1,0);
            std::future<int> fg = executor.commit(gfun{},0);
            std::future<int> gg = executor.commit(A::Afun, 9999); //IDE
            std::future<std::string> gh = executor.commit(A::Bfun, 9998,"mult args", 123);
            std::future<std::string> fh = executor.commit([]()->std::string { std::cout << "hello, fh !  " << std::this_thread::get_id() << std::endl; return "hello,fh ret !"; });

            std::cout << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::microseconds(900));

            for (int i = 0; i < 50; i++) {
                executor.commit(fun1,i*100 );
            }
            std::cout << " =======  commit all ========= " << std::this_thread::get_id()<< " idlsize="<<executor.idlCount() << std::endl;

            std::cout << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));

            gg.get();
            gh.get();
            std::cout << gg.get() << "  " << gh.get().c_str()<< "  " << std::this_thread::get_id() << std::endl;

            ff.get(); //调用.get()获取返回值会等待线程执行完,获取返回值
            std::cout << fg.get() << "  " << fh.get().c_str()<< "  " << std::this_thread::get_id() << std::endl;

            std::cout << " =======  sleep ========= " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));

            std::cout << " =======  fun1,55 ========= " << std::this_thread::get_id() << std::endl;
            executor.commit(fun1,55).get();    //调用.get()获取返回值会等待线程执行完

            std::cout << "end... " << std::this_thread::get_id() << std::endl;


            std::threadpool pool(4);
            std::vector< std::future<int> > results;

            for (int i = 0; i < 8; ++i) {
                results.emplace_back(
                    pool.commit([i] {
                        std::cout << "hello " << i << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        std::cout << "world " << i << std::endl;
                        return i*i;
                    })
                );
            }
            std::cout << " =======  commit all2 ========= " << std::this_thread::get_id() << std::endl;

            for (auto && result : results)
                std::cout << result.get() << ' ';
            std::cout << std::endl;
            return ;
        }
    catch (std::exception& e) {
        std::cout << "some unhappy happened...  " << std::this_thread::get_id() << e.what() << std::endl;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"main thread id "<<QThread::currentThreadId();

    m_pthread = new CTestThread();
    //队列方式   调用槽
    connect(this, SIGNAL(test1()), m_pthread, SLOT(on_test1()), Qt::QueuedConnection);
    connect(this, SIGNAL(test2()), m_pthread, SLOT(on_test2()), Qt::QueuedConnection);

    std::promise<int> prom; // 生成一个 std::promise<int> 对象.
    std::future<int> fut = prom.get_future(); // 和 future 关联.
    std::thread t(set_int, std::ref(prom));
    std::thread t1(print_int, std::ref(fut)); // 将 future 交给另外一个线程t.

    t.join();
    t1.join();

    m_thread = std::shared_ptr<std::thread>(new std::thread(fun_thread, this));

    qDebug()<<" thread run ";

}

MainWindow::~MainWindow()
{
    if (m_thread->joinable())
        m_thread->join();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //队列方式调用槽，被调用的槽在次线程中执行
    emit test1();
}

void MainWindow::on_pushButton_2_clicked()
{
    //队列方式调用槽，被调用的槽在次线程中执行
    emit test2();
}

void MainWindow::on_pushButton_3_clicked()
{
    //主线程直接调用槽，被调用的槽在主线程中执行
    m_pthread->test_1();
}

///[1]
CTestThread::CTestThread()
{
    this->moveToThread(&thread);
    qDebug()<<" thread id "<<QThread::currentThreadId();
    thread.start();
}

void CTestThread::test_1()
{
    qDebug()<<"test_1 thread id "<<QThread::currentThreadId();
}

void CTestThread::test_2()
{
    qDebug()<<"test_2 thread id "<<QThread::currentThreadId();
}

void CTestThread::on_test1()
{
    qDebug()<<"on_test1 thread id "<<QThread::currentThreadId();
    test_1();
}

void CTestThread::on_test2()
{
    qDebug()<<"on_test2 thread id "<<QThread::currentThreadId();
    test_2();
}


void MainWindow::on_pushButton_4_clicked()
{
    test_threadpool();
}
///[1]
