extern "C" {
void *beAction2Info_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036cc80(void);
}
void FUN_0036cc80(void)
{
    igMetaObject_RunStaticInit(beAction2Info_Register);
}
