/* 0x001dcb80 - FUN_001dcb80. Removes a key from a word list by swapping it with the last element after an optional reset call: the inline index search of Gap__Core__igObject__vfunc_32 (spilled key, early goto found), declaration order n,key,a0,v1,r,i; alternate compiler -O3. */
typedef struct L { char p0[8]; int n; int p1; int *d; int cnt; int p2; unsigned char f28; } L;
int igObject_ResetFields(int);
void FUN_001dcb80(L *arg0, int arg1) {
    int n;
    int key;
    int a0;
    int v1;
    int r;
    int i;
    volatile int sp3C;
    sp3C = arg1;
    n = arg0->n;
    key = sp3C;
    for (i = 0; i < n; i++) { if (key == arg0->d[i]) { r = i; goto found; } }
    r = -1;
found:
    if (r >= 0) {
        if (arg0->f28 != 0) {
            igObject_ResetFields(arg1);
        }
        arg0->cnt = arg0->cnt - 1;
        a0 = arg0->cnt;
        if (a0 != r) {
            v1 = arg0->n;
            if (v1 != 0 && a0 >= 0 && a0 < v1 && r >= 0 && r < v1) {
                int *base = arg0->d;
                int t = base[a0];
                base[a0] = base[r];
                base[r] = t;
            }
        }
    }
}
