extern "C" {
void *beSoundInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00343e00(void);
}
void FUN_00343e00(void)
{
    igMetaObject_RunStaticInit(beSoundInfo_Register);
}
