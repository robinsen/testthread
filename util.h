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

static void funitoa(int num, char* p, int iva=10) {
    p = (char*)malloc(10);
    memset(p, 0, 10);
    char* buf = p;
    int val = num;
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

#endif // UTIL_H
