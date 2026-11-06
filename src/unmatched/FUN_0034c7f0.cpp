extern "C" {
void *beParticleCtrl2_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034c7f0(void);
}
void FUN_0034c7f0(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2_Register);
}
