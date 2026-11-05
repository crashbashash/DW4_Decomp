/* 0x003c76c0 — beNDMWLoadIntf2TextOrder_Create. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c7830();
void beNDMWLoadIntf2TextOrder_Create(int arg0);
}

void beNDMWLoadIntf2TextOrder_Create(int arg0) {
    FUN_003c7830();
    igMetaObject_CreateInstance(*(int *)0x58BE90, arg0);
}
