typedef struct Rc { int w0; int refs; } Rc;
typedef struct Ls { char p0[8]; int cnt; char p1[4]; Rc **data; } Ls;
typedef struct O { char p0[304]; Ls *f304; Ls *f308; } O;
int igObject_Destroy();
void FUN_00155db0(O *arg0) {
    Ls *s2;
    int s1;
    int s0;
    int n2;
    int a1;
    Rc *o;
    s2 = arg0->f308;
    s1 = s2->cnt;
    for (s0 = 0; s0 < s1; s0++) {
        o = s2->data[s0];
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = s2->cnt;
    for (a1 = 0; a1 < n2; a1++) {
        s2->data[a1] = 0;
    }
    s2->cnt = 0;
    s2 = arg0->f304;
    s1 = s2->cnt;
    for (s0 = 0; s0 < s1; s0++) {
        o = s2->data[s0];
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = s2->cnt;
    for (a1 = 0; a1 < n2; a1++) {
        s2->data[a1] = 0;
    }
    s2->cnt = 0;
}
