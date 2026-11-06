extern "C" {
void *beParticleCtrl2Info_Register(void);
void igMetaObject_RunStaticInit(void *(*)(void));
void FUN_0034c460(void);
}
void FUN_0034c460(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2Info_Register);
}
