extern "C" {
void *beMessenger_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00357d10(void);
}
void FUN_00357d10(void)
{
    igMetaObject_RunStaticInit(beMessenger_Register);
}
