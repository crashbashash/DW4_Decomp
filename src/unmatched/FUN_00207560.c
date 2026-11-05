int FUN_00113f20();
int FUN_00113f78();
int FUN_001ebc00();
int FUN_001efd90();
int FUN_001f76c0();
int FUN_001f8190();
int FUN_00207470();
int FUN_0020d270();
int FUN_0020d9e0();
int WaitSema();
void FUN_00207400(void);  /* code at 0x207400, passed by address (was DAT_207400; docs/engine/function-inventory.md) */
extern short DAT_00568e0c[16];
extern short DAT_00568e0e[16];
extern short DAT_00568e10[16];
extern short DAT_00568e12[16];
extern short DAT_00568e14[16];
extern short DAT_00568e16[16];
extern short DAT_00568e1c[16];
extern int DAT_00568ed0[16];
extern int DAT_0056bf60[16];
extern volatile long long DAT_0056bf70[16];
extern long long DAT_0056bf78[16];
extern volatile int DAT_0056bf90[16];
extern int DAT_0056bfc8[16];
extern int DAT_0056bfd0[16];
extern int DAT_0056c160[16];
extern volatile int DAT_0056d670[16];
extern volatile int DAT_0056d678[16];
typedef struct { unsigned short a : 9; unsigned short b : 7; } BF;
extern BF DAT_0056ada8[16];
extern BF DAT_0056adb0[16];
typedef struct { char p0[176]; unsigned char m : 2; unsigned char r : 6; char p1[175]; union { BF bf; int w; } u352; int f356; int f360; int f364; } Obj;
extern Obj *DAT_0056ad80[16];
extern int FUN_00207420();
void FUN_00207560(void) {
    /*D*/
    long long sp28;
    long long sp20;
    int s0;
    int a1;
    int v;
    Obj *ob;
    /*E*/
    s0 = FUN_001ebc00();
    DAT_0056bf78[0] += 1;
    if (s0 != 0) {
        FUN_00207470();
    }
    if (DAT_0056bfd0[0] != 0) {
        FUN_00113f20();
        DAT_0056d670[0] |= 4;
        FUN_00113f78();
        while (DAT_0056bf78[0] > DAT_0056bf70[0] + DAT_0056bfc8[0]) {
            FUN_0020d270(&sp28);
            DAT_00568ed0[0] = DAT_0056bf90[0];
            WaitSema(DAT_0056bf90[0]);
            DAT_00568ed0[0] = -1;
            FUN_0020d270(&sp20);
            DAT_0056c160[0] += (long long)((sp20 - sp28) << 0x20) >> 0x20;
        }
        DAT_0056bfc8[0] = 2;
        FUN_00113f20();
        DAT_0056d670[0] &= ~4;
        DAT_0056d678[0] &= ~4;
        FUN_00113f78();
        FUN_001efd90(1, FUN_00207400, DAT_0056bf78[0]);
    } else {
        DAT_0056bf60[0] = 0;
        if (s0 == 0) {
            DAT_00568e14[0] ^= 1;
            a1 = DAT_00568e14[0];
            DAT_0056adb0[0].a = (a1 != 0) ? DAT_00568e1c[0] : 0;
            if (a1 != 0) { v = DAT_00568e1c[0]; } else { v = 0; }
            DAT_0056ada8[0].a = v;
            FUN_001f8190(9);
            FUN_001f8190(7);
        }
    }
    if (DAT_00568e16[0] == 0) {
        DAT_00568e12[0] = ((DAT_00568e12[0] != 0) ^ 1) & 0xFF;
        if (DAT_00568e0c[0] != 0 && (DAT_00568e10[0] == 1 || DAT_00568e0e[0] == 0)) {
            FUN_001efd90(1, &FUN_00207420, DAT_00568e12[0]);
        }
        if (DAT_00568e0e[0] != 0 && DAT_00568e10[0] == 1) {
            if (DAT_00568e12[0] == 0) {
                DAT_0056ad80[0]->m = 3;
            } else {
                DAT_0056ad80[0]->m = 2;
            }
            FUN_001f76c0(0x16);
        }
        if (s0 == 0) {
            if (DAT_00568e0e[0] != 0 && DAT_00568e10[0] == 1) {
                DAT_0056ad80[0]->u352.bf.a = 0;
            } else {
                DAT_0056ad80[0]->u352.bf.a = (DAT_00568e12[0] != 0) ? DAT_00568e1c[0] : 0;
            }
        }
        ob = DAT_0056ad80[0];
        ob->f360 = ob->u352.w;
        ob->f364 = ob->f356;
        FUN_001f76c0(0x2C);
        FUN_001f76c0(0x2D);
        if (DAT_00568e0e[0] == 0 && DAT_00568e10[0] == 2) {
            FUN_0020d9e0();
        }
    }
}
