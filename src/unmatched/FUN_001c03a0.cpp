#include "dw4/reflected.h"
struct Obj { char p0[16]; float a[4]; char p1[16]; long long f48; char p2[4]; int f60; float f64; };
struct Cls { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int v148(int); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void v716(float *); virtual void d178(); virtual void d179(); virtual float v728(); };
struct A1 { char p0[32]; int f32; char p1[16]; int f52; char p2[4]; Cls *f60; char p3[4]; int f68; };
struct A0 { char p0[28]; igDataList *f28; unsigned char f32; char p1[3]; float f36; char p2[24]; unsigned char f64; };
extern "C" {
int FUN_001931b0(...);
int FUN_001b12f0(int, void *);
int FUN_001b13d0(int, void *);
int FUN_001c0250(A0 *);
int FUN_001c0390(A0 *, int);
int FUN_001d9bb0(int, int);
int FUN_001db720(int, int, int);
int FUN_001dc500(int, int, int);
int FUN_001dc610(int);
int FUN_001e07a0(A1 *, A0 *);
long long FUN_00230298(float);
extern Obj *DAT_00562660[4];
extern void *DAT_00562668[4];
extern void *DAT_00562670[4];
extern void *DAT_00562680[4];
extern void *DAT_00562688[4];
extern void *DAT_00562690[4];
extern void *DAT_00562698[4];
extern void *DAT_005626a0[4];
extern void *DAT_005626a8[4];
extern void *DAT_005626b0[4];
extern void *DAT_005626b8[4];
extern void *DAT_005626c0[4];
extern void *DAT_005626c8[4];
extern void *DAT_005626d0[4];
extern void *DAT_005626d8[4];
extern int DAT_00562678[4];
extern unsigned char GPR_00554984;
extern unsigned char GPR_00554b8c;
void FUN_001c03a0(A0 *arg0, A1 *arg1);
}
void FUN_001c03a0(A0 *arg0, A1 *arg1) {
    float sp70[4];
    float f20;
    Cls *s1;
    int s0;
    Obj *s4;
    int v1;
    if (arg0->f28 != 0) v1 = arg0->f28->_count; else v1 = 0;
    if (v1 != 0) {
        if (arg0->f32 != 0 && !(arg0->f36 <= 1.0f)) {
            s1 = arg1->f60;
            if (GPR_00554984 != 0) {
                if ((FUN_001c0390(arg0, arg1->f32) & 0xFF) == 1) GPR_00554b8c = 1; else GPR_00554b8c = 0;
                GPR_00554984 = 0;
            }
            if (GPR_00554b8c != 0) {
                s0 = arg1->f52;
                if (arg0->f64 != 0) {
                    FUN_001c0250(arg0);
                    arg0->f64 = 0;
                }
                s1->v716(sp70);
                f20 = s1->v728();
                s4 = DAT_00562660[0];
                s4->a[0] = sp70[0];
                s4->a[1] = sp70[1];
                s4->a[2] = sp70[2];
                s4->a[3] = sp70[3];
                s4->f60 = FUN_001931b0(sp70, 1);
                s4 = DAT_00562660[0];
                s4->f48 = FUN_00230298(f20);
                s4->f64 = f20;
                FUN_001dc500(arg1->f68, 0, 0);
                FUN_001b12f0(s0, DAT_00562668[0]);
                FUN_001b12f0(s0, DAT_00562670[0]);
                FUN_001d9bb0(arg1->f68, s0);
                FUN_001b12f0(s0, DAT_00562660[0]);
                FUN_001b12f0(s0, DAT_005626b8[0]);
                FUN_001e07a0(arg1, arg0);
                FUN_001b13d0(s0, DAT_005626b8[0]);
                FUN_001b13d0(s0, DAT_00562660[0]);
                FUN_001b13d0(s0, DAT_00562670[0]);
                FUN_001b13d0(s0, DAT_00562668[0]);
                FUN_001d9bb0(arg1->f68, s0);
                FUN_001b12f0(s0, DAT_005626c8[0]);
                FUN_001b12f0(s0, DAT_005626a8[0]);
                FUN_001b12f0(s0, DAT_005626d0[0]);
                FUN_001d9bb0(arg1->f68, s0);
                FUN_001b12f0(s0, DAT_00562680[0]);
                FUN_001b12f0(s0, DAT_00562688[0]);
                if (s1->v148(16) != 0) {
                    FUN_001b12f0(s0, DAT_005626a0[0]);
                } else {
                    FUN_001b12f0(s0, DAT_00562698[0]);
                }
                FUN_001b12f0(s0, DAT_00562690[0]);
                FUN_001b12f0(s0, DAT_005626c0[0]);
                FUN_001b12f0(s0, DAT_005626d8[0]);
                FUN_001db720(arg1->f68, DAT_00562678[0], s0);
                FUN_001b13d0(s0, DAT_005626d8[0]);
                FUN_001b13d0(s0, DAT_005626c0[0]);
                FUN_001b13d0(s0, DAT_00562690[0]);
                if (s1->v148(16) != 0) {
                    FUN_001b13d0(s0, DAT_005626a0[0]);
                } else {
                    FUN_001b13d0(s0, DAT_00562698[0]);
                }
                FUN_001b13d0(s0, DAT_00562688[0]);
                FUN_001b13d0(s0, DAT_00562680[0]);
                FUN_001b13d0(s0, DAT_005626d0[0]);
                FUN_001b13d0(s0, DAT_005626a8[0]);
                FUN_001b13d0(s0, DAT_005626c8[0]);
                FUN_001d9bb0(arg1->f68, s0);
                FUN_001b12f0(s0, DAT_005626b0[0]);
                FUN_001e07a0(arg1, arg0);
                FUN_001b13d0(s0, DAT_005626b0[0]);
                FUN_001d9bb0(arg1->f68, s0);
                FUN_001dc610(arg1->f68);
                return;
            }
        }
        FUN_001dc500(arg1->f68, 0, 0);
        FUN_001e07a0(arg1, arg0);
        FUN_001dc610(arg1->f68);
    }
}
