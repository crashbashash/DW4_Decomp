extern "C" {
void *beNDMWLoadIntf2MakeChr_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c41e0(void);
}
void FUN_003c41e0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2MakeChr_Register);
}
