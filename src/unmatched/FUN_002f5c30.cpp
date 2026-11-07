extern "C" {
void FUN_002f8b20(void *);
void igObject_Destroy(void *);
void FUN_002f5c30(void *arg0);
}
struct Sub { char p[132]; int f132; };
struct Obj { char p0[4]; int refs; };
struct T { char p0[16]; Obj *f16; Sub f20; };
void FUN_002f5c30(void *arg0) {
    T *t = (T *)arg0;
    Sub *s;
    Obj *o;
    s = &t->f20;
    goto set;
back:
    if (t->f16 != 0) {
        FUN_002f8b20(t->f16);
        o = t->f16;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)(int)o->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        t->f16 = 0;
    }
    return;
set:
    s->f132 = 0;
    goto back;
}
