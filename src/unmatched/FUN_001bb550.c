/* 0x001bb550 — FUN_001bb550. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001bbae0(void); /* address-taken; signature not recovered */
void FUN_001bc0e0(void); /* address-taken; signature not recovered */
void FUN_001bc1e0(void); /* address-taken; signature not recovered */
void FUN_001bcdf0(void); /* address-taken; signature not recovered */
void FUN_001bce40(void); /* address-taken; signature not recovered */
void FUN_001bcf70(void); /* address-taken; signature not recovered */
void FUN_001bd0e0(void); /* address-taken; signature not recovered */
void FUN_001bcd80(void);  /* code at 0x1bcd80, passed by address (was DAT_1bcd80; docs/engine/function-inventory.md) */
void FUN_001bcd90(void);  /* code at 0x1bcd90, passed by address (was FUN_001bcd90; docs/engine/function-inventory.md) */
void FUN_001bcda0(void);  /* code at 0x1bcda0, passed by address (was FUN_001bcda0; docs/engine/function-inventory.md) */
void FUN_001bcdb0(void);  /* code at 0x1bcdb0, passed by address (was FUN_001bcdb0; docs/engine/function-inventory.md) */
void FUN_001bcdc0(void);  /* code at 0x1bcdc0, passed by address (was FUN_001bcdc0; docs/engine/function-inventory.md) */
void FUN_001bcdd0(void);  /* code at 0x1bcdd0, passed by address (was FUN_001bcdd0; docs/engine/function-inventory.md) */
void FUN_001bcde0(void);  /* code at 0x1bcde0, passed by address (was FUN_001bcde0; docs/engine/function-inventory.md) */
void FUN_001bd150(void);  /* code at 0x1bd150, passed by address (was FUN_001bd150; docs/engine/function-inventory.md) */
void FUN_001bd160(void);  /* code at 0x1bd160, passed by address (was FUN_001bd160; docs/engine/function-inventory.md) */
int FUN_001b68c0();
int FUN_001e06c0();
int FUN_002fe290();
extern int DAT_005612b0[4];
extern int DAT_00561578[4];
extern int DAT_005615d8[4];
extern int DAT_00561620[4];
extern int DAT_005617a8[4];
extern int DAT_00561860[4];
extern int DAT_00561888[4];
extern int DAT_005618f8[4];
extern int DAT_00561a38[4];
extern int DAT_00561a98[4];
extern int DAT_00561bd8[4];
extern int DAT_00561ca0[4];
extern int DAT_00561e98[4];
extern int DAT_00561ee8[4];
extern int DAT_00561f38[4];
extern int DAT_00562488[4];
void FUN_001bb550(int arg0, int arg1) {
    FUN_001b68c0();
    if (FUN_002fe290(arg1, DAT_00561620[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bcd80);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561bd8[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bcd90);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561a98[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bcdf0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561860[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bcda0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561e98[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bcdb0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561ee8[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bcdc0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_005617a8[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bcdd0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561578[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bcde0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561a38[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bc1e0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_005618f8[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bc0e0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_005612b0[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bbae0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561ca0[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bd0e0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561888[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bce40);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561f38[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bcf70);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00562488[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bd150);
        return;
    }
    if (FUN_002fe290(arg1, DAT_005615d8[0]) != 0) {
        FUN_001e06c0(arg0, arg1, FUN_001bd160);
    }
}
