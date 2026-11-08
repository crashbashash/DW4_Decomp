extern int D_004f5788[];
extern int FUN_002b4b58(int x);
extern void FUN_002b3b38(void *h, int a, int *tbl);
extern void FUN_002b50c8(void *h, int n);
extern void FUN_002b3510(void *h, int a);

void FUN_002b3708(void *h, int a) {
    if (FUN_002b4b58(*(int *)((char *)h + 40)) != 1) {
        FUN_002b3b38(h, a, D_004f5788);
        return;
    }
    FUN_002b50c8(h, 32);
    FUN_002b3510(h, a);
}
