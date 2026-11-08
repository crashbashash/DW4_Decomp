extern int D_004f5920[];
extern int D_004f5928[];
extern int D_004f5958[];
extern int FUN_002b3780(void *p, int *tbl);
extern int FUN_002b4b58(int x);
extern void FUN_002b3b38(void *h, void *a, int *tbl);
extern void FUN_002b4dc8(void *h, unsigned int *p, int a, int b);
extern void FUN_002b4f58(void *h, unsigned int *p, int a, int b);
void FUN_002b4c98(char *h, unsigned int *p, int a, int b) {
    if (*(int *)(h + 4) == 0) {
        *(int *)(h + 4) = FUN_002b3780(p, D_004f5920);
    }
    if (FUN_002b4b58(*(int *)(h + 40)) != 1) {
        FUN_002b3b38(h, p, D_004f5928);
        return;
    }
    switch (*p) {
    case 3:
        FUN_002b4dc8(h, p, a, b);
        return;
    case 2:
        FUN_002b4f58(h, p, a, b);
        return;
    case 1:
    default:
        FUN_002b3b38(h, p, D_004f5958);
        return;
    }
}
