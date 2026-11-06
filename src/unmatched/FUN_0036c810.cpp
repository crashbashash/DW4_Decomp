extern "C" {
void *beAction2InfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036c810(void);
}
void FUN_0036c810(void)
{
    igMetaObject_RunStaticInit(beAction2InfoRam_Register);
}
