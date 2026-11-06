extern "C" {
void *beLoadIntf2ComMdlData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c75a0(void);
}
void FUN_003c75a0(void)
{
    igMetaObject_RunStaticInit(beLoadIntf2ComMdlData_Register);
}
