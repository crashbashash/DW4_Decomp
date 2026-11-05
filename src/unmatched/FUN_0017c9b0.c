int FUN_001e74b0(int);
int FUN_001e7500(int);
int FUN_00208170(int);
struct E { int w[112]; };
struct P { char pad[644]; int a[16]; int b[16]; };
extern int DAT_00560a7c[8];
extern int DAT_00560a9c[8];
extern int DAT_00569330[4];
extern struct E DAT_00569340[];
extern struct E *DAT_0056ad80[4];
void FUN_0017c9b0(struct P *p, int n, int x, int y) {
    int i;
    n = n < 15 ? n : 15;
    if (n < 8) {
        if (p->a[n] == x) {
            DAT_00560a7c[n] += 1;
        }
        if (p->b[n] == y) {
            DAT_00560a9c[n] += 1;
        }
    }
    p->a[n] = x;
    p->b[n] = y;
    if (n > 1) {
        i = n - 1;
    } else {
        i = 0;
    }
    DAT_00569330[0] = n;
    DAT_0056ad80[0] = &DAT_00569340[i];
    switch (x) {
    case 0:
        FUN_001e7500(10);
        break;
    case 2:
        FUN_001e74b0(10);
        FUN_00208170(1);
        break;
    case 1:
        FUN_001e74b0(10);
        FUN_00208170(0);
        break;
    case 3:
        FUN_001e74b0(10);
        FUN_00208170(3);
        break;
    case 5:
        FUN_001e74b0(10);
        FUN_00208170(2);
        break;
    }
    DAT_00569330[0] = 0;
    DAT_0056ad80[0] = &DAT_00569340[0];
}
