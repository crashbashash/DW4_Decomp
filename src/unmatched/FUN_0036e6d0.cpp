extern "C" {
void *ParticleTimer_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036e6d0(void);
}
void FUN_0036e6d0(void)
{
    igMetaObject_RunStaticInit(ParticleTimer_Register);
}
