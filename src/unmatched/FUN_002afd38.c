typedef struct { char pad[8]; int f8; char pad2[56]; } Slot;
extern void FUN_002afdf0(Slot *s, int v);
extern int FUN_002afe38(void *h, int *tbl);
extern void FUN_002a0bb8(void *h, int code);
void FUN_002afd38(void *h, Slot *s, int **ptbl) {
    int *tbl = *ptbl;
    int i;
    for (i = 0; i < 9; i++) {
        s[i].f8 = 0;
        FUN_002afdf0(&s[i], tbl[i]);
    }
    if (FUN_002afe38(h, tbl) != 0) {
        FUN_002a0bb8(h, 0xFF000302);
    }
}
