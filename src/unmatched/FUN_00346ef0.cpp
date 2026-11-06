extern "C" {
void *beSaveUtil_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00346ef0(void);
}
void FUN_00346ef0(void)
{
    igMetaObject_RunStaticInit(beSaveUtil_Register);
}
