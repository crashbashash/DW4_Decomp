/* 0x0018c660 — FUN_0018c660. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0018cc10(void); /* address-taken; signature not recovered */
void FUN_0018d110(void); /* address-taken; signature not recovered */
void FUN_0018d160(void); /* address-taken; signature not recovered */
void thunk_FUN_0018c820(void); /* address-taken; signature not recovered */
void FUN_0018cf20(void);  /* code at 0x18cf20, passed by address (was FUN_0018cf20; docs/engine/function-inventory.md) */
int igSphere_GetMetaObject();
int igAABox_GetMetaObject();
int FUN_0018fbc0();
int FUN_0018fc30();
int FUN_0018fca0();
int FUN_0018fd10();
int FUN_0018fd50();
int FUN_0018fd90();
int FUN_0018fdd0();
int FUN_0018fe10();
int FUN_0018fe50();
int FUN_0018fe90();
int FUN_0018fed0();
int FUN_0018ff10();
void FUN_0018c990(void);  /* code at 0x18c990, passed by address (was DAT_18c990; docs/engine/function-inventory.md) */
void FUN_0018ca00(void);  /* code at 0x18ca00, passed by address (was FUN_0018ca00; docs/engine/function-inventory.md) */
void FUN_0018ca80(void);  /* code at 0x18ca80, passed by address (was FUN_0018ca80; docs/engine/function-inventory.md) */
void FUN_0018d100(void);  /* code at 0x18d100, passed by address (was FUN_0018d100; docs/engine/function-inventory.md) */
void FUN_0018d260(void);  /* code at 0x18d260, passed by address (was FUN_0018d260; docs/engine/function-inventory.md) */
void FUN_0018d270(void);  /* code at 0x18d270, passed by address (was FUN_0018d270; docs/engine/function-inventory.md) */
void FUN_0018d280(void);  /* code at 0x18d280, passed by address (was FUN_0018d280; docs/engine/function-inventory.md) */
extern int DAT_00560fa0[4];
extern int DAT_00560fe0[4];
extern int DAT_005610e0[4];
int FUN_0018c920();
int FUN_0018cb10();
int FUN_0018cfb0();
int FUN_0018d060();
int FUN_0018d0b0();
int FUN_0018d1d0();

void FUN_0018c660(void) {
    FUN_0018fbc0(DAT_00560fe0[0], igAABox_GetMetaObject(), &FUN_0018c920);
    FUN_0018fbc0(DAT_00560fe0[0], DAT_00560fe0[0], FUN_0018ca00);
    FUN_0018fbc0(DAT_00560fe0[0], igSphere_GetMetaObject(), FUN_0018c990);
    FUN_0018fca0(DAT_00560fe0[0], DAT_005610e0[0], (int *)FUN_0018cc10);
    FUN_0018fca0(DAT_00560fe0[0], DAT_00560fe0[0], &FUN_0018cb10);
    FUN_0018fca0(DAT_00560fe0[0], DAT_00560fa0[0], (int *)FUN_0018cf20);
    FUN_0018fc30(DAT_00560fe0[0], DAT_00560fe0[0], FUN_0018d100);
    FUN_0018fc30(DAT_00560fe0[0], DAT_005610e0[0], (int *)FUN_0018d110);
    FUN_0018fc30(DAT_00560fe0[0], DAT_00560fa0[0], (int *)FUN_0018d160);
    FUN_0018fd10(DAT_00560fe0[0], FUN_0018ca80);
    FUN_0018fd90(DAT_00560fe0[0], &FUN_0018cfb0);
    FUN_0018fd50(DAT_00560fe0[0], &FUN_0018d1d0);
    FUN_0018fe10(DAT_00560fe0[0], &FUN_0018d060);
    FUN_0018fdd0(DAT_00560fe0[0], &FUN_0018d0b0);
    FUN_0018fe50(DAT_00560fe0[0], thunk_FUN_0018c820);
    FUN_0018fe90(DAT_00560fe0[0], FUN_0018d260);
    FUN_0018fed0(DAT_00560fe0[0], FUN_0018d270);
    FUN_0018ff10(DAT_00560fe0[0], FUN_0018d280);
}
