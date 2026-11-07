extern "C" {
typedef struct Rc { int w0; int refs; } Rc;
typedef struct O { char p0[76]; Rc *f76; Rc *f80; } O;
Rc *FUN_001c5990(Rc *);
int igObject_IsKindOf(Rc *, int);
int igObject_Destroy(Rc *);
extern int DAT_00561ea0[16];
void FUN_0037a690(O *arg0, Rc *arg1);
}

static inline Rc * cast0(Rc * o) { if (o != 0 && igObject_IsKindOf(o, DAT_00561ea0[0]) != 0) { return o; } return 0; }
void FUN_0037a690(O *arg0, Rc *arg1) {
    Rc *s0;
    Rc *a;
    if (arg1 != 0) {
        if (arg1 != 0) {
            arg1->refs = arg1->refs + 1;
        }
        a = arg0->f76;
        if (a != 0) {
            a->refs = a->refs - 1;
            if (((unsigned long long)(long long)a->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(a);
            }
        }
        arg0->f76 = arg1;
        s0 = FUN_001c5990(arg1);
        s0 = cast0(s0);
        if (s0 != 0) {
            s0->refs = s0->refs + 1;
        }
        a = arg0->f80;
        if (a != 0) {
            a->refs = a->refs - 1;
            if (((unsigned long long)(long long)a->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(a);
            }
        }
        arg0->f80 = s0;
    }
}
