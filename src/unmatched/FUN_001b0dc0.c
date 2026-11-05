typedef struct R { char pad4[4]; int f4; } R;
typedef struct E2 { char pad16[16]; R *f10; } E2;
typedef struct E1 { char pad20[20]; E2 *f14; } E1;
typedef struct L { char pad16[16]; E1 **arr; } L;
typedef struct C { char pad8[8]; int n; } C;
typedef struct G { char pad8[8]; int idx; } G;
typedef struct O { char pad16[16]; L *l; char pad20[16]; C *c24; C *c28; char pad2c[24]; int *base; } O;
extern G *DAT_0055f060[4];
int igObject_Destroy();
void FUN_001b0dc0(O *arg0) {
    int n, i;
    n = arg0->c24->n;
    for (i = 0; i < n; i++) {
        E2 *e = arg0->l->arr[i + arg0->base[DAT_0055f060[0]->idx]]->f14;
        R **slot = &e->f10;
        R *r = *slot;
        if (r != 0) {
            r->f4 = (int)((int) (r->f4 - 1));
            if (((unsigned long long) ((long long) r->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(r);
            }
        }
        *slot = 0;
    }
    arg0->c24->n = 0;
    arg0->c28->n = 0;
}
