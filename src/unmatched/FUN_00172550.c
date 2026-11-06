/* 164 bytes. */
struct N { char pad0[12]; int f12; };
struct S { char pad0[972]; struct N *f972; struct N *f976; struct N *f980; char pad984[4]; struct N *f988; struct N *f992; struct N *f996; struct N *f1000; };
int FUN_00172550(struct S *arg0, int arg1) {
    switch (arg1) {
    case 0: return arg0->f972->f12;
    case 1: return arg0->f976->f12;
    case 2: return arg0->f980->f12;
    case 10: return arg0->f988->f12;
    case 11: return arg0->f992->f12;
    case 12: return arg0->f996->f12;
    case 13: return arg0->f1000->f12;
    default: return 0;
    }
}
