#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <string>
#include <memory.h>
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

    std::cout << __FUNCTION__ << " result = " << result << std::endl;
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
    std::cout << __FUNCTION__ << " result buf = " << p << std::endl;

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

    std::cout << __FUNCTION__ << " result buf = " << p << std::endl;
}

static char* funstrcopy(const char* pSrc, char* pDst)
{
    if (pSrc == nullptr || pDst == nullptr)
        return nullptr;

    char* p = pDst;
    while ((*pDst++ = *pSrc++) != '\0');

    std::cout << __FUNCTION__ << " result copy = " << p << std::endl;
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
    //字节高位   字节低位     联合体共用同一块内存，a在结构体的低地址，如果a = 1,则说明i 的字节低位在低地址，是小端模式；如果 a = 0,则说明 i 的字节高位在地址，是大端模式
    if (end.a == 0x01)
        return true;
    return false;
}

#endif // UTIL_H
