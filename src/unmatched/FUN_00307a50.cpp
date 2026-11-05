class Stream { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int get(); };
extern "C" bool FUN_00307a50(void *unused, Stream *s, char *buf, int *lines);
extern "C" bool FUN_00307a50(void *unused, Stream *s, char *buf, int *lines) {
    int c = s->get();
    int prev = 0;
    bool comment = false;
    int n = 0;
    bool ret = false;
    bool lead = true;
    while (c != -1 && c != 0) {
        while (lead) {
            if (c == 0x20 || c == 9) { prev = c; c = s->get(); }
            else lead = false;
        }
        if (c == 13) { c = s->get(); continue; }
        if (c != 10) {
            if (!comment) {
                if (c == 0x3B) comment = true;
                else if (c == 0x2F && prev == 0x2F) { n -= 1; comment = true; }
                else {
                    if (n < 0xFFF) buf[n] = c;
                    n += 1;
                }
            }
            goto next;
        }
        if (prev != 0x5C) break;
        lead = true;
        *lines += 1;
        if (!comment) n -= 1;
    next:
        prev = c;
        c = s->get();
    }
    if (n > 0 || c != -1) {
        ret = true;
        *lines += 1;
    }
    if (n >= 0x1000) n = 0xFFF;
    buf[n] = 0;
    return ret;
}
