extern "C" {
void *beBaseInfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036a360(void);
}
void FUN_0036a360(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRam_Register);
}
