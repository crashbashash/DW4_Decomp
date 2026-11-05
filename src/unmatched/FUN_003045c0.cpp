/* 0x003045c0 — FUN_003045c0. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
extern "C" {
class Out { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(char *, int, int); };
int FUN_00125220(...);
int vfprintf(...);
int FUN_0012fd08(...);
extern int DAT_004854a0[4];
extern int DAT_004f95a0[4];
extern Out *DAT_005871b8[4];
extern unsigned char GPR_005549a4;
extern unsigned char GPR_005549a8;
void FUN_003045c0(int arg0, int arg1);
void FUN_003045c0(int arg0, int arg1) {
    char buf[4096];
    int var_v0;

    if ((DAT_005871b8[0] != 0) && (GPR_005549a4 != 0)) {
        var_v0 = FUN_0012fd08(buf, 0x1000, arg0, arg1);
        if ((var_v0 < 0) || (var_v0 >= 0x1000)) {
            buf[4095] = 0;
            var_v0 = 0x1000;
        }
        DAT_005871b8[0]->vX(buf, var_v0, 1);
        if (GPR_005549a8 != 0) {
            FUN_00125220(*(int *)((char *)(DAT_004854a0[0]) + 12), &DAT_004f95a0[0], buf);
        }
    } else if (GPR_005549a8 != 0) {
        vfprintf(*(int *)((char *)(DAT_004854a0[0]) + 12), arg0, arg1);
    }
}
}
