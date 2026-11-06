extern "C" {
void *beSoundData_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_003440d0(void);
}
void FUN_003440d0(void)
{
    igMetaObject_RunStaticInit(beSoundData_Register);
}
