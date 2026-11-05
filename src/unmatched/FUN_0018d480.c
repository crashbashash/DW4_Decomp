/* 0x0018d480 — FUN_0018d480. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0018d9b0(void); /* address-taken; signature not recovered */
void FUN_0018dd20(void); /* address-taken; signature not recovered */
void thunk_FUN_0018d630(void); /* address-taken; signature not recovered */
void FUN_0018da00(void);  /* code at 0x18da00, passed by address (was FUN_0018da00; docs/engine/function-inventory.md) */
int igPlane_GetMetaObject();
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
void FUN_0018d700(void);  /* code at 0x18d700, passed by address (was DAT_18d700; docs/engine/function-inventory.md) */
void FUN_0018d7b0(void);  /* code at 0x18d7b0, passed by address (was FUN_0018d7b0; docs/engine/function-inventory.md) */
void FUN_0018d820(void);  /* code at 0x18d820, passed by address (was FUN_0018d820; docs/engine/function-inventory.md) */
void FUN_0018d8b0(void);  /* code at 0x18d8b0, passed by address (was FUN_0018d8b0; docs/engine/function-inventory.md) */
void FUN_0018db20(void);  /* code at 0x18db20, passed by address (was FUN_0018db20; docs/engine/function-inventory.md) */
void FUN_0018dcb0(void);  /* code at 0x18dcb0, passed by address (was FUN_0018dcb0; docs/engine/function-inventory.md) */
void FUN_0018e040(void);  /* code at 0x18e040, passed by address (was FUN_0018e040; docs/engine/function-inventory.md) */
void FUN_0018e150(void);  /* code at 0x18e150, passed by address (was FUN_0018e150; docs/engine/function-inventory.md) */
void FUN_0018e160(void);  /* code at 0x18e160, passed by address (was FUN_0018e160; docs/engine/function-inventory.md) */
void FUN_0018e190(void);  /* code at 0x18e190, passed by address (was FUN_0018e190; docs/engine/function-inventory.md) */
extern int DAT_00560fa0[4];
extern int DAT_00560fe0[4];
extern int DAT_005610e0[4];
int FUN_0018dbc0();
int FUN_0018de10();
int FUN_0018dfc0();

void FUN_0018d480(void) {
    FUN_0018fbc0(DAT_00560fa0[0], igAABox_GetMetaObject(), FUN_0018d700);
    FUN_0018fbc0(DAT_00560fa0[0], igPlane_GetMetaObject(), FUN_0018d7b0);
    FUN_0018fbc0(DAT_00560fa0[0], DAT_00560fa0[0], FUN_0018d820);
    FUN_0018fca0(DAT_00560fa0[0], DAT_005610e0[0], (int *)FUN_0018da00);
    FUN_0018fca0(DAT_00560fa0[0], DAT_00560fe0[0], (int *)FUN_0018d9b0);
    FUN_0018fca0(DAT_00560fa0[0], DAT_00560fa0[0], FUN_0018db20);
    FUN_0018fc30(DAT_00560fa0[0], DAT_005610e0[0], (int *)FUN_0018dd20);
    FUN_0018fc30(DAT_00560fa0[0], DAT_00560fa0[0], &FUN_0018de10);
    FUN_0018fd10(DAT_00560fa0[0], FUN_0018d8b0);
    FUN_0018fd90(DAT_00560fa0[0], &FUN_0018dbc0);
    FUN_0018fd50(DAT_00560fa0[0], &FUN_0018dfc0);
    FUN_0018fe10(DAT_00560fa0[0], FUN_0018dcb0);
    FUN_0018fdd0(DAT_00560fa0[0], FUN_0018e040);
    FUN_0018fe50(DAT_00560fa0[0], thunk_FUN_0018d630);
    FUN_0018fe90(DAT_00560fa0[0], FUN_0018e150);
    FUN_0018fed0(DAT_00560fa0[0], FUN_0018e160);
    FUN_0018ff10(DAT_00560fa0[0], FUN_0018e190);
}
