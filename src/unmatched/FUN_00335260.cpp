extern "C" {
void *igAdxAudio_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_00335260(void);
}
void FUN_00335260(void)
{
    igMetaObject_RunStaticInit(igAdxAudio_Register);
}
