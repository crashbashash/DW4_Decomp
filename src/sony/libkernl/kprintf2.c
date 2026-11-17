/* kprintf2.c - libkernl's formatted kernel output (libkernl.a kprintf2.o). kprintf writes to the
 * serial port, scePrintf to the host console over DECI2; both run one formatter, which sends every
 * character through the current output function. */
#include "dw4/sony/libkernl.h"

typedef unsigned long u_long;

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)__builtin_next_arg(last) - (8 - __builtin_args_info(0)) * 8)
#define va_arg(ap, type) (*(type *)((ap += 8) - 8))

/* the EE serial port: interrupt status and transmit FIFO */
#define SIO_ISR (*(volatile int *)0x1000F130)
#define SIO_TXFIFO (*(volatile char *)0x1000F180)
#define SIO_ISR_TX_FULL 0x8000

#define DECI2_LINE_MAX 128
/* the conversion buffer's last index: the digits end there, and a zero-padded width stops there */
#define PAD_MAX 31

static void serialPutchar(int c);

static int count = 0;
static void (*putchar_hook)(int c) = serialPutchar;
/* characters held back for the host until a newline or a full line */
static char linebuf[DECI2_LINE_MAX];

static int kputchar(int c)
{
    while (SIO_ISR & SIO_ISR_TX_FULL)
        ;
    SIO_TXFIFO = c;
    return c;
}

static void deci2Putchar(int c)
{
    int n = count;

    if (n >= DECI2_LINE_MAX - 2) {
        count = 0;
        linebuf[DECI2_LINE_MAX - 1] = 0;
        kputs(linebuf);
        n = count;
    }
    if (c == '\n') {
        count = 0;
        linebuf[n] = c;
        linebuf[n + 1] = 0;
        kputs(linebuf);
        return;
    }
    count = n + 1;
    linebuf[n] = c;
}

static void serialPutchar(int c)
{
    if (c == '\n') {
        kputchar('\r');
        kputchar('\n');
        return;
    }
    kputchar(c);
}

/* An IEEE double's bits as an integer, rounded: 0 below 2^-53, 9999 from 2^13 up. */
static int ftoi(u_long bits)
{
    long exponent;

    exponent = (bits << 1) >> 53;
    exponent -= 1075;
    if (exponent < -53) {
        return 0;
    }
    if (exponent >= 13) {
        return 9999;
    }
    bits = (bits << 12) >> 12;
    bits |= 1UL << 52;
    if (exponent < 0) {
        exponent = -exponent;
        bits >>= (int)(exponent - 2);
        if ((bits & 3) == 3) {
            bits = (bits >> 2) + 1;
        } else {
            bits >>= 2;
        }
    } else {
        bits <<= (int)exponent;
    }
    return bits;
}

/* Prints `value` as 0.dddddd followed by a decimal exponent. ftoi is handed the scaled value
 * already converted to an integer, not its bits, so the digits come out 0. */
static void printfloat(double value)
{
    int exponent = 0;
    int digits;

    if (value < 0.0) {
        value = 0.0 - value;
        putchar_hook('-');
    }
    if (value < 0.1) {
        while (value < 0.1) {
            value *= 10.0;
            exponent--;
        }
    } else if (value >= 1.0) {
        while (value >= 1.0) {
            value /= 10.0;
            exponent++;
        }
    }
    digits = ftoi(value * 1000000.0);
    kprintf("0.%d", digits);
    if (exponent >= 0) {
        kprintf("e+%d", exponent);
    } else {
        kprintf("e%d", exponent);
    }
}

/* Formats `fmt` with interrupts off. A conversion takes an optional `0` with a width of one or two
 * digits (zero padding up to PAD_MAX), `l` or `h`, then one of o x d u e f s c; any other
 * character ends it unprinted. */
static void kvprintf(const char *fmt, va_list ap)
{
    char buf[PAD_MAX + 1];
    char *p;
    char *pad;
    char *str;
    int width;
    char length;
    long long v;
    unsigned long long u;
    int intr = DIntr();

    while (*fmt) {
        pad = 0;
        length = 0;
        if (*fmt == '%') {
        next:
            fmt++;
            switch (*fmt) {
            case '0': {
                char tens = fmt[1];
                char ones = fmt[2];

                width = tens - '0';
                if (tens >= '0' && tens <= '9') {
                    if (ones >= '0' && ones <= '9') {
                        width = width * 10 + (ones - '0');
                        if (width > PAD_MAX) {
                            width = PAD_MAX;
                        }
                        fmt += 2;
                    } else {
                        fmt++;
                    }
                    pad = &buf[PAD_MAX - width];
                    while (width > 0) {
                        buf[PAD_MAX - width] = '0';
                        width--;
                    }
                }
                goto next;
            }
            case 'l':
                length = 'l';
                goto next;
            case 'h':
                length = 'h';
                goto next;
            case 'o':
                if (length == 'l') {
                    u = va_arg(ap, unsigned long long);
                } else if (length == 'h') {
                    u = va_arg(ap, unsigned short);
                } else {
                    u = va_arg(ap, unsigned int);
                }
                p = &buf[PAD_MAX];
                *p = 0;
                if (u == 0) {
                    *--p = '0';
                } else {
                    do {
                        *--p = '0' + (u & 7);
                        u >>= 3;
                    } while (u);
                }
                if (pad && pad < p) {
                    p = pad;
                }
                while (*p) {
                    putchar_hook(*p++);
                }
                break;
            case 'x':
                if (length == 'l') {
                    u = va_arg(ap, unsigned long long);
                } else if (length == 'h') {
                    u = va_arg(ap, unsigned short);
                } else {
                    u = va_arg(ap, unsigned int);
                }
                p = &buf[PAD_MAX];
                *p = 0;
                if (u == 0) {
                    *--p = '0';
                } else {
                    do {
                        unsigned long long digit = u & 0xF;

                        if (digit < 10) {
                            *--p = '0' + digit;
                        } else {
                            *--p = 'a' + digit - 10;
                        }
                        u >>= 4;
                    } while (u);
                }
                if (pad && pad < p) {
                    p = pad;
                }
                while (*p) {
                    putchar_hook(*p++);
                }
                break;
            case 'd':
                if (length == 'l') {
                    v = va_arg(ap, long long);
                } else if (length == 'h') {
                    v = va_arg(ap, short);
                } else {
                    v = va_arg(ap, int);
                }
                p = &buf[PAD_MAX];
                *p = 0;
                if (v == 0) {
                    *--p = '0';
                } else {
                    if (v < 0) {
                        v = -v;
                        putchar_hook('-');
                    }
                    while (v) {
                        *--p = '0' + v % 10;
                        v /= 10;
                    }
                }
                if (pad && pad < p) {
                    p = pad;
                }
                while (*p) {
                    putchar_hook(*p++);
                }
                break;
            case 'u':
                if (length == 'l') {
                    u = va_arg(ap, unsigned long long);
                } else if (length == 'h') {
                    u = va_arg(ap, unsigned short);
                } else {
                    u = va_arg(ap, unsigned int);
                }
                p = &buf[PAD_MAX];
                *p = 0;
                if (u == 0) {
                    *--p = '0';
                } else {
                    do {
                        *--p = '0' + u % 10;
                        u /= 10;
                    } while (u);
                }
                if (pad && pad < p) {
                    p = pad;
                }
                while (*p) {
                    putchar_hook(*p++);
                }
                break;
            case 'e':
            case 'f': {
                float f = va_arg(ap, double);

                if (f == 0.0f) {
                    putchar_hook('0');
                } else {
                    printfloat(f);
                }
                break;
            }
            case 's':
                str = va_arg(ap, char *);
                if (*str == 0) {
                    putchar_hook('(');
                    putchar_hook('n');
                    putchar_hook('u');
                    putchar_hook('l');
                    putchar_hook('l');
                    putchar_hook(')');
                } else {
                    p = str;
                    do {
                        putchar_hook(*p++);
                    } while (*p);
                }
                break;
            case 'c':
                v = va_arg(ap, char);
                putchar_hook(v);
                break;
            }
        } else {
            putchar_hook(*fmt);
        }
        fmt++;
    }
    if (intr) {
        EIntr();
    }
}

void kprintf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    kvprintf(format, ap);
}

void scePrintf(const char *format, ...)
{
    void (*saved)(int c) = putchar_hook;
    va_list ap;

    putchar_hook = deci2Putchar;
    va_start(ap, format);
    kvprintf(format, ap);
    putchar_hook = saved;
}
