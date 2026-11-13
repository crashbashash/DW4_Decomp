/* The conversions and comparisons MWCC calls for double arithmetic, which the EE's FPU cannot do: each forwards to
 * the software double-precision routines (__floatdidf, dpadd, dpcmp). */

double __floatdidf(long long value);
double dpadd(double a, double b);
int dpcmp(double a, double b);

double _d_ulltod(unsigned long long value) {
    double half;

    if ((long long)value > 0) {
        return __floatdidf(value);
    }
    /* Too big for a signed conversion: convert half, keeping the low bit for rounding, and double it. */
    half = __floatdidf((value >> 1) | (value & 1));
    return dpadd(half, half);
}

double _d_utod(unsigned int value) {
    return _d_ulltod(value);
}

int _dpfeq(double a, double b) {
    return dpcmp(a, b) == 0;
}

int _dpfne(double a, double b) {
    return dpcmp(a, b) != 0;
}

int _dpflt(double a, double b) {
    return dpcmp(a, b) < 0;
}

int _dpfle(double a, double b) {
    return dpcmp(a, b) <= 0;
}

int _dpfgt(double a, double b) {
    return dpcmp(a, b) > 0;
}

int _dpfge(double a, double b) {
    return dpcmp(a, b) >= 0;
}
