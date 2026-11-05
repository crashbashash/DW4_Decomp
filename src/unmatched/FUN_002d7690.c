typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct L { char pad8[8]; int n; char pad12[4]; S1 **data; } L;
int igObject_Destroy();
void FUN_002d7690(char *arg0);
void FUN_002d7690(char *arg0) {
    L *l;
    int n;
    int i;
    S1 *t;
    l = *(L **)(arg0 + 8);
    n = l->n;
    for (i = 0; i < n; i++) {
        t = l->data[i];
        if (t != 0) {
            t->f4 = (int)((int) (t->f4 - 1));
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    n = l->n;
    for (i = 0; i < n; i++) {
        l->data[i] = 0;
    }
    l->n = 0;
}
