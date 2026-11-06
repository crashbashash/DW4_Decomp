int FUN_001c66c0();
int FUN_00306770();
int igObject_Destroy();
extern int DAT_004e4660[4];

typedef struct R { int w0; int refs; } R;

int Gap__Core__igIniShaderFactory__vfunc_24(R **arg0, void *arg1, int arg2) {
    R * volatile sp4C;
    R *t;
    R *a0;

    sp4C = 0;
    t = sp4C;
    if (t != 0) {
        t->refs = t->refs + 1;
    }
    if (FUN_001c66c0(arg1, 0) == 0) {
        *arg0 = 0;
        t = *arg0;
        if (t != 0) {
            t->refs = t->refs + 1;
        }
        a0 = sp4C;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if (((unsigned long long)((long long)a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
        return 0;
    }
    if (FUN_00306770(*(int *)((char *)(arg1) + 32), *(int *)((char *)(arg1) + 40), arg2, &sp4C, &DAT_004e4660[0], 0) == 0) {
        *arg0 = 0;
        t = *arg0;
        if (t != 0) {
            t->refs = t->refs + 1;
        }
        a0 = sp4C;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if (((unsigned long long)((long long)a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
        return 0;
    }
    *arg0 = sp4C;
        t = *arg0;
        if (t != 0) {
            t->refs = t->refs + 1;
        }
        a0 = sp4C;
        if (a0 != 0) {
            a0->refs = a0->refs - 1;
            if (((unsigned long long)((long long)a0->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
    return 0;
}
