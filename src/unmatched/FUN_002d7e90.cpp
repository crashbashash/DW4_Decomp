extern "C" {
int FUN_002d7d60(...);
void *FUN_002d7e90(int *arg0, int arg1);
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); };
void *FUN_002d7e90(int *arg0, int arg1) {
    if (arg0[11] != 0) {
        VC *t = (VC *)((int *)arg0[4])[arg1];
        t->vX(FUN_002d7d60(arg0));
        ((int *)t)[3] = arg1;
        return t;
    }
    return (void *)((int *)arg0[4])[arg1];
}
