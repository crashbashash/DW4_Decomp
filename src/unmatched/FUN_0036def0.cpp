extern "C" {
void *beAction2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036def0(void);
}
void FUN_0036def0(void)
{
    igMetaObject_RunStaticInit(beAction2_Register);
}
