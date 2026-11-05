struct S {
    long long a;
    int b, base, cur, e, f;
    unsigned char x : 1;
    unsigned char y : 1;
    unsigned char z : 6;
    void setY(bool v) { y = v; }
};
extern "C" S *FUN_001eef20(int base, S *s) {
    int c = s->cur - s->base;
    s->a = 0;
    s->b = 0;
    s->base = base;
    s->cur = base + c;
    s->e = 0;
    s->f = 0;
    s->setY(0);
    return s;
}
