extern "C" {
void *beCriFxInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00366e00(void);
}
void FUN_00366e00(void)
{
    igMetaObject_RunStaticInit(beCriFxInfo_Register);
}
