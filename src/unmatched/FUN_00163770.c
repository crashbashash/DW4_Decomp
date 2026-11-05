/* 0x00163770 - FUN_00163770. Float-to-fixed-point conversion: splits a float into mantissa (23-bit bitfield read) and exponent, aligns the mantissa to arg0 fractional bits and ORs in the integer part. Union read-back through the stack; the exponent bias is subtracted after the join (not inside the condition); alternate compiler -O3. */
int FUN_00163770(unsigned int arg0, float fparg0) {
    union { float f; unsigned u; struct { unsigned frac:23; } b; } x;
    int e, v;
    unsigned int s, t, r, m;
    int iv;
    x.f = fparg0;
    e = (x.u >> 23) & 0xFF;
    m = x.b.frac;
    if (m != 0 || e != 0) {
        m |= 0x800000;
    }
    v = e - 0x7F;
    s = 0x17;
    if (v != 0) {
        s -= v;
    } else {
        s += v;
    }
    t = m & ((1 << s) - 1);
    iv = (int)x.f;
    if (arg0 < s) {
        r = t >> (s - arg0);
    } else {
        r = t << (arg0 - s);
    }
    return r | (iv << arg0);
}
