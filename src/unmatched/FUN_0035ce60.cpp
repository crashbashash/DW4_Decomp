extern "C" {
void *beLOA_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0035ce60(void);
}
void FUN_0035ce60(void)
{
    igMetaObject_RunStaticInit(beLOA_Register);
}
