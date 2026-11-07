struct Q { char pad0[8]; int *f8; char pad1[8]; int f20; char pad2[40]; long long f64; };
struct R { char pad0[708]; int f708; char pad1[228]; struct Q *f940; int f944; int *f948; };
extern int FUN_0016cc60();
extern int FUN_0016cd10();
extern int FUN_0016d910();
extern int FUN_0016db20();
extern int FUN_0016e140();
extern int FUN_00177010();
extern int FUN_0017f080();
extern long long FUN_001f0560();
extern int FUN_001f10f0();
extern int FUN_001f2730();
extern int FUN_001f1850();
extern int FUN_001f1fe0();
extern int FUN_001f23a0();
extern int FUN_001f2d90();
extern int FUN_001f3550();
void Gap__Gfx__igPsx2VisualContext__vfunc_74(struct R *arg0, int arg1, int arg2, int arg3, int arg4) {
    int sp8C;
    int sp88;
    int *p;
    int s6, i, *s1, *s0;
    int *rec;
    int *tbl;
    struct Q *q;
    int t;
    if (arg0->f940 != 0) {
        sp8C = 0;
        sp88 = 0;
        s6 = FUN_00177010(arg0, &sp8C, &sp88, -1, -1);
        FUN_0016cc60(arg0);
        p = (int *)(arg0->f948[2] + arg4 * 4);
        switch (arg1) {
        case 0:
            for (i = 0; i < arg2; i++) {
                FUN_0016d910(arg0, *p, arg3, sp8C, sp88, FUN_001f1850, 0);
                arg3 += *p;
                p++;
            }
            break;
        case 2:
            for (i = 0; i < arg2; i++) {
                FUN_0016d910(arg0, *p, arg3, sp8C, sp88, FUN_001f23a0, FUN_001f3550);
                arg3 += *p;
                p++;
            }
            break;
        case 1:
            i = 0;
            if (arg0->f944 != 0) {
                for (; i < arg2; i++) {
                    FUN_0016d910(arg0, *p, arg3, sp8C, sp88, FUN_001f1fe0, FUN_001f2d90);
                    arg3 += *p;
                    p++;
                }
            } else {
                tbl = arg0->f940->f8;
                t = arg0->f708 + 11; rec = (int *)tbl[t];
                s1 = 0;
                if (rec != 0) {
                    s1 = (int *)((char *)rec + arg3 * 8);
                }
                s0 = 0;
                if (tbl[2] != 0) {
                    s0 = (int *)(tbl[2] + arg3 * 4);
                }
                FUN_0016db20(arg0, arg3);
                t = arg3 * 12;
                FUN_001f10f0(sp8C + t, sp88 + t, s0, s1);
                FUN_001f2730(arg2, p);
            }
            break;
        }
        FUN_0016cd10(arg0);
        if (s6 == 1) {
            q = arg0->f940;
            FUN_0016e140(q, (int)FUN_001f0560());
        }
        q = arg0->f940;
        if (q->f20 & 4) {
            q->f64 = FUN_001f0560();
        }
    } else {
        FUN_0017f080(arg0, arg1 + 0x2000);
    }
}
