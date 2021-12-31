#include "mainwindow.h"
#include "vector.h"
#include <QApplication>
#include <iostream>
#include <vector>
#include "dclass.h"
using namespace std;

int g_constructCount=0;
int g_copyConstructCount=0;
int g_destructCount=0;

struct A
{
    A(){
        cout<<"construct: "<<++g_constructCount<<endl;
    }

    A(const A& a)
    {
        cout<<"copy construct: "<<++g_copyConstructCount <<endl;
    }
    ~A()
    {
        cout<<"destruct: "<<++g_destructCount<<endl;
    }
};

A GetA()
{
    return A();
}

int main(int argc, char *argv[])
{
    CVector<int> iv(1);
    iv.push_back(2);
    iv.push_back(4);
    cout<<"vector size ="<<iv.size()<<" capacity = "<<iv.capacity()<<endl;

    CVector<int> fv(1);
    fv.push_back(2.1);
    fv.push_back(4.2);
    cout<<"fv vector size ="<<fv.size()<<" capacity = "<<fv.capacity()<<endl;

    CVector<string> strv(1, "cc");
    strv.push_back(string("aa"));
    strv.push_back(string("bb"));
    cout<<"vector str size ="<<strv.size()<<" capacity = "<<strv.capacity()<<" str= "<<strv[0]<<endl;

    vector<string> str(1);
    str.push_back(string("aa"));
    str.push_back(string("bb"));
    cout<<"vector stra size ="<<strv.size()<<" capacity = "<<str.capacity()<<" str= "<<str[0]<<endl;

    DClass dc;
    dc.testFool();

    return 0;
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
