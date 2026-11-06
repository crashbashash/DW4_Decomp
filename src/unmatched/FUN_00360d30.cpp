extern "C" {
void *beGenerater_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00360d30(void);
}
void FUN_00360d30(void)
{
    igMetaObject_RunStaticInit(beGenerater_Register);
}
