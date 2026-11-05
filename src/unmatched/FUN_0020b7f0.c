struct W { long long f0; char p8[24]; int f32; char p36[12]; int f48; char p52[12]; unsigned char b0:3; unsigned char b3:1; unsigned char b4:4; };
struct V { long long f0; long long f8; };
struct N { long long f0; long long f8; char p16[8]; int f24; char p28[42]; char m:7; char hi:1; };
int FUN_001eef70();
int FUN_001efd90();
int FUN_00207e70();
int FUN_0020b280();
int FUN_0020b650();
void FUN_001f0470(void);  /* code at 0x1f0470, passed by address (was DAT_1f0470; docs/engine/function-inventory.md) */
void FUN_001f74e0(void);  /* code at 0x1f74e0, passed by address (was FUN_001f74e0; docs/engine/function-inventory.md) */
void FUN_001f7500(void);  /* code at 0x1f7500, passed by address (was FUN_001f7500; docs/engine/function-inventory.md) */
extern struct W *DAT_00568f04[4];
extern struct V *DAT_00568f08[4];
extern int DAT_0056c0d0[4];
extern int DAT_0056c0d8[4];
extern int DAT_0056c130[4];
unsigned char FUN_0020b7f0(struct N *arg0) {
    int r;
    long long t;
    int s0;
    struct W *p;
    long long *lp;
    r = -1;
    s0 = FUN_0020b650(arg0, &r, 1, 0);
    if (r >= 0) {
        FUN_0020b280(arg0, s0, r);
    } else {
        s0 = FUN_0020b650(arg0, &r, 0, &t);
        if (r >= 0) {
            if (DAT_0056c130[0] == 1) {
                FUN_00207e70(FUN_001f7500, 0);
                t = DAT_00568f04[0]->f0;
                FUN_001eef70(1);
                FUN_0020b280(arg0, s0, r);
                FUN_001efd90(2, FUN_001f74e0, t);
            } else {
                p = DAT_00568f04[0];
                if (p->f0 == t || p->f32 == p->f48) {
                    p->b3 = 1;
                }
                FUN_001eef70(1, p);
                FUN_0020b280(arg0, s0, r);
                FUN_001efd90(2, FUN_001f0470, t);
            }
            lp = &DAT_00568f08[0]->f8;
            if (*lp < t) {
                *lp = t;
            }
        }
    }
    if (r >= 0) {
        arg0->m = 2;
        arg0->f0 = 0;
        arg0->f8 = 0;
        DAT_0056c0d8[0] = arg0->f24;
        if (DAT_0056c0d8[0] == 0) {
            DAT_0056c0d8[0] = DAT_0056c0d0[0];
        }
    }
    return (~r == 0) ^ 1;
}
