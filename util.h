#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <string>
#include <memory.h>
#include <QDebug>
/**
 * @brief atoi 字符转整数
 * @param p    字符串
 * @param iValue   进制 默认转为10进制
 */
static int funatoi(const char* str) {
    if (str == nullptr)
        return 0;
    //判断是否负数
    bool bNegative = false;
    if (*str == '-')
    {
        bNegative = true;
        str++;
    }

    // proc numbers
    int result = 0;
    while (*str>='0' && *str<='9')
    {
        result = result*10 + *str - '0';
        ++str;
    }
    if (bNegative)
        result = -result;

    qDebug() << __FUNCTION__ << " result = " << result;
    return result;
}

/**
 * @brief funitoa  整数转字符
 * @param num      要转的整数
 * @param p        转换的字符
 * @param iva      默认10进制
 */
static void funitoa(int num, char* p, int iva=10) {
    p = (char*)malloc(10);
    memset(p, 0, 10);
    char* buf = p;
    int val = num;
    //判断正数还是负数
    if (val<0)
    {
        *buf++ = '-';
        val = (unsigned long)(-(long)val);
    }
    char* first = buf;
    while (val>0)
    {
        int mod = val%iva;  //小数部分
        val /= iva;         //余数   整数部分
        if (mod > 9)
            *buf = (char)(mod - 10 + 'a');  //16进制
        else
            *buf = (char)(mod + '0');       //10进制
        ++buf;
    }
    *buf-- = '\0';
    qDebug() << __FUNCTION__ << " result buf = " << p;

    //调整位置
    char temp;
    while (first < buf)
    {
        temp = *buf;
        *buf = *first;
        *first = temp;
        --buf;
        ++first;
    }

    qDebug() << __FUNCTION__ << " result buf = " << p;
}

static char* funitoa1(char buf[], int value) {
    static const char digits[] = {'9','8','7','6','5','4','3','2','1','0','1','2','3','4','5','6','7','8','9'};
    static const char* zero = digits+9;    //指向0

    char* p = buf;
    int i = value;
    do {
       int sd = i%10;
       i /= 10;
       *p++ = zero[sd];
    }while(i!=0);
    if (value<0)
        *p++ = '-';
    std::reverse(buf, p);
    return buf;
}

static char* funstrcopy(const char* pSrc, char* pDst)
{
    if (pSrc == nullptr || pDst == nullptr)
        return nullptr;

    char* p = pDst;
    while ((*pDst++ = *pSrc++) != '\0');

    qDebug() << __FUNCTION__ << " result copy = " << p;
    return p;
}

static bool isBigEndian()
{
    union endian {
        char a;
        int  i;
    };

    endian end;
    end.i = 0x01000002;
    //字节高位   字节低位     联合体共用同一块内存，a在结构体的低地址，如果a = 0x01,则说明i 的字节高位在低地址，是大端模式；如果 a = 2,则说明 i 的字节高位在地址，是小端模式
    if (end.a == 0x01)
        return true;
    return false;
}

static const int const_example()
{
    //整数常量
    int i = 1;
    int a = 2;
    //指针地址指向的值是常量
    const int* p = &i;
    //指针地址的值是常量
    int *const p1 = &i;
    p = &a;
    //*p = a;   //会出错
    *p1 = a;
    //p1 = &a;    //会出错
    qDebug()<<" p = "<<*p<<"; p1 = "<<*p1;
    return a;
}

static void bubbleSort(int num[], int len)
{
    if (len<=1)
        return;
    for (int i=0; i<len; i++)
    {
        bool bflag = false;
        for (int j=0; j<len-i-1; j++)
        {
            if (num[j+1]>num[j])
            {
                int temp = num[j];
                num[j] = num[j+1];
                num[j+1] = temp;
                bflag = true;
            }
        }
        if (!bflag)
            break;
    }
    QString str;
    for (int i=0; i<len; i++)
        str += QString::number(num[i]);
    qDebug()<<"bubble sort = "<<str;
}

/**
 * @brief insertSort   分成有序排列和无序排列
 * @param num
 * @param len
 */
static void insertSort(int num[], int len)
{
    if (len<=1)
        return;
    //初始有序序列从1开始
    for (int i=1; i<len; i++)
    {
        int v = num[i];
        int j = i-1;
        //找出插入位置
        for (;j>=0;j--)
        {
            if (num[j] > v)
            {
                //移动数据
                num[j+1] = num[j];
                qDebug()<<" move j = "<<j;
            }
            else
                break;
        }
        //插入数据
       num[j+1] = v;
    }
    QString str;
    for (int i=0; i<len; i++)
        str += QString::number(num[i]);
    qDebug()<<"insert sort = "<<str;
}

static void selectionSort(int num[], int len)
{

}

#endif // UTIL_H
