extern "C" {
void *beNDMWLoadIntf2ComMdlCtrl_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c7090(void);
}
void FUN_003c7090(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2ComMdlCtrl_Register);
}
