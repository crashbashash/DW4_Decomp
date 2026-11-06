struct S { char p[44]; int f44; int p2; int f52; int f56; int f60; };
int memcpy();
int FUN_0012fde0();
int FUN_0032b5b0();
int FUN_0032bba0(struct S *arg0, int arg1, ...) {
    char buf[16384];
    int n;
    int off;
    int len;
    int cur;
    if (arg0->f60 != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) off = 0; else off = (8 - n) * 8;
    len = FUN_0012fde0(buf, arg1, (char *)__builtin_next_arg(arg1) - off);
    cur = arg0->f52 + len;
    if (cur >= arg0->f56) {
        FUN_0032b5b0(arg0, cur);
    }
    memcpy(arg0->f44 + arg0->f52, buf, len);
    arg0->f52 = arg0->f52 + len;
    return len;
}
