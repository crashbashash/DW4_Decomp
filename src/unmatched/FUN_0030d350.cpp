extern "C" {
int strlen(...);
int strcmp(...);
}
struct Tb { char pad[8]; int n; char pad2[4]; int *arr; };
struct Buf { char pad[8]; int sz; char pad2[4]; char *buf; };
class K { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vH(); char pad[12]; Buf *f16; Tb *f20; };
extern "C" int FUN_0030d350(K *arg0, unsigned int arg1) {
    Tb *t;
    int idx;
    int off;
    int n;
    int cnt;
    char *s;
    char *end;

    t = arg0->f20;
    if (t != 0 && t->n != 0) {
        idx = arg0->vH();
        cnt = 0;
        n = arg0->f20->n;
        for (;;) {
            off = arg0->f20->arr[idx];
            if (off == -1) {
                return -1;
            }
            if (strcmp(arg0->f16->buf + off, arg1) == 0) {
                return off;
            }
            idx += 1;
            if (idx >= n) {
                idx = 0;
            }
            cnt += 1;
            if (cnt >= n) {
                return -1;
            }
        }
    }
    s = arg0->f16->buf;
    end = s + arg0->f16->sz;
    while (s < end) {
        if (strcmp(arg1, s) == 0) {
            return s - arg0->f16->buf;
        }
        s += strlen(s) + 1;
    }
    return -1;
}
