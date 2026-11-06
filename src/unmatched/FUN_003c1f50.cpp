extern "C" {
void *beNDMWLogoInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003c1f50(void);
}
void FUN_003c1f50(void)
{
    igMetaObject_RunStaticInit(beNDMWLogoInfo_Register);
}
