extern "C" {
void *beHitLandModelInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035d5a0(void);
}
void FUN_0035d5a0(void)
{
    igMetaObject_RunStaticInit(beHitLandModelInfo_Register);
}
