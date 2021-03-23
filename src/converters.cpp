#include "converters.hpp"

#define EXPONENT_SYMBOL 15

double atof(const char *buffer)
{
    double ret = 0, fact = 1;
    if (*buffer == '-')
    {
        buffer++;
        fact = -1;
    }
    for (bool point = false; *buffer; buffer++)
    {
        if (*buffer == '.')
        {
            point = true;
            continue;
        }
        int d = *buffer - '0';
        if (d >= 0 && d <= 9)
        {
            if (point)
            {
                fact /= 10.0f;
            }
            ret = ret * 10.0f + (double)d;
        }
    }
    return ret * fact;
}

char *ftoa(float num, int precision)
{
    unsigned long long fraction = 1000000000000LL;
    unsigned long long f = 0;
    unsigned long long d = 0;
    unsigned int data = *((int *)(&num));
    signed char e = data >> 23;

    e &= 0xff;
    e -= 127;

    bool sign = data & 0b10000000000000000000000000000000;

    unsigned int sig = data & 0b00000000011111111111111111111111;
    sig |= 0b00000000100000000000000000000000;
    sig <<= 8;

    for (int i = 23; i; i--)
    {
        bool a = sig & 0b10000000000000000000000000000000;

        if (a)
        {
            unsigned long long ft = fraction, dt = 0;

            for (int ei = e; ei != 0; ei -= (ei >= 0 ? 1 : -1))
            {
                if (ei > 0)
                {
                    ft <<= 1;
                    dt <<= 1;
                }
                else
                {
                    ft >>= 1;
                    dt >>= 1;
                }

                while (ft >= 1000000000000LL)
                {
                    ft -= 1000000000000LL;
                    dt++;
                }
            }
            d += dt;
            f += ft;

            while (f >= 1000000000000LL)
            {
                f -= 1000000000000LL;
                d++;
            }
        }

        fraction >>= 1;
        sig <<= 1;
    }
    char* buffer = (char*)sys_malloc(sizeof(char) * (8 + precision)); // D.FFFFFeEEE | DDDDD.FFFFF -> sign + 6 symbols + precision + '\0'
    char* ptr = buffer; 
    if (sign)
    {
        *ptr++ = '-';
    }
    char dbuffer[21];
    char* dptr = dbuffer;

    char* b = (char*)sys_malloc(sizeof(char) * 21);
    *b = '\0';
    while (d)
    {
        *++b = '0' + d % 10;
        d /= 10;
    }
    int len = 0;
    while (*b)
    {
        *dptr++ = *b--;
        len++;
    }
    *dptr = '\0';
    sys_free(b);
    if (len > 5)
    {
        *ptr++ = dbuffer[0];
        *ptr++ = '.';
        for (int i = 0; i < precision && i < len - 1; i++)
        {
            *ptr++ = dbuffer[i + 1];
        }
        *ptr++ = 15;
        itoa(len - 1, (unsigned char*)ptr);
    }
    else
    {
        if (len)
        {
            for (int i = 0; i < len; i++)
            {
                *ptr++ = dbuffer[i];
            }
        }
        else
        {
            *ptr++ = '0';
        }
        *ptr = '.';
        char fbuffer[12];
        char* fptr = fbuffer + 11;
        for (int i = 11; i >= 0; i--)
        {
            *fptr-- = '0' + f % 10;
            f /= 10;
        }
        ptr += precision;
        bool can_skip = true;
        for (int i = precision - 1; i >= 0; i--)
        {
            if (can_skip)
            {
                if (fbuffer[i] == '0')
                {
                    ptr--;
                    continue;
                }
                *(ptr + 1) = '\0';
                can_skip = false;
            }
            *ptr-- = fbuffer[i];
        }
        if (can_skip)
        {
            *ptr = '\0';
        }
    }
    return buffer;
}
