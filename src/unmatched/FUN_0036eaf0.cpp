extern "C" {
void *ParticleInfo_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0036eaf0(void);
}
void FUN_0036eaf0(void)
{
    igMetaObject_RunStaticInit(ParticleInfo_Register);
}
