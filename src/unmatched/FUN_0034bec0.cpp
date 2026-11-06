extern "C" {
void *beParticleCtrl2InfoRam_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034bec0(void);
}
void FUN_0034bec0(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2InfoRam_Register);
}
