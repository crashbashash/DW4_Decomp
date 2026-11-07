extern "C" {
void FUN_002e31b0(void *, int);
void FUN_002e3a60(void *, void *, int, int);
void FUN_002e3d30(void *);
void igObject_Destroy(void *);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
}
struct R { int w; R() {} R(const R &o) : w(o.w) {} };
struct Obj { char p0[4]; int refs; };
struct T { char p0[104]; Obj *f104; char p108[88]; int f196; };
extern "C" void FUN_002e5f70(int *arg0, T *arg1, int arg2);
void FUN_002e5f70(int *arg0, T *arg1, int arg2) {
    Obj *o;
    R r;
    int *pp;
    if ((arg1->f104 == 0) && (arg2 == 0)) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    if (arg1->f104 == 0) {
        FUN_002e3a60(&r, arg1, arg2, 4);
        pp = (int *)((int)&r + 0);
        if (*pp == DAT_004fb418[0]) {
            if (arg2 != 0) {
                o = arg1->f104;
                if (o != 0) {
                    o->refs = o->refs - 1;
                    if (((unsigned long long)((long long)(int)o->refs << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(o);
                    }
                }
                arg1->f104 = 0;
            }
            *arg0 = DAT_004fb418[0];
            return;
        }
        arg1->f196 = 1;
    }
    if (arg1->f104 == 0) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    FUN_002e3d30(arg1);
    FUN_002e31b0(arg1->f104, 4);
    *arg0 = DAT_004fb410[0];
}
