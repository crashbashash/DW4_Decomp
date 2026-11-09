int FUN_001c59b0();
int List_RemoveWordAt();
int igObject_Destroy();
typedef struct { char pad[4]; int f4; } R;
typedef struct { char pad[8]; int f8; char pad2[4]; int *f10; } L;
typedef struct { char pad[8]; L *f8; } T;
static inline int f8_of(const L *list) { return list->f8; }
int FUN_001c58c0(T *arg0) {
    int s2;
    L *l;
    R *o;
    int ret;
    if (FUN_001c59b0(arg0) == 0) {
        l = arg0->f8;
        ret = *(int *)((char *)l->f10 + (f8_of(l) - 1) * 4);
        s2 = l->f8 - 1;
        o = (R *)l->f10[s2];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long)((long long)o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt(l, s2);
        l->f10[l->f8] = 0;
        return ret;
    }
    return 0;
}
