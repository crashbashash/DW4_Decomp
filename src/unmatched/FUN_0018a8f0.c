/* 0x0018a8f0 — FUN_0018a8f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0018afa0(void); /* address-taken; signature not recovered */
void FUN_0018b050(void); /* address-taken; signature not recovered */
void FUN_0018b110(void); /* address-taken; signature not recovered */
void FUN_0018b170(void); /* address-taken; signature not recovered */
void FUN_0018b300(void); /* address-taken; signature not recovered */
void FUN_0018b350(void); /* address-taken; signature not recovered */
void FUN_0018b450(void); /* address-taken; signature not recovered */
void FUN_0018b540(void); /* address-taken; signature not recovered */
void FUN_0018b630(void); /* address-taken; signature not recovered */
void FUN_0018b6b0(void); /* address-taken; signature not recovered */
void FUN_0018b890(void); /* address-taken; signature not recovered */
void thunk_FUN_0018ac80(void); /* address-taken; signature not recovered */
void FUN_0018b990(void); /* address-taken; signature not recovered */
void FUN_0018b730(void);  /* code at 0x18b730, passed by address (was DAT_18b730; docs/engine/function-inventory.md) */
void FUN_0018b7d0(void);  /* code at 0x18b7d0, passed by address (was FUN_0018b7d0; docs/engine/function-inventory.md) */
void FUN_0018b940(void);  /* code at 0x18b940, passed by address (was FUN_0018b940; docs/engine/function-inventory.md) */
void FUN_0018b970(void);  /* code at 0x18b970, passed by address (was FUN_0018b970; docs/engine/function-inventory.md) */
int igSphere_GetMetaObject();
int igPlane_GetMetaObject();
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
extern int DAT_00560fa0[4];
extern int DAT_00560fe0[4];
extern int DAT_005610e0[4];
void FUN_0018a8f0(void) {
    FUN_0018fbc0(DAT_005610e0[0], DAT_005610e0[0], FUN_0018b050);
    FUN_0018fbc0(DAT_005610e0[0], igPlane_GetMetaObject(), FUN_0018b110);
    FUN_0018fbc0(DAT_005610e0[0], igSphere_GetMetaObject(), FUN_0018afa0);
    FUN_0018fca0(DAT_005610e0[0], DAT_005610e0[0], FUN_0018b350);
    FUN_0018fca0(DAT_005610e0[0], DAT_00560fe0[0], FUN_0018b300);
    FUN_0018fca0(DAT_005610e0[0], DAT_00560fa0[0], FUN_0018b450);
    FUN_0018fc30(DAT_005610e0[0], DAT_005610e0[0], FUN_0018b730);
    FUN_0018fc30(DAT_005610e0[0], DAT_00560fa0[0], FUN_0018b7d0);
    FUN_0018fd10(DAT_005610e0[0], FUN_0018b170);
    FUN_0018fd90(DAT_005610e0[0], FUN_0018b540);
    FUN_0018fd50(DAT_005610e0[0], FUN_0018b6b0);
    FUN_0018fe10(DAT_005610e0[0], FUN_0018b630);
    FUN_0018fdd0(DAT_005610e0[0], FUN_0018b890);
    FUN_0018fe50(DAT_005610e0[0], thunk_FUN_0018ac80);
    FUN_0018fe90(DAT_005610e0[0], FUN_0018b940);
    FUN_0018fed0(DAT_005610e0[0], FUN_0018b970);
    FUN_0018ff10(DAT_005610e0[0], FUN_0018b990);
}
