extern "C" {
void *beNDMWLoadCtrl2CommonIntf_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c4f00(void);
}
void FUN_003c4f00(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2CommonIntf_Register);
}
