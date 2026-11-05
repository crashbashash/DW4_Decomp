class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vf(int, int); int a; int b; int c; unsigned char flag; };
struct Lst { int pad0; int pad1; int count; int pad3; O **data; };
struct T { char pad[28]; Lst *list; };
extern "C" int FUN_002d83b0(T *arg0, int arg1, int arg2) {
    int i;
    O *o;

    for (i = 0; i < arg0->list->count; i++) {
        o = arg0->list->data[i];
        if (o->flag == 1 && (o->vf(arg1, arg2) & 0xFF) == 1) {
            return 1;
        }
    }
    return 0;
}
