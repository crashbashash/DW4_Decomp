extern "C" {
void *beBaseInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036ad20(void);
}
void FUN_0036ad20(void)
{
    igMetaObject_RunStaticInit(beBaseInfo_Register);
}
