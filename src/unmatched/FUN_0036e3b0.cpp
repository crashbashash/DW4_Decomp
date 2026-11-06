extern "C" {
void *ParticleArray_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036e3b0(void);
}
void FUN_0036e3b0(void)
{
    igMetaObject_RunStaticInit(ParticleArray_Register);
}
