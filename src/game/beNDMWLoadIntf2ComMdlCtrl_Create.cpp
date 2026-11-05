/* 0x003c6ea0 — beNDMWLoadIntf2ComMdlCtrl_Create. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_003c7090();
void beNDMWLoadIntf2ComMdlCtrl_Create(int arg0);
}

void beNDMWLoadIntf2ComMdlCtrl_Create(int arg0) {
    FUN_003c7090();
    igMetaObject_CreateInstance(*(int *)0x58BE38, arg0);
}
