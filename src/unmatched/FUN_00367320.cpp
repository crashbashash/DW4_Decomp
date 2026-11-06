extern "C" {
void *beCriAudio_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00367320(void);
}
void FUN_00367320(void)
{
    igMetaObject_RunStaticInit(beCriAudio_Register);
}
