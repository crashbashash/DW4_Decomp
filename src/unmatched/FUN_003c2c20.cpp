extern "C" {
void *beNDMWLoadIntf2ChrDataSel_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c2c20(void);
}
void FUN_003c2c20(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2ChrDataSel_Register);
}
