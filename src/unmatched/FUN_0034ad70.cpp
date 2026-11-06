extern "C" {
void *beSaveMemoryObj_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034ad70(void);
}
void FUN_0034ad70(void)
{
    igMetaObject_RunStaticInit(beSaveMemoryObj_Register);
}
