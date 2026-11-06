extern "C" {
void *beNDMWLoadIntf2MesWin_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c6c70(void);
}
void FUN_003c6c70(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2MesWin_Register);
}
