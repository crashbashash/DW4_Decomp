long long FUN_0022e440(long long a, long long b);

int FUN_00291768(long long a, long long b, long long c) {
    int sign;
    long long d;

    if (c == 0) {
        return ((a ^ b) < 0) ? 0x80000000 : 0x7fffffff;
    }
    d = c;
    sign = 1;
    if (a < 0) {
        sign = -1;
        a = -a;
    }
    if (b < 0) {
        sign = -sign;
        b = -b;
    }
    if (d < 0) {
        d = -d;
        sign = -sign;
    }
    a = (FUN_0022e440(a, b) + d / 2) / d;
    if (sign < 0) {
        a = -a;
    }
    return a;
}
